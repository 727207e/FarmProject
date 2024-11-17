// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Level/FPGameInstance.h"
#include "GameSystem/Data/ItemDataBase.h"
#include "GameSystem/Data/BuildingItemData.h"

UFPGameInstance::UFPGameInstance()
{
}

void UFPGameInstance::AddInventory(TWeakObjectPtr<class UItemDataBase> item)
{
	ItemInventory.Add(item);

	if (item->IsA(UBuildingItemData::StaticClass()))
	{
		TObjectPtr<UBuildingItemData> BuildingItem = Cast<UBuildingItemData>(item);
		BuildingInventory.Add(BuildingItem);
	}
}
