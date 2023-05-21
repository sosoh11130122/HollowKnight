#pragma once

#include "GameObject\GameObject.h"

enum class EBrokenVessel_Animation
{
	Idle,
	Walk,
	Dash,
	Jump,
	Fall,
	OverHeadAttack,
	Stun,
	Roar,
	Death,
	DownStab,
	DownStabLand,
	StartAnimation,
	Sleep
};


class CBrokenVessel :
	public CGameObject
{
	friend class CScene;

protected:
	CBrokenVessel();
	CBrokenVessel(const CBrokenVessel& Obj);
	virtual ~CBrokenVessel();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CColliderBox2D>	m_Radar;
	CSharedPtr<class CColliderBox2D>	m_Dash;
	CSharedPtr<class CGameObject>		m_Player;
	CSharedPtr<class CWallComponent>	m_WallComponent;
	CSharedPtr<class CEffect>			m_Effect;
	class CBullet*						m_Bullet[5];


private:
	int		m_MonsterDir;
	int		m_PrevMonsterDir;
	std::vector<std::string>	m_vecSequenceKey[2];
	EBrokenVessel_Animation	m_PrevMonsterAnim;
	EBrokenVessel_Animation	m_MonsterAnim;
	CSharedPtr<class CAnimation2D> m_Animation;
	Vector3 m_Dir;
	Vector3 m_Pos;
	Vector3 m_PrevPos;
	Vector3 m_PlayerPos;
	bool	 m_Chase;
	float	 m_MoveSpeed;
	int		 m_HP;
	int		 m_DamageCount;

	float	 m_Time;

	bool	 m_Start;
	bool	 m_Roar;
	bool	 m_Idle;
	bool	 m_AttackStart;
	bool	 m_OverHeadAttack;
	bool	 m_Jump;
	bool	 m_DashStart;

	bool	 m_EnableChase;

	bool	 m_DownStab;
	bool	 m_DownStabLand;

	bool	 m_HeadBanging;
	bool	 m_Walk;
	bool	 m_Stun;
	bool	 m_EndRoar;
	bool	 m_Death;
	

	float	 m_PlayTime;




public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBrokenVessel* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	void Idle();
	void Left();
	void Right();
	void DashStart();
	void Jump();
	void Fall();
	void OverHeadAttack();
	void HeadBanging();
	void Stun();
	void StartAnimation();
	void StartRoar();
	void EndRoar();
	void Death();
	void DownStab();
	void DownStabLand();


	void StartAnimation(const CollisionResult& result);
	void Hurt(const CollisionResult& result);
	void HurtEnd(const CollisionResult& result);


};

