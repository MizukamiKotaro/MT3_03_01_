#include "WorldTransform.h"

void WorldTransform::UpdateMatrix() {
	matWorld_ = MyMatrix4x4::MakeAffinMatrix(scale_, rotation_, translation_);

	if (parent_) {
		matWorld_ = MyMatrix4x4::Multiply(matWorld_, parent_->matWorld_);
	}

}

MyVector3 WorldTransform::GetWorldPosition() {

	MyVector3 worldPos = {};
	worldPos.x = matWorld_.m[3][0];
	worldPos.y = matWorld_.m[3][1];
	worldPos.z = matWorld_.m[3][2];
	return worldPos;
}