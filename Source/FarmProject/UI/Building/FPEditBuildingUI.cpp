// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Building/FPEditBuildingUI.h"
#include "Components/Button.h"
#include "GameSystem/Building/ActorComponent/ClickableComponent.h"

#define LeftButtonUIName TEXT("LeftButton_UI")
#define RightButtonUIName TEXT("RightButton_UI")
#define GoInventoryButtonUIName TEXT("GoInventoryButton_UI")
#define MoveButtonUIName TEXT("MoveButton_UI")
#define CancelButtonUIName TEXT("CancelButton_UI")

UFPEditBuildingUI::UFPEditBuildingUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFPEditBuildingUI::ActiveEditBuildUI(class UClickableComponent* ClickableComponent)
{
	SetVisibility(ESlateVisibility::Visible);
	CurTargetClickable = ClickableComponent;
	if (CurTargetClickable == nullptr)
	{
		UE_LOG(LogTemp,Error, TEXT("%s : Can't Find ClickableObject"), *__FUNCTION__);
		return;
	}

	if (LeftButton == nullptr)
	{
		LeftButton = Cast<UButton>(GetWidgetFromName(LeftButtonUIName));
		if (LeftButton)
		{
			LeftButton->OnClicked.AddDynamic(this, &UFPEditBuildingUI::OnLeftButtonClicked);
		}
	}
	if (RightButton == nullptr)
	{
		RightButton = Cast<UButton>(GetWidgetFromName(RightButtonUIName));
		if (RightButton)
		{
			RightButton->OnClicked.AddDynamic(this, &UFPEditBuildingUI::OnRightButtonClicked);
		}
	}
	if (GoInventoryButton == nullptr)
	{
		GoInventoryButton = Cast<UButton>(GetWidgetFromName(GoInventoryButtonUIName));
		if (GoInventoryButton)
		{
			GoInventoryButton->OnClicked.AddDynamic(this, &UFPEditBuildingUI::OnGoInvenButtonClicked);
		}
	}
	if (MoveButton == nullptr)
	{
		MoveButton = Cast<UButton>(GetWidgetFromName(MoveButtonUIName));
		if (MoveButton)
		{
			MoveButton->OnClicked.AddDynamic(this, &UFPEditBuildingUI::OnMoveButtonClicked);
		}
	}	
	if (CancelButton == nullptr)
	{
		CancelButton = Cast<UButton>(GetWidgetFromName(CancelButtonUIName));
		if (CancelButton)
		{
			CancelButton->OnClicked.AddDynamic(this, &UFPEditBuildingUI::OnCancelButtonClicked);
		}
	}
}

void UFPEditBuildingUI::DeactiveEditBuildUI()
{
	SetVisibility(ESlateVisibility::Hidden);
	CurTargetClickable = nullptr;
}

void UFPEditBuildingUI::OnLeftButtonClicked()
{        
	FRotator CurrentRotation = CurTargetClickable->GetOwner()->GetActorRotation();
	FRotator NewRotation = CurrentRotation + FRotator(0.f, 90.f, 0.f);
	CurTargetClickable->GetOwner()->SetActorRotation(NewRotation);
}

void UFPEditBuildingUI::OnRightButtonClicked()
{
	FRotator CurrentRotation = CurTargetClickable->GetOwner()->GetActorRotation();
	FRotator NewRotation = CurrentRotation + FRotator(0.f, -90.f, 0.f);
	CurTargetClickable->GetOwner()->SetActorRotation(NewRotation);
}

void UFPEditBuildingUI::OnGoInvenButtonClicked()
{
	CurTargetClickable->OnDestroySelf();
}

void UFPEditBuildingUI::OnMoveButtonClicked()
{
	CurTargetClickable->OnDestroySelf();
}

void UFPEditBuildingUI::OnCancelButtonClicked()
{
	DeactiveEditBuildUI();
}
