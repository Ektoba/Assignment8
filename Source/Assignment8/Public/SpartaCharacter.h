// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpartaCharacter.generated.h"

struct FBuffData
{
	FBuffData(float Time) : ExpriationTime(Time){}
	float ExpriationTime;
	FTimerHandle TimerHandle;
};
UCLASS()
class ASSIGNMENT8_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	ASpartaCharacter();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpringArm")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	class UWidgetComponent* OverHeadWidgetHPText;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	class UWidgetComponent* OverHeadWidgetHPBar;
	float NomalSpeed;
	float SprintSpeedMultiplier;
	float SprintSpeed;
	int32 MaxHelth;
	int32 CurrentHelth;
	float DefaultFieldofView;
private:

protected:
	UFUNCTION()
	void Move(const struct FInputActionValue& Value);
	UFUNCTION()
	void Look(const struct FInputActionValue& Value);
	UFUNCTION()
	void StartJump(const struct FInputActionValue& Value);
	UFUNCTION()
	void StopJump(const struct FInputActionValue& Value);
	UFUNCTION()
	void StartSprint(const struct FInputActionValue& Value);
	UFUNCTION()
	void StopSprint(const struct FInputActionValue& Value);
	UFUNCTION()
	void ShowMenu(const struct FInputActionValue& Value);
protected:
	void UpdateOverHeadHP();
	void OnDeath();
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;
public:
	void ApplyBuff(FName BuffName, float Duration, FTimerDelegate TimerDelegate = nullptr);
	void RemoveBuff(FName BuffName);
	void ClearBuff();
private:
	TMap<FName, FBuffData> BuffTimers;
public:
	void AddCurrentHP(int32 HP);
	int32 GetMaxHelth() const;
	int32 GetCurrentHelth() const;
};