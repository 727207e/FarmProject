// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SeedDataCSV.generated.h"

USTRUCT(BlueprintType)
struct FSeedDataCSV : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSeedDataCSV() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 Id = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 MaxCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 MNeedTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 LNeedTime = 0;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString SeedMMeshPath = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString SeedLMeshPath = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString SeedImagePath = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString SeedResultPath = "";
};