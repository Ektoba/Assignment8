#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h" 
#include "Containers/EnumAsByte.h"
#include "SpartaPlayerController.generated.h"

UENUM(BlueprintType)
enum class EUIType : uint8
{
	HUD UMETA(DisplayName = "HUD"),
	MainMenu UMETA(DisplayName = "MainMenu"),
	GameOver UMETA(DisplayName = "GameOver"),
	PlayMenu UMETA(DisplayName = "PlayMenu"),
	Setting UMETA(DisplayName = "Setting"),
	Max UMETA(Hidden)
};
ENUM_RANGE_BY_FIRST_AND_LAST(EUIType, EUIType::HUD, EUIType::Setting);

USTRUCT(BlueprintType)
struct FSpartaWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> CustomWidgetClass;
	UPROPERTY()
	UUserWidget* Instance = nullptr;
};

UCLASS()
class ASSIGNMENT8_API ASpartaPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASpartaPlayerController();
	int32 GetPlayerCurrentHelth()const;
	void SetPlayerLocation(const FVector Location);
	int32 GetPlayerMaxHelth() const;
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	class UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	class UInputAction* JumpAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	class UInputAction* SprintAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="UI")
	class UInputAction* MenuAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="UI")
	TMap<EUIType,FSpartaWidget> Widgets;
protected:
	virtual void BeginPlay() override;
protected:
	void ClearMenu();
public:
	UUserWidget* GetWidget(EUIType Type) const;
	UFUNCTION(BlueprintCallable, Category="HUD")
	void ShowGameHUD();
	UFUNCTION(BlueprintCallable, Category="Menu")
	void ShowMainMenu();
	UFUNCTION(BlueprintCallable, Category="Menu")
	void StartGame();
	UFUNCTION(BlueprintCallable, Category="Menu")
	void ShowGameOver();
	UFUNCTION(BlueprintCallable, Category="Menu")
	void ShowPlayMenu();
	UFUNCTION(BlueprintCallable, Category="Menu")
	void ShowSetting();
	UFUNCTION(BlueprintCallable, Category="Menu")
	void ShowGame();
};
