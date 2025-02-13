// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

/*
* ��� : ���÷����� ���� �������̽�.
*/
UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

/*
 * �̰� ���� �������̽� 
 * ������ Ȯ�嵵 ����ؼ� �������̽��� �ۼ��ؾ��Ѵ�.
 * ��ùߵ� Overlap
 * �����ߵ� Overlap
 * �����ߵ� Overlap
 */
class ASSIGNMENT8_API IItemInterface
{
	GENERATED_BODY()
public:
	// Actor�� �����ϴ°� ���� ���� ��츦 ������ �� �ִ�.
	UFUNCTION()
	virtual void OnItemBeginOverlap(
		UPrimitiveComponent* OverlappedComp,	//	�ڱ� �ڽ��� ������Ʈ
		AActor* OtherActor,						//	�浹�� ����
		UPrimitiveComponent* OtherComponent,	//	�浹�� ������ ������Ʈ
		int32 OtherBodyIndex,
		bool bFromSweep, 
		const FHitResult& SweepResult
	) = 0;
	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComponent, 
		int32 OtherBodyIndex) = 0;
	virtual void ActivateItem(AActor* Activator) = 0;
	// FName�� ������ ���̺��� �����Ƿ� Ÿ���� �ް���� ��� ����ϱ� ����.
	virtual FName GetItemType() const = 0;
};

