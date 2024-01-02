#include "ScenePlay.h"
#include "../Manager/Enemy/EnemyManager.h"
#include "Character/Enemy/EnemyZakoBox.h"
#include "Sky/SkyBox.h"
#include "Ground/HeightMap.h"
#include "Star/ShiningStar.h"
#include "Bullet/Player/PlayerBullet.h"
#include "Bullet/Enemy/EnemyBullet.h"


ScenePlay::ScenePlay() {

	// メインカメラ
	_mainCamera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	// プレイヤー
	_player = std::make_shared<Player>(_mainCamera);
	_player->SetPlayerRef(_player);

	// スカイボックス(天空)
	_skyBox = std::make_shared<SkyBox>();

	// ハイトマップ(地上)
	_heightMap = std::make_shared<HeightMap>();

	// 当たり判定
	_collision = std::make_shared<Collision>();

	// 敵に関するあらゆる処理を全て管理
	_enemyManager = std::make_shared<EnemyManager>(_player, _mainCamera, _collision);

	// 画面左下の索敵レーダーの画像
	miniMap_hdl = LoadGraph("graphics/miniMap/radar.jpg");
}


void ScenePlay::RenderEnemyRadarOnMiniMap() {

	// 左下のミニマップレーダー
	std::list<tnl::Vector3> enemy_pos_list = _enemyManager->GetEnemyPositions_FromPlayer();

	for (auto e_pos = enemy_pos_list.begin(); e_pos != enemy_pos_list.end(); e_pos++) {

		tnl::Vector3 screen_pos = tnl::Vector3::ConvertToScreen(
			{ (*e_pos).x, (*e_pos).y, (*e_pos).z },
			miniMap_center_pos.x,
			miniMap_center_pos.y,
			_mainCamera->view_,
			_mainCamera->proj_
		);

		// 敵位置を緑の円で描画
		DrawCircleAA(
			std::clamp((int)screen_pos.x, (int)miniMap_center_pos.x, 160),
			std::clamp((int)screen_pos.y, (int)miniMap_center_pos.y, 660),
			2, 10, GetColor(0, 255, 0));
	}
}


void ScenePlay::Render() {

	_skyBox->Render(_mainCamera);

	_heightMap->Render(_mainCamera);

	_player->Render(_mainCamera);

	_enemyManager->Render();

	// グリッド線
	DrawGridGround(_mainCamera, 100, 30);
	
	// ミニマップ
	DrawRotaGraph(miniMap_center_pos.x, miniMap_center_pos.y, 0.035, 0, miniMap_hdl, 1);
	RenderEnemyRadarOnMiniMap();
}



void ScenePlay::Update(float deltaTime) {

	_skyBox->Update();

	_heightMap->Update();

	_enemyManager->Update(deltaTime);
	
	_player->Update(deltaTime);
	_player->ActivateDarkSoulsCamera();

	// お星さま描画
	ShiningStar s;	s.Update();
}