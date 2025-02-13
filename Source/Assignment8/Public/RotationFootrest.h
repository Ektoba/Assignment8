// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotationFootrest.generated.h"

UENUM(BlueprintType)
enum class EMoveDirection : uint8
{
	UP UMETA(DisplayName = "UP"),
	DOWN UMETA(DisplayName = "DOWN"),
	LEFT UMETA(DisplayName = "LEFT"),
	RIGHT UMETA(DisplayName = "RIGHT")
};
UCLASS()
class ASSIGNMENT8_API ARotationFootrest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotationFootrest();
protected:
	FVector StartLotation;
protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* m_SceneRoot;
	UPROPERTY(EditAnywhere)
	float MoveSpeed;
	UPROPERTY(EditAnywhere)
	float RotationSpeed;
	UPROPERTY(EditAnywhere)
	bool bRotation;
	UPROPERTY(EditAnywhere)
	bool bMoving;
	UPROPERTY(EditAnywhere)
	float MaxRange;
	UPROPERTY(EditAnywhere)
	EMoveDirection Direction;
	bool bReverseMove;
	FVector MoveVector;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
