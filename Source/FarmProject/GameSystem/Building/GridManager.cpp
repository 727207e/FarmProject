// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Building/GridManager.h"
#include "GameSystem/Building/GridCell.h"

UGridManager::UGridManager()
{
}

void UGridManager::StartGrid()
{
    PopulateGrid();
}

void UGridManager::PopulateGrid()
{
    GridArray.Empty();

    float WorldOffset = (GridSize * WorldGridSize * 0.5f) - (WorldGridSize * 0.5f);

    for (int32 y = 0; y < GridSize; y++)
    {
        for (int32 x = 0; x < GridSize; x++)
        {
            FTransform resultTransform(FVector(LevelCenterX + WorldGridSize * x - WorldOffset, LevelCenterY + WorldGridSize * y - WorldOffset, 0.0f));

            if (GridCellREF == nullptr)
            {
                return;
            }

            FActorSpawnParameters SpawnParameters;
            SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

            GridArray.Add(GetWorld()->SpawnActor<AActor>(GridCellREF, resultTransform, SpawnParameters));
        }
    }
}


FVector UGridManager::GetClosestGridPosition(FVector InPoition)
{
    FCollisionShape SphereShape = FCollisionShape::MakeSphere(SphereRadius);
    TArray<FHitResult> HitResults; HitResults;

    bool bHit = GetWorld()->SweepMultiByChannel(
        HitResults,
        InPoition,
        InPoition,
        FQuat::Identity,
        ECC_WorldDynamic,
        SphereShape
    );

    if (bHit)
    {
        AActor* ClosestActor = nullptr;
        float ClosestDistanceSquared = TNumericLimits<float>::Max();

        for (const FHitResult& Hit : HitResults)
        {
            AActor* HitActor = Hit.GetActor();

            if (HitActor && HitActor->IsA<AGridCell>())
            {
                float DistanceSquared = FVector::DistSquared(InPoition, HitActor->GetActorLocation());
                if (DistanceSquared < ClosestDistanceSquared)
                {
                    ClosestDistanceSquared = DistanceSquared;
                    ClosestActor = HitActor;
                }
            }
        }

        if (ClosestActor)
        {
            return ClosestActor->GetActorLocation();
        }
    }
    return FVector::ZeroVector;
}
