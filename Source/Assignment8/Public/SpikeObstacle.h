#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "SpikeObstacle.generated.h"

UCLASS()
class ASSIGNMENT8_API ASpikeObstacle : public ABaseItem
{
	GENERATED_BODY()
public:
	ASpikeObstacle();
protected:
	FVector StartPosition;
	float Distance;
	FTimerHandle DamageTimerHandle;
	float DamageTimerDuration;
	int32 SpikeDamage;
	bool bHasActivity;
	float AccDeltaTime;
protected:
	virtual void BeginPlay() override;
	virtual void ActivateItem(AActor* Activator) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex) override;
};
