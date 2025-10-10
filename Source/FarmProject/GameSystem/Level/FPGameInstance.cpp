// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Level/FPGameInstance.h"

#include "GameSystem/Data/FieldItemData.h"
#include "GameSystem/Data/ItemDataBase.h"
#include "GameSystem/Data/BuildingItemData.h"
#include "GameSystem/Data/SeedDataBase.h"
#include "GameSystem/Data/DataForm/BuildingDataCSV.h"
#include "GameSystem/Data/DataForm/SeedDataCSV.h"
#include "GameSystem/Data/DataForm/AnimalDataCSV.h"
#include "GameSystem/Data/SaveDataStructForm/InvenSaveForm.h"
#include "GameSystem/Data/SaveDataStructForm/FieldSaveForm.h"
#include "GameSystem/Building/FPBuilding.h"
#include "GameSystem/FPSingleTon.h"
#include "GameSystem/Level/MainFPLevelScript.h"
#include "PaperSprite.h"
#include "GameSystem/Building/ActorComponent/ClickableComponent.h"
#include "GameSystem/Data/AnimalDataBase.h"


//TODO : 데이터 기록 방식을 FString에서 TSoftObjectPtr 로 변경할 것 (Seed, Building)
//TODO : 바로 로드하는 방식 말고, 필요에 의해 로드해야할때 비동기 로드로 로드할 것 (지금은 모두 들고있는 형태)
//TODO : 로드하는 클래스를 따로 만들것 (Subsystem으로 분리 필요)
//TODO : 데이터를 통으로 복사해서 가져오지 말고 고정된 데이터는 두고, 가변되는 데이터(갯수, 위치, 시간 등)만 인벤에 넣기

//TODO : 치트 매니저로 이동
static FAutoConsoleCommand CVarAddItemCheat(
	TEXT("AddItem"),
	TEXT("AddItem <ID> <Type> <Amount> - Adds an item to the inventory via UFPGameInstance.\n")
	TEXT("ID: Item identifier (int, >0)\n")
	TEXT("Amount: Number of items (int, >0)")
	TEXT("Type: Item type (int, >=0)\n"),
	FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args)
	{
		for (TObjectIterator<UWorld> It; It; ++It)
		{
			UWorld* World = *It;
			if (World && World->IsGameWorld())
			{
				if (UFPGameInstance* GameIns = Cast<UFPGameInstance>(World->GetGameInstance()))
				{
					// FInvenSaveForm 구성
					int32 ID = FCString::Atoi(*Args[0]);
					int32 Amount = FCString::Atoi(*Args[1]);
					int32 TypeInt = FCString::Atoi(*Args[2]);
					
					// Type을 EItemForm으로 변환
					EItemForm Type;
					if (TypeInt == 1)
					{
						Type = EItemForm::Building;
					}
					else if (TypeInt == 2)
					{
						Type = EItemForm::Seed;
					}
					else if (TypeInt == 3)
					{
						Type = EItemForm::Animal;
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Invalid Type: %d. Use 1 (Building), 2 (Seed), 3 (Animal)"), TypeInt);
						return;
					}
					
					FInvenSaveForm InvenSave;
					InvenSave.Id = ID;
					InvenSave.ItemForm = Type;
					InvenSave.CurrentCount = Amount;

					// AddInven 메서드 직접 호출
					GameIns->AddInven(InvenSave);

					UE_LOG(LogTemp, Log, TEXT("Add Inven Success"));
				}
			}
		}
	}),
	ECVF_Default
);

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
	LoadInven();
	LoadField();
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

void UFPGameInstance::AddInven(const FInvenSaveForm& InFormData)
{
	TObjectPtr<UItemDataBase> Item;
	switch (InFormData.ItemForm)
	{
	case EItemForm::Animal:
		Item = NewObject<UAnimalDataBase>(GetWorld());
		Item->Copy(*GetAnimalArray()[InFormData.Id].Get());
		break;

	case EItemForm::Building:
		Item = NewObject<UBuildingItemData>(GetWorld());
		Item->Copy(*GetBuildingArray()[InFormData.Id].Get());
		break;

	case EItemForm::Seed:
		Item = NewObject<USeedDataBase>(GetWorld());
		Item->Copy(*GetSeedArray()[InFormData.Id].Get());
		break;

	default:
		UE_LOG(LogTemp, Error, TEXT("%hs : Can't Define ItemForm"), __func__);
		break;
	}
		
	if (Item == nullptr)
	{
		return;
	}
	else
	{
		Item->CurrentCount = InFormData.CurrentCount;
		AddItemToInventory(Item);
	}
}

void UFPGameInstance::SaveGame()
{
	UFPSingleTon::Get().SaveInventory(ItemInventory);
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

			SeedDataArray.Add(NewItem->Id, NewItem);
		}
	}
}

void UFPGameInstance::LoadAnimalCSVData()
{
	static const FString ContextString(TEXT("Item Context"));
	TArray<FName> RowNames = AnimalTable->GetRowNames();

	for (const FName& RowName : RowNames)
	{
		FAnimalDataCSV* RowData = AnimalTable->FindRow<FAnimalDataCSV>(RowName, ContextString);
		if (RowData)
		{
			UAnimalDataBase* NewItem = NewObject<UAnimalDataBase>();
			NewItem->Id = RowData->Id;
			NewItem->CurrentCount = 0;
			NewItem->MaxCount = RowData->MaxCount;
			NewItem->Image = RowData->AnimalImagePath.LoadSynchronous();
			NewItem->Name = FText::FromString(RowData->Name);
			UBlueprint* LoadedBlueprint = RowData->AnimalBluePrintPath.LoadSynchronous();
			NewItem->BlueprintObject = LoadedBlueprint ? LoadedBlueprint->GeneratedClass : nullptr;

			AnimalDataArray.Add(NewItem->Id, NewItem);
		}
	}
}

void UFPGameInstance::LoadInven()
{
	TArray<FInvenSaveForm> LoadInvenArray = UFPSingleTon::Get().LoadInven();
	for (FInvenSaveForm FormData : LoadInvenArray)
	{
		AddInven(FormData);
	}
}

void UFPGameInstance::LoadField()
{
	TArray<FFieldSaveForm> LoadInvenArray = UFPSingleTon::Get().LoadField();
	for (FFieldSaveForm FormData : LoadInvenArray)
	{
		TObjectPtr<AFPBuilding> Item;
		if (FormData.ItemForm == 1)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			TObjectPtr<UBuildingItemData> BuildingData = BuildingDataArray.FindRef(FormData.Id);

			AFPBuilding* BuildActor = GetWorld()->SpawnActor<AFPBuilding>(BuildingData->BlueprintObject, FormData.Transform, SpawnParameters);
			BuildActor->BuildingData = BuildingData;

			if (BuildActor && *ClickableComponentREF)
			{
				UClickableComponent* Clickable = NewObject<UClickableComponent>(BuildActor, ClickableComponentREF);

				if (Clickable)
				{
					BuildActor->AddInstanceComponent(Clickable);
					Clickable->RegisterComponent();

					BuildActor->UpdateClickInfo();

					AMainFPLevelScript* Ma = Cast<AMainFPLevelScript>(GetWorld()->GetLevelScriptActor());
					Ma->AddField(BuildActor);
				}
			}
		}

		if (Item == nullptr)
		{
			continue;
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
