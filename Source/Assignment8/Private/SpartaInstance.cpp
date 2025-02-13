#include "SpartaInstance.h"
#include "SpartaState.h"
#include "Kismet/GameplayStatics.h"
#include "SpartaPlayerController.h"
#include "Define.h"
USpartaInstance::USpartaInstance()
{
	LevelMapNames.Add(TEXT("BasicLevel"));
	LevelMapNames.Add(TEXT("IntermediateLevel"));
	LevelMapNames.Add(TEXT("AdvancedLevel"));
	MaxLevels = LevelMapNames.Num();
}
void USpartaInstance::Init()
{
	Super::Init();
	TotalScore = 0;
	CurrentLevelIndex = 0;
}

void USpartaInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
}

int32 USpartaInstance::GetCurrentLevelIndex() const
{
	return CurrentLevelIndex;
}

void USpartaInstance::SetCurrentLevelIndex(int32 Index)
{
	CurrentLevelIndex = Index;
}

int32 USpartaInstance::GetTotalScore() const
{
	return TotalScore;
}
void USpartaInstance::PrevLevel()
{
	CurrentLevelIndex--;

	if (CurrentLevelIndex < 0)
		return;

	if (LevelMapNames[CurrentLevelIndex].IsValid())
	{
		UGameplayStatics::OpenLevel(
			GetWorld(),
			LevelMapNames[CurrentLevelIndex]
		);
	}
}
void USpartaInstance::NextLevel()
{
	CurrentLevelIndex++;

	if (EndLevel())
	{
		OnGameOver();
		return;
	}
	
	if (LevelMapNames[CurrentLevelIndex].IsValid())
	{
		UGameplayStatics::OpenLevel(
			GetWorld(),
			LevelMapNames[CurrentLevelIndex]
			);
	}
}

bool USpartaInstance::EndLevel() const
{
	return CurrentLevelIndex == MaxLevels;
}

FName USpartaInstance::GetCurrentLevelName()
{
	return LevelMapNames[CurrentLevelIndex];
}

FName USpartaInstance::GetPrevLevelName()
{
	return LevelMapNames[FMath::Clamp(CurrentLevelIndex-1, 0, MaxLevels-1)];
}

FName USpartaInstance::GetNextLevelName()
{
	return LevelMapNames[FMath::Clamp(CurrentLevelIndex + 1, 0, MaxLevels - 1)];
}

void USpartaInstance::RestartSetting()
{
	TotalScore = 0;
	CurrentLevelIndex = 0;
}

void USpartaInstance::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			SpartaPlayerController->ShowGameOver();
		}
	}
}
