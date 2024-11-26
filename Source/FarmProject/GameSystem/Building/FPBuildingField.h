// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSystem/Building/FPBuilding.h"
#include "GameSystem/Data/FieldItemData.h"
#include "Components/StaticMeshComponent.h"
#include "FPBuildingField.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API AFPBuildingField : public AFPBuilding
{
	GENERATED_BODY()
	
public:
	AFPBuildingField();

	virtual void BeginPlay() override;
	virtual void ShowBuildingUI() override;

	UFUNCTION()
	void ChangeStaticMesh(EFieldState ECurState);

	UFUNCTION()
	void ClickDoneUI();

protected:
	UPROPERTY()
	TObjectPtr<class AFPHud> MyHud;

	UPROPERTY()
	TObjectPtr<UFieldItemData> FieldData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UStaticMeshComponent>> FarmMeshArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UWidgetComponent> FieldFinishWidget;

	UPROPERTY()
	TObjectPtr<class UFPFieldDoneUI> DoneUI;

	//본인이 가지고 있는 식물의 데이터를 가지고 있어야 함.
	//UI 업데이트는 데이터 보내주기
};
