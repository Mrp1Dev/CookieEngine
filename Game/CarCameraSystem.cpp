#include "CarCameraSystem.h"
#include "CarFollowCameraData.h"
#include <Rendering/TransformData.h>
using namespace ck;
using namespace ck::math;
void CarCameraSystem::Update(World* world)
{
	auto cams { world->QueryEntities<TransformData, CarFollowCameraData>() };
	cams->Foreach([&](TransformData& transform, CarFollowCameraData& cam)
	{
		auto& carTrans = *world->TryGetComponent<TransformData>(cam.car).value();
		transform.position = carTrans.position + carTrans.rotation * cam.baseOffset;
		/*transform.rotation =
			Quaternion::Euler(Vector3::Up() * Vector3::Angle((carTrans.position - transform.position).Normalized().X0Y(), (transform.rotation * Vector3::Forward()).Normalized().X0Y())) * cam.baseRotation;*/
		auto dir = (carTrans.position - transform.position).Normalized();
		std::cout << dir.x << ' ' << dir.y << ' ' << dir.z << '\n';
		transform.rotation = Quaternion::LookRotation(dir, Vector3::Up());
		if (Vector3::Dot(transform.rotation * Vector3::Forward(), dir.Normalized()) < 0.99f)
		{
			std::cout << "Not seeing corrently" << '\n';
		}
	});
}