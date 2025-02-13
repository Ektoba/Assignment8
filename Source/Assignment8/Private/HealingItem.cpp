// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingItem.h"
#include "SpartaCharacter.h"
AHealingItem::AHealingItem()
{
	HealAmount = 20;
	ItemType = "HealingItem";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (ASpartaCharacter* Sparta = Cast<ASpartaCharacter>(Activator))
		{
			Sparta->AddCurrentHP(HealAmount);
		}
		DestroyItem();
	}
}
