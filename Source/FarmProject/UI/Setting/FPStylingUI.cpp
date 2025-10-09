// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Setting/FPStylingUI.h"
#include "GameSystem/Level/MainFPLevelScript.h"
#include "Components/ScrollBox.h"
#include "PaperSprite.h"
#include "Components/Button.h"
#include "GameSystem/Building/ActorComponent/ClickableComponent.h"
#include "GameSystem/Data/ItemDataBase.h"
#include "GameSystem/Data/BuildingItemData.h"
#include "GameSystem/Level/FPGameInstance.h"
#include "GameSystem/Building/FPBuilding.h"
#include "UI/Building/FPEditBuildingUI.h"
#include "GameSystem/Building/GridCell.h"

#define BuildingScrollBoxUIName TEXT("BuildingScrollBox_UI")
#define EditBuildingUIName TEXT("EditBuilding_UI")
#define StylingUIShutDownName TEXT("StylingUIShutDown_UI")

UFPStylingUI::UFPStylingUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFPStylingUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (FPLevel == nullptr)
	{
		FPLevel = Cast<AMainFPLevelScript>(GetWorld()->GetLevelScriptActor());
	}
	BuildingScrollBox = Cast<UScrollBox>(GetWidgetFromName(BuildingScrollBoxUIName));
	CancelButton = Cast<UButton>(GetWidgetFromName(StylingUIShutDownName));
	EditBuildingUI = Cast<UFPEditBuildingUI>(GetWidgetFromName(EditBuildingUIName));
	if (EditBuildingUI != nullptr)
	{
		EditBuildingUI->SetVisibility(ESlateVisibility::Hidden);
		EditBuildingUI->OnBuildingJustDelete.BindUObject(this, &UFPStylingUI::DeleteBuilding);
		EditBuildingUI->OnBuildingDeleteAndMove.BindUObject(this, &UFPStylingUI::BuildingMoveSelect);
	}
}

void UFPStylingUI::DeleteBuilding(AActor* Target)
{
	AFPBuilding* BuildingInfo = Cast<AFPBuilding>(Target);
	if (BuildingInfo == nullptr)
	{
		return;
	}
	FString BuildingName = BuildingInfo->BuildingData->Name.ToString();

	bool bIsFind = false;
	for (TObjectPtr<UFPBuildingButtonUI> Button : BuildingButtonArray)
	{
		if (BuildingName.Equals(Button->GetBuildingName()))
		{
			Button->AddBuildingCount(1);
			GameInst->EditItemCount(BuildingInfo->BuildingData, 1);
			bIsFind = true;

			TArray<AActor*> OverlappingActors;
			BuildingInfo->GetOverlappingActors(OverlappingActors, AGridCell::StaticClass());

			for (AActor* Actor : OverlappingActors)
			{
				if (AGridCell* GridCellActor = Cast<AGridCell>(Actor))
				{
					GridCellActor->ResetGridState();
				}
			}
			break;
		}
	}

	if (!bIsFind)
	{
		BuildingInfo->BuildingData->CurrentCount = 1;
		GameInst->AddItemToInventory(BuildingInfo->BuildingData);
		GenerateBuildingButtonUI(BuildingInfo->BuildingData);
	}
}

void UFPStylingUI::BuildingMoveSelect(AActor* Target)
{
	AFPBuilding* BuildingInfo = Cast<AFPBuilding>(Target);
	if (BuildingInfo == nullptr)
	{
		return;
	}
	FString BuildingName = BuildingInfo->BuildingData->Name.ToString();
	BuildingInfo->BuildingData->CurrentCount += 1;

	bool bIsFind = false;
	for (TObjectPtr<UFPBuildingButtonUI> Button : BuildingButtonArray)
	{
		if (BuildingName.Equals(Button->GetBuildingName()))
		{
			Button->AddBuildingCount(1);
			GameInst->EditItemCount(BuildingInfo->BuildingData, 1);
			Button->OnButtonClicked();
			bIsFind = true;

			TArray<AActor*> OverlappingActors;
			BuildingInfo->GetOverlappingActors(OverlappingActors, AGridCell::StaticClass());

			for (AActor* Actor : OverlappingActors)
			{
				if (AGridCell* GridCellActor = Cast<AGridCell>(Actor))
				{
					GridCellActor->ResetGridState();
				}
			}
			break;
		}
	}

	if (!bIsFind)
	{
		BuildingInfo->BuildingData->CurrentCount = 1;
		GameInst->AddItemToInventory(BuildingInfo->BuildingData);
		GenerateBuildingButtonUI(BuildingInfo->BuildingData)->OnButtonClicked();
	}
}

