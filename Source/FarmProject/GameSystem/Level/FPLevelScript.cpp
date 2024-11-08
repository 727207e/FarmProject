// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Level/FPLevelScript.h"
#include "GameSystem/FPSingleTon.h"
#include "UI/Setting/FPSettingUI.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"

AFPLevelScript::AFPLevelScript()
{
	static ConstructorHelpers::FClassFinder<UFPSettingUI> FPSettingUISubclassREF(TEXT("/Game/Blueprint/UI/WBP_SettingUI.WBP_SettingUI_C"));
	if (FPSettingUISubclassREF.Class)
	{
		UFPSettingUISubclass = FPSettingUISubclassREF.Class;
	}
}

void AFPLevelScript::BeginPlay()
{
	UGameplayStatics::SpawnSound2D(this, BackGroundSound);

	UFPSingleTon::Get().LoadAudioData();

	FPSettingUI = CreateWidget<UFPSettingUI>(GetWorld(), UFPSettingUISubclass);
	if (FPSettingUI)
	{
		FPSettingUI->AddToViewport();
	}
}
