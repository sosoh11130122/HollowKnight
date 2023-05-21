#pragma once

#include "GameObject/GameObject.h"

enum class EVengefly_Animation
{
	Idle,
	Chase,
	Startle,
	Turn,
	Death
};

class CVengefly :
	public CGameObject
{
	friend class CScene;

protected:
	CVengefly();
	CVengefly(const CVengefly& Obj);
	virtual ~CVengefly();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CColliderOBB2D>	m_Body;
	CSharedPtr<class CColliderSphere2D> m_Radar;
	CSharedPtr<class CColliderBox2D> m_Dash;
	CSharedPtr<class CGameObject> m_Player;

private:
	int		m_MonsterDir;
	std::vector<std::string>	m_vecSequenceKey[2];
	EVengefly_Animation	m_PrevMonsterAnim;
	EVengefly_Animation	m_MonsterAnim;
	CSharedPtr<class CAnimation2D> m_Animation;
	Vector3 m_Dir;
	Vector3 m_Pos;
	Vector3 m_PrevPos;
	Vector3 m_PlayerPos;
	bool m_Chase;
	float m_MoveSpeed;
	int m_HP;
	int m_DamageCount;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CVengefly* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);


public:
	void Idle(const CollisionResult& result);
	void Chase(const CollisionResult& result);
	void Damage(const CollisionResult& result);
	void Left();
	void Right();
};

