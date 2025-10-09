// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "FPBuildingButtonUI.generated.h"

class UBuildingItemData;
DECLARE_DELEGATE(FBuildingButtonActiveDelegate);
DECLARE_DELEGATE(FBuildingButtonDeactiveDelegate);

/**
 * 
 */

UCLASS()
class FARMPROJECT_API UFPBuildingButtonUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFPBuildingButtonUI(const FObjectInitializer& ObjectInitializer);
	void ButtonInit(const TObjectPtr<UBuildingItemData> Data);
	void DeactiveUI();

	void AddBuildingCount(int32 AddValue);
	void SetBuildingCount(int32 SetValue);

	UFUNCTION()
	void OnButtonClicked();

	FORCEINLINE FString GetBuildingName() { return BuildingNameText->GetText().ToString(); };

public:
	FBuildingButtonActiveDelegate OnBuildingButtonActive;
	FBuildingButtonDeactiveDelegate OnBuildingButtonDeactive;

protected:
	virtual void NativeConstruct() override;

	void OnButtonActive();
	void OnButtonDeactive();

	void SpawnBuilding();
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UButton> BuildingButton;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UTextBlock> CountText;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UTextBlock> BuildingNameText;

private:
	void FindUI();

private:
	TWeakObjectPtr<class UBuildingItemData> BuildingData;
	
	bool bIsOn = false;
};
