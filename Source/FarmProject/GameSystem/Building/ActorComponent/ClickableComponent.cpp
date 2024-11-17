// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Building/ActorComponent/ClickableComponent.h"
#include "GameSystem/Building/GridCell.h"
#include "GameSystem/Level/MainFPLevelScript.h"

UClickableComponent::UClickableComponent()
{
}

void UClickableComponent::OnClick()
{

}

void UClickableComponent::OnDestroySelf()
{
	//�κ��丮�� �߰��ϴ� ����
	//UPaperSprite* LoadedSprite = LoadObject<UPaperSprite>(nullptr, TEXT("/Game/DownloadAsset/Ground_Game_UI/Sprites/Buttons/Active/Button__14__Sprite.Button__14__Sprite"));
	//UTexture2D* SpriteTexture = LoadedSprite->GetBakedTexture();
	//InfoArray.Add(FBuildingInfo(FText::FromString("TESTBuild"), 1, SpriteTexture));

	GetOwner()->Destroy();
}


void UClickableComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OverlappingActors;
	GetOwner()->GetOverlappingActors(OverlappingActors, AGridCell::StaticClass());

	for (AActor* Actor : OverlappingActors)
	{
		if (AGridCell* GridCellActor = Cast<AGridCell>(Actor))
		{
			OverlappedGridSet.Add(GridCellActor);
			GridCellActor->UpdateGridState(EBuildState::OverlapBuilding);
		}
	}
}