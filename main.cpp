#include <Novice.h>
#include <Novice.h>
#include <imgui.h>
#include "MakeMatrix.h"
#include "MatrixMath.h"
#include "Vector3Math.h"
#include "Draw.h"
#include "algorithm"

const char kWindowTitle[] = "LE2B_17_ナガイ_コハク_MT3_3_1 階層構造";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//ウィンドウサイズ
	float kWindowWidth = 1280.0f;
	float kWindowHeight = 720.0f;

	//カメラ:平行移動
	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };

	//カメラ:回転
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	//カメラ:距離
	Vector3 baseOffset{ 0.0f,0.0f,-6.0f };

	//描画クラス
	Draw draw;

	//平行移動
	Vector3 translates[3] = {
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f}
	};

	//回転
	Vector3 rotates[3] = {
		{0.0f,0.0f,-6.0f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f}
	};

	//大きさ
	Vector3 scales[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f}
	};

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

		ImGui::Text("WASD : CameraRotate");
		ImGui::Text("UpArrow : ZoomIn");
		ImGui::Text("DownArrow : ZoomDown");

		if (ImGui::TreeNode("Camera")) {
			ImGui::DragFloat3("Translate", &cameraTranslate.x, 0.01f);
			ImGui::DragFloat3("Rotate", &cameraRotate.x, 0.01f);
			ImGui::DragFloat3("offset", &baseOffset.x, 0.01f);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Shoulder")) {
			ImGui::DragFloat3("Translate", &translates[0].x, 0.01f);
			ImGui::DragFloat3("rotate", &rotates[0].x, 0.01f);
			ImGui::DragFloat3("scale", &scales[0].x, 0.01f);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Elbow")) {
			ImGui::DragFloat3("Translate", &translates[1].x, 0.01f);
			ImGui::DragFloat3("rotate", &rotates[1].x, 0.01f);
			ImGui::DragFloat3("scale", &scales[1].x, 0.01f);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Hand")) {
			ImGui::DragFloat3("Translate", &translates[2].x, 0.01f);
			ImGui::DragFloat3("rotate", &rotates[2].x, 0.01f);
			ImGui::DragFloat3("scale", &scales[2].x, 0.01f);
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

		draw.DrawArm(translates, rotates, scales);

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