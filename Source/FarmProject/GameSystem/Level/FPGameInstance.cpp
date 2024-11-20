// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Level/FPGameInstance.h"
#include "GameSystem/Data/ItemDataBase.h"
#include "GameSystem/Data/BuildingItemData.h"

UFPGameInstance::UFPGameInstance()
{
}

void UFPGameInstance::AddInventory(TObjectPtr<UItemDataBase> item)
{
	bool bFind = false;
	for (TObjectPtr<UItemDataBase> AItem : ItemInventory)
	{
		if (AItem->Name.EqualTo(item->Name))
		{
			bFind = true;
			break;
		}
	}

	if (bFind)
	{
		EditInventoryItem(item, item->CurrentCount);
	}
	else
	{
		ItemInventory.Add(item);
		SortItem(item);
	}
}

void UFPGameInstance::EditInventoryItem(TObjectPtr<UItemDataBase> item, int32 Num)
{
	for (TObjectPtr<UItemDataBase> AItem : ItemInventory)
	{
		if (AItem->Name.EqualTo(item->Name))
		{
			AItem->CurrentCount += Num;

			if (AItem->CurrentCount <= 0)
			{
				ItemInventory.Remove(AItem);
			}

			SortItem(AItem);

			item->ConditionalBeginDestroy();
			item = nullptr;
			break;
		}
	}
}

void UFPGameInstance::SortItem(TObjectPtr<UItemDataBase> item)
{
	if (item->IsA(UBuildingItemData::StaticClass()))
	{
		TObjectPtr<UBuildingItemData> BuildingItem = Cast<UBuildingItemData>(item);
		if (item->CurrentCount <= 0)
		{
			BuildingInventory.Remove(BuildingItem);
		}
		else
		{
			BuildingInventory.Add(BuildingItem);
		}
	}
}
