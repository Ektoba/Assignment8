#include "ReverseControlItem.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
#include "Kismet/GameplayStatics.h"
AReverseControlItem::AReverseControlItem()
{
	ReverseMoveDuration = 1.f;
	bHasActivity = false;
}

void AReverseControlItem::ActivateItem(AActor* Activator)
{
	if (bHasActivity)
		return;

	bHasActivity = true;
	Super::ActivateItem(Activator);

	if (SpartaPlayer)
	{
		FTimerDelegate Delegate;
		Delegate.BindLambda([this]() {
				bHasActivity = false;
				if (UWorld* World = GetWorld())
				{
					if (ASpartaPlayerController* Controller = Cast<ASpartaPlayerController>(World->GetFirstPlayerController()))
					{
						if (ASpartaCharacter* Player = Cast<ASpartaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
						{
							Player->RemoveBuff("ReverseControl");
						}
					}
				}
			});
		SpartaPlayer->ApplyBuff("ReverseControl", ReverseMoveDuration, Delegate);
	}
}
