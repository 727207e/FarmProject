// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/FPInvenItem.h"

#include "GameSystem/Level/FPGameInstance.h"

void UFPInvenItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UFPGameInstance* FPGameInst = Cast<UFPGameInstance>(GetWorld()->GetGameInstance());
	if (FPGameInst == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%hs : Can't Find GameInst"), __func__);
		return;
	}
	
	UFPInvenData* ItemData = Cast<UFPInvenData>(ListItemObject);
	ItemId = ItemData->ItemId;
	ItemType = ItemData->ItemType;

	TWeakObjectPtr<UItemDataBase> ItemDataBase;
	
	//아이템 데이터 가져오기
	switch (ItemType)
	{
		case EFPInventoryItemType::Animal:
			ItemDataBase = FPGameInst->GetAnimalInvenData(ItemId);
			break;
		
		default:
			UE_LOG(LogTemp, Error, TEXT("%hs : No Logic In Type : %d"), __func__, ItemType);
			break;
	}

	if (ItemDataBase != nullptr)
	{
		BP_OnSetItemImage(ItemDataBase->Image);
		BP_OnSetItemCount(ItemDataBase->CurrentCount);
	}
}