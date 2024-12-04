// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AnimalDataCSV.generated.h"

USTRUCT(BlueprintType)
struct FAnimalDataCSV : public FTableRowBase
{
	GENERATED_BODY()

public:
	FAnimalDataCSV() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 Id = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 MaxCount = 0;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString BuildingUIPath = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString BuildingMeshPath = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString BuildingImagePath = "";
};