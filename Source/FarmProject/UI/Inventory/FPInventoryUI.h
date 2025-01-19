// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/FPUserWidget.h"
#include "FPInventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UFPInventoryUI : public UFPUserWidget
{
	GENERATED_BODY()

public :

	virtual void ActiveUI() override;
	virtual void DeactiveUI() override;
};
