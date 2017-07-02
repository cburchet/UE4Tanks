// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AITankController.generated.h"

/**
 * 
 */

class ATank;
UCLASS()
class BATTLETANK_API AAITankController : public AAIController
{
	GENERATED_BODY()
	
private:
	void BeginPlay() override;

	ATank* GetControlledTank() const;

	ATank* GetPlayerTank() const;

	void Tick(float DeltaSeconds) override;

	UPROPERTY()
	ATank* playerTank;

	UPROPERTY()
	ATank* aiTank;
};
