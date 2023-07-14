#include "Cube.h"
#include"calc.h"
#include"Novice.h"

void Cube::Initialize(const MyVector3& center, const MyVector3& size, const MyVector3& rotate, const int& image) {
	worldTransform_.translation_ = center;
	size_ = size;
	worldTransform_.rotation_ = rotate;
	image_ = image;

	vertex_[0] = { -size_.x / 2,size.y / 2,-size.z / 2 };
	vertex_[1] = { size_.x / 2,size.y / 2,-size.z / 2 };
	vertex_[2] = { size_.x / 2,size.y / 2,size.z / 2 };
	vertex_[3] = { -size_.x / 2,size.y / 2,size.z / 2 };
	vertex_[4] = { -size_.x / 2,-size.y / 2,-size.z / 2 };
	vertex_[5] = { size_.x / 2,-size.y / 2,-size.z / 2 };
	vertex_[6] = { size_.x / 2,-size.y / 2,size.z / 2 };
	vertex_[7] = { -size_.x / 2,-size.y / 2,size.z / 2 };

}

void Cube::Update() {
	
}

MyVector3 Cube::GetWorldPosition() {

	MyVector3 worldPos = {};
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

float Cube::MakeNBCZ(const MyMatrix4x4& viewProjectionMatrix) {
	MyMatrix4x4 worldViewProjectionMatrix = MyMatrix4x4::Multiply(worldTransform_.matWorld_, viewProjectionMatrix);
	//return MyMatrix4x4::Transform({}, worldViewProjectionMatrix).z;

	return worldViewProjectionMatrix.m[3][3];
}

void Cube::Draw(const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix) {

	//MyMatrix4x4 worldMatrix = MyMatrix4x4::MakeAffinMatrix(worldTransform_.scale_,worldTransform_.rotation_,worldTransform_.translation_);
	MyMatrix4x4 worldViewProjectionMatrix = MyMatrix4x4::Multiply(worldTransform_.matWorld_, viewProjectionMatrix);

	MyVector3 nbc[8] = {};
	MyVector3 screen[8] = {};

	int imageSize = 32;

	for (int i = 0; i < 8; i++) {
		nbc[i] = MyMatrix4x4::Transform(vertex_[i], worldViewProjectionMatrix);
		screen[i] = MyMatrix4x4::Transform(nbc[i], viewportMatrix);
	}

	MyVector3 cameraDirection = { 0.0f,0.0f,1.0f };

	for (int i = 0; i < 3; i++) {
		if (Calc::Dot(cameraDirection, Calc::Cross(screen[i + 1] - screen[i], screen[i + 5] - screen[i + 1])) >= 0) {
			if (i == 1) {
				Novice::DrawQuad(int(screen[i].x), int(screen[i].y), int(screen[i + 1].x), int(screen[i + 1].y),
					int(screen[i + 4].x), int(screen[i + 4].y), int(screen[i + 5].x), int(screen[i + 5].y),
					0, 0, imageSize, imageSize, image_, 0xFFFFFFFF);
			}
			else {
				Novice::DrawQuad(int(screen[i].x), int(screen[i].y), int(screen[i + 1].x), int(screen[i + 1].y),
					int(screen[i + 4].x), int(screen[i + 4].y), int(screen[i + 5].x), int(screen[i + 5].y),
					0, 0, imageSize, imageSize, image_, 0xAAAAAAFF);
			}
			Novice::DrawLine(int(screen[i].x), int(screen[i].y), int(screen[i + 1].x), int(screen[i + 1].y), 0x000000FF);
			Novice::DrawLine(int(screen[i + 4].x), int(screen[i + 4].y), int(screen[i + 5].x), int(screen[i + 5].y), 0x000000FF);
			Novice::DrawLine(int(screen[i].x), int(screen[i].y), int(screen[i + 4].x), int(screen[i + 4].y), 0x000000FF);
			Novice::DrawLine(int(screen[i + 5].x), int(screen[i + 5].y), int(screen[i + 1].x), int(screen[i + 1].y), 0x000000FF);
		}
	}

	if (Calc::Dot(cameraDirection, Calc::Cross(screen[0] - screen[3], screen[4] - screen[0])) >= 0) {
		Novice::DrawQuad(int(screen[3].x), int(screen[3].y), int(screen[0].x), int(screen[0].y),
			int(screen[7].x), int(screen[7].y), int(screen[4].x), int(screen[4].y),
			0, 0, imageSize, imageSize, image_, 0xFFFFFFFF);
		Novice::DrawLine(int(screen[0].x), int(screen[0].y), int(screen[3].x), int(screen[3].y), 0x000000FF);
		Novice::DrawLine(int(screen[0].x), int(screen[0].y), int(screen[4].x), int(screen[4].y), 0x000000FF);
		Novice::DrawLine(int(screen[3].x), int(screen[3].y), int(screen[7].x), int(screen[7].y), 0x000000FF);
		Novice::DrawLine(int(screen[4].x), int(screen[4].y), int(screen[7].x), int(screen[7].y), 0x000000FF);
	}

	if (Calc::Dot(cameraDirection, Calc::Cross(screen[2] - screen[3], screen[1] - screen[2])) >= 0) {
		Novice::DrawQuad(int(screen[3].x), int(screen[3].y), int(screen[2].x), int(screen[2].y),
			int(screen[0].x), int(screen[0].y), int(screen[1].x), int(screen[1].y),
			0, 0, imageSize, imageSize, image_, 0x777777FF);
		Novice::DrawLine(int(screen[2].x), int(screen[2].y), int(screen[1].x), int(screen[1].y), 0x000000FF);
		Novice::DrawLine(int(screen[0].x), int(screen[0].y), int(screen[3].x), int(screen[3].y), 0x000000FF);
		Novice::DrawLine(int(screen[3].x), int(screen[3].y), int(screen[2].x), int(screen[2].y), 0x000000FF);
		Novice::DrawLine(int(screen[0].x), int(screen[0].y), int(screen[1].x), int(screen[1].y), 0x000000FF);
	}

	if (Calc::Dot(cameraDirection, Calc::Cross(screen[5] - screen[4], screen[6] - screen[5])) >= 0) {
		Novice::DrawQuad(int(screen[4].x), int(screen[4].y), int(screen[5].x), int(screen[5].y),
			int(screen[7].x), int(screen[7].y), int(screen[6].x), int(screen[6].y),
			0, 0, imageSize, imageSize, image_, 0x777777FF);
		Novice::DrawLine(int(screen[5].x), int(screen[5].y), int(screen[6].x), int(screen[6].y), 0x000000FF);
		Novice::DrawLine(int(screen[5].x), int(screen[5].y), int(screen[4].x), int(screen[4].y), 0x000000FF);
		Novice::DrawLine(int(screen[6].x), int(screen[6].y), int(screen[7].x), int(screen[7].y), 0x000000FF);
		Novice::DrawLine(int(screen[4].x), int(screen[4].y), int(screen[7].x), int(screen[7].y), 0x000000FF);
	}

}
