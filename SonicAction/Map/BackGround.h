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
		int handle;//背景画像の画像ハンドル
		Vector2f initpos;//初期座標
		float rate;//移動レート(小さいほど動かない)
		LayoutType type;//背景のタイプ
		int repeatX;//繰り返し距離
		Size size;//拡大後のサイズ(デフォルトは絵の実寸)
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
	///背景パーツを登録する
	///@param filapath 画像ファイルパス
	///@param pos 初期座標
	///@param rate 多重スクロール用移動レート
	///@param fromBottom 下から座標計算する(ブール型)
	///@param type 繰り返しタイプ
	///@param size サイズ(デフォルトなら-1になり画像のサイズが入る)
	///@param repeatX 繰り返し幅(デフォルト-1の場合画像のサイズになる)
	///@remarks 登録した順に描画される
	///最背面は最初に最前面は最後に登録する
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

