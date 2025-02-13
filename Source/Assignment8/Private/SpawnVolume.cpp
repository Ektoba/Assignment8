// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "ItemSpawnRow.h"
ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	ItemDataTable = nullptr;
}

void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
}

// 아이템을 스폰한다.
AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> Itemclass)
{
	if (!Itemclass) return nullptr;
	
	return GetWorld()->SpawnActor<AActor>(
		Itemclass,
		GetRandomPointInVolume(),
		FRotator::ZeroRotator
	);
}

FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	//	테이블의 랜덤한 값을 가지고 온다.
	if (!ItemDataTable) 
		return nullptr;

	// 1)모든 행 가져오기
	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext"));
	ItemDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty()) return nullptr;

	// 2) 전체 확률 합 구하기.
	float TotalChance = Algo::Accumulate(
		AllRows,
		0.f,
		[](float Sum, const FItemSpawnRow* Row)->float
		{
			return Sum + Row->SpawnChance;
		}
	);

	// 3) 0 ~ TotalChance의 랜덤값
	const float RandValue = FMath::FRandRange(0.f, TotalChance);

	// 4) 누적 확률로 아이템 선택
	float AccumulateChance = 0.f;
	for (FItemSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue <= AccumulateChance)
		{
			return Row;
		}
	}
	return nullptr;
}

AActor* ASpawnVolume::SpawnRandomItem()
{
	if (FItemSpawnRow* SelectedRow = GetRandomItem())
	{
		if (UClass* ActualClass = SelectedRow->ItemClass)
		{
			return SpawnItem(ActualClass);
		}
	}

	return nullptr;
}

// 스폰할 좌표를 가지고 온다.
FVector ASpawnVolume::GetRandomPointInVolume() const
{
	// 중심 -> 끝까지의 거리이다.
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();	
	// 컴포넌트가 위치한 좌표의 중심 좌표.
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}
