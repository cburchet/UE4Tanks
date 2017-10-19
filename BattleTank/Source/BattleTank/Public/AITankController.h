// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AITankController.generated.h"

/**
 * 
 */

class UTankAimingComponent;
class ATank;
UCLASS()
class BATTLETANK_API AAITankController : public AAIController
{
	GENERATED_BODY()
	
private:
	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	UPROPERTY()
	ATank* playerTank;

	UTankAimingComponent* TankAimingComponent;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000.0f;	//80m
};
