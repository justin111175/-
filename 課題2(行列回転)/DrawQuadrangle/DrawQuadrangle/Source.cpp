#include<DxLib.h>
#include<cmath>
#include"Geometry.h"

///�Ƃ���_�𒆐S�ɉ�]���āA���̉�]��̍��W��Ԃ��܂��B
///@param center ��]���S�_
///@param angle ��]�p�x
///@param pos ���̍��W
///@return �ϊ���̍��W
Position2 RotatePosition(const Position2& center, float angle, Position2 pos) {
	Position2 ret;

	//�@���S�����_�ɕ��s�ړ�����
	pos -= center;
	//�A���_���S�ɉ�]����
	ret.x = pos.x * cos(angle) - pos.y * sin(angle);
	ret.y = pos.x * sin(angle) + pos.y * cos(angle);

	//�B���S�����̍��W�֖߂�

	ret += center;


	//�����ɉ�]�ϊ��������Ă�������
	return ret;//�f�t�H���g�͂��̂܂ܕԂ��Ă܂��B
	//��������������āA����̓_�𒆐S�ɉ�]���s���悤�ɂ��Ă��������B
}

int WINAPI WinMain(HINSTANCE , HINSTANCE, LPSTR,int) {
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	Position2 positions[4] = {
		{100,100},//����
		{200,100},//�E��
		{200,200},//�E��
		{100,200},//����
	};

	float angle = 0.0f;
	while (ProcessMessage()==0) {
		ClearDrawScreen();

		int mx, my;
		GetMousePoint(&mx, &my);

		int minput = GetMouseInput();

		if (minput&MOUSE_INPUT_LEFT) {
			angle = 0.1f;
		}
		else if (minput&MOUSE_INPUT_RIGHT) {
			angle = -0.1f;
		}
		else {
			angle = 0.0f;
		}

		//���ꂼ��̒��_�ɉ�]�ϊ����{��
		for (auto& pos : positions) {
			pos = RotatePosition(Position2(mx, my), angle, pos);
		}

		DrawQuadrangle(
			positions[0].x,positions[0].y,
			positions[1].x, positions[1].y,
			positions[2].x, positions[2].y, 
			positions[3].x, positions[3].y, 
			0xffffff,false);
		ScreenFlip();
	}
	DxLib_End();
}