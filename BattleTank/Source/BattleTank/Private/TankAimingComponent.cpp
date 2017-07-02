// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelSet)
{
	Barrel = barrelSet;
}


void UTankAimingComponent::AimAt(FVector location, float LaunchSpeed)
{
	if (!Barrel)
	{
		return;
	}
	FVector LaunchVelocity;
	FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector AimDirection;
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, startLocation, location, LaunchSpeed, 
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		float time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Elevate called at speed %f"), time, LaunchSpeed);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No solution found"));
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	//get rotator from current barrel rotation to AimDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;
	//rotate barrel
	UE_LOG(LogTemp, Warning, TEXT("starting to elevate"));
	Barrel->Elevate(5.0f);
}

