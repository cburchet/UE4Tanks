// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	lastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (AmmoCount <= 0)
	{
		firingState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - lastFireTime) < reloadTimeSeconds)
	{
		firingState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		firingState = EFiringState::Aiming;
	}
	else
	{
		firingState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
	{
		return false;
	}
	return !AimDirection.FVector::Equals(Barrel->GetForwardVector(), 0.05f);
}

void UTankAimingComponent::AimAt(FVector location)
{
	if (!ensure(Barrel && Turret))
	{
		return;
	}
	FVector LaunchVelocity;
	FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, startLocation, location, LaunchSpeed, 
		false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
}


int32 UTankAimingComponent::GetAmmoCount() const
{
	return AmmoCount;
}

void UTankAimingComponent::Fire()
{
	if (firingState == EFiringState::Aiming || firingState == EFiringState::Locked)
	{
		if (!ensure(Barrel && ProjectileBlueprint))
		{
			return;
		}
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));
		projectile->LaunchProjectile(LaunchSpeed);
		lastFireTime = FPlatformTime::Seconds();
		AmmoCount--;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* barrelSet, UTankTurret* turretSet)
{
	Turret = turretSet;

	Barrel = barrelSet;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return firingState;
}

void UTankAimingComponent::MoveBarrel(FVector aimDirection)
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
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

