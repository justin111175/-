#include <Dxlib.h>
#include "geometory.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	DxLib::ChangeWindowMode(true);
	if (DxLib::DxLib_Init())
	{
		return -1;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);

	while (!DxLib::ProcessMessage()&& !keystate[KEY_INPUT_ESCAPE])
	{
		DxLib::ClearDrawScreen();
		DxLib::GetHitKeyStateAll(keystate);
		DxLib::SetMainWindowText("“–‚½‚è”»’è");


		//if (!IsHitAABB(rcA,rcB))
		//{
		//	Move();
		//}
		//else
		//{
		//	color = 0xFFAAAA;
		//}
		Move();
		if (IsHitCircle(cirA,cirB))
		{
			color = 0xFFAAAA;
		}
		else
		{
			color = 0xFFFFFF;
		}


		if (keystate[KEY_INPUT_Z])
		{
			rcA.posX = 0;
			rcA.posY = 0;

			cirA.posX = 200;
			cirA.posY = 200;
			color = 0xffffff;
		}

		//DrawBox(rcA.posX, rcA.posY, rcA.posX+rcA.sizeX, rcA.posY+rcA.sizeY, color, true);
		//DrawBox(rcB.posX, rcB.posY, rcB.posX+rcB.sizeX, rcB.posY+rcB.sizeY, color, true);

		DrawCircle(cirA.posX, cirA.posY, cirA.rang,color, true);
		DrawCircle(cirB.posX, cirB.posY, cirB.rang,color, true);
		DxLib::ScreenFlip();
	}
	DxLib::DxLib_End();
	return 0;
}

void Move(void)
{
	if (keystate[KEY_INPUT_UP])
	{
		rcA.posY -= speed;
		cirA.posY -= speed;
	}
	if (keystate[KEY_INPUT_DOWN])
	{
		rcA.posY += speed;
		cirA.posY += speed;
	}
	if (keystate[KEY_INPUT_LEFT])
	{
		rcA.posX -= speed;
		cirA.posX -= speed;
	}
	if (keystate[KEY_INPUT_RIGHT])
	{
		rcA.posX += speed;
		cirA.posX += speed;
	}
}

//’·•ûŒ`‚Ì“–‚½‚è”»’è
bool IsHitAABB(const Rect& rcA, const Rect& rcB)
{
	if (rcA.posX<rcB.posX + rcB.sizeX &&
		rcA.posX + rcA.sizeX>rcB.posX &&
		rcA.posY<rcB.posY + rcB.sizeY &&
		rcA.posY + rcA.sizeY>rcB.posY)
	{
		return true;
	}
	else
	{
		return false;

	}

}

bool IsHitCircle(const Circle& cirA, const Circle& cirB)
{
	int longX = cirA.posX - cirB.posX;
	int longY = cirA.posY - cirB.posY;
	int leath = cirA.rang + cirB.rang;


	return(longX * longX + longY * longY < leath* leath);

}
