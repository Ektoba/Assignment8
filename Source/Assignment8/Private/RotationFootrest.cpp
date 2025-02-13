// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationFootrest.h"

// Sets default values
ARotationFootrest::ARotationFootrest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MaxRange = 100.f;
	MoveSpeed = 100.f;
	RotationSpeed = 90.f;
	m_SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(m_SceneRoot);
	bReverseMove = false;
}

// Called when the game starts or when spawned
void ARotationFootrest::BeginPlay()
{
	Super::BeginPlay();
	StartLotation = GetActorLocation();
		
	switch (Direction)
	{
		case EMoveDirection::UP : MoveVector = FVector::UpVector;break;
		case EMoveDirection::DOWN : MoveVector = FVector::DownVector;break;
		case EMoveDirection::LEFT : MoveVector = FVector::LeftVector;break;
		case EMoveDirection::RIGHT : MoveVector = FVector::RightVector;break;
	}
}

// Called every frame
void ARotationFootrest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(MoveSpeed) && bMoving)
	{
		float Dist = FVector::Distance(StartLotation,GetActorLocation());
		
		if (Dist >= MaxRange && !bReverseMove)
		{
			bReverseMove = !bReverseMove;
			MoveVector *= -1;
		}
		else if (Dist < 1.f && bReverseMove)
		{
			bReverseMove = !bReverseMove;
			MoveVector *= -1;
		}
		AddActorLocalOffset(MoveVector);
	}
	if (!FMath::IsNearlyZero(RotationSpeed) && bRotation)
	{
		AddActorLocalRotation(FRotator(0, RotationSpeed * DeltaTime, 0));
	}
}

