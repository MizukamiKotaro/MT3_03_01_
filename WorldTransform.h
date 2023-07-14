#pragma once

#include "MyMatrix4x4.h"
#include "MyVector3.h"

struct WorldTransform
{
	// ローカルスケール
	MyVector3 scale_ = { 1, 1, 1 };
	// X,Y,Z軸回りのローカル回転角
	MyVector3 rotation_ = { 0, 0, 0 };
	// ローカル座標
	MyVector3 translation_ = { 0, 0, 0 };
	// ローカル → ワールド変換行列
	MyMatrix4x4 matWorld_ = {};
	// 親となるワールド変換へのポインタ
	const WorldTransform* parent_ = nullptr;

	void UpdateMatrix();

	MyVector3 GetWorldPosition();
};

