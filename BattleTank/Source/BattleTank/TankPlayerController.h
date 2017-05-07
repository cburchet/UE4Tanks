// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	
	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

private:

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& hitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = .5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = .3333f;
};
