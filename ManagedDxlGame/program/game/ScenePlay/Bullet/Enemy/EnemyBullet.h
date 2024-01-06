#pragma once
#include "../Bullet.h"
#include "../../Character/Enemy/EnemyBase.h"
#include "../../Character/Player/Player.h"

class Player;


class EnemyBullet : public Bullet
{
public:

	EnemyBullet(){}
	~EnemyBullet(){}
	EnemyBullet(const float bullet_speed) {}

	EnemyBullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& direction) {}
	EnemyBullet(const tnl::Vector3& spawn_pos, const tnl::Vector3& direction, Shared<Player> player_ref) {}


public:

	tnl::Vector3 _move_dir = { 0,0,0 };  //  進行方向

protected:

	Shared<Player> _player_ref;
	Shared<EnemyBase> _enemy_ref;


	tnl::Vector3 prev_pos;

public:

	float _speed;
	bool _isActive;


protected:

	float _elapsed;
	float _vx;
	float _vy;
	float _vz;

	int _num;
	float _shot_interval;    // 発射間隔
	float _shot_duration{}; // 何秒間発射し続けるか

	float _angle;            // 現在向いている方向の角度
	float _to_player_angle;  // プレイヤーとの角度差
};