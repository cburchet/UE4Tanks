// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator,
		AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

protected:

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "setup")
	int32 StartingHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "health")
	int32 CurrentHealth = StartingHealth;
};
