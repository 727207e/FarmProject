// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPBuilding.generated.h"

UCLASS()
class FARMPROJECT_API AFPBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	AFPBuilding();

	void UpdateClickInfo();

	UFUNCTION()
	void ShowBuildingUI();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY()
	TObjectPtr<class UBuildingItemData> BuildingData;
};
