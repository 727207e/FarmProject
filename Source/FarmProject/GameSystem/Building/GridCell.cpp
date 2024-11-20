// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Building/GridCell.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

AGridCell::AGridCell()
{
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	GridMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridMesh"));
	GridMesh->SetupAttachment(RootComp);
}

void AGridCell::ResetGridState()
{
	if (MyState == EBuildState::OverlapBuilding)
	{
		MyState = EBuildState::Wait;
		UpdateGridState(EBuildState::Wait);
	}
}

void AGridCell::UpdateGridState(EBuildState CurState)
{
	if (MyState == EBuildState::OverlapBuilding)
	{
		return;
	}

	switch (CurState)
	{
	case EBuildState::Wait:
		GridMesh->SetMaterial(0, NormalMat);
		break;
	case EBuildState::Buildable:
		GridMesh->SetMaterial(0, BuilableMat);
		break;
	case EBuildState::NotBuildable:
	case EBuildState::OverlapBuilding:
		GridMesh->SetMaterial(0, NotBuilableMat);
		break;
	default:
		break;
	}

	MyState = CurState;
}