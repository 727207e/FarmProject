// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPDownInfoWidget.h"
#include "GameSystem/Data/FieldItemData.h"

UFPDownInfoWidget::UFPDownInfoWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFPDownInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UFPDownInfoWidget::ActiveUI()
{
	this->SetVisibility(ESlateVisibility::Visible);
}

void UFPDownInfoWidget::DeactiveUI()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UFPDownInfoWidget::DataChangeUI()
{
}

void UFPDownInfoWidget::CurUISetting(TObjectPtr<UFieldItemData> FieldData)
{
	if (CurData == nullptr)
	{
		CurData = FieldData;
		ActiveUI();
	}
	else if (CurData == FieldData)
	{
		CurData = nullptr;
		DeactiveUI();
	}
	else if (CurData != FieldData)
	{
		CurData = FieldData;
		DataChangeUI();
	}
}
