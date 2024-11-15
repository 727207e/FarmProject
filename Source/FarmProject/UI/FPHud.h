// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPHud.generated.h"

class UClickableComponent;
DECLARE_DELEGATE_OneParam(FOnClickClickabeComp, UClickableComponent*)
/**
 * 
 */
UCLASS()
class FARMPROJECT_API AFPHud : public AHUD
{
	GENERATED_BODY()
	
public:
	AFPHud();

	UFUNCTION()
	void OpenStylingUI();

	FOnClickClickabeComp OnClickClickableComp;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> StylingUIClass;

private:
	UPROPERTY()
	TObjectPtr<class UFPStylingUI> StylingUI;

	UPROPERTY()
	TScriptInterface<class IBuildManagerInterface> BuildManager;
};
