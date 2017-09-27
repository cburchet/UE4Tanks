// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

}


UTankBarrel* UTankAimingComponent::GetBarrel() const
{
	return Barrel;
}

void UTankAimingComponent::AimAt(FVector location, float LaunchSpeed)
{
	if (!ensure(Barrel && Turret))
	{
		return;
	}
	FVector LaunchVelocity;
	FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector AimDirection;
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, startLocation, location, LaunchSpeed, 
		false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* barrelSet, UTankTurret* turretSet)
{
	Turret = turretSet;

	Barrel = barrelSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret))
	{
		return;
	}
	//get rotator from current barrel rotation to AimDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;
	//rotate barrel
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

