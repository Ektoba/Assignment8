// Fill out your copyright notice in the Description page of Project Settings.


#include "SmallCoinItem.h"

ASmallCoinItem::ASmallCoinItem()
{
	ItemType = "SmallCoin";
	PointValue = 10;
}

void ASmallCoinItem::ActivateItem(AActor* Actor)
{
	Super::ActivateItem(Actor);
}
