#include "PhysicsSystem.h"
#include <cassert>
#include <PhysicsComponents.h>
#include <Resources.h>
#include <RenderingComponents.h>
#include <ckMath.h>
#include <Physics/MeshColliderData.h>
namespace cookie
{
	namespace physics
	{
		namespace px = physx;
		using namespace math;

		px::PxFilterFlags filterShader(
			px::PxFilterObjectAttributes attributes0,
			px::PxFilterData filterData0,
			px::PxFilterObjectAttributes attributes1,
			px::PxFilterData filterData1,
			px::PxPairFlags& pairFlags,
			const void* constantBlock,
			px::PxU32 constantBlockSize)
		{
			pairFlags |= px::PxPairFlag::eSOLVE_CONTACT;
			pairFlags |= px::PxPairFlag::eDETECT_DISCRETE_CONTACT;
			pairFlags |= px::PxPairFlag::eDETECT_CCD_CONTACT;
			return px::PxFilterFlags();
		}

		void PhysicsSystem::Start(World* world)
		{
			foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocatorCallBack, errorCallBack);
			if (!foundation)
			{
				std::cout << "ERROR::PHYSX: Couldn't create foundation.\n";
				return;
			}
			constexpr bool recordMemoryAllocations { true };
			auto scale = px::PxTolerancesScale();
			scale.length = 1;

			physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, scale, recordMemoryAllocations);
			if (!physics)
			{
				std::cout << "ERROR::PHYSX: Couldn't create physics.\n";
				return;
			}

			dispatcher = px::PxDefaultCpuDispatcherCreate(1);

			auto desc = px::PxSceneDesc(scale);
			desc.filterShader = filterShader;
			desc.cpuDispatcher = dispatcher;
			desc.broadPhaseType = px::PxBroadPhaseType::eABP;
			desc.flags |= px::PxSceneFlag::eENABLE_CCD;
			desc.gravity = Vector3(0.0f, -9.806f, 0.0f);
			scene = physics->createScene(desc);
			if (!scene)
			{
				std::cout << "ERROR::PHYSX: Couldn't create physics scene.\n";
				return;
			}

			pvd = px::PxCreatePvd(*foundation);

			cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, px::PxCookingParams(scale));
			if (!cooking)
			{
				std::cout << "ERROR::PHYSX: Couldn't create cooking.\n";
				return;
			}
			if (!PxInitExtensions(*physics, pvd))
			{
				std::cout << "ERROR::PHYSX: Couldn't init extensions.\n";
				return;
			}

		}
		void PhysicsSystem::FixedUpdate(World* world)
		{
			auto* time { world->GetResource<Time>() };
			auto* query { world->QueryEntities<TransformData, RigidbodyData>() };
			query->EntityForeach([&](Entity entity, TransformData& transform, RigidbodyData& rb)
			{
				auto boxCollider = world->TryGetComponent<BoxColliderData>(entity);
				auto meshCollider = world->TryGetComponents<MeshColliderData, ModelRendererData, TransformData>(entity);
				if (!rb.initialized)
				{
					px::PxRigidActor* rbActor { nullptr };
					auto pos = transform.position;
					const auto pxTrans { px::PxTransform(pos, transform.rotation) };
					if (rb.mode == RigidBodyMode::Dynamic)
					{
						rbActor = physics->createRigidDynamic(pxTrans);
						scast<px::PxRigidDynamic*>(rbActor)->setRigidBodyFlag(px::PxRigidBodyFlag::eENABLE_CCD, true);
					}
					else
						rbActor = physics->createRigidStatic(pxTrans);

					if (!rbActor) std::cout << "SSHIT RB DYNAMIC IS NULL\n";

					if (boxCollider.has_value())
					{
						px::PxShape* shape = px::PxRigidActorExt::createExclusiveShape(
							*rbActor,
							px::PxBoxGeometry(boxCollider.value()->extents.ScaledBy(transform.scale) / 2.0f),
							*physics->createMaterial(rb.physicsMaterial.staticFriction,
													 rb.physicsMaterial.dynamicFriction, rb.physicsMaterial.restitution),
							px::PxShapeFlag::eSIMULATION_SHAPE
						);
						shape->setLocalPose(px::PxTransform(boxCollider.value()->offset.ScaledBy(transform.scale), Quaternion::Identity()));
						rb.pxShape = shape;
					}
					else if (meshCollider.has_value())
					{
						const auto& collider = *std::get<0>(meshCollider.value());
						const auto& mesh = *std::get<1>(meshCollider.value());
						const auto& transform = *std::get<2>(meshCollider.value());
						u32 vertCount { 0 };
						u32 indexCount { 0 };
						for (u32 i = 0; i < mesh.model->meshes.size(); i++)
						{
							vertCount += mesh.model->meshes[i].vertices.size();
							indexCount += mesh.model->meshes[i].indices.size();
						}
						std::vector<px::PxVec3> verts {};
						verts.reserve(vertCount);
						std::vector<u32> indices {};
						indices.reserve(indexCount);
						u32 indexOffset { 0 };
						for (auto& modelMesh : mesh.model->meshes)
						{
							for (auto& vertex : modelMesh.vertices)
							{
								verts.push_back(scast<Vector3>(vertex.position));
							}
							for (auto& index : modelMesh.indices)
							{
								indices.push_back(index + indexOffset);
							}
							indexOffset += modelMesh.indices.size();
						}
						px::PxTriangleMeshDesc meshDesc;
						meshDesc.points.count = vertCount;
						meshDesc.points.stride = sizeof(px::PxVec3);
						meshDesc.points.data = &verts[0];

						meshDesc.triangles.count = indices.size() / 3;
						meshDesc.triangles.stride = 3 * sizeof(px::PxU32);
						meshDesc.triangles.data = &indices[0];

						px::PxDefaultMemoryOutputStream writeBuffer;
						px::PxTriangleMeshCookingResult::Enum result;
						bool status = cooking->cookTriangleMesh(meshDesc, writeBuffer, &result);
						if (!status)
						{
							std::cout << "ERROR::PHYSX: Couldn't create triangle mesh.\n";
							return;
						}

						px::PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
						auto triangleMesh = physics->createTriangleMesh(readBuffer);
						px::PxMeshScale scale { transform.scale, transform.rotation };
						auto geometry = px::PxTriangleMeshGeometry(triangleMesh, scale);
						auto shape =
							px::PxRigidActorExt::createExclusiveShape(
								*rbActor,
								geometry,
								*physics->createMaterial(rb.physicsMaterial.staticFriction, rb.physicsMaterial.dynamicFriction, rb.physicsMaterial.restitution), px::PxShapeFlag::eSIMULATION_SHAPE
							);
						shape->setLocalPose(px::PxTransform(collider.offset.ScaledBy(transform.scale), Quaternion::Identity()));
						rb.pxShape = shape;
					}

					rb.pxRbActor = rbActor;
					scene->addActor(*rbActor);
					rb.initialized = true;
				}

				auto pos = rb.pxRbActor->getGlobalPose().p;
				rb.pxRbActor->setGlobalPose(px::PxTransform(pos, transform.rotation));
				auto rot = rb.pxRbActor->getGlobalPose().q;
				transform.position = pos;
				transform.rotation = rot;

				if (rb.mode == RigidBodyMode::Dynamic)
				{
					auto rbd = scast<px::PxRigidDynamic*>(rb.pxRbActor);
					rbd->setLinearVelocity(rb.linearVelocity);
					rbd->setMass(rb.mass);
				}
			});
			scene->simulate(time->fixedDeltaTime);
			scene->fetchResults(true);
		}
		void PhysicsSystem::Destroy(World* world)
		{
			scene->release();
			physics->release();
			cooking->release();
			pvd->release();
			foundation->release();
		}


	}
}