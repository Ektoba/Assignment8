#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemSpawnRow.generated.h"

USTRUCT(BlueprintType)
struct FItemSpawnRow :public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<AActor> ItemClass;	//ItemClass, �����ϴ� ���´� �ƴ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float SpawnChance;				// Ȯ��
};
