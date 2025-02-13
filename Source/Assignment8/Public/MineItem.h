// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT8_API AMineItem : public ABaseItem
{
	GENERATED_BODY()
public:
	AMineItem();
public:
	class USphereComponent* ExplosionCollision;
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
	FTimerHandle ExplosionTimer;
	bool bHasExploded;
public:
	virtual void ActivateItem(AActor* Activator) override;
	virtual void DestroyItem() override;
	void Explode();
};
