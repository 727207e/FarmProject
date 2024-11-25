// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPDownInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UFPDownInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFPDownInfoWidget(const FObjectInitializer& ObjectInitializer);
	void CurUISetting(TObjectPtr<class UFieldItemData> FieldData);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SeedSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void SeedOpening();

	UFUNCTION()
	void SettingRemainTimeText();

protected:
	UPROPERTY()
	TWeakObjectPtr<class UFieldItemData> CurData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UImage> PropertyUI;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UImage> MainImageUI;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UTextBlock> TitleTextUI;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UTextBlock> ContentTextUI;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UButton> SeedButtonUI;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UComboBoxString> SeedComboBoxUI;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UTextBlock> SeedComboBoxHintTextUI;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UFPGameInstance> GameIns;
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<class USeedDataBase>> SeedInven;

private:
	void ActiveUI();
	void DeactiveUI();
	void DataChangeUI();

private:
	FTimerHandle PlantTimerHandle;
};
