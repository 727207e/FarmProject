// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPDownInfoWidget.h"
#include "GameSystem/Data/FieldItemData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#define PropertyUIName TEXT("Property_UI")
#define MainImageUIName TEXT("MainImage_UI")
#define TitleTextUIName TEXT("TitleText_UI")
#define ContentTextUIName TEXT("ContentText_UI")
#define SeedButtonUIName TEXT("SeedButton_UI")

UFPDownInfoWidget::UFPDownInfoWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFPDownInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PropertyUI = Cast<UImage>(GetWidgetFromName(PropertyUIName));
	MainImageUI = Cast<UImage>(GetWidgetFromName(MainImageUIName));
	TitleTextUI = Cast<UTextBlock>(GetWidgetFromName(TitleTextUIName));
	ContentTextUI = Cast<UTextBlock>(GetWidgetFromName(ContentTextUIName));
	SeedButtonUI = Cast<UButton>(GetWidgetFromName(SeedButtonUIName));
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
