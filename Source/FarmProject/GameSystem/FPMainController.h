// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "FPMainController.generated.h"

DECLARE_DELEGATE(FOnInputTriggeredW);
DECLARE_DELEGATE(FOnInputTriggeredS);
DECLARE_DELEGATE(FOnInputTriggeredA);
DECLARE_DELEGATE(FOnInputTriggeredD);
DECLARE_DELEGATE_OneParam(FOnInputTriggeredWheel, float);

class UInputAction;

UCLASS()
class FARMPROJECT_API AFPMainController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AFPMainController();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputAction> KeyW;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputAction> KeyA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputAction> KeyS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputAction> KeyD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputAction> MouseWheel;

	FOnInputTriggeredW OnInputTriggeredW;
	FOnInputTriggeredS OnInputTriggeredS;
	FOnInputTriggeredA OnInputTriggeredA;
	FOnInputTriggeredD OnInputTriggeredD;
	FOnInputTriggeredWheel OnInputTriggeredWheel;

protected:
	UFUNCTION()
	void OnInputStartedW();
	UFUNCTION()
	void OnInputStartedA();
	UFUNCTION()
	void OnInputStartedS();
	UFUNCTION()
	void OnInputStartedD();
	
	UFUNCTION()
	void OnInputStartedWheel(const FInputActionValue &InputValue);


protected:
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;

	virtual void BeginPlay();

private:
	bool bIsTouch;
};


