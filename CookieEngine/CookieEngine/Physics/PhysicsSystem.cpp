#include "PhysicsSystem.h"
#include <cassert>
#include <PhysicsComponents.h>
#include <Resources.h>
#include <RenderingComponents.h>
#include <ckMath.h>
#include <Physics/MeshColliderData.h>
#include <Physics/PhysicsHandler.h>
namespace cookie
{
	namespace physics
	{
		using namespace physx;
		using namespace math;
		void PhysicsSystem::Start(World* world)
		{
			PhysicsHandler::SetupPhysics();
		}
		void PhysicsSystem::FixedUpdate(World* world)
		{
			auto* time { world->GetResource<Time>() };
			auto* queryStatic { world->QueryEntities<TransformData, RigidBodyStaticData>() };
			queryStatic->EntityForeach([&](Entity entity, TransformData& transform, RigidBodyStaticData& rb)
			{
				auto boxCollider = world->TryGetComponent<BoxColliderData>(entity);
				auto meshCollider = world->TryGetComponents<MeshColliderData, ModelRendererData, TransformData>(entity);
				if (!rb.initialized)
				{
					if (boxCollider.has_value())
					{
						PxShape* shape = PxRigidActorExt::createExclusiveShape(
							*rb.pxRb,
							PxBoxGeometry(boxCollider.value()->extents.ScaledBy(transform.scale) / 2.0f),
							*PhysicsHandler::ctx.physics->createMaterial(boxCollider.value()->material.staticFriction,
													 boxCollider.value()->material.dynamicFriction, boxCollider.value()->material.restitution),
							PxShapeFlag::eSIMULATION_SHAPE
						);
						shape->setLocalPose(PxTransform(boxCollider.value()->offset.ScaledBy(transform.scale), Quaternion::Identity()));
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
						std::vector<PxVec3> verts {};
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
						PxTriangleMeshDesc meshDesc;
						meshDesc.points.count = vertCount;
						meshDesc.points.stride = sizeof(PxVec3);
						meshDesc.points.data = &verts[0];

						meshDesc.triangles.count = indices.size() / 3;
						meshDesc.triangles.stride = 3 * sizeof(PxU32);
						meshDesc.triangles.data = &indices[0];

						PxDefaultMemoryOutputStream writeBuffer;
						PxTriangleMeshCookingResult::Enum result;
						bool status = PhysicsHandler::ctx.cooking->cookTriangleMesh(meshDesc, writeBuffer, &result);
						if (!status)
						{
							std::cout << "ERROR::PHYSX: Couldn't create triangle mesh.\n";
							return;
						}

						PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
						auto triangleMesh = PhysicsHandler::ctx.physics->createTriangleMesh(readBuffer);
						PxMeshScale scale { transform.scale, transform.rotation };
						auto geometry = PxTriangleMeshGeometry(triangleMesh, scale);
						auto shape =
							PxRigidActorExt::createExclusiveShape(
								*rb.pxRb,
								geometry,
								*PhysicsHandler::ctx.physics->createMaterial(collider.material.staticFriction, collider.material.dynamicFriction, collider.material.restitution), PxShapeFlag::eSIMULATION_SHAPE
							);
						shape->setLocalPose(PxTransform(collider.offset.ScaledBy(transform.scale), Quaternion::Identity()));
					}
					rb.pxRb->setGlobalPose(PxTransform(transform.position, transform.rotation));
					rb.initialized = true;
				}
				auto pos = rb.pxRb->getGlobalPose().p;
				auto rot = rb.pxRb->getGlobalPose().q;
				transform.position = pos;
				transform.rotation = rot;
			});
			PhysicsHandler::ctx.scene->simulate(time->fixedDeltaTime);
			PhysicsHandler::ctx.scene->fetchResults(true);
		}
		void PhysicsSystem::Destroy(World* world)
		{
			PhysicsHandler::ctx.scene->release();
			PhysicsHandler::ctx.physics->release();
			PhysicsHandler::ctx.cooking->release();
			PhysicsHandler::ctx.pvd->release();
			PhysicsHandler::ctx.foundation->release();
		}


	}
}