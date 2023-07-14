#pragma once
#include<MyVector2.h>
#include"MyVector3.h"

class Ease {
public:
	//イージングチートシートより
	enum class EaseType {
		Constant,

		EaseInSine,
		EaseOutSine,
		EaseInOutSine,

		//Quadから
		//index乗で対応してる
		EaseIn,
		EaseOut,
		EaseInOut,
		//Quintまで

		EaseInExpo,
		EaseOutExpo,
		EaseInOutExpo,
		EaseInCirc,
		EaseOutCirc,
		EaseInOutCirc,
		EaseInBack,
		EaseOutBack,
		EaseInOutBack,
		EaseInElastic,
		EaseOutElastic,
		EaseInOutElastic,
		EaseInBounce,
		EaseOutBounce,
		EaseInOutBounce,
	};

	static float UseEase(float a, float b, float t);

	static MyVector2 UseEase(const MyVector2& a, const MyVector2& b, float t);

	static MyVector3 UseEase(const MyVector3& a, const MyVector3& b, float t);

	static float MakeEaseT(int nowFrame, int maxFrame, EaseType easeType, int index);
	//返ってくるのはイージングに使うtの値
	static float MakeEaseT(float t, EaseType easeType, int index);
	//返ってくるのはイージングに使うtの値

	//使うのはここから下4つだと思う。

	static float UseEase(float a, float b, int nowFrame, int maxFrame, EaseType easeType, int index);

	static float UseEase(float a, float b, float t, EaseType easeType, int index);

	static MyVector2 UseEase(const MyVector2& a, const MyVector2& b, int nowFrame, int maxFrame, EaseType easeType, int index);

	static MyVector2 UseEase(const MyVector2& a, const MyVector2& b, float t, EaseType easeType, int index);

	static MyVector3 UseEase(const MyVector3& a, const MyVector3& b, int nowFrame, int maxFrame, EaseType easeType, int index);

	static MyVector3 UseEase(const MyVector3& a, const MyVector3& b, float t, EaseType easeType, int index);
	//返ってくる値はイージングされた値
	//aにt=0のときの値、bにt=1の時の値
	//easeTypeには使用するイージング、上のenumの文字列を入力。EaseInBackとか。
	//indexにはEaseIn,Out,InOutのべき乗を入力

	static MyVector2 EaseInMove(MyVector2& OwnPos, MyVector2& tmp1, MyVector2& tmp2, int& nowFrame, int& maxFrame);

	static MyVector2 EaseOutMove(MyVector2& OwnPos, MyVector2& tmp1, MyVector2& tmp2, int& nowFrame, int& maxFrame);


};

