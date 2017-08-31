// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeYawSpeed)
{
	RelativeYawSpeed = FMath::Clamp<float>(RelativeYawSpeed, -1.0f, 1.0f);
	float yawChange = RelativeYawSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	float rawNewYaw = RelativeRotation.Yaw + yawChange;

	SetRelativeRotation(FRotator(0, rawNewYaw, 0));
}

