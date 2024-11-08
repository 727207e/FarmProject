// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Setting/FPSettingUI.h"
#include "Components/Slider.h"
#include "GameSystem/FPSingleTon.h"

#define MusicSliderUIName TEXT("MusicSlider_UI")
#define SFXSliderUIName TEXT("SFXSlider_UI")

UFPSettingUI::UFPSettingUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFPSettingUI::NativeConstruct()
{
	Super::NativeConstruct();
		
	MusicSlider = Cast<USlider>(GetWidgetFromName(MusicSliderUIName));
	if (MusicSlider)
	{
		MusicSlider->OnValueChanged.AddDynamic(this, &UFPSettingUI::OnMusicSlideValueChange);
	}

	SFXSlider = Cast<USlider>(GetWidgetFromName(SFXSliderUIName));
	if (SFXSlider)
	{
		SFXSlider->OnValueChanged.AddDynamic(this, &UFPSettingUI::OnSFXSlideValueChange);
	}

	MusicSlider->SetValue(UFPSingleTon::Get().GetMusicValue());
	SFXSlider->SetValue(UFPSingleTon::Get().GetSFXValue());
}

void UFPSettingUI::OnMusicSlideValueChange(float value)
{
	UFPSingleTon::Get().SetMusicValue(GetWorld(), value);
}

void UFPSettingUI::OnSFXSlideValueChange(float value)
{
	UFPSingleTon::Get().SetSFXValue(GetWorld(), value);
}