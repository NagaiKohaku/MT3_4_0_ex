#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include "cmath"

/*球*/
struct Sphere {
	Vector3 center; //中心点
	float radius;   //半径
};

/*平面*/
struct Plane {
	Vector3 normal; //法線
	float distance; //距離
};

/*三角形*/
struct Triangle {
	Vector3 vertices[3]; //点
};

/*軸平行境界箱(Axis Aligned Bounding Box)*/
struct AABB {
	Vector3 min; //最小点
	Vector3 max; //最大点
};

/*有向境界箱(Oriented Bounding Box)*/
struct OBB {
	Vector3 center; //中心点
	Vector3 orientations[3]; //座標軸
	Vector3 size; //座標軸方向の長さの半分
};

class Draw {

public:

	void CamaraRotate(Vector3& baseOffset, Vector3& rotate, Vector3& translate, char keys[256]);
	void Pipeline(Vector3& cameraTranslate, Vector3& cameraRotate, float kWindowWidth, float kWindowHeight);
	void DrawGrid();
	void DrawSphere(Sphere sphere, uint32_t color);
	void DrawLine(Vector3 start, Vector3 end, uint32_t color);
	void DrawPlane(Plane plane, uint32_t color);
	void DrawTriangle(Triangle triangle, uint32_t color);
	void DrawAABB(const AABB& aabb, uint32_t color);
	void DrawOBB(const OBB& obb, uint32_t color);
	void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, uint32_t color);
	void DrawArm(const Vector3(&translates)[3], const Vector3(&rotates)[3], const Vector3(&scales)[3]);

private:

	Matrix4x4 cameraMatrix_;

	Matrix4x4 viewMatrix_;

	Matrix4x4 projectionMatrix_;

	Matrix4x4 viewProjectionMatrix_;

	Matrix4x4 viewPortMatrix_;

};