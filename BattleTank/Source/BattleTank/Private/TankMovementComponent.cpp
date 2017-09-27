// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTracks.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	FVector TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	
	IntendMoveForward(FVector::DotProduct(AIForwardIntention, TankForwardVector));

	FVector rightThrowVector = FVector::CrossProduct(TankForwardVector, AIForwardIntention);
	IntendTurnRight(rightThrowVector.Z);
	//UE_LOG(LogTemp, Warning, TEXT("Tank moving to %s"), *AIForwardIntention)
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
	{
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
	{
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialise(UTankTracks* LeftTrackSet, UTankTracks* RightTrackSet)
{
	LeftTrack = LeftTrackSet;
	RightTrack = RightTrackSet;
}
