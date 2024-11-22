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

protected:
	UPROPERTY()
	TObjectPtr<class UFieldItemData> CurData;

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
private:
	void ActiveUI();
	void DeactiveUI();
	void DataChangeUI();
};
