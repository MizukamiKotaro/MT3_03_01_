#pragma once
#include "WorldTransform.h"


class Cube
{
public:

	

	void Initialize(const MyVector3& center, const MyVector3& size, const MyVector3& rotate, const int& image);

	void Update();

	float MakeNBCZ(const MyMatrix4x4& viewProjectionMatrix);

	void Draw(const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix);

	//MyVector3 GetWorldPos();

	//MyMatrix4x4 GetMat() { return worldTransform_.matWorld_; }

	const WorldTransform* GetWorldTransform() { return &worldTransform_; }
	const WorldTransform GetWorldTransform2() { return worldTransform_; }

	MyVector3 GetWorldPosition();

	MyVector3 GetTranslation() { return worldTransform_.translation_; }

	const MyVector3 GetRot() { return worldTransform_.rotation_; }

	void SetPos(const MyVector3& pos) { worldTransform_.translation_ = pos; }

	void SetRot(const MyVector3& rot) { worldTransform_.rotation_ = rot; }

	void UpdateMatrix() { worldTransform_.UpdateMatrix(); }

	void SetParent(const WorldTransform* parent){ worldTransform_.parent_ = parent; }

	void SetWorldTransform(const WorldTransform worldTransform) { worldTransform_ = worldTransform; }

	
	//MyVector3 GetRotate();

public:
	

private:
	
	WorldTransform worldTransform_;
	MyVector3 vertex_[8] = {};
	MyVector3 size_ = {};
	int image_ = 0;


};

