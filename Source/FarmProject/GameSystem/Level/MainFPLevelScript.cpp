// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Level/MainFPLevelScript.h"
#include "GameSystem/Building/GridManager.h"
#include "GameSystem/Building/ActorComponent/BuildableCheckComponent.h"
#include "GameSystem/Building/ActorComponent/ClickableComponent.h"
#include "GameSystem/Data/BuildingItemData.h"
#include "GameSystem/Building/FPBuilding.h"
#include "Kismet/GameplayStatics.h"
#include "GameSystem/Level/FPGameInstance.h"
#include "GameSystem/FPSingleTon.h"
#include "GameSystem/Building/GridCell.h"

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


void AMainFPLevelScript::SetPlacementModeEnable(bool IsEnabled, TObjectPtr<UBuildingItemData> TargetData)
{
	if (bIsPlacementModeEnable == IsEnabled)
	{
		return;
	}

	bIsPlacementModeEnable = IsEnabled;
	TargetDataREF = TargetData;

	if (bIsPlacementModeEnable && TargetDataREF)
	{
		FTransform SpawnTransform(FVector(0, 0, -1000000.0f));
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		PlaceableActor = GetWorld()->SpawnActor<AActor>(TargetDataREF->BlueprintObject, SpawnTransform, SpawnParameters);

		if (PlaceableActor && *BuildableCheckComponentREF)
		{
			UBuildableCheckComponent* BuildableCheck = NewObject<UBuildableCheckComponent>(PlaceableActor, BuildableCheckComponentREF);

			if (BuildableCheck)
			{
				PlaceableActor->AddInstanceComponent(BuildableCheck);
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

	if (PlaceableActor && TargetDataREF)
	{
		UBuildableCheckComponent* TargetAC = PlaceableActor->GetComponentByClass<UBuildableCheckComponent>();
		if (TargetAC != nullptr && TargetAC->bIsPlacementValid)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AFPBuilding* BuildActor = GetWorld()->SpawnActor<AFPBuilding>(TargetDataREF->BlueprintObject, PlaceableActor->GetTransform(), SpawnParameters);
			BuildActor->BuildingData = TargetDataREF;

			if(BuildActor && *ClickableComponentREF)
			{
				TArray<AActor*> OverlappingActors;
				BuildActor->GetOverlappingActors(OverlappingActors, AGridCell::StaticClass());

				for (AActor* Actor : OverlappingActors)
				{
					if (AGridCell* GridCellActor = Cast<AGridCell>(Actor))
					{
						GridCellActor->UpdateGridState(EBuildState::OverlapBuilding);
					}
				}

				UClickableComponent* Clickable= NewObject<UClickableComponent>(BuildActor, ClickableComponentREF);

				if (Clickable)
				{
					BuildActor->AddInstanceComponent(Clickable);
					Clickable->RegisterComponent();

					BuildActor->UpdateClickInfo();

					FieldArray.Add(BuildActor);
					SaveCurLevel();
				}

				if (OnSpawnBuilding.IsBound())
				{
					OnSpawnBuilding.Execute();
				}
			}
		}
	}
}

void AMainFPLevelScript::SaveCurLevel()
{
	UFPGameInstance* GameIns = Cast<UFPGameInstance>(GetWorld()->GetGameInstance());
	if (GameIns)
	{
		GameIns->SaveGame();
	}

	UFPSingleTon::Get().SaveField(FieldArray);
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