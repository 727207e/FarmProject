// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Building/ActorComponent/BuildableCheckComponent.h"
#include "GameSystem/Building/GridCell.h"
#include "GameFramework/Actor.h"

UBuildableCheckComponent::UBuildableCheckComponent()
{
}

void UBuildableCheckComponent::BeginPlay()
{
	Super::BeginPlay();

    GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UBuildableCheckComponent::OnActorBeginOverlap);
    GetOwner()->OnActorEndOverlap.AddDynamic(this, &UBuildableCheckComponent::OnActorEndOverlap);
}

void UBuildableCheckComponent::OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    AGridCell* TargetGridCell = Cast<AGridCell>(OtherActor);
    if (TargetGridCell)
    {
        GridArray.Add(TargetGridCell);
    }

    if (!GridArray.IsEmpty())
    {
        bool bTrigger = true;
        for (AGridCell* Grid : GridArray)
        {
            EBuildState TargetState = Grid->GetBuildState();
            if (TargetState == EBuildState::OverlapBuilding)
            {
                bTrigger = false;
                break;
            }
        }

        UpdateState(bTrigger);
        bIsPlacementValid = bTrigger;
    }
}

void UBuildableCheckComponent::OnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    AGridCell* TargetGridCell = Cast<AGridCell>(OtherActor);
    if (TargetGridCell)
    {
        int32 TargetNum = GridArray.Find(TargetGridCell);
        GridArray.RemoveAt(TargetNum);
        TargetGridCell->UpdateGridState(EBuildState::Wait);
    }
}

void UBuildableCheckComponent::UpdateState(bool IsOverlapActors)
{
    TArray<UStaticMeshComponent*> StaticMeshComponents;
    GetOwner()->GetComponents<UStaticMeshComponent>(StaticMeshComponents);

    if (IsOverlapActors)
    {
        for (AGridCell* Grid : GridArray)
        {
            Grid->UpdateGridState(EBuildState::Buildable);
        }
        for (UStaticMeshComponent* MeshComponent : StaticMeshComponents)
        {
            MeshComponent->SetMaterial(0, BuilableMat);
        }
    }
    else
    {
        for (AGridCell* Grid : GridArray)
        {
            Grid->UpdateGridState(EBuildState::NotBuildable);
        }
        for (UStaticMeshComponent* MeshComponent : StaticMeshComponents)
        {
            MeshComponent->SetMaterial(0, NotBuilableMat);
        }
    }
}