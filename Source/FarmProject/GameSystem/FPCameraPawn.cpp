// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/FPCameraPawn.h"
#include "Camera/CameraComponent.h"
#include "GameSystem/FPMainController.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameSystem/Level/Interface/BuildManagerInterface.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/LevelScriptActor.h"
#include "UI/FPHud.h"

// Sets default values
AFPCameraPawn::AFPCameraPawn()
{
	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	SetRootComponent(rootComp);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	FloatMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovemet"));
}

void AFPCameraPawn::PossessedBy(AController* NewController)
{
	AFPMainController* FPCont = Cast<AFPMainController>(NewController);
	if (FPCont != nullptr)
	{
		FPCont->OnInputTriggeredWheel.BindUObject(this, &AFPCameraPawn::ZoomInOut);
		FPCont->OnInputTriggeredW.BindUObject(this, &AFPCameraPawn::MoveForward);
		FPCont->OnInputTriggeredS.BindUObject(this, &AFPCameraPawn::MoveBack);
		FPCont->OnInputTriggeredD.BindUObject(this, &AFPCameraPawn::MoveRight);
		FPCont->OnInputTriggeredA.BindUObject(this, &AFPCameraPawn::MoveLeft);

		AFPHud* MyHud = Cast<AFPHud>(FPCont->GetHUD());
		if (MyHud)
		{
			FPCont->OnInputTriggeredO.BindUObject(MyHud, &AFPHud::OpenStylingUI);
		}

		IBuildManagerInterface* MyBuildInterface = Cast<IBuildManagerInterface>(GetWorld()->GetLevelScriptActor());
		if (MyBuildInterface)
		{
			FPCont->OnInputTriggeredMouseRight.BindLambda([MyBuildInterface]()
				{
					MyBuildInterface->SpawnBuilding();
				});
		}
	}
}

void AFPCameraPawn::MoveForward()
{
	FVector WorldDirection = FVector(1.0f, 1.0f, 0.0f).GetSafeNormal();
	AddMovementInput(WorldDirection, 1.0, false);
}

void AFPCameraPawn::MoveBack()
{
	FVector WorldDirection = FVector(-1.0f, -1.0f, 0.0f).GetSafeNormal();
	AddMovementInput(WorldDirection, 1.0, false);
}

void AFPCameraPawn::MoveRight()
{
	FVector WorldDirection = FVector(-1.0f, 1.0f, 0.0f).GetSafeNormal();
	AddMovementInput(WorldDirection, 1.0, false);
}

void AFPCameraPawn::MoveLeft()
{
	FVector WorldDirection = FVector(1.0f, -1.0f, 0.0f).GetSafeNormal();
	AddMovementInput(WorldDirection, 1.0, false);
}

void AFPCameraPawn::ZoomInOut(float value)
{
	float ResultOrthoWidth = CameraComponent->OrthoWidth + (value * -100.0f);
	ResultOrthoWidth = FMath::Clamp(ResultOrthoWidth, 500.0f, 3000.0f);

	CameraComponent->OrthoWidth = ResultOrthoWidth;
}