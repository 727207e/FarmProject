// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Building/ActorComponent/ClickableComponent.h"
#include "GameSystem/Level/MainFPLevelScript.h"

UClickableComponent::UClickableComponent()
{
}

void UClickableComponent::OnClick()
{
	if (OnClicked.IsBound())
	{
		OnClicked.Execute();
	}
}

void UClickableComponent::OnDestroySelf()
{
	if (GetOwner())
	{
		GetOwner()->Destroy();
	}
}