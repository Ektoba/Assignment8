// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObstacle.h"
#include "ExplodeObstacle.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT8_API AExplodeObstacle : public ABaseObstacle
{
	GENERATED_BODY()
public:
	AExplodeObstacle();
protected:
	class USphereComponent* ExplosionCollision;
public:
	UFUNCTION(BlueprintCallable)
	void Explode();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionRadus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ExplosionDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	UParticleSystem* ExplosionParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	USoundBase* ExplodeSound;
};
