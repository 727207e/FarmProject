// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/FPSingleTon.h"
#include "Kismet/GameplayStatics.h"
#include "Internationalization/Internationalization.h"
#include "Info/NameDefine.h"
#include "GameSystem/FPGameSave.h"
#include "GameSystem/Data/ItemDataBase.h"
#include "GameSystem/Data/BuildingItemData.h"
#include "GameSystem/Data/SeedDataBase.h"
#include "GameSystem/Data/SaveDataStructForm/InvenSaveForm.h"
#include "GameSystem/Data/SaveDataStructForm/FieldSaveForm.h"
#include "GameSystem/Building/FPBuilding.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"


UFPSingleTon::UFPSingleTon()
{
	static ConstructorHelpers::FObjectFinder<USoundMix> SoundMixObj(TEXT("/Game/Data/Sound/GameSoundMix.GameSoundMix"));
	if (SoundMixObj.Succeeded())
	{
		SoundMix = SoundMixObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundClass> MusicSoundObj(TEXT("/Game/Data/Sound/MusicSoundClass.MusicSoundClass"));
	if (MusicSoundObj.Succeeded())
	{
		MusicSound = MusicSoundObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundClass> SFXSoundObj(TEXT("/Game/Data/Sound/SFXSoundClass.SFXSoundClass"));
	if (SFXSoundObj.Succeeded())
	{
		SFXSound = SFXSoundObj.Object;
	}

	static ConstructorHelpers::FClassFinder<UFPGameSave> SaveGameClassObj(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/GameSystem/Level/BP_FPGameSave.BP_FPGameSave_C'"));
	if (SaveGameClassObj.Succeeded())
	{
		SaveGameSubclass = SaveGameClassObj.Class;
	}
}

UFPSingleTon& UFPSingleTon::Get()
{
	UFPSingleTon* Singleton = Cast<UFPSingleTon>(GEngine->GameSingleton);
	if (Singleton != nullptr)
	{
		return *Singleton;
	}
	else
	{
		return *NewObject<UFPSingleTon>();
	}
}

void UFPSingleTon::SetMusicValue(UObject* TargetWorld, float value)
{
	if (nullptr == SaveGameREF)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Can't Find FPGameSave"), *FString(__FUNCTION__));
		return;
	}

	SaveGameREF->MusicValue = value;

	UGameplayStatics::SetSoundMixClassOverride(TargetWorld, SoundMix, MusicSound, value, 1.0f, 1.0f, true);
	UGameplayStatics::PushSoundMixModifier(TargetWorld, SoundMix);
	UGameplayStatics::SaveGameToSlot(SaveGameREF, SAVEGAME_NAME, 0);
}

void UFPSingleTon::SetSFXValue(UObject* TargetWorld, float value)
{
	if (nullptr == SaveGameREF)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Can't Find FPGameSave"), *FString(__FUNCTION__));
		return;
	}

	SaveGameREF->SFXValue = value;

	UGameplayStatics::SetSoundMixClassOverride(TargetWorld, SoundMix, SFXSound, value, 1.0f, 1.0f, true);
	UGameplayStatics::PushSoundMixModifier(TargetWorld, SoundMix);
	UGameplayStatics::SaveGameToSlot(SaveGameREF, SAVEGAME_NAME, 0);
}

void UFPSingleTon::SetLanguageValue(UObject* TargetWorld, ELanguageType value)
{
	if (nullptr == SaveGameREF)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Can't Find FPGameSave"), *FString(__FUNCTION__));
		return;
	}

	SaveGameREF->LanguageValue = value;
	
	UGameplayStatics::SaveGameToSlot(SaveGameREF, SAVEGAME_NAME, 0);
	FInternationalization::Get().SetCurrentCulture(GetLangStringValue(value));
}

void UFPSingleTon::SaveInventory(TArray<TObjectPtr<UItemDataBase>> TargetArray)
{
	for (TObjectPtr<UItemDataBase> Target : TargetArray)
	{
		FInvenSaveForm SaveForm;
		SaveForm.Id = Target->Id;
		SaveForm.CurrentCount = Target->CurrentCount;
		if(Target->IsA<UBuildingItemData>()) SaveForm.ItemForm = 1;
		else if(Target->IsA<USeedDataBase>()) SaveForm.ItemForm = 2;

		SaveGameREF->ItemInvenSaveArray.Add(SaveForm);
	}

	UGameplayStatics::SaveGameToSlot(SaveGameREF, SAVEGAME_NAME, 0);
}

void UFPSingleTon::SaveField(TArray<TObjectPtr<class AFPBuilding>> TargetArray)
{
	for (TObjectPtr<AFPBuilding> Target : TargetArray)
	{
		FFieldSaveForm SaveForm;
		SaveForm.Id = Target->BuildingData->Id;
		SaveForm.Transform = Target->GetTransform();
		SaveForm.Date = Target->GetStartTime();
		if (Target->IsA<AFPBuilding>()) SaveForm.ItemForm = 1;

		if (SaveGameREF->FieldSaveArray.Find(SaveForm) == INDEX_NONE)
		{
			SaveGameREF->FieldSaveArray.Add(SaveForm);
		}
	}

	UGameplayStatics::SaveGameToSlot(SaveGameREF, SAVEGAME_NAME, 0);
}

void UFPSingleTon::LoadData()
{
	if (UGameplayStatics::DoesSaveGameExist(SAVEGAME_NAME, 0))
	{
		SaveGameREF = Cast<UFPGameSave>(UGameplayStatics::LoadGameFromSlot(SAVEGAME_NAME, 0));
		SetLanguageValue(GetWorld(), SaveGameREF->LanguageValue);
	}
	else
	{
		SaveGameREF = Cast<UFPGameSave>(UGameplayStatics::CreateSaveGameObject(SaveGameSubclass));
	}
}

FString UFPSingleTon::GetLangStringValue(ELanguageType LangType)
{
	switch (LangType)
	{
		case ELanguageType::Korean:
			return "ko";
		case ELanguageType::English:
			return "en";
		default:
			return "en";
	}
}

TArray<FInvenSaveForm> UFPSingleTon::LoadInven()
{
	TArray<FInvenSaveForm> TargetArray;

	if (UGameplayStatics::DoesSaveGameExist(SAVEGAME_NAME, 0))
	{
		SaveGameREF = Cast<UFPGameSave>(UGameplayStatics::LoadGameFromSlot(SAVEGAME_NAME, 0));
		TargetArray = SaveGameREF->ItemInvenSaveArray;
	}
	else
	{
		SaveGameREF = Cast<UFPGameSave>(UGameplayStatics::CreateSaveGameObject(SaveGameSubclass));
	}
	return TargetArray;
}

TArray<FFieldSaveForm> UFPSingleTon::LoadField()
{
	TArray<FFieldSaveForm> TargetArray;

	if (UGameplayStatics::DoesSaveGameExist(SAVEGAME_NAME, 0))
	{
		SaveGameREF = Cast<UFPGameSave>(UGameplayStatics::LoadGameFromSlot(SAVEGAME_NAME, 0));
		TargetArray = SaveGameREF->FieldSaveArray;
	}
	else
	{
		SaveGameREF = Cast<UFPGameSave>(UGameplayStatics::CreateSaveGameObject(SaveGameSubclass));
	}

	return TargetArray;
}
