#include "Body.h"
#include<imgui.h>
#include "Ease.h"
#include"calc.h"

Body::~Body() {
	
	delete leftHand_;
	delete rightHand_;
	delete leftForeArm_;
	delete rightForeArm_;
	delete leftUpperArm_;
	delete rightUpperArm_;
	delete head_;
	delete chest_;
	delete lowerBack_;
	delete leftThigh_;
	delete rightThigh_;
	delete leftCalf_;
	delete rightCalf_;
	delete leftLeg_;
	delete rightLeg_;
}

void Body::Initialize(const MyVector3& pos, const float height, const MyVector3& rotate, const int& image) {

	PartCreate(pos, height, rotate, image);

	input_ = Input::GetInstance();

	lowerBackHeight_ = height / 2;

}

void Body::SetRotates() {
	
	for (int i = 0; i < 2; i++) {
		easeRot_[0][i] = leftWrist_.rotation_;
		easeRot_[1][i] = rightWrist_.rotation_;

		easeRot_[2][i] = leftElbow_.rotation_;
		easeRot_[3][i] = rightElbow_.rotation_;

		easeRot_[4][i] = leftShoulder_.rotation_;
		easeRot_[5][i] = rightShoulder_.rotation_;

		easeRot_[6][i] = neck_.rotation_;

		easeRot_[7][i] = stomach_.rotation_;

		easeRot_[8][i] = leftHipJoint_.rotation_;
		easeRot_[9][i] = rightHipJoint_.rotation_;

		easeRot_[10][i] = leftKnee_.rotation_;
		easeRot_[11][i] = rightKnee_.rotation_;

		easeRot_[12][i] = leftAnkle_.rotation_;
		easeRot_[13][i] = rightAnkle_.rotation_;

		easeRot_[14][i] = lowerBack_->GetRot();
	}
}

void Body::SetRots(int maxFrame) {
	leftWrist_.rotation_ = Ease::UseEase(easeRot_[0][0], easeRot_[0][1], nowFrame_, maxFrame, Ease::EaseType::EaseInOutSine, 2);
	rightWrist_.rotation_ = Ease::UseEase(easeRot_[1][0], easeRot_[1][1], nowFrame_, maxFrame, Ease::EaseType::EaseInOutSine, 2);

	leftElbow_.rotation_ = Ease::UseEase(easeRot_[2][0], easeRot_[2][1], nowFrame_, maxFrame, Ease::EaseType::EaseInOutSine, 2);
	rightElbow_.rotation_ = Ease::UseEase(easeRot_[3][0], easeRot_[3][1], nowFrame_, maxFrame, Ease::EaseType::EaseInOutSine, 2);

	leftShoulder_.rotation_ = Ease::UseEase(easeRot_[4][0], easeRot_[4][1], nowFrame_, maxFrame, Ease::EaseType::EaseInOutSine, 2);
	rightShoulder_.rotation_ = Ease::UseEase(easeRot_[5][0], easeRot_[5][1], nowFrame_, maxFrame, Ease::EaseType::EaseInOutSine, 2);

	neck_.rotation_ = Ease::UseEase(easeRot_[6][0], easeRot_[6][1], nowFrame_, maxFrame, Ease::EaseType::EaseInOutSine, 2);

	stomach_.rotation_ = Ease::UseEase(easeRot_[7][0], easeRot_[7][1], nowFrame_, maxFrame, Ease::EaseType::EaseInOutSine, 2);

	leftHipJoint_.rotation_ = Ease::UseEase(easeRot_[8][0], easeRot_[8][1], nowFrame_, maxFrame, Ease::EaseType::EaseInOutSine, 2);
	rightHipJoint_.rotation_ = Ease::UseEase(easeRot_[9][0], easeRot_[9][1], nowFrame_, maxFrame, Ease::EaseType::EaseInOutSine, 2);

	leftKnee_.rotation_ = Ease::UseEase(easeRot_[10][0], easeRot_[10][1], nowFrame_, maxFrame, Ease::EaseType::EaseInOutSine, 2);
	rightKnee_.rotation_ = Ease::UseEase(easeRot_[11][0], easeRot_[11][1], nowFrame_, maxFrame, Ease::EaseType::EaseInOutSine, 2);

	leftAnkle_.rotation_ = Ease::UseEase(easeRot_[12][0], easeRot_[12][1], nowFrame_, maxFrame, Ease::EaseType::EaseInOutSine, 2);
	rightAnkle_.rotation_ = Ease::UseEase(easeRot_[13][0], easeRot_[13][1], nowFrame_, maxFrame, Ease::EaseType::EaseInOutSine, 2);

	lowerBack_->SetRot(Ease::UseEase(easeRot_[14][0], easeRot_[14][1], nowFrame_, maxFrame, Ease::EaseType::EaseInOutSine, 2));
}

