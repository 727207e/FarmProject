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

	void AddItemToInventory(TObjectPtr<class UItemDataBase> item);
	void EditItemCount(TObjectPtr<class UItemDataBase> item, int32 Num);

public:
	TArray<TObjectPtr<class UBuildingItemData>> BuildingInventory;
	TArray<TObjectPtr<class USeedDataBase>> SeedInventory;

protected:
	UPROPERTY()
	TArray<TObjectPtr<class UItemDataBase>> ItemInventory;

	//...

private:
	void SortItem(TObjectPtr<class UItemDataBase> item);
};
