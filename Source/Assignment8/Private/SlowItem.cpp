#include "SlowItem.h"
#include "SpartaCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
ASlowItem::ASlowItem()
{
	ReductionRate = 0.5f;
	OriginalSpeed = 0.f;
	ReductionSpeed = 0.f;
	ReductionDuration = 3.f;
	ActivatorPlayer = nullptr;
	bHasActivated = false;
}

void ASlowItem::ActivateItem(AActor* Activator)
{
	if (bHasActivated)
		return;

	bHasActivated = true;

	ActivatorPlayer = Cast<ASpartaCharacter>(Activator);
	if (ActivatorPlayer)
	{
		OriginalSpeed = ActivatorPlayer->GetMovementComponent()->GetMaxSpeed();
		ReductionSpeed = OriginalSpeed * ReductionRate;		
		SetActorRedctionSpeed();
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda(
			[this]()->void
			{
			if (UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(ActivatorPlayer->GetMovementComponent()))
			{
				Movement->MaxWalkSpeed = OriginalSpeed;
				ActivatorPlayer->RemoveBuff("SlowMove");
			}
			this->bHasActivated = false;
			});
		ActivatorPlayer->ApplyBuff("SlowMove", ReductionDuration, TimerDelegate);
	}
}

void ASlowItem::SetActorRedctionSpeed()
{
	if (ActivatorPlayer)
	{
		if (UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(ActivatorPlayer->GetMovementComponent()))
		{
			Movement->MaxWalkSpeed *= ReductionRate;
		}
	}
}