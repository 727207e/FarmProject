// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UFPGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFPGameInstance();

	void AddInventory(TWeakObjectPtr<class UItemDataBase> item);

public:
	TArray<TWeakObjectPtr<class UBuildingItemData>> BuildingInventory;

protected:
	UPROPERTY()
	TArray<TWeakObjectPtr<class UItemDataBase>> ItemInventory;

	//...
};
