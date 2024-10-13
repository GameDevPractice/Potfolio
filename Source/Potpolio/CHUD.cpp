#include "CHUD.h"
#include "Global.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

ACHUD::ACHUD()
{
	CHelpers::GetAsset(&CrossHairTexture,"/Game/UI/Img/T_Crosshair");
	CHelpers::GetClass(&BulletWidget, "/Game/UI/WB_BulletCount");
	bVisibleAim = false;
}

void ACHUD::BeginPlay()
{
	Super::BeginPlay();

	CheckNull(BulletWidget);
	BulletCountWidget = CreateWidget(GetWorld(), BulletWidget);

	CheckNull(BulletCountWidget);
	BulletCountWidget->AddToViewport();
	
}

void ACHUD::DrawHUD()
{
	BulletCountWidget->SetVisibility(ESlateVisibility::Hidden);

	CheckFalse(bVisibleAim);
	BulletCountWidget->SetVisibility(ESlateVisibility::Visible);

	FVector2D Center(Canvas->ClipX * .5f, Canvas->ClipY * .5f);
	FVector2D ImageSize(CrossHairTexture->GetSizeX() * 1.f, CrossHairTexture->GetSizeY() * 0.5f);

	Center -= ImageSize;
	FCanvasTileItem Item(Center, CrossHairTexture->Resource, FLinearColor::White);
	Item.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(Item);
}

void ACHUD::VisibleAim()
{
	if(!bVisibleAim)
	bVisibleAim = true;
}

void ACHUD::InVisibleAim()
{
	if(bVisibleAim)
	bVisibleAim = false;
}
