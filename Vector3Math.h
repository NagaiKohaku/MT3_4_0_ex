#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

struct Line {
	Vector3 origin; //始点
	Vector3 diff; //終点の差分ベクトル
};

struct Ray {
	Vector3 origin; //始点
	Vector3 diff; //終点の差分ベクトル
};

struct Segment {
	Vector3 origin; //始点
	Vector3 diff; //終点の差分ベクトル
};

//加算
Vector3 Add(const Vector3& v1, const Vector3& v2);

//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

//スカラー倍
Vector3 Multiply(float scalar, const Vector3& v);

//内積
float Dot(const Vector3& v1, const Vector3& v2);

//長さ(ノルム)
float Length(const Vector3& v);

//正規化
Vector3 Normalize(const Vector3& v);

//垂直
Vector3 Perpendicular(const Vector3& v);

//クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);

//正射影ベクトルの生成
Vector3 Project(const Vector3& v1, const Vector3& v2);

//最近接点の生成
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

Vector3 Bezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t);