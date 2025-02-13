// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "SlowItem.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT8_API ASlowItem : public ABaseItem
{
	GENERATED_BODY()
public:
	ASlowItem();
protected:
	virtual void ActivateItem(AActor* Activator) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReductionRate;
	float OriginalSpeed;
	float ReductionSpeed;
	float ReductionDuration;
	FTimerHandle ReductionRateTimer;
	class ASpartaCharacter* ActivatorPlayer;
	bool bHasActivated;
protected:
	void SetActorRedctionSpeed();
	void SetActorOriginSpeed();
};