void Body::SetUnderRot() {
	float pi = 3.14f;

	lowerBack_->UpdateMatrix();
	leftHipJoint_.UpdateMatrix();
	leftThigh_->UpdateMatrix();
	leftKnee_.UpdateMatrix();

	float len[4] = {};
	len[0] = Calc::MakeLength(leftKnee_.translation_) + Calc::MakeLength(leftThigh_->GetTranslation());
	len[1] = Calc::MakeLength(leftKnee_.GetWorldPosition(), leftAnkle_.GetWorldPosition());
	len[2] = Calc::MakeLength(leftHipJoint_.GetWorldPosition(), leftAnkle_.GetWorldPosition());
	len[3] = Calc::MakeLength(leftCalf_->GetTranslation()) + Calc::MakeLength(leftAnkle_.translation_);

	leftHipJoint_.rotation_.x = -Calc::MakeRadian(len[1], len[0], len[2]) - Calc::MakeRadian(len[3], len[0], len[2]);
	rightHipJoint_.rotation_.x = leftHipJoint_.rotation_.x;

	leftKnee_.rotation_.x = pi - Calc::MakeRadian(len[2], len[0], len[3]);
	rightKnee_.rotation_.x = leftKnee_.rotation_.x;

	lowerBack_->UpdateMatrix();
	leftHipJoint_.UpdateMatrix();
	leftThigh_->UpdateMatrix();
	leftKnee_.UpdateMatrix();

	MyVector3 a = leftKnee_.GetWorldPosition();
	MyVector3 b = leftAnkle_.GetWorldPosition();

	a.y = b.y;

	leftAnkle_.rotation_.x = -pi / 2 + Calc::MakeRadian(b, a, leftKnee_.GetWorldPosition());
	rightAnkle_.rotation_.x = leftAnkle_.rotation_.x;
}

void Body::StandInitialize() {
	nowFrame_ = 0;

	SetRotates();

	for (int i = 0; i < 15; i++) {
		easeRot_[i][1] = {};
	}

}

void Body::WalkInitialize() {
	nowFrame_ = 0;
	IsStand = false;

	SetRotates();

	float pi = 3.14f;

	if (IsHalf) {
		easeRot_[4][1].x = -pi / 6;
		easeRot_[2][1].x = -pi / 6;

		easeRot_[5][1].x = pi / 6;
		easeRot_[3][1].x = 0.0f;

		easeRot_[9][1].x = -pi / 6;
		easeRot_[11][1].x = pi / 6;

		easeRot_[8][1].x = pi / 12;
		easeRot_[10][1].x = 0.0f;

	}
	else {
		easeRot_[5][1].x = -pi / 6;
		easeRot_[3][1].x = -pi / 6;

		easeRot_[4][1].x = pi / 6;
		easeRot_[2][1].x = 0.0f;

		easeRot_[9][1].x = pi / 12;
		easeRot_[11][1].x = 0.0f;

		easeRot_[8][1].x = -pi / 6;
		easeRot_[10][1].x = pi / 6;

	}
}

void Body::RunInitialize() {
	nowFrame_ = 0;
	IsStand = false;

	SetRotates();

	float pi = 3.14f;

	if (IsHalf) {
		easeRot_[4][1].x = -pi / 6;
		easeRot_[2][1].x = -pi / 2;

		easeRot_[5][1].x = pi / 4;
		easeRot_[3][1].x = -pi / 2;

		easeRot_[9][1].x = -pi / 2;
		easeRot_[11][1].x = pi / 2;

		easeRot_[8][1].x = pi / 12;
		easeRot_[10][1].x = 0.0f;

	}
	else {
		easeRot_[5][1].x = -pi / 6;
		easeRot_[3][1].x = -pi / 2;

		easeRot_[4][1].x = pi / 4;
		easeRot_[2][1].x = -pi / 2;

		easeRot_[9][1].x = pi / 12;
		easeRot_[11][1].x = 0.0f;

		easeRot_[8][1].x = -pi / 2;
		easeRot_[10][1].x = pi / 2;

	}
}

