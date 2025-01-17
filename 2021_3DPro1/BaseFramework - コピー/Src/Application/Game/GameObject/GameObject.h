﻿#pragma once

//前方宣言
class DebugObject;
// 球の情報
struct SphereInfo
{
	// デフォルトコンストラクタ
	SphereInfo(const Math::Vector3& pos, float radius):
		m_pos(pos),
		m_radius(radius)
	{}

	const Math::Vector3 m_pos;
	float m_radius = 1.0f;
};

// レイの情報
struct RayInfo
{
	RayInfo(const Math::Vector3& pos, const Math::Vector3& dir, float range):
		m_pos(pos),
		m_dir(dir),
		m_range(range){m_dir.Normalize();}

	Math::Vector3 m_pos;
	Math::Vector3 m_dir;
	float m_range = 0.0f;

};

struct BumpResult
{
	bool m_isHit = false;
	Math::Vector3 m_pushVec;
};

class GameObject
{
public:

	enum classID
	{
		eBase,
		eStage,
		ePlayer,
		eEnemy
	};

	GameObject(){}
	virtual ~GameObject() { Release(); }

	virtual void Init(){}
	virtual void Deserialize(const json11::Json& jsonObj);
	virtual void Update(){}
	virtual void DrawShadowMap();
	virtual void Draw();
	virtual void DrawEffect() {}
	virtual void Draw2D() {}

	void Destroy() {}

	virtual void SetPos(const Math::Vector3& pos)
	{
		m_mWorld.Translation(pos);
	}

	bool IsAlive() { return m_isAlive; }

	virtual const Math::Vector3 GetPos() const { return m_mWorld.Translation(); }
	const Math::Matrix GetMatrix() const { return m_mWorld; }

	virtual classID GetClassID() const { return eBase; }

	virtual void DrawDebug();

	// 押し戻しの衝突判定
	bool CheckCollisionBump(const SphereInfo& info, BumpResult& result);
	// オブジェクト同士の衝突判定
	bool CheckCollisionBump(const RayInfo& info, BumpResult& result);

// 継承したもののみ触れる 
protected:

	KdModelWork		m_modelWork;
	Math::Matrix	m_mWorld;

	bool			m_isAlive = true;

	float			m_radius = 0.0f;

	//デバッグObject
	std::shared_ptr<DebugObject> m_spDebugObject = nullptr;

private:
	void Release() {}

};