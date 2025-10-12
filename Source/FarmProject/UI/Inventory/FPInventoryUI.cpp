// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/FPInventoryUI.h"

#include "FPInvenItem.h"
#include "Components/ListView.h"
#include "GameSystem/Level/FPGameInstance.h"
#include "UI/FPHud.h"

void UFPInventoryUI::ActiveUI()
{
	SetVisibility(ESlateVisibility::Visible);

	if (LV_Animal)
	{
		LV_Animal->OnItemClicked().AddUObject(this, &ThisClass::OnInvenItemClicked);
	}
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

void UFPInventoryUI::OnCloseButtonClicked()
{
	if (AFPHud* FPHud = Cast<AFPHud>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{
		FPHud->ToggleInventoryUI();
	}
}

void UFPInventoryUI::OnInvenItemClicked(UObject* InItem)
{
	//아이템 클릭시 해당 데이터 가져오기

	//마우스 커서에 아이템 캐릭터(오브젝트) 붙여서 이동하기

	//다시 클릭시 해당 월드좌표에 배치
}

void UFPInventoryUI::UpdateAnimalInven() const
{
	const UFPGameInstance* FPGameInst = Cast<UFPGameInstance>(GetWorld()->GetGameInstance());
	if (FPGameInst == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%hs : Can't Find GameInst"), __func__);
		return;
	}

	if (LV_Animal == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%hs : Can't Find AnimalListView"), __func__);
		return;
	}
	
	for (const TObjectPtr<UAnimalDataBase>& AnimalData : FPGameInst->AnimalInventory)
	{
		if (AnimalData == nullptr)
		{
			continue;
		}

		UFPInvenData* InvenData = NewObject<UFPInvenData>();
		InvenData->ItemId = AnimalData->Id;
		InvenData->ItemType = EFPInventoryItemType::Animal;
		LV_Animal->AddItem(InvenData);
	}
}
