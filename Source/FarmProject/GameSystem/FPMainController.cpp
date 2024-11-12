// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/FPMainController.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"

AFPMainController::AFPMainController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AFPMainController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AFPMainController::OnInputStartedW()
{
	if (OnInputTriggeredW.IsBound())
	{
		OnInputTriggeredW.Execute();
	}
}

void AFPMainController::OnInputStartedA()
{
	if (OnInputTriggeredA.IsBound())
	{
		OnInputTriggeredA.Execute();
	}
}

void AFPMainController::OnInputStartedS()
{
	if (OnInputTriggeredS.IsBound())
	{
		OnInputTriggeredS.Execute();
	}
}

void AFPMainController::OnInputStartedD()
{
	if (OnInputTriggeredD.IsBound())
	{
		OnInputTriggeredD.Execute();
	}
}

void AFPMainController::OnInputStartedWheel(const FInputActionValue &InputValue)
{ 
	if (OnInputTriggeredWheel.IsBound()) 
	{ 
		OnInputTriggeredWheel.Execute(InputValue.Get<float>());
	}
}

void AFPMainController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(KeyW, ETriggerEvent::Triggered, this, &AFPMainController::OnInputStartedW);
		EnhancedInputComponent->BindAction(KeyS, ETriggerEvent::Triggered, this, &AFPMainController::OnInputStartedS);
		EnhancedInputComponent->BindAction(KeyA, ETriggerEvent::Triggered, this, &AFPMainController::OnInputStartedA);
		EnhancedInputComponent->BindAction(KeyD, ETriggerEvent::Triggered, this, &AFPMainController::OnInputStartedD);
		EnhancedInputComponent->BindAction(MouseWheel, ETriggerEvent::Triggered, this, &AFPMainController::OnInputStartedWheel);
	}
}