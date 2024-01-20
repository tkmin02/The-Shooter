#pragma once
#include "../../../DxLibEngine.h"
#include "../../Character/Enemy/EnemyBase.h"

class PlayerBullet;
class EnemyBase;
class FreeLookCamera;

class Player
{
public:

	enum class CameraPos {

		DIR_RIGHT,
		DIR_LEFT,
		DIR_UP,
		DIR_DOWN,
	};

    
	Player(){}

	Player(Shared<FreeLookCamera> camera_ref);


	void Update(float delta_time);
	void UpdateStraightBullet(float delta_time);
	void Render(Shared<FreeLookCamera> playerCamera);

	void MoveForward(const float deltaTime);

	void ControlPlayerMove();
	void ControlMainCameraPos(const CameraPos enum_camera_pos);
	void NormalizeCameraSpeed();


	void ShotPlayerBullet();

	void AdjustPlayerVelocity();

	void ControlRotationByMouse();

	float GetDistanceToEnemy(const float& x, const float& y, const float& z);

	float GetAngleBtw_PlayerAndEnemy(Shared<dxe::Mesh> enemy);

	void ChangeTarget_ByMouseWheel();

	void RenderFollowPointer();


	void ActivateDarkSoulsCamera();

	void ControlCameraWithoutEnemyFocus(tnl::Vector3& player_pos);

	const tnl::Vector3 GetPos() const   { return _mesh->pos_; }
	void SetPos(const tnl::Vector3 pos) { _mesh->pos_ = pos; }

	// 管理するエネミーのリストの参照用
	void SetEnemiesListRef_ClassP(std::vector<Shared<EnemyBase>> enemy_list_ref);
	void SetPlayerRef(Shared<Player> player_ref) { _player_ref = player_ref; }


	const tnl::Vector3 GetTargetsScreenCoordinates(const float& x, const float& y, const float& z);

private:

	bool IsEnemyInCapturableRange();

public:

	Shared<dxe::Mesh> _mesh = nullptr;
	std::list<Shared<PlayerBullet>> _straight_bullets_p;

	tnl::Vector3 collide_size{};

private:

	tnl::PointsLerp* points = nullptr;
	std::vector<tnl::Vector3> positions;

	Shared<Player> _player_ref = nullptr;
	Shared<FreeLookCamera> _mainCamera_ref = nullptr;

	Shared<EnemyBase> _enemy_ref = nullptr;
	std::vector <Shared<EnemyBase>> _enemies_list_ref{};

	int _hp{};
	int  _enemy_index{};
	float _player_behind_cameraX{};

	float _radius{};
	float _forward_velocity = 1.0f;

	bool _isDead{};
	bool _isInvincible{};
	float _invincibleTime = 1.5f;
	float _invincibleRestTime{};

	float moveSpeed = 0.4f;
	float camera_pos_offset = 1.f;


	float centroid_radius_ = 100; // 重心
	float mass_ = 100;            // 質量
	float friction_ = 0.6f;       // 摩擦
	tnl::Vector3 move_vel_{};
	tnl::Vector3 past_move_vel_{};
	tnl::Vector3 center_of_gravity_{};
	tnl::Quaternion rot_y_{};
	tnl::Quaternion rot_x_{};
	tnl::Quaternion rot_xz_{};

	tnl::Vector3 _camera_pivot{};

	tnl::Vector3 targets_screen_coords{};
	tnl::Vector3 distance_player_enemy{};
	float        _delta_angle{};
};