#include "CarCameraSystem.h"
#include "CarFollowCameraData.h"
#include <Rendering/TransformData.h>
using namespace ck;
using namespace ck::math;
void CarCameraSystem::FixedUpdate(World* world)
{
	auto cams { world->QueryEntities<TransformData, CarFollowCameraData>() };
	cams->Foreach([&](TransformData& transform, CarFollowCameraData& cam)
	{
		auto& carTrans = *world->TryGetComponent<TransformData>(cam.car).value();

		auto lerpedPos = Vector3::Lerp(transform.position, carTrans.position + carTrans.rotation * cam.baseOffset, 1 - cam.followEasing);
		transform.position = carTrans.position + Vector3::ClampMagnitude(lerpedPos - carTrans.position, cam.baseOffset.X0Y().Magnitude() * 1.2f);
		auto dir = (carTrans.position - transform.position).Normalized();
		transform.rotation = Quaternion::LookRotation(dir, Vector3::Up());
		if (Vector3::Dot(transform.rotation * Vector3::Forward(), dir.Normalized()) < 0.99f)
		{
			std::cout << "Not seeing corrently" << '\n';
		}
	});
}