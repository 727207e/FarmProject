// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FPCameraPawn.generated.h"

UCLASS()
class FARMPROJECT_API AFPCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	AFPCameraPawn();

protected:
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION()
	void MoveForward();
	UFUNCTION()
	void MoveBack();
	UFUNCTION()
	void MoveRight();
	UFUNCTION()
	void MoveLeft();
	UFUNCTION()
	void ClickableClick();

	UFUNCTION()
	void ZoomInOut(float value);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USceneComponent> rootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class AFPMainController> FPCont;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class AMainFPLevelScript> MainLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class AFPHud> MyHud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UFloatingPawnMovement> FloatMovement;
};
