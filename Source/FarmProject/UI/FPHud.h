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

	//동물도 같은 메소드 사용
	//이때 파라미터만 수정해서 사용하면 될듯.
	//Field 랑 Animal 이랑 이렇게 해서.
	void DownInfoUIUpdate(TObjectPtr<class UFieldItemData> FieldData);

	FOnClickClickabeComp OnClickClickableComp;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> StylingUIClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> DownInfoUIClass;

private:
	UPROPERTY()
	TObjectPtr<class UFPStylingUI> StylingUI;
	UPROPERTY()
	TObjectPtr<class UFPDownInfoWidget> DownInfoUI;

	UPROPERTY()
	TScriptInterface<class IBuildManagerInterface> BuildManager;
};
