// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTracks;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "input")
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = "setup")
	void Initialise(UTankTracks* LeftTrackSet, UTankTracks* RightTrackSet);

private:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTracks* LeftTrack = nullptr;
	UTankTracks* RightTrack = nullptr;
};