void Body::JumpInitialize() {
	nowFrame_ = 0;
	IsStand = true;

	SetRotates();

	for (int i = 0; i < 15; i++) {
		easeRot_[i][1] = {};
	}

	float pi = 3.14f;

	easeRot_[4][1].x = -pi / 2;
	easeRot_[2][1].x = -pi / 2;

	easeRot_[5][1].x = -pi / 2;
	easeRot_[3][1].x = -pi / 2;

}

void Body::JumpInitialize2() {
	//nowFrame_ = 0;

	SetRotates();

	for (int i = 0; i < 15; i++) {
		easeRot_[i][1] = {};
	}

	float pi = 3.14f;

	easeRot_[4][1].x = pi / 3;
	easeRot_[2][1].x = 0.0f;

	easeRot_[5][1].x = pi / 3;
	easeRot_[3][1].x = 0.0f;

	easeLowerBackTranslation_[0] = lowerBack_->GetTranslation();
	easeLowerBackTranslation_[1] = lowerBack_->GetTranslation();

	easeLowerBackTranslation_[1].y = easeLowerBackTranslation_[1].y * 2 / 3;
	easeLowerBackTranslation_[1].z = -easeLowerBackTranslation_[1].y / 10;

	easeRot_[14][1].x = pi / 4;
}

void Body::JumpInitialize3() {
	SetRotates();

	float pi = 3.14f;

	for (int i = 0; i < 15; i++) {
		easeRot_[i][1] = {};
	}

	easeRot_[4][1].x = -pi / 4 * 3;
	easeRot_[2][1].x = -pi / 6;

	easeRot_[5][1].x = -pi / 4 * 3;
	easeRot_[3][1].x = -pi / 6;

	easeLowerBackTranslation_[0] = lowerBack_->GetTranslation();
	easeLowerBackTranslation_[1] = lowerBack_->GetTranslation();

	easeLowerBackTranslation_[1].z = 0.0f;

	easeRot_[14][1].x = 0.0f;
}

void Body::JumpInitialize4() {
	//nowFrame_ = 0;

	SetRotates();

	for (int i = 0; i < 15; i++) {
		easeRot_[i][1] = {};
	}

	float pi = 3.14f;

	easeRot_[4][1].x = pi / 6;
	easeRot_[2][1].x = 0.0f;

	easeRot_[5][1].x = pi / 6;
	easeRot_[3][1].x = 0.0f;

	easeLowerBackTranslation_[0] = lowerBack_->GetTranslation();
	easeLowerBackTranslation_[1] = lowerBack_->GetTranslation();

	easeLowerBackTranslation_[1].y = easeLowerBackTranslation_[1].y * 3 / 4;
	easeLowerBackTranslation_[1].z = -easeLowerBackTranslation_[1].y / 10;

	easeRot_[14][1].x = pi / 6;
}

void Body::JumpInitialize5() {
	//nowFrame_ = 0;

	SetRotates();

	for (int i = 0; i < 15; i++) {
		easeRot_[i][1] = {};
	}

	

	easeLowerBackTranslation_[0] = lowerBack_->GetTranslation();
	easeLowerBackTranslation_[1] = lowerBack_->GetTranslation();

	easeLowerBackTranslation_[1].y = lowerBackHeight_;
	easeLowerBackTranslation_[1].z = 0.0f;
}

void Body::StandUpdate() {

	if (!IsStand) {
		int maxFrame = 30;

		nowFrame_++;

		SetRots(maxFrame);

		if (nowFrame_ == maxFrame) {
			IsStand = true;
			IsHalf = true;
		}
	}

}

void Body::WalkUpdate() {

	int maxFrame = 40;

	nowFrame_++;

	SetRots(maxFrame);

	if (nowFrame_ == maxFrame) {

		if (IsHalf) {
			IsHalf = false;
		}
		else {
			IsHalf = true;
		}

		WalkInitialize();
	}

}

void Body::RunUpdate() {
	int maxFrame = 30;

	nowFrame_++;

	SetRots(maxFrame);

	if (nowFrame_ == maxFrame) {

		if (IsHalf) {
			IsHalf = false;
		}
		else {
			IsHalf = true;
		}

		RunInitialize();
	}
}

