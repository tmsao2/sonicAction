#pragma once
#include "../Geometry.h"
#include <vector>

class Camera;
enum class LayoutType
{
	norepeat,
	repeat,
	random,
};

class BackGround
{
private:
	const Camera& _camera;
	struct Obj
	{
		int handle;//�w�i�摜�̉摜�n���h��
		Vector2f initpos;//�������W
		float rate;//�ړ����[�g(�������قǓ����Ȃ�)
		LayoutType type;//�w�i�̃^�C�v
		int repeatX;//�J��Ԃ�����
		Size size;//�g���̃T�C�Y(�f�t�H���g�͊G�̎���)
		Obj(int h, const Vector2f& p, float r, LayoutType lt, int repX, Size s) :
			handle(h),
			initpos(p),
			rate(r),
			type(lt),
			repeatX(repX),
			size(s) {}
	};
	std::vector<Obj> _bgparts;
public:
	BackGround(const Camera&);
	~BackGround();
	///�w�i�p�[�c��o�^����
	///@param filapath �摜�t�@�C���p�X
	///@param pos �������W
	///@param rate ���d�X�N���[���p�ړ����[�g
	///@param fromBottom ��������W�v�Z����(�u�[���^)
	///@param type �J��Ԃ��^�C�v
	///@param size �T�C�Y(�f�t�H���g�Ȃ�-1�ɂȂ�摜�̃T�C�Y������)
	///@param repeatX �J��Ԃ���(�f�t�H���g-1�̏ꍇ�摜�̃T�C�Y�ɂȂ�)
	///@remarks �o�^�������ɕ`�悳���
	///�Ŕw�ʂ͍ŏ��ɍőO�ʂ͍Ō�ɓo�^����
	void AddParts(const char* filepath,
		const Vector2f& pos,
		float rate,
		bool fromBottom,
		LayoutType type,
		Size size,
		int repeatX = -1);
	void Update();
	void DrawBg();
};

