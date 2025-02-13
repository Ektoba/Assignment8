// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SpartaState.generated.h"

enum class EUIType : uint8;

UCLASS()
class ASSIGNMENT8_API ASpartaState : public AGameState
{
	GENERATED_BODY()
protected:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin");
	int32 Score;
	//	생성할 아이템 개수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin");
	int32 ItemSpawnCount;	
	//	현재 레벨에서 스폰된 코인 개수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin");
	int32 SpawnedCoinCount;
	//	플레이어가 수집한 코인 개수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin");
	int32 CollectedCoinCount;
	//	레벨이 유지되는 시간
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	float LevelDuration;
	// 전체 레벨의 개수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	FTimerHandle LevelTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;
	FTimerDelegate HUDUpdateDelegate;	
private:
	int32 WaveCount;
	int32 MaxWave;
	class ASpartaPlayerController* SpartaController;
	class USpartaInstance* SpartaInstance;
protected:
	virtual void BeginPlay() override;
	void InitState();
	void NextWave();
	void ItemSpawnStart();
public:
	void AddScore(int32 Amount);
	void OnLevelTimeUp();
	void OnCoinCollected();
	void OnGameOver();
	void NextLevel();
	UFUNCTION()
	void UpdateWidget(EUIType Type);
	void HUDUpdate();
};
