#include "SpartaCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "SpartaPlayerController.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "SpartaState.h"
#include "Define.h"
ASpartaCharacter::ASpartaCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(L"SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bUsePawnControlRotation = true; // 회전시 카메라도 이동한다.
	
	Camera = CreateDefaultSubobject<UCameraComponent>(L"Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // 끝부분을 가리킨다.
	Camera->bUsePawnControlRotation = false; // 카메라도 회전하면 정신없으므로 false

	NomalSpeed = 600.f;
	SprintSpeedMultiplier = 1.5f;
	SprintSpeed = NomalSpeed * SprintSpeedMultiplier;

	MaxHelth = 100;
	CurrentHelth = MaxHelth;
	GetCharacterMovement()->MaxWalkSpeed = NomalSpeed;

	OverHeadWidgetHPText = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHeadWidgetHPText"));
	OverHeadWidgetHPText->SetupAttachment(GetMesh());
	OverHeadWidgetHPText->SetWidgetSpace(EWidgetSpace::Screen);
	OverHeadWidgetHPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHeadWidgetHPBar"));
	OverHeadWidgetHPBar->SetupAttachment(GetMesh());
	OverHeadWidgetHPBar->SetWidgetSpace(EWidgetSpace::Screen);
}

void ASpartaCharacter::Move(const struct FInputActionValue& Value)
{
	if (!Controller) return;

	FVector2D MoveInput = Value.Get<FVector2D>();

	if (BuffTimers.Contains("ReverseControl"))
	{
		MoveInput *= -1.f;
	}

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void ASpartaCharacter::Look(const struct FInputActionValue& Value)
{
	//if (!Controller) return;
	const FVector2D LookInput = Value.Get<FVector2D>();
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void ASpartaCharacter::StartJump(const struct FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		Jump();
	}
}

void ASpartaCharacter::StopJump(const struct FInputActionValue& Value)
{
	if (!Value.Get<bool>())
	{
		StopJumping();
	}
}

void ASpartaCharacter::StartSprint(const struct FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void ASpartaCharacter::StopSprint(const struct FInputActionValue& Value)
{
	if (!Value.Get<bool>())
	{
		GetCharacterMovement()->MaxWalkSpeed = NomalSpeed;
	}
}
void ASpartaCharacter::ShowMenu(const struct FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			LOG_SCREEN("call ShowPlayMenu!");
			PlayerController->ShowPlayMenu();
		}
	}
}
void ASpartaCharacter::UpdateOverHeadHP()
{
	if (!OverHeadWidgetHPText || !OverHeadWidgetHPBar)
		return;

	UUserWidget* OverheadWidgetHPTextInstance = OverHeadWidgetHPText->GetUserWidgetObject();
	UUserWidget* OverheadWidgetHPBarInstance = OverHeadWidgetHPBar->GetUserWidgetObject();

	if (!OverheadWidgetHPTextInstance)
		return;
	if (!OverheadWidgetHPBarInstance)
		return;
	if (UTextBlock* Widget = Cast<UTextBlock>(OverheadWidgetHPTextInstance->GetWidgetFromName(TEXT("HPText"))))
	{
		Widget->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), CurrentHelth, MaxHelth)));
	}
	if (UProgressBar* Widget = Cast<UProgressBar>(OverheadWidgetHPBarInstance->GetWidgetFromName(TEXT("HPBar"))))
	{
		Widget->SetPercent((float)CurrentHelth / (float)MaxHelth);
	}
}
void ASpartaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpartaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInput==nullptr)
	{
		return;
	}
	ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController());
	if (PlayerController==nullptr)
	{
		return;
	}

	EnhancedInput->BindAction(
		PlayerController->MoveAction,
		ETriggerEvent::Triggered,
		this,
		&ASpartaCharacter::Move);
	EnhancedInput->BindAction(
		PlayerController->SprintAction,
		ETriggerEvent::Triggered,
		this,
		&ASpartaCharacter::StartSprint);
	EnhancedInput->BindAction(
		PlayerController->SprintAction,
		ETriggerEvent::Completed,
		this,
		&ASpartaCharacter::StopSprint);
	
	EnhancedInput->BindAction(
		PlayerController->LookAction,
		ETriggerEvent::Triggered,
		this,
		&ASpartaCharacter::Look);
	
	EnhancedInput->BindAction(
		PlayerController->JumpAction,
		ETriggerEvent::Triggered,
		this,
		&ASpartaCharacter::StartJump);
	EnhancedInput->BindAction(
		PlayerController->JumpAction,
		ETriggerEvent::Completed,
		this,
		&ASpartaCharacter::StopJump);	
	EnhancedInput->BindAction(
		PlayerController->MenuAction,
		ETriggerEvent::Triggered,
		this,
		&ASpartaCharacter::ShowMenu);
}
void ASpartaCharacter::BeginPlay()
{
	Super::BeginPlay();
	UpdateOverHeadHP();
}
void ASpartaCharacter::OnDeath()
{
	if (UWorld* World = GetWorld())
	{
		if (ASpartaPlayerController* PlayerController = 
			World->GetFirstPlayerController<ASpartaPlayerController>())
		{
			PlayerController->SetPause(true);
			PlayerController->ShowGameOver();
		}
	}
}
float ASpartaCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	AddCurrentHP(-DamageAmount);

	UpdateOverHeadHP();

	if (CurrentHelth <= 0)
	{
		OnDeath();
	}

	return ActualDamage;
}

void ASpartaCharacter::ApplyBuff(FName BuffName, float Duration, FTimerDelegate TimerDelegate)
{
	float CurrentTime = GetWorld()->GetTimeSeconds();
	float NewExpirationTime = CurrentTime + Duration;

	if (BuffTimers.Contains(BuffName))
	{
		BuffTimers[BuffName].ExpriationTime = FMath::Max(BuffTimers[BuffName].ExpriationTime, NewExpirationTime - BuffTimers[BuffName].ExpriationTime);
	}
	else
	{
		BuffTimers.Add(BuffName, FBuffData(NewExpirationTime));
	}

	GetWorldTimerManager().ClearTimer(BuffTimers[BuffName].TimerHandle);

	if (TimerDelegate.IsBound() == false)
	{
		TimerDelegate.BindLambda([BuffName,this]() {
			RemoveBuff(BuffName); 
			});
	}

	GetWorldTimerManager().SetTimer(BuffTimers[BuffName].TimerHandle, 
		TimerDelegate,
		Duration,
		false
		);
}

void ASpartaCharacter::RemoveBuff(FName BuffName)
{
	if (BuffTimers[BuffName].TimerHandle.IsValid())
		GetWorldTimerManager().ClearTimer(BuffTimers[BuffName].TimerHandle);
	BuffTimers.Remove(BuffName);
}

void ASpartaCharacter::ClearBuff()
{
	GetWorldTimerManager().ClearAllTimersForObject(this);
	BuffTimers.Empty();
}

void ASpartaCharacter::AddCurrentHP(int32 HP)
{
	CurrentHelth = FMath::Clamp(CurrentHelth+HP, 0, MaxHelth);
	UpdateOverHeadHP();
}

int32 ASpartaCharacter::GetMaxHelth() const
{
	return MaxHelth;
}

int32 ASpartaCharacter::GetCurrentHelth() const
{
	return CurrentHelth;
}
