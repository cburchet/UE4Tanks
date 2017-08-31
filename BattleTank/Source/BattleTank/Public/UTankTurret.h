// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "UTankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UUTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotate(float RelativeYawSpeed);

private:
	UPROPERTY(EditAnywhere, category = Setup)
		float MaxDegreesPerSecond = 5.0f;

	UPROPERTY(EditAnywhere, category = Setup)
		float MaxDegreeElevation = 40.0f;

	UPROPERTY(EditAnywhere, category = Setup)
		float MinDegreeElevation = 0.0f;
};
