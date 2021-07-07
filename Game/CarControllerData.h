#pragma once
#include <Usings.h>
#include <ckMath.h>

struct CarControllerData
{
	float maxSpeed;
	float acceleration;
	float turnSpeed;
	float maxTurnSpeed;
	float slowdown;
	float brakingStrength;
	float sidewaysDrag;
};