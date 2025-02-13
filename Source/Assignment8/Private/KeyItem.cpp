#include "KeyItem.h"
#include "SpartaCharacter.h"

AKeyItem::AKeyItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AKeyItem::OnItemBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AKeyItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
}

void AKeyItem::ActivateItem(AActor* Activator)
{
}

FName AKeyItem::GetItemType() const
{
	return FName();
}
