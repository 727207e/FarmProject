// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Building/GridManager.h"
#include "GameSystem/Building/GridCell.h"

// Sets default values
AGridManager::AGridManager()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
    Super::BeginPlay();

    PopulateGrid();
}

// Called every frame
void AGridManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AGridManager::PopulateGrid()
{
    GridArray.Empty();

    WorldOffset = (GridSize * WorldGridSize * 0.5f) - (WorldGridSize * 0.5f);
    FVector Pos = GetActorLocation();

    for (int32 y = 0; y < GridSize; y++)
    {
        for (int32 x = 0; x < GridSize; x++)
        {
            FTransform resultTransform(FVector(Pos.X + WorldGridSize * x - WorldOffset, Pos.Y + WorldGridSize * y - WorldOffset, 0.0f));

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

FVector AGridManager::GetClosestGridPosition(FVector InPoition)
{
    FCollisionShape SphereShape = FCollisionShape::MakeSphere(SphereRadius);
    TArray<FHitResult> HitResults; HitResults;

    // Sphere Trace ½ÇÇà
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
