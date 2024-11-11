// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Setting/FPSettingUI.h"
#include "Components/Slider.h"
#include "Components/ComboBoxString.h"
#include "GameSystem/FPSingleTon.h"
#include "Kismet/GameplayStatics.h"
#include "Info/NameDefine.h"

#define MusicSliderUIName TEXT("MusicSlider_UI")
#define SFXSliderUIName TEXT("SFXSlider_UI")
#define ComboBoxLanguageUIName TEXT("ComboBoxLanguage_UI")

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

	ComboBoxLanguage = Cast<UComboBoxString>(GetWidgetFromName(ComboBoxLanguageUIName));
	if (ComboBoxLanguage)
	{
		for (int32 i = 0; i < StaticEnum<ELanguageType>()->NumEnums() - 1; ++i)
		{
			FString EnumName = UEnum::GetValueAsString(static_cast<ELanguageType>(i)); 
			EnumName.RemoveFromStart("ELanguageType::");
			ComboBoxLanguage->AddOption(EnumName);
		}

		ComboBoxLanguage->OnSelectionChanged.AddDynamic(this, &UFPSettingUI::OnLanguageValueChange);
	}

	MusicSlider->SetValue(UFPSingleTon::Get().GetMusicValue());
	SFXSlider->SetValue(UFPSingleTon::Get().GetSFXValue());

	UEnum* EnumPtr = StaticEnum<ELanguageType>();
	FString LangValue = EnumPtr->GetNameStringByValue(static_cast<int64>(UFPSingleTon::Get().GetLanguageValue()));
	ComboBoxLanguage->SetSelectedOption(LangValue);
}

void UFPSettingUI::OnMusicSlideValueChange(float value)
{
	UFPSingleTon::Get().SetMusicValue(GetWorld(), value);
}

void UFPSettingUI::OnSFXSlideValueChange(float value)
{
	UGameplayStatics::SpawnSound2D(this, ClickSound, 1.0f, 1.0f, 0.0f, SoundConcurrnecy.Get());
	UFPSingleTon::Get().SetSFXValue(GetWorld(), value);
}

void UFPSettingUI::OnLanguageValueChange(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (UEnum* EnumPtr = StaticEnum<ELanguageType>())
	{
		int32 EnumIndex = EnumPtr->GetIndexByName(FName(*SelectedItem));
		if (EnumIndex != INDEX_NONE)
		{
			ELanguageType Language = static_cast<ELanguageType>(EnumIndex);
			UFPSingleTon::Get().SetLanguageValue(GetWorld(), Language);

			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Invalid enum string or enum not found: %s"), *SelectedItem);
}