// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "AITankController.h"




void AAITankController::BeginPlay()
{
	Super::BeginPlay();
}

void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerTank)
	{
		aiTank = Cast<ATank>(GetPawn());
		MoveToActor(playerTank, AcceptanceRadius);	//assume check radius is in cm
		if (aiTank)
		{
			aiTank->AimAt(playerTank->GetActorLocation());
		}
		aiTank->Fire();
	}
}
