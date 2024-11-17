// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPEditBuildingUI.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UFPEditBuildingUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFPEditBuildingUI(const FObjectInitializer& ObjectInitializer);

	void ActiveEditBuildUI(class UClickableComponent* ClickableComponent);
	void DeactiveEditBuildUI();

protected:
	UFUNCTION()
	void OnLeftButtonClicked();
	UFUNCTION()
	void OnRightButtonClicked();
	UFUNCTION()
	void OnGoInvenButtonClicked();
	UFUNCTION()
	void OnMoveButtonClicked();
	UFUNCTION()
	void OnCancelButtonClicked();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UButton> LeftButton;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UButton> RightButton;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UButton> GoInventoryButton;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UButton> MoveButton;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UButton> CancelButton;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UClickableComponent> CurTargetClickable;
};
