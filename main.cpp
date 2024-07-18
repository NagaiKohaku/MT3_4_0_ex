#include <Novice.h>
#include <Novice.h>
#include <imgui.h>
#include "MakeMatrix.h"
#include "MatrixMath.h"
#include "Vector3Math.h"
#include "Draw.h"
#include "algorithm"

const char kWindowTitle[] = "LE2B_17_ナガイ_コハク_MT3_4_0_ex ばねへの重力の追加";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	struct Spring {
		Vector3 anchor;
		float naturalLength;
		float stiffness;
		float dampingCoefficient;
	};

	struct Ball {
		Vector3 position;
		Vector3 velocity;
		Vector3 acceleration;
		float mass;
		float radius;
		unsigned int color;
	};

	//ウィンドウサイズ
	float kWindowWidth = 1280.0f;
	float kWindowHeight = 720.0f;

	//カメラ:平行移動
	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };

	//カメラ:回転
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	//カメラ:距離
	Vector3 baseOffset{ 0.0f,0.0f,-6.0f };

	Spring spring{};
	spring.anchor = { 0.0f,1.0f,0.0f };
	spring.naturalLength = 0.7f;
	spring.stiffness = 100.0f;
	spring.dampingCoefficient = 2.0f;

	Ball ball{};
	ball.position = { 0.8f,0.2f,0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;

	Spring initSpring = spring;

	Ball initBall = ball;

	const Vector3 kGravity{ 0.0f,-9.8f,0.0f };

	bool startMove = false;

	//描画クラス
	Draw draw;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		float deltaTime = 1.0f / 60.0f;

		Vector3 diff = ball.position - spring.anchor;

		float length = Length(diff);

		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {

			spring = initSpring;

			ball = initBall;

			startMove = true;
		}

		if (startMove) {

			if (length != 0.0f) {

				Vector3 direction = Normalize(diff);
				Vector3 restPosition = spring.anchor + direction * spring.naturalLength;
				Vector3 displacement = length * (ball.position - restPosition);
				Vector3 restoringForce = -spring.stiffness * displacement;
				Vector3 dampingForce = -spring.dampingCoefficient * ball.velocity;
				Vector3 force = restoringForce + dampingForce + kGravity;
				ball.acceleration = force / ball.mass;
			}

			ball.velocity = ball.velocity + ball.acceleration * deltaTime;
			ball.position = ball.position + ball.velocity * deltaTime;
		}

		ImGui::Text("WASD : CameraRotate");
		ImGui::Text("UpArrow : ZoomIn");
		ImGui::Text("DownArrow : ZoomDown");
		ImGui::Text("\nSpace : Move Start\n\n");

		if (ImGui::TreeNode("Camera")) {
			ImGui::DragFloat3("Translate", &cameraTranslate.x, 0.01f);
			ImGui::DragFloat3("Rotate", &cameraRotate.x, 0.01f);
			ImGui::DragFloat3("offset", &baseOffset.x, 0.01f);
			ImGui::TreePop();
		}

		draw.CamaraRotate(baseOffset, cameraRotate, cameraTranslate, keys);

		draw.Pipeline(cameraTranslate, cameraRotate, kWindowWidth, kWindowHeight);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		draw.DrawGrid();

		draw.DrawLine(spring.anchor, diff, WHITE);

		draw.DrawSphere(
			Sphere(
				ball.position,
				ball.radius
			),
			ball.color
		);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