void UFPStylingUI::ActiveUI()
{
	GetInventory();
	ScrollBoxSetup();
}

void UFPStylingUI::DeactiveUI()
{
	if (FPLevel)
	{
		FPLevel->SetPlacementModeEnable(false, nullptr);
		EditBuildingUI->DeactiveEditBuildUI();
	}

	for (UFPBuildingButtonUI* ButtonUI : BuildingButtonArray)
	{
		ButtonUI->DeactiveUI();
	}
}

void UFPStylingUI::ActiveEditBuildMode(UClickableComponent* ClickableComponent)
{
	if (FPLevel->GetIsBuildMode())
	{
		if (!FPLevel->GetIsPlacementMode())
		{
			EditBuildingUI->ActiveEditBuildUI(ClickableComponent);
		}
	}
}

void UFPStylingUI::GetInventory()
{
	GameInst = Cast<UFPGameInstance>(GetGameInstance());
}

void UFPStylingUI::ScrollBoxSetup()
{
	for (const TObjectPtr<UBuildingItemData> BuildingData : GameInst->BuildingInventory)
	{
		if (BuildingData == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("%hs : Can't Find BuildingData"), __func__);
			continue;
		}
		
		TObjectPtr<UFPBuildingButtonUI> TargetUIButton;
		if (IsAlreadyGenUI(BuildingData, TargetUIButton))
		{
			//이미 있으면 갱신
			TargetUIButton->SetBuildingCount(BuildingData->CurrentCount);
		}
		else
		{
			//새로운 UI를 배치해야하는 경우
			GenerateBuildingButtonUI(BuildingData);	
		}
	}
}

TObjectPtr<class UFPBuildingButtonUI> UFPStylingUI::GenerateBuildingButtonUI(const TObjectPtr<UBuildingItemData> Data)
{
	UFPBuildingButtonUI* NewButton = CreateWidget<UFPBuildingButtonUI>(this, BuildingButtonREF);
	if (NewButton == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%hs : Fail Generate BuildingButton"), __func__);
		return nullptr;
	}
	
	NewButton->ButtonInit(Data);
	BuildingButtonArray.Add(NewButton);
	if (BuildingScrollBox)
	{
		BuildingScrollBox->AddChild(NewButton);
	}

	return NewButton;
}

void UFPStylingUI::RemoveBuildingButton(UFPBuildingButtonUI* ButtonToRemove)
{
	if (BuildingScrollBox && ButtonToRemove)
	{
		BuildingScrollBox->RemoveChild(ButtonToRemove);
	}

	BuildingButtonArray.Remove(ButtonToRemove);

	ButtonToRemove->RemoveFromParent();
	ButtonToRemove = nullptr;
}

bool UFPStylingUI::IsAlreadyGenUI(const TObjectPtr<UBuildingItemData> InData, TObjectPtr<UFPBuildingButtonUI>& OutTargetUI)
{
	if (InData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%hs : Can't Find InData"), __func__);
		return false;
	}
	
	for (TObjectPtr<UFPBuildingButtonUI> ButtonUI : BuildingButtonArray)
	{
		if (ButtonUI == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("%hs : Can't Find ButtonUI"), __func__);
			continue;
		}
		
		//이미 UI가 배치된 경우
		if (InData->Name.ToString().Equals(ButtonUI->GetBuildingName()))
		{
			OutTargetUI = ButtonUI;
			return true;
		}
	}

	return false;
}