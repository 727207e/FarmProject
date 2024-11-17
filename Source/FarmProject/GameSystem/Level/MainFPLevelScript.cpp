// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Level/MainFPLevelScript.h"
#include "GameSystem/Building/GridManager.h"
#include "GameSystem/Building/ActorComponent/BuildableCheckComponent.h"
#include "GameSystem/Building/ActorComponent/ClickableComponent.h"
#include "Kismet/GameplayStatics.h"

AMainFPLevelScript::AMainFPLevelScript()
{
}

void AMainFPLevelScript::BeginPlay()
{
	Super::BeginPlay();

	if (GridManagerREF)
	{
        GridManager = NewObject<UGridManager>(this, GridManagerREF);
        if (GridManager)
        {
            GridManager->RegisterComponent();
        }
	}
}

void AMainFPLevelScript::ActiveBuildMode()
{
	bIsBuildModeEnable = true;
    if (GridManager)
    {
        GridManager->StartGrid();
    }
}

void AMainFPLevelScript::DeactiveBuildMode()
{
	bIsBuildModeEnable = false;
	if (GridManager)
	{
		GridManager->DeactivGrid();
	}
}

void AMainFPLevelScript::SetPlacementModeEnable(bool IsEnabled, TSubclassOf<UObject> TargetBuilding)
{
	if (bIsPlacementModeEnable == IsEnabled)
	{
		return;
	}

	bIsPlacementModeEnable = IsEnabled;
	PlaceableActorREF = TargetBuilding;

	if (bIsPlacementModeEnable && PlaceableActorREF)
	{
		FTransform SpawnTransform(FVector(0, 0, -1000000.0f));
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		PlaceableActor = GetWorld()->SpawnActor<AActor>(PlaceableActorREF, SpawnTransform, SpawnParameters);

		if (PlaceableActor && *BuildableCheckComponentREF)
		{
			UBuildableCheckComponent* BuildableCheck = NewObject<UBuildableCheckComponent>(PlaceableActor, BuildableCheckComponentREF);

			if (BuildableCheck)
			{
				BuildableCheck->RegisterComponent();
			}
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this]()
			{
				UpdatePlacement();
			}), 0.01f, true);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		if (PlaceableActor != nullptr)
		{
			PlaceableActor->Destroy();
		}
	}
}

void AMainFPLevelScript::SpawnBuilding()
{
	if (!bIsPlacementModeEnable)
	{
		return;
	}

	if (PlaceableActor && PlaceableActorREF)
	{
		UBuildableCheckComponent* TargetAC = PlaceableActor->GetComponentByClass<UBuildableCheckComponent>();
		if (TargetAC != nullptr && TargetAC->bIsPlacementValid)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AActor* BuildActor = GetWorld()->SpawnActor<AActor>(PlaceableActorREF, PlaceableActor->GetTransform(), SpawnParameters);

			if(BuildActor && *ClickableComponentREF)
			{
				UClickableComponent* Clickable= NewObject<UClickableComponent>(BuildActor, ClickableComponentREF);

				if (Clickable)
				{
					Clickable->RegisterComponent();
				}

				if (OnSpawnBuilding.IsBound())
				{
					OnSpawnBuilding.Execute();
				}
			}
		}
	}
}

void AMainFPLevelScript::UpdatePlacement()
{
	FVector2D MousePosition;
	if (PlayerCont == nullptr)
	{
		PlayerCont = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
		return;
	}

	if (PlayerCont->GetMousePosition(MousePosition.X, MousePosition.Y))
	{
		FVector WorldPosition;
		FVector WorldDirection;

		if (PlayerCont->DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldPosition, WorldDirection))
		{
			FVector Start = WorldPosition;
			FVector End = WorldPosition + (WorldDirection * 100000.0f);

			FHitResult HitResult;
			FCollisionQueryParams TraceParams(FName(TEXT("PlaceTrace")), true, this);
			TraceParams.bTraceComplex = false;
			TraceParams.bReturnPhysicalMaterial = false;
			TraceParams.AddIgnoredActor(this);

			bool bHit = GetWorld()->LineTraceSingleByChannel(
				HitResult,
				Start,
				End,
				ECC_GameTraceChannel1,
				TraceParams
			);

			if (bHit && PlaceableActor)
			{
				PlaceableActor->SetActorLocation(GridManager->GetClosestGridPosition(HitResult.Location));
			}
		}
	}
}