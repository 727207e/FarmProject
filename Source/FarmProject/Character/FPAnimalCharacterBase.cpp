// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FPAnimalCharacterBase.h"

// Sets default values
AFPAnimalCharacterBase::AFPAnimalCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPAnimalCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPAnimalCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bNeedFollowMousePosition)
	{
		FollowMousePosition();
	}
}

void AFPAnimalCharacterBase::OnIconClickedDown()
{
	bNeedFollowMousePosition = true;
}

void AFPAnimalCharacterBase::FollowMousePosition()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		FVector2D MousePosition;
		PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

		FVector WorldLocation, WorldDirection;
		PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

		// Raycast 설정
		FHitResult HitResult;
		FVector Start = WorldLocation;
		FVector End = Start + (WorldDirection * 10000.0f);

		// 땅/바닥 전용 Collision Channel
		ECollisionChannel GroundChannel = ECC_WorldStatic; // 정적 월드 오브젝트

		if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
			GroundChannel))
		{
			// 정확히 땅 높이로 배치
			FVector TargetLocation = HitResult.Location;
	            
			// 캐릭터 바닥에 딱 붙이도록 Z 조정
			TargetLocation.Z += GetSimpleCollisionHalfHeight(); // 바닥에 딱 붙임
	            
			// 부드러운 이동 (선택사항)
			SetActorLocation(TargetLocation);
		}
		else
		{
			// 대체 위치 (카메라 앞)
			FVector FallbackLocation = WorldLocation + (WorldDirection * 500.0f);
			FallbackLocation.Z = 100.0f; // 기본 높이
			SetActorLocation(FallbackLocation);
		}
	}
}