// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "AITankController.h"




void AAITankController::BeginPlay()
{
	Super::BeginPlay();
	ATank* aiTank = GetControlledTank();
	ATank* playerTank = GetPlayerTank();
	if (aiTank && playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI possessed tank: %s targeting: %s"), *aiTank->GetName(), *playerTank->GetName());
	}
}

ATank* AAITankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* AAITankController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
