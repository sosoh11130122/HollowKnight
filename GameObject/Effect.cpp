#include "Effect.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Resource/Material/Material.h"
#include "Animation/Animation2D.h"
#include "Player2D.h"
#include "Scene/Scene.h"

CEffect::CEffect()	:
	m_EffectType(EEffect_Type::Once)
{
	SetTypeID<CEffect>();

	m_ObjectTypeName = "Effect";
}

CEffect::CEffect(const CEffect& Obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("sprite");
	m_Body = (CColliderBox2D*)FindComponent("Effect");
}

CEffect::~CEffect()
{
}

void CEffect::SetCollisionProfileName(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
}

void CEffect::Start()
{
	CGameObject::Start();

	m_Body = CreateComponent<CColliderBox2D>("Effect");
	m_Sprite = CreateComponent<CSpriteComponent>("sprite");

	SetRootComponent(m_Body);

	m_Body->SetCollisionProfile("Effect");
	m_Body->AddChild(m_Sprite);
	m_Body->SetPivot(0.5f, 0.5f);
	m_Body->SetBoxSize(157.f, 114.f);

	m_Sprite->SetRelativeScale(150.f, 150.f);
	m_Sprite->SetPivot(0.5f, 0.5f);

	//m_Sprite->SetRelativeScale(50.f, 50.f);
	m_Animation = m_Sprite->SetAnimation<CAnimation2D>("Effect");

	// Player
	m_Animation->AddAnimation("SlashLeft", "SlashLeft", 1.f, 1.5f, false);
	m_Animation->AddAnimation("SlashRight", "SlashRight", 1.f, 1.5f, false, true);


	m_Animation->AddAnimation("AttackUpLeftEffect", "AttackUpLeftEffect", 1.f, 1.5f, false);
	m_Animation->AddAnimation("AttackUpRightEffect", "AttackUpRightEffect", 1.f, 1.5f, false);

	m_Animation->AddAnimation("AttackDownLeftEffect", "AttackDownLeftEffect", 1.f, 1.8f, false);
	m_Animation->AddAnimation("AttackDownRightEffect", "AttackDownRightEffect", 1.f, 1.8f, false);

	m_Animation->AddAnimation("DashLeftEffect", "DashLeftEffect", 1.f, 1.5f, false);
	m_Animation->AddAnimation("DashRightEffect", "DashRightEffect", 1.f, 1.5f, false);

	m_Animation->AddAnimation("FocusEffect", "FocusEffect", 1.f, 1.5f, true, false);

	// monster
	m_Animation->AddAnimation("SwordLeft", "SwordLeft", 1.f, 1.5f, false);
	m_Animation->AddAnimation("SwordRight", "SwordRight", 1.f, 1.5f, false, true);


	// Grimm
	m_Animation->AddAnimation("GrimmChildInEffect", "GrimmChildInEffect", 1.f, 0.5f, true);
	m_Animation->AddAnimation("Light", "Light", 1.f, 0.5f, true);

	// brokenvessel
	m_Animation->AddAnimation("OverAttackEffect", "OverAttackEffect", 0.7f, 1.f, true);
	//m_Animation->AddAnimation("BossOrangeEffect", "BossOrangeEffect", 0.7f, 1.f);
	m_Animation->AddAnimation("SwordEffectLeft", "SwordEffectLeft", 0.7f, 1.f);
	m_Animation->AddAnimation("SwordEffectRight", "SwordEffectRight", 0.7f, 1.f);


	//
	m_Body->SetCollisionCallback<CEffect>(ECollision_Result::Collision, this, &CEffect::CollisionEffect);

}

bool CEffect::Init()
{
	CGameObject::Init();

    return true;
}

void CEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Player = (CPlayer2D*)m_Scene->FindObject("Player2D");

	m_PlayerDir = m_Player->GetPlayer();
}

void CEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CEffect* CEffect::Clone() const
{
	return new CEffect(*this);
}

void CEffect::PlayerAttack()
{
	//m_Animation->ChangeAnimation("SlashRight");

}

void CEffect::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
	{
		Destroy();
	}
}

void CEffect::CollisionEffect(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "Monster")
	{
		if (m_PlayerDir == 1)
		{
			m_Animation->ChangeAnimation("SwordLeft");
		}

		else
			m_Animation->ChangeAnimation("SwordRight");
	}
}