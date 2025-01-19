// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UFPUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public :

	virtual void ActiveUI() {};
	virtual void DeactiveUI() {};
};
