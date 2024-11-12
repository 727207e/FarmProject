// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/FPCameraPawn.h"
#include "Camera/CameraComponent.h"
#include "GameSystem/FPMainController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AFPCameraPawn::AFPCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
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
		FPCont->OnInputTriggeredWheel.BindUObject(this, &AFPCameraPawn::MoveTT);
	}
}

void AFPCameraPawn::MoveTT(float value)
{
	
	float ResultOrthoWidth = CameraComponent->OrthoWidth + (value * -100.0f);
	ResultOrthoWidth = FMath::Clamp(ResultOrthoWidth, 500.0f, 2000.0f);

	CameraComponent->OrthoWidth = ResultOrthoWidth;
}

// Called every frame
void AFPCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}