#include<DxLib.h>
#include<cmath>
#include"common/Vector2.h"
#include <random>
#include "common/TimeCount.h"


///�����蔻��֐�
///@param posA A�̍��W
///@param radiusA A�̔��a
///@param posB B�̍��W
///@param radiusB B�̔��a
bool IsHit(const Vector2Flt& posA, float radiusA, const Vector2Flt& posB,  float radiusB) {
	//�����蔻����������Ă�������

	Vector2Flt _long = { posA.x - posB.x,posA.y - posB.y };
	float _rang = radiusA + radiusB;
	if (_long.x * _long.x + _long.y * _long.y <= _rang * _rang)
	{
		return true;
	}
	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetMainWindowText("1916229_YANG CHIHCHENG");
	if (DxLib_Init() != 0) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	//�w�i�p
	int bgH[4];
	LoadDivGraph("img/bganim.png", 4, 4, 1, 256, 192, bgH);

	int skyH = LoadGraph("img/sky.png");
	int sky2H = LoadGraph("img/sky2.png");

	auto bulletH=LoadGraph("img/bullet.png");
	int playerH[10];
	LoadDivGraph("img/player.png", 10, 5, 2, 16, 24,playerH );

	int enemyH[2];
	LoadDivGraph("img/enemy.png", 2, 2, 1, 32, 32, enemyH);

	struct Bullet {
		Vector2Flt pos;//���W
		Vector2Flt vel;//���x
		bool isActive = false;//�����Ă邩�`�H
	};


	//�e�̔��a
	float bulletRadius = 5.0f;

	//���@�̔��a
	float playerRadius = 10.0f;

	//�K����256���炢����Ƃ�
	Bullet bullets[256];

	Vector2Flt enemypos(320,25);//�G���W
	Vector2Flt playerpos(320, 400);//���@���W

	unsigned int frame = 0;//�t���[���Ǘ��p
	unsigned int bulframe = 0;//�e�؂�ւ��p�Ǘ��p

	char keystate[256];
	bool isDebugMode = false;
	int skyy = 0;
	int skyy2 = 0;
	int bgidx = 0;

	std::mt19937 mt;
	std::uniform_real_distribution<float> angleRange(-DX_PI / 8, DX_PI / 8);

	while (ProcessMessage() == 0) {
		
		ClearDrawScreen();

		GetHitKeyStateAll(keystate);

		_timeCount.Run();

		isDebugMode = keystate[KEY_INPUT_P];

		//�w�i
		DrawExtendGraph(0, 0, 640, 480, bgH[bgidx / 8], false);
		bgidx = (bgidx + 1) % 32;

		//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		skyy = (skyy + 1) % 480;
		skyy2 = (skyy2 + 2) % 480;
		DrawExtendGraph(0, skyy, 640, skyy + 480, skyH, true);
		DrawExtendGraph(0, skyy - 480, 640, skyy, skyH, true);
		DrawExtendGraph(0, skyy2, 640, skyy2 + 480, sky2H, true);
		DrawExtendGraph(0, skyy2 - 480, 640, skyy2, sky2H, true);


		//�v���C���[
		if (keystate[KEY_INPUT_RIGHT]) {
			playerpos.x = min(640,playerpos.x+4);
		}
		else if (keystate[KEY_INPUT_LEFT]) {
			playerpos.x = max(0,playerpos.x-4);
		}
		if (keystate[KEY_INPUT_UP]) {
			playerpos.y = max(0,playerpos.y-4);
		}else if (keystate[KEY_INPUT_DOWN]) {
			playerpos.y = min(480,playerpos.y+4);
		}

		int pidx = (frame/4 % 2)*5+3;
		
		if (!_timeCount.GetFlag("���G"))
		{
			DrawRotaGraph(playerpos.x, playerpos.y, 2.0f, 0.0f, playerH[pidx],true );

		}
		else
		{
			DrawRotaGraph(playerpos.x, playerpos.y, 2.0f, 0.0f, playerH[pidx], frame/10%2);
			DrawString(playerpos.x-40, playerpos.y-40, "������ꂽ", 0x000000);

		}

		if (isDebugMode) {
			//���@�̖{��(�����蔻��)
			DrawCircle(playerpos.x, playerpos.y, playerRadius, 0xffaaaa, false, 3);
		}

		//�e����
		if (frame % 12 ==0) {
			
			if (bulframe < 300)
			{
				//�v���C���[�����̒e
				auto v = playerpos - enemypos;
				for (auto& b : bullets)
				{
					if (!b.isActive) {

						b.pos = enemypos;
						b.vel = v;
						b.isActive = true;

						break;
					}
				}
			}
			else if (bulframe < 600)
			{
				//3Way�e
				auto v = playerpos - enemypos;
				
				constexpr float degreen30 = DX_PI_F / 6.0f;
				float baseAngle = atan2(v.y, v.x);
				for (int i = 0; i < 3; i++)
				{
					auto angle = baseAngle + (float)(i - 1) * degreen30;
					for (auto& b : bullets)
					{
						if (!b.isActive) {
							b.pos = enemypos;
							b.vel = Vector2Flt(cosf(angle),sinf(angle));
							b.isActive = true;
							break;
						}
					}
				}
			}
			else if (bulframe < 900)
			{
				//�S�����e
				const float diffAngle= DX_PI_F / 8.0f;
				float angle = 0;
				for (int i = 0; i < 16; i++)
				{
					for (auto& b : bullets)
					{
						if (!b.isActive)
						{
							b.pos = enemypos;
							b.vel = Vector2Flt(cosf(angle), sinf(angle)) * diffAngle;
							b.isActive = true;
							break;
						}
					}
					angle += diffAngle;
				}		
			}
			else if (bulframe < 1200)
			{
				// �����_���S�����e
				const float diffAngle = DX_PI_F / 8.0f;
				float angle = 0;
				for (int i = 0; i < 16; i++)
				{
					for (auto& b : bullets)
					{
						if (!b.isActive)
						{
							b.pos = enemypos;
							b.vel = Vector2Flt(cosf(angle), sinf(angle)) * diffAngle;
							b.isActive = true;
							break;
						}
					}
					angle += (diffAngle+angleRange(mt));
				}
			}


		}


		//�e�̍X�V����ѕ\��
		for (auto& b : bullets) {
			if (!b.isActive) {
				continue;
			}

			//�e�̌��ݍ��W�ɒe�̌��ݑ��x�����Z���Ă�������
			b.pos+= Normalize(b.vel)*3.0f;
			
			float angle = atan2(playerpos.y-b.pos.y, playerpos.x - b.pos.x);
			//�e�̊p�x��atan2�Ōv�Z���Ă��������Bangle�ɒl������񂾂�I�D
			
			DrawRotaGraph(b.pos.x, b.pos.y,1.0f,angle, bulletH, true);
			
			if (isDebugMode) {
				//�e�̖{��(�����蔻��)
				DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
			}
			//�e���E��
			if (b.pos.x + 16 < 0 || b.pos.x - 16 > 640 ||
				b.pos.y + 24 < 0 || b.pos.y - 24 > 480) {
				b.isActive = false;
			}

			//������I
			//����IsHit�͎����������Ă܂���B�����ŏ����Ă��������B
			if (!_timeCount.GetFlag("���G"))
			{
				if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {
					//�������������������Ă��������B
					b.isActive = false;
					_timeCount.Set("���G", true, 3);
					playerpos = { 320,400 };
				}
			}

		}

		//�G�̕\��
		enemypos.x = abs((int)((frame+320) % 1280) - 640);
		int eidx = (frame / 4 % 2);
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx],true);

		if (isDebugMode) {
			//�G�̖{��(�����蔻��)
			DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
		}
		
		bulframe = (bulframe + 1) % 1200;
		frame++;
		ScreenFlip();
	}

	DxLib_End();

	return 0;
}