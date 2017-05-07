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
		UE_LOG(LogTemp, Warning, TEXT("%s"), *hitLocation.ToString());

	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	int32 viewportX, viewportY;
	GetViewportSize(viewportX, viewportY);
	FVector crosshairPosition, crosshairRotation;
	FVector2D screenLocation = FVector2D(CrossHairXLocation * viewportX, CrossHairYLocation * viewportY);
	DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, crosshairPosition, crosshairRotation);

}
