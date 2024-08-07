#include "CHUD.h"
#include "Global.h"
#include "Engine/Canvas.h"

ACHUD::ACHUD()
{
	CHelpers::GetAsset(&CrossHairTexture,"/Game/UI/Img/T_Crosshair");
	bVisibleAim = false;
}

void ACHUD::BeginPlay()
{
	Super::BeginPlay();

}

void ACHUD::DrawHUD()
{
	CheckFalse(bVisibleAim);
	FVector2D Center(Canvas->ClipX * .5f, Canvas->ClipY * .5f);
	FVector2D ImageSize(CrossHairTexture->GetSizeX() * 0.5f, CrossHairTexture->GetSizeY() * 0.5f);

	Center -= ImageSize;
	FCanvasTileItem Item(Center, CrossHairTexture->Resource, FLinearColor::White);
	Item.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(Item);
}

void ACHUD::VisibleAim()
{
	bVisibleAim = true;
}

void ACHUD::InVisibleAim()
{
	bVisibleAim = false;
}
