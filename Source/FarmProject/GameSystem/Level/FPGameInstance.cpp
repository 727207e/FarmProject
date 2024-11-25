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
		TWeakObjectPtr<UFieldItemData> TopData = TimeCheckArray[0];

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

void UFPGameInstance::AddTimeCheckArray(TWeakObjectPtr<UFieldItemData> Target)
{
	int32 InsertIndex = -1;

	UE_LOG(LogTemp, Log, TEXT("Current Target: %s"), *Target->GetName());

	for (int32 i = 0; i < TimeCheckArray.Num(); ++i)
	{

		UE_LOG(LogTemp, Log, TEXT("%d : %s"), i, *Target->GetName());
		if (*Target < *TimeCheckArray[i])
		{
			UE_LOG(LogTemp, Log, TEXT("Change"));
			InsertIndex = i;
			break;
		}
	}

	if (InsertIndex == -1)
	{
		if (TimeCheckArray.Num() > 0)
		{
			InsertIndex = TimeCheckArray.Num();
		}
		else
		{
			InsertIndex = 0;
		}
	}

	TimeCheckArray.Insert(Target, InsertIndex);

	UE_LOG(LogTemp, Log, TEXT("Result"));
	for (int32 i = 0; i < TimeCheckArray.Num(); ++i)
	{
		UE_LOG(LogTemp, Log, TEXT("%d : %s"), i, *TimeCheckArray[i]->GetName());
	}
}

void UFPGameInstance::RemoveTimeCheckArray(TWeakObjectPtr<UFieldItemData> Target)
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
