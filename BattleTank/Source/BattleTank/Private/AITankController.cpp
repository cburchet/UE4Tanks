// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "AITankController.h"




void AAITankController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

}

void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerTank)
	{
		MoveToActor(playerTank, AcceptanceRadius);	//assume check radius is in cm
		if (!ensure(TankAimingComponent))
		{
			return;
		}
		TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(TankAimingComponent))
		{
			return;
		}
		TankAimingComponent->AimAt(playerTank->GetActorLocation());
		if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
		{
			TankAimingComponent->Fire();
		}
	}
}
