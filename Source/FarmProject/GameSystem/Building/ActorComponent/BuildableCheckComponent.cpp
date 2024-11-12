// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Building/ActorComponent/BuildableCheckComponent.h"
#include "GameFramework/Actor.h"

UBuildableCheckComponent::UBuildableCheckComponent()
{
}

void UBuildableCheckComponent::BeginPlay()
{
	Super::BeginPlay();

    GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UBuildableCheckComponent::OnActorBeginOverlap);
    GetOwner()->OnActorEndOverlap.AddDynamic(this, &UBuildableCheckComponent::OnActorEndOverlap);
    UpdateState();
}

void UBuildableCheckComponent::OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    UpdateState();
}

void UBuildableCheckComponent::OnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    UpdateState();
}

void UBuildableCheckComponent::UpdateState()
{
	TSet<AActor*> OverlapActors;
	GetOwner()->GetOverlappingActors(OverlapActors, AActor::StaticClass());
    bIsPlacementValid = OverlapActors.IsEmpty();
	
    TArray<UStaticMeshComponent*> StaticMeshComponents;
    GetOwner()->GetComponents<UStaticMeshComponent>(StaticMeshComponents);
    for (UStaticMeshComponent* MeshComponent : StaticMeshComponents)
    {
        if (bIsPlacementValid)
        {
            MeshComponent->SetMaterial(0, BuilableMat);
        }
        else
        {
            MeshComponent->SetMaterial(0, NotBuilableMat);
        }
    }
}
