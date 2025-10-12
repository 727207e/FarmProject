// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "UI/FPUserWidget.h"
#include "FPInvenItem.generated.h"

enum class EFPInventoryItemType : uint8;

UCLASS()
class FARMPROJECT_API UFPInvenData : public UObject
{
	GENERATED_BODY()

public:
	int32 ItemId;
	EFPInventoryItemType ItemType;
};

UCLASS()
class FARMPROJECT_API UFPInvenItem : public UFPUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnSetItemImage(const UTexture2D* InTexture);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnSetItemCount(const int32 InItemCount);
	
private:
	int32 ItemId;
	EFPInventoryItemType ItemType;
};
