// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};


class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState firingState = EFiringState::Reloading;

public:	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void AimAt(FVector location);

	UFUNCTION(BlueprintCallable, Category = "setup")
	void Initialise(UTankBarrel* barrelSet, UTankTurret* turretSet);

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetAmmoCount() const;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f;

	bool IsBarrelMoving();

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	void MoveBarrel(FVector aimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeSeconds = 3.0f;

	double lastFireTime = 0;

	FVector AimDirection;
	
	int AmmoCount = 3;
};
