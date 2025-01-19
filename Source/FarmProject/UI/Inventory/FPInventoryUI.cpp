// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/FPInventoryUI.h"

void UFPInventoryUI::ActiveUI()
{
	SetVisibility(ESlateVisibility::Visible);
	UE_LOG(LogTemp, Error, TEXT("Inven Act"));
}

void UFPInventoryUI::DeactiveUI()
{
	UE_LOG(LogTemp, Error, TEXT("Inven Deact"));
	SetVisibility(ESlateVisibility::Hidden);
}
