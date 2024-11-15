// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Building/FPBuildingButtonUI.h"
#include "FPStylingUI.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UFPStylingUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFPStylingUI(const FObjectInitializer& ObjectInitializer);

	void ActiveStylingUI();
	void DeactiveStylingUI();

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UScrollBox> BuildingScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UFPBuildingButtonUI> BuildingButtonREF;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<class UFPBuildingButtonUI>> BuildingButtonArray;

private:
	void GetInventory();
	void GenerateBuildingButtonUI();

private:
	TObjectPtr<class AMainFPLevelScript> FPLevel;
	TArray<FBuildingInfo> InfoArray;
	//UFPBuildingButtonUI가 가지고 있는 데이터 가져오기
};
