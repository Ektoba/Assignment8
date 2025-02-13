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
	// ���� ��ü ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 TotalScore;
	// ���� ���� �ε��� (GameState������ ������ �� ������, �� ��ȯ �Ŀ��� �츮�� �ʹٸ� GameInstance�� ������ �� ����)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 CurrentLevelIndex;
	// ���� ���� �� �̸� �迭. ���� �ִ� �ε����� ���ʴ�� ����
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
