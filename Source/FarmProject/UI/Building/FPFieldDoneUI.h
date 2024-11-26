// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPFieldDoneUI.generated.h"

DECLARE_DELEGATE(FOnButtonClicked);

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UFPFieldDoneUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFPFieldDoneUI(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	
	FOnButtonClicked OnButtonClicked;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UButton> ButtonUI;

protected:
	UFUNCTION()
	void OnClickButton();

};