void Body::JumpUpdate() {
	int maxFrame = 180;

	nowFrame_++;

	if (nowFrame_ <= 20) {
		SetRots(20);

		if (nowFrame_ == 20) {
			JumpInitialize2();
		}
	}

	if (20 < nowFrame_ && nowFrame_ <= 40) {
		
		if (nowFrame_ <= 35) {
			leftElbow_.rotation_ = Ease::UseEase(easeRot_[2][0], easeRot_[2][1], nowFrame_ - 20, 15, Ease::EaseType::EaseInOutSine, 2);
			rightElbow_.rotation_ = Ease::UseEase(easeRot_[3][0], easeRot_[3][1], nowFrame_ - 20, 15, Ease::EaseType::EaseInOutSine, 2);
		}

		leftShoulder_.rotation_ = Ease::UseEase(easeRot_[4][0], easeRot_[4][1], nowFrame_ - 20, 20, Ease::EaseType::EaseInOutSine, 2);
		rightShoulder_.rotation_ = Ease::UseEase(easeRot_[5][0], easeRot_[5][1], nowFrame_ - 20, 20, Ease::EaseType::EaseInOutSine, 2);

		lowerBack_->SetRot(Ease::UseEase(easeRot_[14][0], easeRot_[14][1], nowFrame_ - 20, 20, Ease::EaseType::EaseInOutSine, 2));

		lowerBack_->SetPos(Ease::UseEase(easeLowerBackTranslation_[0], easeLowerBackTranslation_[1], nowFrame_ - 20, 20, Ease::EaseType::EaseInOutSine, 2));

		SetUnderRot();

		if (nowFrame_ == 40) {
			JumpInitialize3();
		}
	}

	if (40 < nowFrame_ && nowFrame_ <= 100) {

		MyVector3 pos = {};

		pos.y = 0.1f -0.002f * (nowFrame_ - 40);

		nowFrame_ -= 40;
		SetRots(60);
		nowFrame_ += 40;

		if (nowFrame_ <= 50) {

			lowerBack_->SetPos(Ease::UseEase(easeLowerBackTranslation_[0], easeLowerBackTranslation_[1], nowFrame_ - 40, 10, Ease::EaseType::EaseInOutSine, 2));



		}
		else {
			MyVector3 a = lowerBack_->GetTranslation() + pos;

			if (nowFrame_ >= 80 && a.y <= lowerBackHeight_) {
				a.y = lowerBackHeight_;
			}

			lowerBack_->SetPos(a);
		}

		


	}

	if (nowFrame_ > 100 && nowFrame_ <= 126) {
		MyVector3 pos = {};

		pos.y = 0.1f - 0.002f * (nowFrame_ - 40);

		/*nowFrame_ -= 40;
		SetRots(60);
		nowFrame_ += 40;

		if (nowFrame_ <= 60) {

			lowerBack_->SetPos(Ease::UseEase(easeLowerBackTranslation_[0], easeLowerBackTranslation_[1], nowFrame_ - 40, 20, Ease::EaseType::EaseInOutSine, 2));

		}*/

		MyVector3 a = lowerBack_->GetTranslation() + pos;

		if (a.y <= lowerBackHeight_) {
			a.y = lowerBackHeight_;

			JumpInitialize4();
		}

		lowerBack_->SetPos(a);
	}

	if (115 + 11 < nowFrame_ && nowFrame_ <= 145 + 11) {

		if (nowFrame_ <= 135 + 11) {
			leftElbow_.rotation_ = Ease::UseEase(easeRot_[2][0], easeRot_[2][1], nowFrame_ - 115 - 11, 20, Ease::EaseType::EaseInOutSine, 2);
			rightElbow_.rotation_ = Ease::UseEase(easeRot_[3][0], easeRot_[3][1], nowFrame_ - 115 - 11, 20, Ease::EaseType::EaseInOutSine, 2);
		}

		leftShoulder_.rotation_ = Ease::UseEase(easeRot_[4][0], easeRot_[4][1], nowFrame_ - 115 - 11, 30, Ease::EaseType::EaseInOutSine, 2);
		rightShoulder_.rotation_ = Ease::UseEase(easeRot_[5][0], easeRot_[5][1], nowFrame_ - 115 - 11, 30, Ease::EaseType::EaseInOutSine, 2);

		lowerBack_->SetRot(Ease::UseEase(easeRot_[14][0], easeRot_[14][1], nowFrame_ - 115 - 11, 30, Ease::EaseType::EaseInOutSine, 2));

		lowerBack_->SetPos(Ease::UseEase(easeLowerBackTranslation_[0], easeLowerBackTranslation_[1], nowFrame_ - 115 - 11, 30, Ease::EaseType::EaseInOutSine, 2));

		SetUnderRot();

		if (nowFrame_ == 145 + 11) {
			JumpInitialize5();
		}
	}

	if (145 + 11 < nowFrame_) {
		nowFrame_ -= 145 + 11;
		SetRots(35);
		nowFrame_ += 145 + 11;

		lowerBack_->SetPos(Ease::UseEase(easeLowerBackTranslation_[0], easeLowerBackTranslation_[1], nowFrame_ - 145 - 11, 35, Ease::EaseType::EaseInOutSine, 2));
	}



	if (nowFrame_ == maxFrame + 11) {

		IsHalf = true;

		phase_ = Phase::Stand;

		nowFrame_ = 0;
	}
}

