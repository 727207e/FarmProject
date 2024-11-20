// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Building/ActorComponent/ClickableComponent.h"
#include "GameSystem/Building/GridCell.h"
#include "GameSystem/Level/MainFPLevelScript.h"

UClickableComponent::UClickableComponent()
{
}

void UClickableComponent::OnClick()
{

}

void UClickableComponent::OnDestroySelf()
{
	for (TObjectPtr<class AGridCell> GridCellActor  : OverlappedGridSet)
	{
		GridCellActor->ResetGridState();
	}

	if (GetOwner())
	{
		GetOwner()->Destroy();
	}
}


void UClickableComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OverlappingActors;
	GetOwner()->GetOverlappingActors(OverlappingActors, AGridCell::StaticClass());

	for (AActor* Actor : OverlappingActors)
	{
		if (AGridCell* GridCellActor = Cast<AGridCell>(Actor))
		{
			OverlappedGridSet.Add(GridCellActor);
			GridCellActor->UpdateGridState(EBuildState::OverlapBuilding);
		}
	}
}