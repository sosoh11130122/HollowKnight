#pragma once

#include "GameObject/GameObject.h"

enum class EEffect_Type
{
	Once,
	Duration,
	Loop

};
class CEffect :
    public CGameObject
{
	friend class CScene;

protected:
	CEffect();
	CEffect(const CEffect& Obj);
	virtual ~CEffect();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CAnimation2D>		m_Animation;
	CSharedPtr<class CPlayer2D>			m_Player;

private:
	EEffect_Type	m_EffectType;
	float			m_Duration;
	float			m_Time;
	int				m_PlayerDir;

public:
	void SetCollisionProfileName(const std::string& Name);

public:
	EEffect_Type GetEffectType()	const
	{
		return m_EffectType;
	}

	void SetDuration(float Duration)
	{
		m_Duration = Duration;
	}

	CAnimation2D* GetAnimation()	const
	{
		return m_Animation;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CEffect* Clone()    const;

public:
	void PlayerAttack();
	void AnimationEnd();

private:
	void CollisionEffect(const CollisionResult& result);
};

