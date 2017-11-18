// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent))
	{
		return;
	}
	FoundAimingComponent(TankAimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn())
	{
		return;
	}
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent))
	{
		return;
	}
	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation))
	{
		TankAimingComponent->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	int32 viewportX, viewportY;
	GetViewportSize(viewportX, viewportY);
	FVector2D screenLocation = FVector2D(CrossHairXLocation * viewportX, CrossHairYLocation * viewportY);
	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection))
	{
		return GetLookVectorHitLocation(hitLocation, lookDirection);
		
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const
{
	FVector cameraPosition;
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraPosition, lookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& hitLocation, FVector lookDirection) const
{
	FHitResult hitData;
	FVector position = PlayerCameraManager->GetCameraLocation();
	FVector endPosition = position + (lookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(hitData, position, endPosition, ECollisionChannel::ECC_Camera))
	{
		hitLocation = hitData.Location;
		return true;
	}
	return false;
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))
		{
			return;
		}
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}
