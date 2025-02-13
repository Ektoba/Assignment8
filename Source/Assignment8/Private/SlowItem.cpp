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
		GetWorldTimerManager().SetTimer(
			ReductionRateTimer,
			this,
			&ASlowItem::SetActorOriginSpeed,
			ReductionDuration,
			false);
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

void ASlowItem::SetActorOriginSpeed()
{
	if (ActivatorPlayer)
	{
		if (UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(ActivatorPlayer->GetMovementComponent()))
		{
			Movement->MaxWalkSpeed = OriginalSpeed;
		}
		bHasActivated = false;
	}
}
