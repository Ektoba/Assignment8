// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

/*
* 기능 : 리플렉션을 위한 인터페이스.
*/
UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

/*
 * 이게 ㄹㅇ 인터페이스 
 * 앞으로 확장도 고려해서 인터페이스를 작성해야한다.
 * 즉시발동 Overlap
 * 지연발동 Overlap
 * 범위발동 Overlap
 */
class ASSIGNMENT8_API IItemInterface
{
	GENERATED_BODY()
public:
	// Actor를 가정하는게 가장 많은 경우를 상정할 수 있다.
	UFUNCTION()
	virtual void OnItemBeginOverlap(
		UPrimitiveComponent* OverlappedComp,	//	자기 자신의 컴포넌트
		AActor* OtherActor,						//	충돌한 액터
		UPrimitiveComponent* OtherComponent,	//	충돌한 액터의 컴포넌트
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
	// FName은 내부의 테이블이 있으므로 타입을 받고싶은 경우 사용하기 좋다.
	virtual FName GetItemType() const = 0;
};

