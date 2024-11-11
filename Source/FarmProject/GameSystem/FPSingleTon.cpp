// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/FPSingleTon.h"
#include "Kismet/GameplayStatics.h"
#include "Info/NameDefine.h"
#include "GameSystem/FPGameSave.h"
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

	static ConstructorHelpers::FClassFinder<UFPGameSave> SaveGameClassObj(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/GameSystem/BP_FPGameSave.BP_FPGameSave_C'"));
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
}

void UFPSingleTon::LoadAudioData()
{
	if (UGameplayStatics::DoesSaveGameExist(SAVEGAME_NAME, 0))
	{
		SaveGameREF = Cast<UFPGameSave>(UGameplayStatics::LoadGameFromSlot(SAVEGAME_NAME, 0));
		if(nullptr == SaveGameREF)
		{
			UE_LOG(LogTemp, Error, TEXT("%s : Can't Cast FPGameSave"), *FString(__FUNCTION__));
		}
	}
	else
	{
		SaveGameREF = Cast<UFPGameSave>(UGameplayStatics::CreateSaveGameObject(SaveGameSubclass));
	}
}

void UFPSingleTon::LoadLanguageData()
{
	if (UGameplayStatics::DoesSaveGameExist(SAVEGAME_NAME, 0))
	{
		SaveGameREF = Cast<UFPGameSave>(UGameplayStatics::LoadGameFromSlot(SAVEGAME_NAME, 0));
		if (nullptr == SaveGameREF)
		{
			UE_LOG(LogTemp, Error, TEXT("%s : Can't Cast FPGameSave"), *FString(__FUNCTION__));
		}
	}
	else
	{
		SaveGameREF = Cast<UFPGameSave>(UGameplayStatics::CreateSaveGameObject(SaveGameSubclass));
	}
}