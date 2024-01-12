#pragma once
#include "./../../DxLibEngine.h"
#include "../../ScenePlay/Character/Enemy/EnemyBase.h"
#include "../../ScenePlay/Character/Player/Player.h"

class Collision;
class EnemyZakoBox;
struct EnemyZakoInfo;
struct EnemyBossInfo;


// 生成・削除・更新を管理

class EnemyManager
{
public:

	EnemyManager() {}

	EnemyManager(int stageID, const Shared<Player>& player, const Shared<dxe::Camera>& camera, Shared<Collision>& collision, const std::string difficulty);

	~EnemyManager() { _enemy_zako_list.clear(); }

	bool Update(const float& deltaTime);
	void Render() const;

	std::list< tnl::Vector3> GetEnemyPositions_FromPlayer();

private:

	void InitEnemyZakoInfo(int stage_id);

	void InitEnemyBossInfo(int stage_id);

	// 敵のスポーン位置はプレイヤーの位置や行動に応じて決める
	void CheckDoSpawnEnemy(const float& delta_time);

	void SetCollisionPairList();

private:

	Shared<CsvLoader> _csvLoader = nullptr;
	Shared<EnemyBase> _enemyBase = nullptr;

	Shared<EnemyZakoBox> _enemy_zakoBox = nullptr;

	// Zako
	std::vector<Shared<EnemyBase>> _enemy_zako_list;
	std::unordered_map<int, EnemyZakoInfo> _enemyZakoData_map;
	EnemyZakoInfo _sEnemy_zakoBox_info{};
	EnemyZakoInfo _sEnemy_zakoDome_info{};
	EnemyZakoInfo _sEnemy_zakoCylinder_info{};

	// Boss
	std::vector<Shared<EnemyBase>> _enemy_boss_list;
	std::unordered_map<int, EnemyBossInfo> _enemyBossData_map;
	EnemyBossInfo _sBoss_PatchouliKnowledge_info{};
	EnemyBossInfo _sBoss_Cirno_info{};
	EnemyBossInfo _sBoss_MoriyaSuwako_info{};


	// 参照
	Shared<Player> _player_ref;

	Shared<dxe::Camera> _mainCamera_ref;

	Shared<Collision> _collision_ref;

private:

	const std::string _SELECTED_LEVEL;

	static int _deadCount_zakoBox ;

	int _stageID{};

	// 1度に生成が可能な最大数
	int maxEnemySpawnCount_PerInterval{};
};