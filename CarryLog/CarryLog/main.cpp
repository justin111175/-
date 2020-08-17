#include<DxLib.h>
#include<cmath>
#include"Geometry.h"


using namespace std;

void DrawWood(const Capsule& cap, int handle) {


	auto v = cap.posB - cap.posA;
	auto angle = atan2(v.y, v.x) + DX_PI_F / 2.0f;
	auto w = cos(angle)*cap.radius;
	auto h = sin(angle)*cap.radius;

	DrawModiGraph(
		cap.posA.x - w, cap.posA.y - h,
		cap.posB.x - w, cap.posB.y - h,
		cap.posB.x + w, cap.posB.y + h,
		cap.posA.x + w, cap.posA.y + h, handle, true);
}


///とある点を中心に回転して、その回転後の座標を返します。
///@param center 回転中心点
///@param angle 回転角度
///@param pos 元の座標
///@return 変換後の座標
Matrix RotatePosition(const Position2& center, float angle) {
	//①中心を原点に平行移動して
	//②原点中心に回転して
	//③中心を元の座標へ戻す

	Matrix mat = IdentityMat();
	mat= MultipleMat(TranslateMat(center.x, center.y),
		MultipleMat(RotateMat(angle),
		TranslateMat(-center.x, -center.y)));
	return mat;
	//これを書き換えて、特定の点を中心に回転を行うようにしてください。
}

float Clamp(float value, float minVal = 0.0f, float maxVal = 1.0f) {
	//今は値をそのまま返していますが、クランプ(最小値最大値の範囲を超えたら最小値もしくは最大値にする)した
	//値を返してください。
	return max(minVal, min(value, maxVal));
}
//カプセルと円が当たったか？
bool IsHit(const Capsule& cap, const Circle& cc) {

	
	//1まず2つのベクトルVP、Vを作る
	//	２内積をVの２乗で割る
	//	３２を０～１にクランプする
	//	４２＊３のベクトルを作る
	//	５VP－４の大きさをはかり、半径と比較


	//	//手順
	//①まず、カプセル形状の端点cap.posAからccの中心点までのベクトルvpを作ります。
	auto vp = cc.pos - cap.posA;
	//②次にカプセル形状そのもののベクトルposA→posBへのベクトルvを作ります。
	auto v = cap.posB - cap.posA;
	//③①と②の内積を求めます。
	auto dot = Dot(vp, v);
	//④③の結果を②の大きさの2乗で割ります
	auto vrate =  dot/(v*v);
	//⑤④の結果をクランプします
	vrate = Clamp(vrate);
	//⑥⑤の結果を②の結果にかけます
	v *= vrate;
	//⑦①のベクトルから②のベクトルを引きます
		//vp -= v;
	//⑧⑦のベクトルの大きさを測ります
		//vp.Magnitude();
	//⑨⑧の値と、cap.radius+cc.radiusの値を比較します。
	return (vp - v).Magnitude() <= cap.radius + cc.radius;

}




