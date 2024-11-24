// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Level/FPGameInstance.h"
#include "GameSystem/Data/FieldItemData.h"
#include "GameSystem/Data/ItemDataBase.h"
#include "GameSystem/Data/BuildingItemData.h"
#include "GameSystem/Data/SeedDataBase.h"

UFPGameInstance::UFPGameInstance()
{
}

void UFPGameInstance::GameStart()
{
	GetWorld()->GetTimerManager().SetTimer(TimeCheckHandle, this, &UFPGameInstance::TimeCheckTimer, 0.1f, true);
}

void UFPGameInstance::AddItemToInventory(TObjectPtr<UItemDataBase> item)
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
		EditItemCount(item, item->CurrentCount);
	}
	else
	{
		ItemInventory.Add(item);
		SortItem(item);
	}
}

void UFPGameInstance::EditItemCount(TObjectPtr<UItemDataBase> item, int32 Num)
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

void UFPGameInstance::TimeCheckTimer()
{
	FDateTime Now = FDateTime::Now();

	while (!TimeCheckArray.IsEmpty())
	{
		TObjectPtr<UFieldItemData> TopData = TimeCheckArray[0];

		UE_LOG(LogTemp, Log, TEXT("Current State: %s"), *TopData->NextNeedTime.ToString());

		if (TopData->NextNeedTime < Now)
		{
			TopData->NextState();
			TimeCheckArray.Remove(TopData);

			if (TopData->ECurState != EFieldState::L)
			{
				AddTimeCheckArray(TopData);
			}
		}
		else
		{
			break;
		}
	}
}

void UFPGameInstance::AddTimeCheckArray(TObjectPtr<UFieldItemData> Target)
{
	int32 InsertIndex = 0;
	for (int32 i = 0; i < TimeCheckArray.Num(); ++i)
	{
		if (Target < TimeCheckArray[i])
		{
			InsertIndex = i;
			break;
		}
	}

	if (InsertIndex == 0 && TimeCheckArray.Num() > 0 && !(Target < TimeCheckArray.Last()))
	{
		InsertIndex = TimeCheckArray.Num();
	}

	TimeCheckArray.Insert(Target, InsertIndex);
}

void UFPGameInstance::RemoveTimeCheckArray(TObjectPtr<class UFieldItemData> Target)
{
	TimeCheckArray.Remove(Target);
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
	else if (item->IsA(USeedDataBase::StaticClass()))
	{
		TObjectPtr<USeedDataBase> SeedItem = Cast<USeedDataBase>(item);
		if (item->CurrentCount <= 0)
		{
			SeedInventory.Remove(SeedItem);
		}
		else
		{
			SeedInventory.Add(SeedItem);
		}
	}
}
