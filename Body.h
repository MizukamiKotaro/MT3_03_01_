#pragma once

#include "Cube.h"
#include "Input.h"

class Body
{
public:

	~Body();

	void Initialize(const MyVector3& pos, const float height, const MyVector3& rotate, const int& image);

	void Update();

	void Draw(const MyMatrix4x4& viewProjectionMatrixMatrix, const MyMatrix4x4& viewportMatrix);

private:

	void PartCreate(const MyVector3& pos, const float height, const MyVector3& rotate, const int& image);

	void UpdateMatrix();

	void StandInitialize();

	void WalkInitialize();

	void RunInitialize();

	void JumpInitialize();

	void JumpInitialize2();

	void JumpInitialize3();

	void JumpInitialize4();

	void JumpInitialize5();

	void StandUpdate();

	void WalkUpdate();

	void RunUpdate();

	void JumpUpdate();

	void SetRotates();

	void SetRots(int maxFrame);

	void WithImGui();

	void SetUnderRot();

private:

	Input* input_ = nullptr;

	enum class Phase {
		Stand,
		Walk,
		Run,
		Jump
	};

	static void(Body::* spPhaseUpdateTable[])();

	Phase phase_ = Phase::Stand;

	int nowFrame_ = 0;

	bool IsHalf = true;

	bool IsStand = true;

	MyVector3 easeRot_[15][2] = {};

	MyVector3 easeLowerBackTranslation_[2] = {};

	float lowerBackHeight_ = 0;

private:

	///関節
	//手首
	WorldTransform leftWrist_;
	WorldTransform rightWrist_;
	//肘
	WorldTransform leftElbow_;
	WorldTransform rightElbow_;
	//肩
	WorldTransform leftShoulder_;
	WorldTransform rightShoulder_;
	//首
	WorldTransform neck_;
	//腹
	WorldTransform stomach_;
	//股関節
	WorldTransform leftHipJoint_;
	WorldTransform rightHipJoint_;
	//膝
	WorldTransform leftKnee_;
	WorldTransform rightKnee_;
	//くるぶし
	WorldTransform leftAnkle_;
	WorldTransform rightAnkle_;

	//足元
	WorldTransform foot_;

	///部位
	//手
	Cube* leftHand_ = nullptr;
	Cube* rightHand_ = nullptr;
	//前腕
	Cube* leftForeArm_ = nullptr;
	Cube* rightForeArm_ = nullptr;
	//上腕
	Cube* leftUpperArm_ = nullptr;
	Cube* rightUpperArm_ = nullptr;
	//頭
	Cube* head_ = nullptr;
	//胸
	Cube* chest_ = nullptr;
	//腰
	Cube* lowerBack_ = nullptr;
	//太もも
	Cube* leftThigh_ = nullptr;
	Cube* rightThigh_ = nullptr;
	//ふくらはぎ
	Cube* leftCalf_ = nullptr;
	Cube* rightCalf_ = nullptr;
	//足
	Cube* leftLeg_ = nullptr;
	Cube* rightLeg_ = nullptr;

};

