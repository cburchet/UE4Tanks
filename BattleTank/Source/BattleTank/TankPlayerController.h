// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
class ATank;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* TankAimingReference);

public:
	
	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

private:

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& hitLocation) const;

	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;

	bool GetLookVectorHitLocation(FVector& hitLocation, FVector lookDirection) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = .5f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = .3333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;
};
