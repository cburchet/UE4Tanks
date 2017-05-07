// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* player = GetControlledTank();
	if (player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Playercontroller has possessed tank %s"), *player->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation))
	{
		GetControlledTank()->AimAt(hitLocation);
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
		if (GetLookVectorHitLocation(hitLocation, lookDirection))
		{
			return true;
		}
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
	if (GetWorld()->LineTraceSingleByChannel(hitData, position, endPosition, ECollisionChannel::ECC_Visibility))
	{
		hitLocation = hitData.Location;
		return true;
	}
	return false;
}
