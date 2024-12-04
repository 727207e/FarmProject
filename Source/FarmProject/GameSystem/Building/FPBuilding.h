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
	virtual void ShowBuildingUI();

	virtual FDateTime GetStartTime() { return FDateTime(); }

public:
	UPROPERTY()
	TObjectPtr<class UBuildingItemData> BuildingData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USceneComponent> RootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> BuildingUIClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> BuildingUI;
};