int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetGraphMode(512, 800, 32);
	SetWindowText("1916229_YANG CHIHCHENG");											// タイトルバー

	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	int sw, sh;//スクリーン幅、高さ
	GetDrawScreenSize(&sw, &sh);

	auto woodH = LoadGraph("img/wood.png");
	int wdW, wdH;
	GetGraphSize(woodH, &wdW, &wdH);
	wdW = 200;

	auto cascadeH = LoadGraph("img/cascade_chip.png");
	auto chipH = LoadGraph("img/atlas0.png");
	auto circle= LoadGraph("img/rock.png"); 
	auto clear = LoadGraph("img/clear.png");

	Capsule cap(20,Position2((sw-wdW)/2,sh-100),Position2((sw - wdW) / 2+wdW,sh-100));
	Circle circle_;
	circle_.pos = { 300,0 };
	circle_.radius = 24;

	char keystate[256];
	
	float angle = 0.0f;

	int frame = 0;
	bool isLeft = false;
	bool gameOverFlag_ = false;
	bool gameclearFlag_ = false;

	auto Init = [&]() {
		wdW = 200;
		cap.radius = 20;
		cap.posA = Position2((sw - wdW) / 2, sh - 100);
		cap.posB= Position2((sw - wdW) / 2 + wdW, sh - 100);

		circle_.pos = { 300,0 };
		circle_.radius = 24;


		angle = 0.0f;

		frame = 0;
		isLeft = false;
		gameOverFlag_ = false;
		gameclearFlag_ = false;

	};
	auto OverCheck = [&]() {
		if (cap.posA.x < 30 || cap.posB.x < 30)
		{
			gameOverFlag_ = true;
		}
		if (cap.posA.x > 512 - 24 * 2 || cap.posB.x > 512 - 24 * 2)
		{
			gameOverFlag_ = true;
		}
	
	
	};



	while (ProcessMessage() == 0) {
		ClearDrawScreen();
		GetHitKeyStateAll(keystate);

		DrawBox(0, 0, sw, sh, 0xaaffff, true);
		
		int mx = 0, my = 0;

		circle_.pos.y += 4;

		if (cap.posA.y < 50 || cap.posB.y < 50)
		{
			gameclearFlag_ = true;
		}

		if (!gameclearFlag_)
		{
			if (keystate[KEY_INPUT_LEFT]) {
				isLeft = true;
			}
			else if (keystate[KEY_INPUT_RIGHT]) {
				isLeft = false;
			}

			if (isLeft) {
				mx = cap.posA.x;
				my = cap.posA.y;
			}
			else {
				mx = cap.posB.x;
				my = cap.posB.y;
			}

			if (keystate[KEY_INPUT_Z]) {

				angle = -0.05f;
			}
			else if (keystate[KEY_INPUT_X]) {

				angle = 0.05f;
			}
			else {
				angle = 0.0f;
			}

			//当たり判定を完成させて当たったときの反応を書いてください
			if(IsHit(cap,circle_)){
				gameOverFlag_ = true;
			}
			OverCheck();


			//カプセル回転
			Matrix rotMat=RotatePosition(Position2(mx, my), angle);
			cap.posA = MultipleVec(rotMat, cap.posA);
			cap.posB = MultipleVec(rotMat, cap.posB);
		}


		//背景の描画
		//滝
		int chipIdx = (frame/4) % 3;
		constexpr int dest_chip_size = 32;
		int destY = 48;
		while (destY < sh) {
			int destX = 0;
			while (destX < sw) {
				DrawRectExtendGraph(
					destX, destY, destX + dest_chip_size, destY+dest_chip_size,
					chipIdx * 16, 0,
					16, 16,
					cascadeH, false);
				destX += dest_chip_size;
			}
			destY += dest_chip_size;
		}

		DrawRectGraph(0, 0, 96, 0, 32, 32, chipH, true);
		DrawRectGraph(sw - 32, 0, 32, 0, 32, 32, chipH, true);
		DrawRectGraph(0, 32, 96, 32, 32, 32, chipH, true);
		DrawRectGraph(sw-32, 32, 32, 32, 32, 32, chipH, true);
		




		destY = 64;
		while (destY < sh) {
			DrawRectGraph(0, destY, 96, 64, 32, 32, chipH, true);
			DrawRectGraph(sw - 32, destY, 32, 64, 32, 32, chipH, true);
			destY += dest_chip_size;
		}

		if (circle_.pos.y > 800)
		{
			circle_.pos.x =GetRand(512);
			if (circle_.pos.x < 24)
			{
				circle_.pos.x = 24;
			}
			if (circle_.pos.x > 512 - 24*2)
			{
				circle_.pos.x = 512 - 24*2;
			}

			circle_.pos.y = 0;
		}

		
		if (gameclearFlag_)
		{
			DrawGraph(25, 300, clear, true);
			SetFontSize(30);
			DrawString(85, 500, "スペースキーでリセット", 0x000000);

			if (keystate[KEY_INPUT_SPACE])
			{
				Init();
			}

		}


		if (!gameOverFlag_)
		{
			DrawWood(cap, woodH);

			if (!gameclearFlag_)
			{
				DrawCircle(mx, my, 30, 0xff0000, false, 3);
				DrawGraph(circle_.pos.x, circle_.pos.y, circle, true);

			}

		}
		else
		{
			SetFontSize(65);
			DrawString(125, 350, "GameOver", 0x000000,0xFFFFFF);

			SetFontSize(30);
			DrawString(85, 450, "スペースキーでリセット", 0x000000);

			if (keystate[KEY_INPUT_SPACE])
			{
				Init();
			}


		}

		++frame;
		
		ScreenFlip();
	}

	DxLib_End();


}