void Body::WithImGui() {
	WorldTransform tmp = lowerBack_->GetWorldTransform2();

	ImGui::Begin("Body");
	//ImGui::Checkbox("IsDebugCamera", &isDebug_);
	ImGui::DragFloat3("translation", &foot_.translation_.x, 0.01f);
	ImGui::SliderFloat3("rotate", &foot_.rotation_.x, -3.14f, 3.14f);

	ImGui::SliderFloat3("neckRotate", &neck_.rotation_.x, -3.14f, 3.14f);
	ImGui::SliderFloat3("leftShoulderRotate", &leftShoulder_.rotation_.x, -3.14f, 3.14f);
	ImGui::SliderFloat3("leftElbowRotate", &leftElbow_.rotation_.x, -3.14f, 3.14f);
	ImGui::SliderFloat3("leftWristRotate", &leftWrist_.rotation_.x, -3.14f, 3.14f);

	ImGui::SliderFloat3("rightShoulderRotate", &rightShoulder_.rotation_.x, -3.14f, 3.14f);
	ImGui::SliderFloat3("rightElbowRotate", &rightElbow_.rotation_.x, -3.14f, 3.14f);
	ImGui::SliderFloat3("rightWristRotate", &rightWrist_.rotation_.x, -3.14f, 3.14f);

	ImGui::SliderFloat3("leftHipJointRotate", &leftHipJoint_.rotation_.x, -3.14f, 3.14f);
	ImGui::SliderFloat3("leftKneeRotate", &leftKnee_.rotation_.x, -3.14f, 3.14f);
	ImGui::SliderFloat3("leftAnkleRotate", &leftAnkle_.rotation_.x, -3.14f, 3.14f);

	ImGui::SliderFloat3("stomachRotate", &stomach_.rotation_.x, -3.14f, 3.14f);
	ImGui::SliderFloat3("lowerBackRotate", &tmp.rotation_.x, -3.14f, 3.14f);

	ImGui::SliderFloat3("rightHipJointRotate", &rightHipJoint_.rotation_.x, -3.14f, 3.14f);
	ImGui::SliderFloat3("rightKneeRotate", &rightKnee_.rotation_.x, -3.14f, 3.14f);
	ImGui::SliderFloat3("rightAnkleRotate", &rightAnkle_.rotation_.x, -3.14f, 3.14f);
	ImGui::End();

	lowerBack_->SetWorldTransform(tmp);
}

void (Body::* Body::spPhaseUpdateTable[])() {
	&Body::StandUpdate,
	&Body::WalkUpdate,
	&Body::RunUpdate,
	&Body::JumpUpdate,

};

void Body::Body::Update() {

	WithImGui();
	
	if (input_->PushKey(DIK_1) && phase_ != Phase::Stand && phase_ != Phase::Jump) {
		phase_ = Phase::Stand;

		StandInitialize();
	}
	else if (input_->PushKey(DIK_2) && phase_ != Phase::Walk && phase_ != Phase::Jump) {
		phase_ = Phase::Walk;

		WalkInitialize();
	}
	else if (input_->PushKey(DIK_3) && phase_ != Phase::Run && phase_ != Phase::Jump) {
		phase_ = Phase::Run;

		RunInitialize();
	}
	else if (input_->PushKey(DIK_4) && phase_ != Phase::Jump) {
		phase_ = Phase::Jump;

		JumpInitialize();
	}

	(this->*spPhaseUpdateTable[static_cast<size_t>(phase_)])();

	UpdateMatrix();
	
}

