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

	UFUNCTION()
	void ActiveEditBuildMode(class UClickableComponent* ClickableComponent);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void DeleteBuilding(AActor* Target);

	UFUNCTION()
	void BuildingMoveSelect(AActor* Target);

	UFUNCTION()
	void RemoveBuildingButton(UFPBuildingButtonUI* ButtonToRemove);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UScrollBox> BuildingScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UFPBuildingButtonUI> BuildingButtonREF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UObject> ttttt;

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
	TObjectPtr<class UFPBuildingButtonUI> GenerateBuildingButtonUI(TObjectPtr<class UBuildingItemData> Data);

private:
	TObjectPtr<class AMainFPLevelScript> FPLevel;
};