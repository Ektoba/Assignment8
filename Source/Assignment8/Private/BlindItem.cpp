#include "BlindItem.h"
#include "Kismet/GameplayStatics.h"
ABlindItem::ABlindItem()
{
	BlindDuration = 1.f;
	bHasActivated = false;
}

void ABlindItem::ActivateItem(AActor* Actor)
{
	if (bHasActivated)
		return;

	Super::ActivateItem(Actor);
	bHasActivated = true;

	SpartaController->ShowBlind();
	FTimerDelegate Delegate;
	Delegate.BindLambda([this]() 
		{
			if (UWorld* World = GetWorld())
			{
				if (ASpartaPlayerController* Controller = Cast<ASpartaPlayerController>(World->GetFirstPlayerController()))
				{
					Controller->ShowGameHUD();
					if (ASpartaCharacter* Player = Cast<ASpartaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
					{
						Player->RemoveBuff("Blind");
					}
				}
			}
			this->bHasActivated = false;
		});
	SpartaPlayer->ApplyBuff("Blind", BlindDuration,Delegate);
}
