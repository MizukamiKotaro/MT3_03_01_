#pragma once
#include "Cube.h"

class BodyPart
{
public:
	void Initialize(const MyVector3& center, const MyVector3& size, const MyVector3& rotate, const int& image);

	void Update();

	void Draw(const MyMatrix4x4& viewProjectionMatrixMatrix, const MyMatrix4x4& viewportMatrix);



public:
	Cube cube_;
};

