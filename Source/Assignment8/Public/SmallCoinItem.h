// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoinItem.h"
#include "SmallCoinItem.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT8_API ASmallCoinItem : public ACoinItem
{
	GENERATED_BODY()
public:
	ASmallCoinItem(); 
public:
	virtual void ActivateItem(AActor* Actor) override;
};
