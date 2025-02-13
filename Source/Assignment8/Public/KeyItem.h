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
		UPrimitiveComponent* OverlappedComp,	//	자기 자신의 컴포넌트
		AActor* OtherActor,						//	충돌한 액터
		UPrimitiveComponent* OtherComponent,	//	충돌한 액터의 컴포넌트
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
