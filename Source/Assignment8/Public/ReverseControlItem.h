// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ReverseControlItem.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT8_API AReverseControlItem : public ABaseItem
{
	GENERATED_BODY()
public:
	AReverseControlItem();
protected:
	UPROPERTY()
	float ReverseMoveDuration;
	bool bHasActivity;
	FTimerHandle ReverseMoveTimer;
protected:
	virtual void ActivateItem(AActor* Activator) override;
};
