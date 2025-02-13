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

// �������� �����Ѵ�.
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
	//	���̺��� ������ ���� ������ �´�.
	if (!ItemDataTable) 
		return nullptr;

	// 1)��� �� ��������
	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext"));
	ItemDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty()) return nullptr;

	// 2) ��ü Ȯ�� �� ���ϱ�.
	float TotalChance = Algo::Accumulate(
		AllRows,
		0.f,
		[](float Sum, const FItemSpawnRow* Row)->float
		{
			return Sum + Row->SpawnChance;
		}
	);

	// 3) 0 ~ TotalChance�� ������
	const float RandValue = FMath::FRandRange(0.f, TotalChance);

	// 4) ���� Ȯ���� ������ ����
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

// ������ ��ǥ�� ������ �´�.
FVector ASpawnVolume::GetRandomPointInVolume() const
{
	// �߽� -> �������� �Ÿ��̴�.
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();	
	// ������Ʈ�� ��ġ�� ��ǥ�� �߽� ��ǥ.
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}
