#include "SpartaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "SpartaState.h"
#include "Kismet/GameplayStatics.h"
#include "SpartaInstance.h"
#include "Components/TextBlock.h"
#include "SpartaCharacter.h"
ASpartaPlayerController::ASpartaPlayerController() :
	InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr),
	SprintAction(nullptr)
{		
	for (EUIType Type : TEnumRange<EUIType>())
	{
		Widgets.Add(Type, FSpartaWidget());
	}
}

void ASpartaPlayerController::SetPlayerLocation(const FVector Location)
{
	if (ASpartaCharacter* Sparta = Cast<ASpartaCharacter>(GetPawn()))
	{
		Sparta->SetActorLocation(Location);
	}
}
int32 ASpartaPlayerController::GetPlayerMaxHelth() const
{
	if (ASpartaCharacter* Sparta = Cast<ASpartaCharacter>(GetPawn()))
	{
		return Sparta->GetMaxHelth();
	}
	return 0;
}
int32 ASpartaPlayerController::GetPlayerCurrentHelth() const
{
	if (ASpartaCharacter* Sparta = Cast<ASpartaCharacter>(GetPawn()))
	{
		return Sparta->GetCurrentHelth();
	}
	return 0;
}

void ASpartaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 로컬 플레이어는 입력을 관리하는 객체이다.
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0); // 우선순위 0
			}
		}
	}

	FString CurrentMapName = GetWorld()->GetMapName();
	//Contains = 같은 값인지 비교
	if (CurrentMapName.Contains("MenuLevel"))
	{
		ShowMainMenu();
	}
}

void ASpartaPlayerController::ShowGameHUD()
{
	ClearMenu();
	Widgets[EUIType::HUD].Instance = CreateWidget<UUserWidget>(this, Widgets[EUIType::HUD].CustomWidgetClass);
	if (Widgets[EUIType::HUD].Instance)
	{
		Widgets[EUIType::HUD].Instance->AddToViewport();
		SetInputMode(FInputModeGameOnly());
	}
}


void ASpartaPlayerController::ShowMainMenu()
{
	ClearMenu();
	SetPause(true);
	EUIType Type = EUIType::MainMenu;
	Widgets[Type].Instance = CreateWidget<UUserWidget>(this, Widgets[Type].CustomWidgetClass);
	if (Widgets[Type].Instance)
	{
		bShowMouseCursor = true;
		Widgets[Type].Instance->AddToViewport();
		SetInputMode(FInputModeUIOnly());
	}
}

void ASpartaPlayerController::StartGame()
{
	ClearMenu();
	SetPause(false);
	if (USpartaInstance* Instance = GetGameInstance<USpartaInstance>())
	{
		Instance->RestartSetting();
	}
	UGameplayStatics::OpenLevel(GetWorld(), FName("BasicLevel"));
}

void ASpartaPlayerController::ShowGameOver()
{
	ClearMenu();
	SetPause(true);
	EUIType Type = EUIType::GameOver;
	Widgets[Type].Instance = CreateWidget<UUserWidget>(this, Widgets[Type].CustomWidgetClass);
	if (Widgets[Type].Instance)
	{
		bShowMouseCursor = true;
		Widgets[Type].Instance->AddToViewport();
		if (UFunction* Function = Widgets[Type].Instance->FindFunction("PlayGameOverAnim"))
		{
			Widgets[Type].Instance->ProcessEvent(Function,nullptr);
		}
		SetInputMode(FInputModeUIOnly());
	}
}

void ASpartaPlayerController::ShowPlayMenu()
{
	ClearMenu();
	SetPause(true);
	EUIType Type = EUIType::PlayMenu;
	Widgets[Type].Instance = CreateWidget<UUserWidget>(this, Widgets[Type].CustomWidgetClass);
	if (Widgets[Type].Instance)
	{
		bShowMouseCursor = true;
		Widgets[Type].Instance->AddToViewport();
		SetInputMode(FInputModeUIOnly());
	}
}

void ASpartaPlayerController::ShowSetting()
{
	ClearMenu();
	SetPause(true);
	EUIType Type = EUIType::Setting;
	Widgets[Type].Instance = CreateWidget<UUserWidget>(this, Widgets[Type].CustomWidgetClass);
	if (Widgets[Type].Instance)
	{
		bShowMouseCursor = true;
		Widgets[Type].Instance->AddToViewport();
		SetInputMode(FInputModeUIOnly());
	}
}

void ASpartaPlayerController::ShowGame()
{
	ClearMenu();
	SetPause(false);
	ShowGameHUD();
}

void ASpartaPlayerController::ClearMenu()
{
	for (EUIType Type : TEnumRange<EUIType>())
	{
		if (Widgets[Type].Instance)
		{
			Widgets[Type].Instance->RemoveFromParent();
			Widgets[Type].Instance = nullptr;
		}
	}
}

UUserWidget* ASpartaPlayerController::GetWidget(EUIType Type) const
{
	return Widgets[Type].Instance;
}
