// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = firing)
		void Fire();

	UFUNCTION(BlueprintCallable, Category = setup)
	void SetTankReferences(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.0f; 

	UPROPERTY(EditDefaultsOnly, Category = setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float reloadTimeSeconds = 3.0f;

	double lastFireTime = 0;
};
