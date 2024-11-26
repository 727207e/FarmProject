// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Level/FPGameInstance.h"
#include "GameSystem/Data/FieldItemData.h"
#include "GameSystem/Data/ItemDataBase.h"
#include "GameSystem/Data/BuildingItemData.h"
#include "GameSystem/Data/SeedDataBase.h"
#include "GameSystem/Data/DataForm/BuildingDataCSV.h"
#include "GameSystem/Data/DataForm/SeedDataCSV.h"
#include "GameSystem/Data/DataForm/AnimalDataCSV.h"
#include "GameSystem/FPSingleTon.h"
#include "PaperSprite.h"

#define BuildingCSVNum 6
#define SeedCSVNum 9

UFPGameInstance::UFPGameInstance()
{
}

void UFPGameInstance::GameStart()
{
	LoadSeedCSVData();
	LoadBuildingCSVData();
	LoadAnimalCSVData();

	GetWorld()->GetTimerManager().SetTimer(TimeCheckHandle, this, &UFPGameInstance::TimeCheckTimer, 0.1f, true);

	UFPSingleTon::Get().LoadData();
	UFPSingleTon::Get().SaveInventory(ItemInventory);

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

	for (int32 i = 0; i < TimeCheckArray.Num(); ++i)
	{
		if (*Target < *TimeCheckArray[i])
		{
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
}

void UFPGameInstance::RemoveTimeCheckArray(TWeakObjectPtr<UFieldItemData> Target)
{
	TimeCheckArray.Remove(Target);
}

void UFPGameInstance::LoadBuildingCSVData()
{
	static const FString ContextString(TEXT("Item Context"));
	TArray<FName> RowNames = BuildingTable->GetRowNames();

	for (const FName& RowName : RowNames)
	{
		FBuildingDataCSV* RowData = BuildingTable->FindRow<FBuildingDataCSV>(RowName, ContextString);
		if (RowData)
		{
			UBuildingItemData* NewItem = NewObject<UBuildingItemData>();
			NewItem->Id = RowData->Id;
			NewItem->CurrentCount = 0;
			NewItem->MaxCount = RowData->MaxCount;
			NewItem->Image = LoadObject<UPaperSprite>(nullptr, *RowData->BuildingImagePath)->GetBakedTexture();
			NewItem->Name = FText::FromString(RowData->Name);
			NewItem->BlueprintObject = LoadClass<UObject>(nullptr, *RowData->BuildingBlueprintPath);

			//NewItem->BlueprintUI

			BuildingDataArray.Add(NewItem->Id, NewItem);
		}
	}
}

void UFPGameInstance::LoadSeedCSVData()
{
	static const FString ContextString(TEXT("Item Context"));
	TArray<FName> RowNames = SeedTable->GetRowNames();

	for (const FName& RowName : RowNames)
	{
		FSeedDataCSV* RowData = SeedTable->FindRow<FSeedDataCSV>(RowName, ContextString);
		if (RowData)
		{
			USeedDataBase* NewItem = NewObject<USeedDataBase>();
			NewItem->Id = RowData->Id;
			NewItem->CurrentCount = 0;
			NewItem->MaxCount = RowData->MaxCount;
			NewItem->Image = LoadObject<UPaperSprite>(nullptr, *RowData->SeedImagePath)->GetBakedTexture();
			NewItem->Name = FText::FromString(RowData->Name);
			NewItem->NeedMTime = RowData->MNeedTime;
			NewItem->NeedLTime = RowData->LNeedTime;
			NewItem->MStaticMesh = LoadObject<UStaticMesh>(nullptr, *RowData->SeedMMeshPath);
			NewItem->LStaticMesh = LoadObject<UStaticMesh>(nullptr, *RowData->SeedLMeshPath);

			//NewItem->BlueprintObject
			
			SeedDataArray.Add(NewItem->Id, NewItem);
		}
	}
}

void UFPGameInstance::LoadAnimalCSVData()
{
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
