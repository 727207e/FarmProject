// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/FPInventoryUI.h"

void UFPInventoryUI::ActiveUI()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UFPInventoryUI::DeactiveUI()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UFPInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UFPInventoryUI::NativeDestruct()
{
	Super::NativeDestruct();
}

void UFPInventoryUI::OnTabButtonSelect(const EFPInventoryItemType InSelectType)
{
	switch (InSelectType) {
		{
			case EFPInventoryItemType::Farm:
			BP_OnSwitchChange(EFPInventoryItemType::Farm);
			break;
			
			case EFPInventoryItemType::Animal:
			BP_OnSwitchChange(EFPInventoryItemType::Animal);
			break;
			
			case EFPInventoryItemType::Building:
			BP_OnSwitchChange(EFPInventoryItemType::Building);
			break;
			
			case EFPInventoryItemType::Seed:
			BP_OnSwitchChange(EFPInventoryItemType::Seed);
			break;
			
			case EFPInventoryItemType::Egg:
			BP_OnSwitchChange(EFPInventoryItemType::Egg);
			break;
			
			default:
			break;
		} }
}

void UFPInvenAnimalItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	
}
