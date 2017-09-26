// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector hitLocation)
{
	TankAimingComponent->AimAt(hitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeSeconds;
	if (!barrel || !isReloaded)
	{
		return;
	}
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
		barrel->GetSocketLocation(FName("Projectile")), 
		barrel->GetSocketRotation(FName("Projectile")));
	projectile->LaunchProjectile(LaunchSpeed);
	lastFireTime = FPlatformTime::Seconds();
}

void ATank::SetTankReferences(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	SetTurretReference(TurretToSet);
	SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	barrel = BarrelToSet;
}