// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativePitchSpeed);

private:
	UPROPERTY(EditAnywhere, category = Setup)
	float MaxDegreesPerSecond = 5.0f;
	
	UPROPERTY(EditDefaultsOnly, category = Setup)
	float MaxDegreeElevation = 40.0f;

	UPROPERTY(EditDefaultsOnly, category = Setup)
	float MinDegreeElevation = 0.0f;
};
