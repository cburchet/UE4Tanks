// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
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


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* barrelSet)
{
	Barrel = barrelSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
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
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, startLocation, location, LaunchSpeed, false, 0.0f, 0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Firing at %s"), *AimDirection.ToString());
	}
}

