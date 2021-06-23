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
		std::cout << carTrans.position.x << ' ' << carTrans.position.y << ' ' << carTrans.position.z << '\n';
		transform.rotation = Quaternion::LookRotation(carTrans.position - transform.position, Vector3::Up());
	});
}