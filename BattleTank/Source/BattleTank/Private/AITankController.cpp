// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "AITankController.h"




void AAITankController::BeginPlay()
{
	Super::BeginPlay();
	aiTank = GetControlledTank();
	playerTank = GetPlayerTank();
}

ATank* AAITankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* AAITankController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (playerTank)
	{
		if (aiTank)
		{
			aiTank->AimAt(playerTank->GetActorLocation());
		}
	}
}
