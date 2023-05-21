#pragma once

#include "GameObject/GameObject.h"

enum class EPlayer_Animation
{
	Idle,
	Up,
	Down,
	Move,
	Jump,
	Attack,
	Dash,
	Hurt,
	Focus,
	SuperDash,
	QuickCast,
	DoubleJump,
	AttackUp,
	AttackDown,
	Death,                                                                                            
	Fall
	/*
	QuickMap
	DreamNail
	Inventory
	*/
};

class CPlayer2D :
	public CGameObject
{
	friend class CScene;

protected:
	CPlayer2D();
	CPlayer2D(const CPlayer2D& Obj);
	virtual ~CPlayer2D();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CSceneComponent>	m_RightChild;
	CSharedPtr<class CSpriteComponent>	m_SpriteChild;
	CSharedPtr<class CCameraComponent>	m_Camera;
	CSharedPtr<class CTargetArm>		m_Arm;
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CNavigationAgent>	m_NavAgent;
	CSharedPtr<class CGravityComponent>	m_Gravity;
	CSharedPtr<class CSceneComponent>   m_UpdateComponent;
	CSharedPtr<class CWallComponent>	m_Wall;
	CSharedPtr<class CBackObj>			m_BackObj;
	CSharedPtr<class CSecondBackObj>	m_SecondBackObj;
	CSharedPtr<class CBossMap>			m_BossMapBackObj;
	
	CSharedPtr<class CEffect>			m_Effect;
	CSharedPtr<class CEffect>			m_SwordEffect;
	CSharedPtr<class CUIProgressBar>	m_ProgressBar;
	CSharedPtr<class CFirstSceneUI>		m_PlayerUI;

private:
	int		m_PlayerDir;
	int		m_HP;
	std::vector<std::string>	m_vecSequenceKey[2];
	EPlayer_Animation	m_PrevPlayerAnim;
	EPlayer_Animation	m_PlayerAnim;
	CSharedPtr<class CAnimation2D> m_Animation;
	float	m_WallObjSize;

//1127
private:
	float	m_Velocity; // 가속도.
	float   m_FallTime; // 낙하시간.
//1129_API 
	float	m_JumpTime; // 점프 타임.
	float	m_JumpTimeMax; // 최대 점프 타임.
	float	m_JumpAccel; //점프가속도.

private:
	bool	m_Dash;
	bool	m_Attack;
	bool	m_Fall;
	bool	m_Jump;
	bool	m_Idle;
	bool	m_Move;
	bool	m_Up;
	bool	m_Down;
	bool	m_Hurt;
	bool    m_Left;
	bool	m_Right;

	float	m_Time;
	bool	m_Focus;

// 
//11272
private:
	class CTile*	m_Tile;
	class CTileMapComponent* m_TileMap;
//11272

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual float InflictDamage(float Damage);
	virtual CPlayer2D* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

public:
	void CollisionBegin(const CollisionResult& result);
	void CollisionEnd(const CollisionResult& result);

public:
	int GetPlayer()	const
	{
		return m_PlayerDir;
	}

	bool GetHurt() const
	{
		return m_Hurt;
	}

	int GetHP() const
	{
		return m_HP;
	}

	//11272
	float GetVelocity()
	{
		return m_Velocity;
	}

	void SetHP(int HP)
	{
		m_HP = HP;
	}

	void SetFallTime(float FallTime)
	{
		m_FallTime = FallTime;
	}

	void SetVelocity(float Velocity)
	{
		m_Velocity = Velocity;
	}


public:
	void Up();
	void UpKeyUp();
	void Down();
	void DownKeyUp();
	void Left();
	void LeftKeyUp();
	void Right();
	void RightKeyUp();

	void Jump();
	void JumpKeyUp();
	void Fall();
	void Attack();
	void AttackKeyUp();
	void Dash();
	void DashKeyUp();
	void Focus();
	void FocusKeyUp();
	void Hurt();

	void QuickMap();
	void SuperDash();
	void DreamNail();

	void QuickCast();
	void Inventory();

};