void Body::Draw(const MyMatrix4x4& viewProjectionMatrixMatrix, const MyMatrix4x4& viewportMatrix) {
	
	

	struct Hoge
	{
		float z[15] = {};
		int num[15] = {};
	};

	Hoge hoge = {};

	hoge.z[0] = leftHand_->MakeNBCZ(viewProjectionMatrixMatrix);
	hoge.z[1] = rightHand_->MakeNBCZ(viewProjectionMatrixMatrix);
	hoge.z[2] = leftForeArm_->MakeNBCZ(viewProjectionMatrixMatrix);
	hoge.z[3] = rightForeArm_->MakeNBCZ(viewProjectionMatrixMatrix);
	hoge.z[4] = leftUpperArm_->MakeNBCZ(viewProjectionMatrixMatrix);
	hoge.z[5] = rightUpperArm_->MakeNBCZ(viewProjectionMatrixMatrix);
	hoge.z[6] = head_->MakeNBCZ(viewProjectionMatrixMatrix);
	hoge.z[7] = chest_->MakeNBCZ(viewProjectionMatrixMatrix);
	hoge.z[8] = lowerBack_->MakeNBCZ(viewProjectionMatrixMatrix);
	hoge.z[9] = leftThigh_->MakeNBCZ(viewProjectionMatrixMatrix);
	hoge.z[10] = rightThigh_->MakeNBCZ(viewProjectionMatrixMatrix);
	hoge.z[11] = leftCalf_->MakeNBCZ(viewProjectionMatrixMatrix);
	hoge.z[12] = rightCalf_->MakeNBCZ(viewProjectionMatrixMatrix);
	hoge.z[13] = leftLeg_->MakeNBCZ(viewProjectionMatrixMatrix);
	hoge.z[14] = rightLeg_->MakeNBCZ(viewProjectionMatrixMatrix);

	for (int i = 0; i < 15; i++) {
		hoge.num[i] = i;
	}

	float tmp = 0.0f;
	int kamo = 0;
	int index = 0;

	for (int i = 0; i < 15; i++) {
		
		for (int j = i + 1; j < 15; j++) {
			
			if (hoge.z[i] < hoge.z[j]) {
				tmp = hoge.z[i];
				hoge.z[i] = hoge.z[j];
				hoge.z[j] = tmp;
				kamo = hoge.num[i];
				hoge.num[i] = hoge.num[j];
				hoge.num[j] = kamo;
			}

		}
	}


	for (int i = 0; i < 15; i++) {
		switch (hoge.num[i])
		{
		case 0:
			leftHand_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
			break;
		case 1:
			rightHand_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
			break;
		case 2:
			leftForeArm_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
			break;
		case 3:
			rightForeArm_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
			break;
		case 4:
			leftUpperArm_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
			break;
		case 5:
			rightUpperArm_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
			break;
		case 6:
			head_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
			break;
		case 7:
			chest_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
			break;
		case 8:
			lowerBack_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
			break;
		case 9:
			leftThigh_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
			break;
		case 10:
			rightThigh_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
			break;
		case 11:
			leftCalf_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
			break;
		case 12:
			rightCalf_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
			break;
		case 13:
			leftLeg_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
			break;
		case 14:
			rightLeg_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
			break;
		default:
			break;
		}
		
	}


	/*leftHand_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
	rightHand_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
	leftForeArm_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
	rightForeArm_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
	leftUpperArm_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
	rightUpperArm_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
	head_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
	chest_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
	lowerBack_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
	leftThigh_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
	rightThigh_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
	leftCalf_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
	rightCalf_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
	leftLeg_->Draw(viewProjectionMatrixMatrix, viewportMatrix);
	rightLeg_->Draw(viewProjectionMatrixMatrix, viewportMatrix);*/

}


