#include "ChildCalculationSystem.h"
#include <RenderingComponents.h>
#include "ChildData.h"
namespace cookie
{
    void ChildCalculationSystem::Update(World* world)
    {
        auto query { world->QueryEntities<TransformData, ChildData>() };
        query->Foreach([&](TransformData& transform, ChildData& child)
            {
                auto parent { world->TryGetComponent<TransformData>(child.parent) };
                if (!parent.has_value())
                {
                    transform.position = child.localPosition;
                    transform.rotation = child.localRotation;
                    return;
                }
                transform.position = parent.value()->position + child.localPosition;
                transform.rotation = parent.value()->rotation * child.localRotation;
            });
    }
}