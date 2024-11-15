// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPBuildingButtonUI.generated.h"

DECLARE_DELEGATE_OneParam(FBuildingButtonActiveDelegate, UFPBuildingButtonUI&);
DECLARE_DELEGATE_OneParam(FBuildingButtonDeactiveDelegate, UFPBuildingButtonUI&);

/**
 * 
 */

USTRUCT(BlueprintType)
struct FBuildingInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	FText BuildingName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	int32 BuildingCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	UTexture2D* Image;

	FBuildingInfo() : BuildingName(FText::GetEmpty()), BuildingCount(0), Image(nullptr) {}
	FBuildingInfo(FText Name, int32 Count, UTexture2D* image) 
		: BuildingName(Name), BuildingCount(Count), Image(image) {}
};



UCLASS()
class FARMPROJECT_API UFPBuildingButtonUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFPBuildingButtonUI(const FObjectInitializer& ObjectInitializer);
	void ButtonInit(FBuildingInfo BuildingInfo);

public:
	FBuildingButtonActiveDelegate OnBuildingButtonActive;
	FBuildingButtonDeactiveDelegate OnBuildingButtonDeactive;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonClicked();

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
	bool bIsOn = false;
};
