#include "calc.h"
#include <math.h>

float Calc::MakeLength(const MyVector2& v) {
	float result = static_cast<float>(sqrt(powf(v.x, 2) + powf(v.y, 2)));
	return result;
}
float Calc::MakeLength(const MyVector3& v) {
	float result = static_cast<float>(sqrt(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2)));
	return result;
}
float Calc::MakeLength(const MyVector2& v1, const MyVector2& v2) {
	float result = static_cast<float>(sqrt(powf(v1.x - v2.x, 2) + powf(v1.y - v2.y, 2)));
	return result;
}
float Calc::MakeLength(const MyVector3& v1, const MyVector3& v2) {
	float result = static_cast<float>(sqrt(powf(v1.x - v2.x, 2) + powf(v1.y - v2.y, 2) + powf(v1.z - v2.z, 2)));
	return result;
}

float Calc::MakeLength(const MyVector2& v1, const MyVector2& v2, const MyVector2& v3) {
	MyVector2 lineV[2] = { v3,v1 };
	lineV[0] -= v2;
	lineV[1] -= v2;

	float dot = Dot(lineV[0], lineV[1]);

	float lineLength = MakeLength(v2, v3);

	float t = dot / lineLength / lineLength;

	MyVector2 pos = {};
	if (t < 0) {
		pos = v2;
	}
	else if (t > 1) {
		pos = v3;
	}
	else {
		pos = lineV[0] * t + v2;
	}

	float length = MakeLength(v1, pos);
	return length;
}

float Calc::MakeLength(const MyVector3& v1, const MyVector3& v2, const MyVector3& v3) {
	MyVector3 lineV[2] = { v3,v1 };
	lineV[0] -= v2;
	lineV[1] -= v2;

	float dot = Dot(lineV[0], lineV[1]);

	float lineLength = MakeLength(v2, v3);

	float t = dot / lineLength / lineLength;

	MyVector3 pos = {};
	if (t < 0) {
		pos = v2;
	}
	else if (t > 1) {
		pos = v3;
	}
	else {
		pos = lineV[0] * t + v2;
	}

	float length = MakeLength(v1, pos);
	return length;
}

float Calc::MakeLength(const MyVector2& v1, const MyVector2& v2, const MyVector2& v3, LineType linetype) {
	MyVector2 lineV[2] = { v3,v1 };
	lineV[0] -= v2;
	lineV[1] -= v2;

	float dot = Dot(lineV[0], lineV[1]);

	float lineLength = MakeLength(v2, v3);

	float t = dot / lineLength / lineLength;

	MyVector2 pos = {};

	switch (linetype)
	{
	case Calc::LineType::Line:
		pos = lineV[0] * t + v2;
		break;
	case Calc::LineType::Ray:
		if (t < 0) {
			pos = v2;
		}
		else {
			pos = lineV[0] * t + v2;
		}
		break;
	case Calc::LineType::Segment:
		if (t < 0) {
			pos = v2;
		}
		else if (t > 1) {
			pos = v3;
		}
		else {
			pos = lineV[0] * t + v2;
		}
		break;
	default:
		break;
	}

	float length = MakeLength(v1, pos);
	return length;
}

float Calc::MakeLength(const MyVector3& v1, const MyVector3& v2, const MyVector3& v3, LineType linetype) {
	MyVector3 lineV[2] = { v3,v1 };
	lineV[0] -= v2;
	lineV[1] -= v2;

	float dot = Dot(lineV[0], lineV[1]);

	float lineLength = MakeLength(v2, v3);

	float t = dot / lineLength / lineLength;

	MyVector3 pos = {};

	switch (linetype)
	{
	case Calc::LineType::Line:
		pos = lineV[0] * t + v2;
		break;
	case Calc::LineType::Ray:
		if (t < 0) {
			pos = v2;
		}
		else {
			pos = lineV[0] * t + v2;
		}
		break;
	case Calc::LineType::Segment:
		if (t < 0) {
			pos = v2;
		}
		else if (t > 1) {
			pos = v3;
		}
		else {
			pos = lineV[0] * t + v2;
		}
		break;
	default:
		break;
	}

	float length = MakeLength(v1, pos);
	return length;
}

MyVector3 Calc::Project(const MyVector3& v1, const MyVector3& v2) {
	float dot = Dot(v1, v2);
	float length = MakeLength(v2);

	float t = dot / length / length;

	MyVector3 result = v2;
	result *= t;
	return result;
}

MyVector3 Calc::ClosestPoint(const MyVector3& point, const Segment& segment) {
	MyVector3 lineV = point;
	lineV -= segment.origin;

	float dot = Dot(lineV, segment.diff);

	float lineLength = MakeLength(segment.diff);

	float t = dot / lineLength / lineLength;

	MyVector3 pos = segment.origin;

	if (t > 1) {
		pos += segment.diff;
	}
	else if(t > 0 ) {
		MyVector3 project = segment.diff;
		pos += project * t;
	}

	return pos;
}

MyVector2 Calc::Normalize(const MyVector2& v) {
	float len = MakeLength(v);

	MyVector2 result = {};

	if (len != 0) {
		result = { v.x / len,v.y / len };
	}

	return result;
}

MyVector3 Calc::Normalize(const MyVector3& v) {
	float len = MakeLength(v);

	MyVector3 result = {};

	if (len != 0) {
		result = { v.x / len, v.y / len, v.z / len };
	}

	return result;
}

float Calc::Dot(const MyVector2& v1, const MyVector2& v2) {
	float dot = v1.x * v2.x + v1.y * v2.y;
	return dot;
}

float Calc::Dot(const MyVector3& v1, const MyVector3& v2) {
	float dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return dot;
}

float Calc::Outer(const MyVector2& v1, const MyVector2& v2) {
	float outer = v1.x * v2.y - v1.y * v2.x;
	return outer;
}

MyVector3 Calc::Cross(const MyVector3& v1, const MyVector3& v2) {
	MyVector3 result = { v1.y * v2.z - v1.z * v2.y,v1.z * v2.x - v1.x * v2.z ,v1.x * v2.y - v1.y * v2.x };
	return result;
}

float Calc::MakeRadian(const MyVector3& v1, const MyVector3& v2, const MyVector3& v3) {

	float a = MakeLength(v2, v3);
	float b = MakeLength(v1, v2);
	float c = MakeLength(v1, v3);

	if (a == 0 || b == 0 || c == 0) {
		return 0.0f;
	}

	float cos = (-powf(a, 2) +powf(b, 2) + powf(c, 2)) / b / c / 2;

	if (cos < -1) {
		return 3.14f;
	}
	else if (cos > 1) {
		return 0.0f;
	}

	return acosf(cos);
}

float Calc::MakeRadian(float a, float b, float c) {

	if (a == 0 || b == 0 || c == 0) {
		return 0.0f;
	}

	float cos = (-powf(a, 2) + powf(b, 2) +powf(c, 2)) / b / c / 2;

	if (cos < -1) {
		return 3.14f;
	}
	else if (cos > 1) {
		return 0.0f;
	}

	return acosf(cos);
}
