#include "SpartaState.h"
#include "SpawnVolume.h"
#include "Kismet/GameplayStatics.h"
#include "CoinItem.h"
#include "SpartaInstance.h"
#include "Define.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "SpartaPlayerController.h"
#include "SpartaCharacter.h"
#include "ExplodeObstacle.h"
void ASpartaState::BeginPlay()
{
	Super::BeginPlay();
	ItemSpawnCount = 40;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	LevelDuration = FMath::RandRange(10.f, 30.f);
	WaveCount = 0;
	MaxWave = 3;
	InitState();
}

void ASpartaState::InitState()
{
	if (UWorld* World = GetWorld())
	{
		SpartaInstance = World->GetGameInstance<USpartaInstance>();
		SpartaController = World->GetFirstPlayerController<ASpartaPlayerController>();
	}
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;


	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ASpartaState::OnLevelTimeUp,
		LevelDuration,
		false
	);
	HUDUpdateDelegate.BindUFunction(this, "UpdateWidget", EUIType::HUD);
	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		HUDUpdateDelegate,
		0.1f,
		true
	);

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	for (int32 i = 0; i < ItemSpawnCount; ++i)
	{
		if (!FoundVolumes.IsEmpty())
		{
			if (ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]))
			{
				AActor* SpawnActor = SpawnVolume->SpawnRandomItem();
				if (SpawnActor != nullptr && SpawnActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}
	}

	if (SpartaController)
		SpartaController->ShowGameHUD();
}

void ASpartaState::NextWave()
{
	++WaveCount;

	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ASpartaState::OnLevelTimeUp,
		FMath::RandRange(10.f, LevelDuration),
		false
	);
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	if (SpikeTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(SpikeTimer);		

	}
	if (ExplodeTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(ExplodeTimer);
	}

	if (SpartaController)
	{
		SpartaController->SetPlayerLocation(SpartaController->GetSpawnLocation());
	}
	ItemSpawnStart();
	if (WaveCount == MaxWave)
	{
		NextLevel();
	}
}

void ASpartaState::ItemSpawnStart()
{
	// 모든 아이템을 지워버린다.
	TArray<AActor*> FoundItem;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseItem::StaticClass(), FoundItem);
	if (!FoundItem.IsEmpty())
	{
		for (AActor* Actor : FoundItem)
		{
			if (ABaseItem* Item = Cast<ABaseItem>(Actor))
			{
				Item->DestroyItem();
			}
		}
	}
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	for (int32 i = 0; i < FMath::RandRange(20, 50); ++i)
	{
		if (!FoundVolumes.IsEmpty())
		{
			if (ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]))
			{
				AActor* SpawnActor = SpawnVolume->SpawnRandomItem();
				
				switch (WaveCount)
				{
				case 1:
					if (!SpikeTimer.IsValid())
					{
						FTimerDelegate Delegate;
						Delegate.BindLambda([this, SpawnVolume]() {
							if (Wave2SpawnItem)
								SpawnVolume->SpawnItem(Wave2SpawnItem);
							});
						GetWorldTimerManager().SetTimer(SpikeTimer,
							Delegate,
							1.f,
							true);
					}
					break;
				case 2:
					if (!ExplodeTimer.IsValid())
					{
						FTimerDelegate Delegate;
						Delegate.BindLambda([this, SpawnVolume]() {
								if (Wave3SpawnItem)
								{
									AExplodeObstacle* Explode = Cast<AExplodeObstacle>(SpawnVolume->SpawnItem(Wave3SpawnItem));
									Explode->Explode();
								}
							});
						GetWorldTimerManager().SetTimer(ExplodeTimer,
							Delegate,
							1.f,
							true);
					}
					break;
				default:
					break;
				}
				if (SpawnActor != nullptr && SpawnActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}
	}
}

void ASpartaState::AddScore(int32 Amount)
{
	if (USpartaInstance* Instance = GetGameInstance<USpartaInstance>())
	{
		Instance->AddToScore(Amount);
	}
	UpdateWidget(EUIType::HUD);
}

void ASpartaState::OnLevelTimeUp()
{
	NextWave();
}

void ASpartaState::OnCoinCollected()
{
	CollectedCoinCount++;

	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		NextWave();
	}
	UpdateWidget(EUIType::HUD);
}

void ASpartaState::OnGameOver()
{
	if (SpartaController)
		SpartaController->ShowGameOver();
}

void ASpartaState::NextLevel()
{
	if (SpartaController)
	{
		if (ASpartaCharacter* Character = Cast<ASpartaCharacter>(SpartaController->GetLocalPlayer()))
		{
			Character->ClearBuff();
		}
	}
	//	타이머 해제
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	GetWorldTimerManager().ClearTimer(HUDUpdateTimerHandle);
	//	다음 레벨로
	if (UWorld* World = GetWorld())
	{
		if (USpartaInstance* Instance = World->GetGameInstance<USpartaInstance>())
		{
			Instance->NextLevel();
		}
	}
}
void ASpartaState::UpdateWidget(EUIType Type)
{
	if (SpartaController == nullptr || SpartaInstance == nullptr)
		return;

	switch (Type)
	{
	case EUIType::HUD:
	{
		if (UUserWidget* Widget = SpartaController->GetWidget(Type))
		{
			if (UTextBlock* TimeText = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("Time"))))
			{
				float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
				TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
			}

			if (UTextBlock* ScoreText = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("TotalScore"))))
			{
				ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), SpartaInstance->GetTotalScore())));
			}

			if (UTextBlock* LevelIndexText = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("Level"))))
			{
				LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d Wave : %d"), SpartaInstance->GetCurrentLevelIndex() + 1, WaveCount+1)));
			}
			if (UTextBlock* Text = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("CoinCount"))))
			{
				Text->SetText(FText::FromString(FString::Printf(TEXT("Coin: %d / %d"), CollectedCoinCount, SpawnedCoinCount)));
			}
			if (UProgressBar* Bar = Cast<UProgressBar>(Widget->GetWidgetFromName(TEXT("HPBar"))))
			{				
				if (SpartaController)
				{
					float Percent = static_cast<float>(SpartaController->GetPlayerCurrentHelth()) / static_cast<float>(SpartaController->GetPlayerMaxHelth());
					Bar->SetPercent(Percent);
				}
			}
		}
	}
	break;
	}
}

void ASpartaState::HUDUpdate()
{
	UpdateWidget(EUIType::HUD);
}
