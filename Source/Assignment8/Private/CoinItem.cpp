// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"
#include "SpartaState.h"
ACoinItem::ACoinItem() : 
	PointValue(NULL)
{
	ItemType = "DefaultCoin";
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (UWorld* World = GetWorld())
		{
			if (ASpartaState* State = World->GetGameState<ASpartaState>())
			{
				State->OnCoinCollected();
				State->AddScore(PointValue);
			}
		}

		DestroyItem();
	}
}
