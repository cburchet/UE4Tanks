// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTracks.h"


UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTracks::ApplySidewaysForce()
{
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	float ChangeInTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectionAcceleration = -SlippageSpeed / ChangeInTime * GetRightVector();
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTracks::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);
}

void UTankTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTracks::SetThrottle(float throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + throttle, -1, 1);
}

void UTankTracks::DriveTrack()
{
	//TODO: clamp throttle value
	FVector forceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}