void Body::PartCreate(const MyVector3& pos, const float height, const MyVector3& rotate, const int& image) {
	MyVector3 tmp = pos;
	tmp.y = tmp.y + height / 2.0f;
	MyVector3 size = { height / 7.0f,height / 7.0f,height / 7.0f * 0.4f };

	foot_.translation_ = pos;
	foot_.rotation_ = rotate;
	foot_.UpdateMatrix();

	lowerBack_ = new Cube();
	lowerBack_->Initialize({ 0.0f,height / 2.0f,0.0f }, size, {}, image);
	lowerBack_->SetParent(&foot_);
	lowerBack_->UpdateMatrix();

	leftHipJoint_.parent_ = lowerBack_->GetWorldTransform();
	leftHipJoint_.translation_ = { -size.x / 3,-size.y / 2,0.0f };
	leftHipJoint_.rotation_ = {};
	leftHipJoint_.UpdateMatrix();

	rightHipJoint_.parent_ = lowerBack_->GetWorldTransform();
	rightHipJoint_.translation_ = { size.x / 3,-size.y / 2,0.0f };
	rightHipJoint_.rotation_ = {};
	rightHipJoint_.UpdateMatrix();

	leftThigh_ = new Cube();
	leftThigh_->Initialize({ 0.0f,-size.y * 3.0f / 4.4f,0.0f }, { size.x / 3.0f,size.y * 3.0f / 2.6f,size.z }, {}, image);
	leftThigh_->SetParent(&leftHipJoint_);
	leftThigh_->UpdateMatrix();

	rightThigh_ = new Cube();
	rightThigh_->Initialize({ 0.0f,-size.y * 3.0f / 4.4f,0.0f }, { size.x / 3.0f,size.y * 3.0f / 2.6f,size.z }, {}, image);
	rightThigh_->SetParent(&rightHipJoint_);
	rightThigh_->UpdateMatrix();
	//
	leftKnee_.parent_ = leftThigh_->GetWorldTransform();
	leftKnee_.translation_ = { 0.0f,-size.y * 3.0f / 4.4f,0.0f };
	leftKnee_.rotation_ = {};
	leftKnee_.UpdateMatrix();

	rightKnee_.parent_ = rightThigh_->GetWorldTransform();
	rightKnee_.translation_ = { 0.0f,-size.y * 3.0f / 4.4f,0.0f };
	rightKnee_.rotation_ = {};
	rightKnee_.UpdateMatrix();

	leftCalf_ = new Cube();
	leftCalf_->Initialize({ 0.0f,-size.y * 3.0f / 4.4f,0.0f }, { size.x / 3.0f,size.y * 3.0f / 2.6f,size.z }, {}, image);
	leftCalf_->SetParent(&leftKnee_);
	leftCalf_->UpdateMatrix();

	rightCalf_ = new Cube();
	rightCalf_->Initialize({ 0.0f,-size.y * 3.0f / 4.4f,0.0f }, { size.x / 3.0f,size.y * 3.0f / 2.6f,size.z }, {}, image);
	rightCalf_->SetParent(&rightKnee_);
	rightCalf_->UpdateMatrix();

	leftAnkle_.parent_ = leftCalf_->GetWorldTransform();
	leftAnkle_.translation_ = { 0.0f,-size.y * 3.0f / 3.8f,0.0f };
	leftAnkle_.rotation_ = {};
	leftAnkle_.UpdateMatrix();

	rightAnkle_.parent_ = rightCalf_->GetWorldTransform();
	rightAnkle_.translation_ = { 0.0f,-size.y * 3.0f / 3.8f,0.0f };
	rightAnkle_.rotation_ = {};
	rightAnkle_.UpdateMatrix();

	leftLeg_ = new Cube();
	leftLeg_->Initialize({ 0.0f,0.0f,size.z / 1.7f}, { size.x / 3.0f,size.y / 4.0f,size.z * 2 }, {}, image);
	leftLeg_->SetParent(&leftAnkle_);
	leftLeg_->UpdateMatrix();

	rightLeg_ = new Cube();
	rightLeg_->Initialize({ 0.0f,0.0f,size.z / 1.7f}, { size.x / 3.0f,size.y / 4.0f,size.z * 2 }, {}, image);
	rightLeg_->SetParent(&rightAnkle_);
	rightLeg_->UpdateMatrix();
	//足まで

	//ここから上半身
	stomach_.parent_ = lowerBack_->GetWorldTransform();
	stomach_.translation_ = { 0.0f,size.y * 3.0f / 4.0f,0.0f };
	stomach_.rotation_ = {};
	stomach_.UpdateMatrix();

	chest_ = new Cube();
	chest_->Initialize({ 0.0f,size.y * 3.0f / 4.0f,0.0f }, size, {}, image);
	chest_->SetParent(&stomach_);
	chest_->UpdateMatrix();

	neck_.parent_ = chest_->GetWorldTransform();
	neck_.translation_ = { 0.0f,size.y * 2.5f / 4.0f,0.0f };
	neck_.rotation_ = {};
	neck_.UpdateMatrix();

	head_ = new Cube();
	head_->Initialize({ 0.0f,size.y * 2.5f / 4.0f,0.0f }, { size.x / 3.0f,size.y,size.z }, {}, image);
	head_->SetParent(&neck_);
	head_->UpdateMatrix();

	leftShoulder_.parent_ = chest_->GetWorldTransform();
	leftShoulder_.translation_ = { -size.x * 3.0f / 4.0f,size.y / 4.0f,0.0f };
	leftShoulder_.rotation_ = {};
	leftShoulder_.UpdateMatrix();

	rightShoulder_.parent_ = chest_->GetWorldTransform();
	rightShoulder_.translation_ = { size.x * 3.0f / 4.0f,size.y / 4.0f,0.0f };
	rightShoulder_.rotation_ = {};
	rightShoulder_.UpdateMatrix();

	leftUpperArm_ = new Cube();
	leftUpperArm_->Initialize({ 0.0f,-size.y * 5.0f / 8.0f,0.0f }, { size.x / 4.0f,size.y,size.z }, {}, image);
	leftUpperArm_->SetParent(&leftShoulder_);
	leftUpperArm_->UpdateMatrix();

	rightUpperArm_ = new Cube();
	rightUpperArm_->Initialize({ 0.0f,-size.y * 5.0f / 8.0f,0.0f }, { size.x / 4.0f,size.y,size.z }, {}, image);
	rightUpperArm_->SetParent(&rightShoulder_);
	rightUpperArm_->UpdateMatrix();

	leftElbow_.parent_ = leftUpperArm_->GetWorldTransform();
	leftElbow_.translation_ = { 0.0f,-size.y * 4.2f / 8.0f,0.0f };
	leftElbow_.rotation_ = {};
	leftElbow_.UpdateMatrix();

	rightElbow_.parent_ = rightUpperArm_->GetWorldTransform();
	rightElbow_.translation_ = { 0.0f,-size.y * 4.2f / 8.0f,0.0f };
	rightElbow_.rotation_ = {};
	rightElbow_.UpdateMatrix();

	leftForeArm_ = new Cube();
	leftForeArm_->Initialize({ 0.0f,-size.y * 5.0f / 8.0f,0.0f }, { size.x / 4.0f,size.y,size.z }, {}, image);
	leftForeArm_->SetParent(&leftElbow_);
	leftForeArm_->UpdateMatrix();

	rightForeArm_ = new Cube();
	rightForeArm_->Initialize({ 0.0f,-size.y * 5.0f / 8.0f,0.0f }, { size.x / 4.0f,size.y,size.z }, {}, image);
	rightForeArm_->SetParent(&rightElbow_);
	rightForeArm_->UpdateMatrix();

	leftWrist_.parent_ = leftForeArm_->GetWorldTransform();
	leftWrist_.translation_ = { 0.0f,-size.y * 4.2f / 8.0f,0.0f };
	leftWrist_.rotation_ = {};
	leftWrist_.UpdateMatrix();

	rightWrist_.parent_ = rightForeArm_->GetWorldTransform();
	rightWrist_.translation_ = { 0.0f,-size.y * 4.2f / 8.0f,0.0f };
	rightWrist_.rotation_ = {};
	rightWrist_.UpdateMatrix();

	leftHand_ = new Cube();
	leftHand_->Initialize({ 0.0f,-size.y / 2.4f,0.0f }, { size.x / 4.0f,size.y / 2.0f,size.z }, {}, image);
	leftHand_->SetParent(&leftWrist_);
	leftHand_->UpdateMatrix();

	rightHand_ = new Cube();
	rightHand_->Initialize({ 0.0f,-size.y / 2.4f,0.0f }, { size.x / 4.0f,size.y / 2.0f,size.z }, {}, image);
	rightHand_->SetParent(&rightWrist_);
	rightHand_->UpdateMatrix();
}

