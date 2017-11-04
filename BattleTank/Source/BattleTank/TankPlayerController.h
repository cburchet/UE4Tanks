// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* TankAimingReference);

public:	
	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnTankDeath();

private:
	UTankAimingComponent* TankAimingComponent;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& hitLocation) const;

	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;

	bool GetLookVectorHitLocation(FVector& hitLocation, FVector lookDirection) const;

	virtual void SetPawn(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = .5f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = .3333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;
};
