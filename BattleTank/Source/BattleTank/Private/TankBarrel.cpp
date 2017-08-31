// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"




void UTankBarrel::Elevate(float RelativePitchSpeed)
{
	RelativePitchSpeed = FMath::Clamp<float>(RelativePitchSpeed, -1.0f, 1.0f);
	float elevationChange = RelativePitchSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	float rawNewElevation = RelativeRotation.Pitch + elevationChange;
	float elevation = FMath::Clamp<float>(rawNewElevation, MinDegreeElevation, MaxDegreeElevation);

	SetRelativeRotation(FRotator(elevation, 0, 0));
}
