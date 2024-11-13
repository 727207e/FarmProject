// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridManager.generated.h"

UCLASS(Blueprintable)
class FARMPROJECT_API UGridManager : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UGridManager();

	void StartGrid();
	FVector GetClosestGridPosition(FVector InPoition);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GridSize = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WorldGridSize = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SphereRadius = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LevelCenterX = 1500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LevelCenterY = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AGridCell> GridCellREF;

private:
	void PopulateGrid();

private:
	TArray<TObjectPtr<AActor>> GridArray;
};
