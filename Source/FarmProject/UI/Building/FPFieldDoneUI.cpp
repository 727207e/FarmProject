// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Building/FPFieldDoneUI.h"
#include "Components/Button.h"

#define ButtonUIName TEXT("Button_UI")

UFPFieldDoneUI::UFPFieldDoneUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFPFieldDoneUI::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonUI = Cast<UButton>(GetWidgetFromName(ButtonUIName));
	if (ButtonUI)
	{
		ButtonUI->OnClicked.AddDynamic(this, &UFPFieldDoneUI::OnClickButton);
	}
}

void UFPFieldDoneUI::OnClickButton()
{
	if (OnButtonClicked.IsBound())
	{
		OnButtonClicked.Execute();
	}
}
