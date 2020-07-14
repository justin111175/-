#include "Dxlib.h"
#include "common/Vector2.h"
#include <math.h>

#define shot Bulltom::GetInstance()

char keystate[256];
Vector2Flt _catPos = { 320,240 };
Vector2Flt _mousePos;

Vector2 screen_size = { 1280,720 };

Vector2Flt bulPos;
Vector2Flt bulVec;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	SetGraphMode(screen_size.x, screen_size.y, 16);											

	DxLib::ChangeWindowMode(true);
	if (DxLib::DxLib_Init())
	{
		return -1;
	}

	DxLib::SetDrawMode(DX_DRAWMODE_BILINEAR);	//優点：線がスムースになる　　　欠点：トッド絵は使えない
	DxLib::SetDrawScreen(DX_SCREEN_BACK);

	auto catH = LoadGraph("image/arrowcat.png");
	int fram = 0;
	while (!DxLib::ProcessMessage() && !keystate[KEY_INPUT_ESCAPE])
	{
		DxLib::ClearDrawScreen();

		int tmpX,tmpY;
		DxLib::GetMousePoint(&tmpX, &tmpY);

		_mousePos = { static_cast<float>(tmpX),static_cast<float>(tmpY) };
		auto diffV = _mousePos - _catPos;

		//if (fram % 120==0)
		//{
		//	bulPos = _catPos;
		//	bulVec = Magnitude(_mousePos,bulPos);
		//}
		//bulPos += bulVec/static_cast<float>(10);

		if (fram % 120 == 0)
		{
			

			//new Bulltom;
			//bulPos = _catPos;
			//auto tmp = _mousePos - bulPos;
			//// 正規化をとってあげる
			//bulVec = Normalize(tmp);
		}
		// 座標+正規化したベクトル（大きさを１に）＊（ほしい速度の倍数）
		//bulPos += bulVec * 5.0f;

		DrawRotaGraph(_catPos.x, _catPos.y, 1.0f, atan2(diffV.y, diffV.x), catH, true);

		
		DxLib::GetHitKeyStateAll(keystate);
		DxLib::SetMainWindowText("ベクトル");


		fram++;
		DxLib::ScreenFlip();


	}
	DxLib::DxLib_End();
	return 0;
}

struct Bulltom
{

	void Run(void);
	void Draw(void);
	Bulltom();
	~Bulltom();

	Vector2Flt _pos;
	Vector2Flt _vec;
	float _rang;


};

void Bulltom::Run(void)
{
}

void Bulltom::Draw(void)
{
	DrawCircle(_pos.x, _pos.y, 10, 0xFFFFFF, true);

}

Bulltom::Bulltom()
{
	_pos = _catPos;
	_rang = 10;
}

Bulltom::~Bulltom()
{
}
