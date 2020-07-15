#include"Geometry.h"
#include<DxLib.h>
#include<cmath>


void
Rect::Draw() {
	DxLib::DrawBox(Left()*2, Top()*2, Right()*2, Bottom()*2, 0xffffffff, false);
}

void
Rect::Draw(Vector2& offset) {
	DxLib::DrawBox((Left()+offset.x)*2, (Top()+offset.y)*2, (Right()+offset.x)*2, (Bottom()+offset.y)*2, 0xffffffff, false);
}

void
Vector2::operator*=(float scale) {
	x *= scale;
	y *= scale;
}

Vector2
Vector2::operator*(float scale) {
	return Vector2(x*scale,y*scale);
}

Vector2 operator+(const Vector2& va, const Vector2 vb) {
	Vector2 ret;
	ret.x = va.x+vb.x;
	ret.y = va.y + vb.y;
	return ret;
}

Vector2 operator-(const Vector2& va, const Vector2 vb){
	return Vector2(va.x-vb.x,va.y-vb.y);
}

float
Vector2::Magnitude()const {
	return hypot(x, y);
}


void 
Vector2::Normalize() {
	float mag = Magnitude();
	x /= mag;
	y /= mag;
}


Vector2
Vector2::Normalized() {
	float mag = Magnitude();
	return Vector2(x / mag,	y /mag);
}


///���ς�Ԃ�
float
Dot(const Vector2& va, const Vector2& vb) {
	return va.x*vb.x + va.y*vb.y;
}

///�O�ς�Ԃ�
float
Cross(const Vector2& va, const Vector2& vb) {
	return va.x*vb.y - vb.x*va.y;
}

///���ω��Z�q
float 
operator*(const Vector2& va, const Vector2& vb) {
	return Dot(va, vb);
}

///�O�ω��Z�q
float 
operator%(const Vector2& va, const Vector2& vb) {
	return Cross(va, vb);
}


void 
Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
}
void 
Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
}


///�Q�̍s��̏�Z��Ԃ�
///@param lmat ���Ӓl(�s��)
///@param rmat �E�Ӓl(�s��)
///@attention ��Z�̏����ɒ��ӂ��Ă�������
Matrix 
MultipleMat(const Matrix& lmat, const Matrix& rmat) {
	Matrix ret ;
	
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{

			//int z = 0;
			//while(z<3)
			//{
			//	ret.m[j][i] += lmat.m[j][z] * rmat.m[z][i];
			//	z++;

			//}

			ret.m[j][i] =	lmat.m[j][0] * rmat.m[0][i] +
							lmat.m[j][1] * rmat.m[1][i] +
							lmat.m[j][2] * rmat.m[2][i];

		}

	}


	return ret;

}

///�x�N�g���ɑ΂��čs���Z��K�p���A���ʂ̃x�N�g����Ԃ�
///@param mat �s��
///@param vec �x�N�g��
Vector2 
MultipleVec(const Matrix& mat, const Vector2& vec) {
	Vector2 ret;
	ret = { mat.m[0][0] * vec.x + mat.m[0][1] * vec.y+	mat.m[0][2],
			mat.m[1][0] * vec.x + mat.m[1][1] * vec.y + mat.m[1][2]};


	return ret;
}


///�P�ʍs���Ԃ�
Matrix IdentityMat() {
	Matrix ret;
	ret = {	1,0,0,
			0,1,0,
			0,0,1 };

	//for (int i= 0; i < 3; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		if (i == j)
	//		{
	//			ret.m[i][j] = 1;
	//		}
	//	}
	//}
	
	return ret;
}

///���s�ړ��s���Ԃ�
///@param x X�������s�ړ���
///@param y Y�������s�ړ���
Matrix TranslateMat(float x, float y) {
	Matrix ret = {	1,0,x,
					0,1,y,
					0,0,1};
	return ret;
}

///��]�s���Ԃ�
///@param angle ��]�p�x
Matrix RotateMat(float angle) {
	Matrix ret = {	cosf(angle),	-sinf(angle),	0,
					sinf(angle),	cosf(angle),	0,
					0,				0,				1};


	return ret;
}