// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/FPMainController.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "GameSystem/Building/GridManager.h"
#include "GameSystem/Building/ActorComponent/BuildableCheckComponent.h"

AFPMainController::AFPMainController()
{
	PrimaryActorTick.bCanEverTick = true;
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

	SetPlacementModeEnable(true);
}

void AFPMainController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsPlacementModeEnable)
	{
		UpdatePlacement();
	}
}

void AFPMainController::SetPlacementModeEnable(bool IsEnabled)
{
	if (bIsPlacementModeEnable == IsEnabled)
	{
		return;
	}

	bIsPlacementModeEnable = IsEnabled;
	if (bIsPlacementModeEnable)
	{
		FTransform SpawnTransform(FVector(0,0,-1000000.0f));
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		PlaceableActor = GetWorld()->SpawnActor<AActor>(PlaceableActorREF, SpawnTransform, SpawnParameters);
		
		//여기서 PlaceableActor의 ClickableAC 를 삭제하는 로직이 있었음.
		if (PlaceableActor && *BuildableCheckComponentREF)
		{
			UBuildableCheckComponent* BuildableCheck = NewObject<UBuildableCheckComponent>(PlaceableActor, BuildableCheckComponentREF);

			if (BuildableCheck)
			{
				BuildableCheck->RegisterComponent();
			}
		}
	}
	else
	{
		if (PlaceableActor != nullptr)
		{
			PlaceableActor->Destroy();
		}
	}
}

void AFPMainController::SpawnBuilding()
{
	if (PlaceableActor != nullptr)
	{
		UBuildableCheckComponent* TargetAC = PlaceableActor->GetComponentByClass<UBuildableCheckComponent>();
		if (TargetAC != nullptr && TargetAC->bIsPlacementValid)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			GetWorld()->SpawnActor<AActor>(PlaceableActorREF, PlaceableActor->GetTransform(), SpawnParameters);
		}
	}
}

void AFPMainController::UpdatePlacement()
{
	FVector2D MousePosition;
	if (GetMousePosition(MousePosition.X, MousePosition.Y))
	{
		FVector WorldPosition;
		FVector WorldDirection;

		if (DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldPosition, WorldDirection))
		{
			FVector Start = WorldPosition;
			FVector End = WorldPosition + (WorldDirection * 100000.0f);

			FHitResult HitResult;
			FCollisionQueryParams TraceParams(FName(TEXT("PlaceTrace")), true, this);
			TraceParams.bTraceComplex = false;
			TraceParams.bReturnPhysicalMaterial = false;
			TraceParams.AddIgnoredActor(this->GetPawn());

			bool bHit = GetWorld()->LineTraceSingleByChannel(
				HitResult,
				Start,
				End,
				ECC_GameTraceChannel1,
				TraceParams
			);

			if (bHit && PlaceableActor)
			{
				AActor* Manager = UGameplayStatics::GetActorOfClass(GetWorld(), AGridManager::StaticClass());
				AGridManager* GM = Cast<AGridManager>(Manager);
				PlaceableActor->SetActorLocation(GM->GetClosestGridPosition(HitResult.Location));
			}
		}
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

void AFPMainController::OnInputStartedO()
{
	if (OnInputTriggeredO.IsBound())
	{
		OnInputTriggeredO.Execute();
	}
}

void AFPMainController::OnInputStartedMouseRight()
{
	SpawnBuilding();

	if (OnInputTriggeredMouseRight.IsBound())
	{
		//OnInputTriggeredMouseRight.Execute();
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
		EnhancedInputComponent->BindAction(MouseWheel, ETriggerEvent::Triggered, this, &AFPMainController::OnInputStartedWheel);
	}
}