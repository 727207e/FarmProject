// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPSettingUI.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UFPSettingUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFPSettingUI(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnMusicSlideValueChange(float value);

	UFUNCTION()
	void OnSFXSlideValueChange(float value);

	UFUNCTION()
	void OnLanguageValueChange(FString SelectedItem, ESelectInfo::Type SelectionType);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class USlider> MusicSlider;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class USlider> SFXSlider;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UComboBoxString> ComboBoxLanguage;
};
