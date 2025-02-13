// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnRow.h"
#include "SpawnVolume.generated.h"

UCLASS()
class ASSIGNMENT8_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
public:	
	ASpawnVolume();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	class UBoxComponent* SpawningBox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	class UDataTable* ItemDataTable;
public:
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	AActor* SpawnRandomItem();
protected:
	virtual void BeginPlay() override;
protected:
	AActor* SpawnItem(TSubclassOf<AActor> Itemclass);
	FItemSpawnRow* GetRandomItem() const;
	FVector GetRandomPointInVolume() const;
};
