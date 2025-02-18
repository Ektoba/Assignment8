// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeObstacle.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
ASpikeObstacle::ASpikeObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
	ItemType = "SpikeObstacle";
	DamageTimerDuration = 0.5f;
	Distance = 100.f;
	SpikeDamage = 10;	
	
}

void ASpikeObstacle::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = GetActorLocation();
	StartPosition.Z = 0;

	SetActorLocation(StartPosition);
}

void ASpikeObstacle::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	if (bHasActivity)
		return;

	bHasActivity = true;
}

void ASpikeObstacle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector ActorLocation = GetActorLocation();

	if (FVector::Dist(StartPosition, ActorLocation) >= Distance)
	{
		SetActorLocation(StartPosition);
	}
	AddActorLocalOffset(FVector::UpVector * Distance * DeltaSeconds);

	if (bIsOverlapping && SpartaPlayer)
	{
		AccDeltaTime += DeltaSeconds;

		if (AccDeltaTime >= DamageTimerDuration)
		{
			UGameplayStatics::ApplyDamage(
				SpartaPlayer,
				SpikeDamage,
				nullptr,
				this,
				UDamageType::StaticClass()
			);
			AccDeltaTime = 0.f;
		}
	}
}

void ASpikeObstacle::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	Super::OnItemEndOverlap(OverlappedComp, OtherActor, OtherComponent, OtherBodyIndex);

	if(SpartaPlayer == nullptr && PickupSoundComponent)
		PickupSoundComponent->Stop();
}
