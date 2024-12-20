// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/FPMainController.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "GameSystem/Level/FPGameInstance.h"
#include "PaperSprite.h"
#include "GameSystem/Data/BuildingItemData.h"
#include "GameSystem/Data/SeedDataBase.h"

#include "GameSystem/FPSingleTon.h"

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

	///////테스트 코드 - 인벤토리에 강제로 아이템 주입 (GameInst 에서 생성하는 로직도 만들어야 할듯 - 삭제가 안됨)
	UE_LOG(LogTemp, Warning, TEXT("%s : Spawn Inventory Item"), TEXT(__FUNCTION__));
	UFPGameInstance* GameInst = Cast<UFPGameInstance>(GetGameInstance());

	GameInst->GameStart();

	TObjectPtr<UBuildingItemData> NewItemData = NewObject<UBuildingItemData>(this);
	NewItemData->Copy(*GameInst->GetBuildingArray()[1].Get());
	NewItemData->CurrentCount = 10;
	GameInst->AddItemToInventory(NewItemData);

	TObjectPtr<USeedDataBase> SeedTe = NewObject<USeedDataBase>(this);
	SeedTe->Copy(*GameInst->GetSeedArray()[1].Get());
	SeedTe->CurrentCount = 10;
	GameInst->AddItemToInventory(SeedTe);
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

void AFPMainController::OnInputStartedO()
{
	if (OnInputTriggeredO.IsBound())
	{
		OnInputTriggeredO.Execute();
	}
}

void AFPMainController::OnInputStartedMouseRight()
{
	if (OnInputTriggeredMouseRight.IsBound())
	{
		OnInputTriggeredMouseRight.Execute();
	}
}

void AFPMainController::OnInputStartedMouseLeft()
{
	if (OnInputTriggeredMouseLeft.IsBound())
	{
		OnInputTriggeredMouseLeft.Execute();
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
		EnhancedInputComponent->BindAction(KeyO, ETriggerEvent::Started, this, &AFPMainController::OnInputStartedO);
		EnhancedInputComponent->BindAction(MouseRightClick, ETriggerEvent::Started, this, &AFPMainController::OnInputStartedMouseRight);
		EnhancedInputComponent->BindAction(MouseLeftClick, ETriggerEvent::Started, this, &AFPMainController::OnInputStartedMouseLeft);
		EnhancedInputComponent->BindAction(MouseWheel, ETriggerEvent::Triggered, this, &AFPMainController::OnInputStartedWheel);
	}
}