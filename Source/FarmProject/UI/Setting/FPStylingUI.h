// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Building/FPBuildingButtonUI.h"
#include "UI/FPUserWidget.h"
#include "FPStylingUI.generated.h"

class UBuildingItemData;
/**
 * 
 */
UCLASS()
class FARMPROJECT_API UFPStylingUI : public UFPUserWidget
{
	GENERATED_BODY()
	
public:
	UFPStylingUI(const FObjectInitializer& ObjectInitializer);

	virtual void ActiveUI() override;
	virtual void DeactiveUI() override;
	UFUNCTION()
	void ActiveEditBuildMode(class UClickableComponent* ClickableComponent);

	void RemoveBuildingButton(UFPBuildingButtonUI* ButtonToRemove);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void DeleteBuilding(AActor* Target);

	UFUNCTION()
	void BuildingMoveSelect(AActor* Target);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UScrollBox> BuildingScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UFPBuildingButtonUI> BuildingButtonREF;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<class UFPBuildingButtonUI>> BuildingButtonArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UButton> CancelButton;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UFPEditBuildingUI> EditBuildingUI;

	UPROPERTY()
	TObjectPtr<class UFPGameInstance> GameInst;

private:
	void GetInventory();
	void ScrollBoxSetup();
	bool IsAlreadyGenUI(const TObjectPtr<UBuildingItemData> InData, TObjectPtr<UFPBuildingButtonUI>& OutTargetUI);
	
	TObjectPtr<class UFPBuildingButtonUI> GenerateBuildingButtonUI(const TObjectPtr<class UBuildingItemData> Data);

private:
	TObjectPtr<class AMainFPLevelScript> FPLevel;
};