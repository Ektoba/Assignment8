#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SpartaInstance.generated.h"

UCLASS()
class ASSIGNMENT8_API USpartaInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	USpartaInstance();
protected:
	// 게임 전체 누적 점수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 TotalScore;
	// 현재 레벨 인덱스 (GameState에서도 관리할 수 있지만, 맵 전환 후에도 살리고 싶다면 GameInstance에 복제할 수 있음)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 CurrentLevelIndex;
	// 실제 레벨 맵 이름 배열. 여기 있는 인덱스를 차례대로 연동
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;
	int32 MaxLevels;
public:
	virtual void Init() override;
public:	
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);
	UFUNCTION(BlueprintCallable, Category = "GameData")
	int32 GetCurrentLevelIndex() const;
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void SetCurrentLevelIndex(int32 Index);
	UFUNCTION(BlueprintCallable, Category = "GameData")
	int32 GetTotalScore() const;
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void PrevLevel();
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void NextLevel();
	UFUNCTION(BlueprintCallable, Category = "GameData")
	bool EndLevel() const;
	UFUNCTION(BlueprintCallable, Category = "GameData")
	FName GetCurrentLevelName();
	UFUNCTION(BlueprintCallable, Category = "GameData")
	FName GetPrevLevelName();
	UFUNCTION(BlueprintCallable, Category = "GameData")
	FName GetNextLevelName();
public:
	void RestartSetting();
protected:
	void OnGameOver();
};