void Body::UpdateMatrix() {

	foot_.UpdateMatrix();

	lowerBack_->UpdateMatrix();

	leftHipJoint_.UpdateMatrix();
	rightHipJoint_.UpdateMatrix();
	leftThigh_->UpdateMatrix();
	rightThigh_->UpdateMatrix();
	leftKnee_.UpdateMatrix();
	rightKnee_.UpdateMatrix();
	leftCalf_->UpdateMatrix();
	rightCalf_->UpdateMatrix();
	leftAnkle_.UpdateMatrix();
	rightAnkle_.UpdateMatrix();
	leftLeg_->UpdateMatrix();
	rightLeg_->UpdateMatrix();

	stomach_.UpdateMatrix();
	chest_->UpdateMatrix();
	neck_.UpdateMatrix();
	head_->UpdateMatrix();
	
	leftShoulder_.UpdateMatrix();
	rightShoulder_.UpdateMatrix();
	leftUpperArm_->UpdateMatrix();
	rightUpperArm_->UpdateMatrix();
	leftElbow_.UpdateMatrix();
	rightElbow_.UpdateMatrix();
	leftForeArm_->UpdateMatrix();
	rightForeArm_->UpdateMatrix();
	leftWrist_.UpdateMatrix();
	rightWrist_.UpdateMatrix();
	leftHand_->UpdateMatrix();
	rightHand_->UpdateMatrix();

}