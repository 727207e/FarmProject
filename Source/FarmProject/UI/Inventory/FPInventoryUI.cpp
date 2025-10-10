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
			UpdateAnimalInven();
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
		}
	}
}

void UFPInventoryUI::UpdateAnimalInven()
{
	//인벤에서 Animal 데이터 가져오기
	//데이터 가져와서 UObject 제작
	//제작한거 ListView에 추가
}

void UFPInvenAnimalItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	
}
