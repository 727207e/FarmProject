// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BuildingDataCSV.generated.h"

USTRUCT(BlueprintType)
struct FBuildingDataCSV : public FTableRowBase
{
	GENERATED_BODY()

public:
	FBuildingDataCSV() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 Id = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 MaxCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString BuildingUIPath = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString BuildingBlueprintPath = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString BuildingImagePath = "";
};