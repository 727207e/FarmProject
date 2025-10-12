// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserListEntry.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "UI/FPUserWidget.h"
#include "FPInventoryUI.generated.h"

class UListView;
class UButton;
/**
 * 
 */

UENUM(BlueprintType)
enum class EFPInventoryItemType : uint8
{
	Farm = 0,
	Animal,
	Building,
	Seed,
	Egg,
};

UCLASS()
class FARMPROJECT_API UFPInventoryUI : public UFPUserWidget
{
	GENERATED_BODY()

public :
	virtual void ActiveUI() override;
	virtual void DeactiveUI() override;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
	void OnTabButtonSelect(const EFPInventoryItemType InSelectType);

	UFUNCTION(BlueprintCallable)
	void OnCloseButtonClicked();
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnSwitchChange(const EFPInventoryItemType InSelectType);
	
	void OnInvenItemClicked(UObject* InItem);
	void UpdateAnimalInven() const;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UListView> LV_Animal;
};