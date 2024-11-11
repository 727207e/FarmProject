// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameSystem/FPGameSave.h"
#include "Info/NameDefine.h"
#include "FPSingleTon.generated.h"

/**
 * 
 */

UCLASS()
class FARMPROJECT_API UFPSingleTon : public UObject
{
	GENERATED_BODY()
	
public:
	UFPSingleTon();
	static UFPSingleTon& Get();

	void SetMusicValue(UObject* TargetWorld, float value);
	void SetSFXValue(UObject* TargetWorld, float value);
	void SetLanguageValue(UObject* TargetWorld, ELanguageType value);

	FORCEINLINE float GetMusicValue() const { return SaveGameREF != nullptr ? SaveGameREF->MusicValue : 1.0f; }
	FORCEINLINE float GetSFXValue() const { return SaveGameREF != nullptr ? SaveGameREF->SFXValue : 1.0f; }
	FORCEINLINE ELanguageType GetLanguageValue() const { return SaveGameREF != nullptr ? SaveGameREF->LanguageValue : ELanguageType::Korean; }

	void LoadAudioData();
	void LoadLanguageData();

protected:
	UPROPERTY()
	TObjectPtr<class USoundMix> SoundMix;

	UPROPERTY()
	TObjectPtr<class USoundClass> MusicSound;

	UPROPERTY()
	TObjectPtr<class USoundClass> SFXSound;

	UPROPERTY()
	TObjectPtr<UFPGameSave> SaveGameREF;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class UFPGameSave> SaveGameSubclass;
};
