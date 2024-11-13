// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"

UCLASS()
class FARMPROJECT_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//////////////////////////////////////////////////
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GridSize = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WorldGridSize = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SphereRadius = 100.0f;

	TArray<TObjectPtr<AActor>> GridArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGridCell> GridCellREF;

	float WorldOffset;

	void PopulateGrid();
	FVector GetClosestGridPosition(FVector InPoition);
};
