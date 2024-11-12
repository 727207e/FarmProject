// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/FPCameraPawn.h"
#include "Camera/CameraComponent.h"
#include "GameSystem/FPMainController.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AFPCameraPawn::AFPCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called when the game starts or when spawned
void AFPCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
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

// Called every frame
void AFPCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}