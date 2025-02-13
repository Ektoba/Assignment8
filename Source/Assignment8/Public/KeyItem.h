// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "KeyItem.generated.h"

UCLASS()
class ASSIGNMENT8_API AKeyItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
public:	
	AKeyItem();
protected:
	virtual void OnItemBeginOverlap(
		UPrimitiveComponent* OverlappedComp,	//	�ڱ� �ڽ��� ������Ʈ
		AActor* OtherActor,						//	�浹�� ����
		UPrimitiveComponent* OtherComponent,	//	�浹�� ������ ������Ʈ
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override;
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex) override;
	virtual void ActivateItem(AActor* Activator) override;
	virtual FName GetItemType() const override;
};
