#include "Vengefly.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "Component/NavigationAgent.h"
#include "Resource/Material/Material.h"
#include "Input.h"
#include "Monster.h"
#include "Player2D.h"
#include "Scene/SceneInfo.h"
#include "Scene/Scene.h"

CVengefly::CVengefly() :
	m_Chase(false),
	m_MoveSpeed(-0.05f),
	m_HP(10.f)
{
	SetTypeID<CVengefly>();

	m_ObjectTypeName = "Vengefly";

	m_MonsterAnim = EVengefly_Animation::Idle;
	m_PrevMonsterAnim = EVengefly_Animation::Idle;
}

CVengefly::CVengefly(const CVengefly& Obj)
{
	m_Body = (CColliderOBB2D*)FindComponent("Body");
	m_Sprite = (CSpriteComponent*)FindComponent("sprite");
	m_Radar = (CColliderSphere2D*)FindComponent("Radar");
	m_Dash = (CColliderBox2D*)FindComponent("Dash");
}

CVengefly::~CVengefly()
{
}

void CVengefly::Start()
{
	CGameObject::Start();

	m_Body = CreateComponent<CColliderOBB2D>("Body");
	m_Radar = CreateComponent<CColliderSphere2D>("Radar");
	m_Dash = CreateComponent<CColliderBox2D>("Dash");
	m_Sprite = CreateComponent<CSpriteComponent>("sprite");


	SetRootComponent(m_Body);

	m_Body->SetCollisionProfile("Monster");
	m_Body->AddChild(m_Sprite);
	m_Body->AddChild(m_Radar);
	m_Body->AddChild(m_Dash);

	m_Sprite->SetPivot(0.5f, 0.f);
	m_Sprite->SetRelativeScale(100.f, 100.f);
	m_Sprite->SetRelativePosition(0.f, -50.f);

	m_Radar->SetPivot(0.5f, 0.5f);
	m_Radar->SetRelativeScale(5.f, 5.f);
	m_Radar->SetCollisionProfile("MonsterAttack");

	m_Body->SetWorldPosition(1220.f, 500.f);
	
	m_Body->SetCollisionCallback<CVengefly>(ECollision_Result::Collision, this, &CVengefly::Damage);

	m_Radar->SetCollisionCallback<CVengefly>(ECollision_Result::Collision, this, &CVengefly::Chase);
	m_Radar->SetCollisionCallback<CVengefly>(ECollision_Result::Release, this, &CVengefly::Idle);

	m_Animation = m_Sprite->SetAnimation<CAnimation2D>("Vengefly");

	m_Animation->AddAnimation("VengeflyIdleLeft", "VengeflyIdleLeft", 1.f, 1.f, true);
	m_Animation->AddAnimation("VengeflyIdleRight", "VengeflyIdleRight", 1.f, 1.f, true, true);
	m_Animation->AddAnimation("VengeflyChaseLeft", "VengeflyChaseLeft", 1.f, 1.f, true);
	m_Animation->AddAnimation("VengeflyChaseRight", "VengeflyChaseRight", 1.f, 1.f, true, true);
	m_Animation->AddAnimation("VengeflyStartleLeft", "VengeflyStartleLeft", 1.f, 1.f, true);
	m_Animation->AddAnimation("VengeflyStartleRight", "VengeflyStartleRight", 1.f, 1.f, true, true);
	m_Animation->AddAnimation("VengeflyTurnLeft", "VengeflyTurnLeft", 1.f, 1.f, true);
	m_Animation->AddAnimation("VengeflyTurnRight", "VengeflyTurnRight", 1.f, 1.f, true, true);
	m_Animation->AddAnimation("VengeflyDeathLeft", "VengeflyDeathLeft", 1.f, 1.f, true);
	m_Animation->AddAnimation("VengeflyDeathRight", "VengeflyDeathRight", 1.f, 1.f, true, true);

	m_vecSequenceKey[0].push_back("VengeflyIdleLeft");
	m_vecSequenceKey[0].push_back("VengeflyChaseLeft");
	m_vecSequenceKey[0].push_back("VengeflyStartleLeft");
	m_vecSequenceKey[0].push_back("VengeflyTurnLeft");
	m_vecSequenceKey[0].push_back("VengeflyDeathLeft");

	m_vecSequenceKey[1].push_back("VengeflyIdleRight");
	m_vecSequenceKey[1].push_back("VengeflyChaseRight");
	m_vecSequenceKey[1].push_back("VengeflyStartleRight");
	m_vecSequenceKey[1].push_back("VengeflyTurnRight");
	m_vecSequenceKey[1].push_back("VengeflyDeathRight");


	m_Pos = m_Body->GetWorldPos();
	m_PrevPos = m_Pos;
}

bool CVengefly::Init()
{
	CGameObject::Init();
	m_MonsterDir = -1;

	return true;
}

void CVengefly::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Player = m_Scene->FindObject("Player2D");

	m_Pos = m_Body->GetWorldPos();

	AddWorldPosition(m_Pos * DeltaTime * m_MoveSpeed * GetWorldAxis(AXIS_X));

	int	AnimDirectionIndex = 0;

	if (m_MonsterDir == -1)
		AnimDirectionIndex = 1;


	switch (m_MonsterAnim)
	{
	case EVengefly_Animation::Idle:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][0]);
		break;
	case EVengefly_Animation::Chase:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][1]);
		break;
	case EVengefly_Animation::Startle:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][2]);
		break;
	case EVengefly_Animation::Turn:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][3]);
		break;
	case EVengefly_Animation::Death:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][4]);
		break;
	}

	m_PrevMonsterAnim = m_MonsterAnim;

	float Move = m_Pos.x - m_PlayerPos.x;

	if (Move < 0.f)
		Right();

	else
		Left();

	if (m_Player)
	{
		m_PlayerPos = m_Player->GetWorldPos();

		if (m_Chase)
		{
			m_MonsterAnim = EVengefly_Animation::Chase;

			Vector3 Dir = m_PlayerPos - m_Pos;

			Dir.Normalize();

			m_Body->AddWorldPosition(Dir * 100.f * g_DeltaTime);
		}
	}

}

void CVengefly::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	m_PrevMonsterAnim = m_MonsterAnim;

	if (m_HP == 0)
		m_Body->Destroy();
}

CVengefly* CVengefly::Clone() const
{
	return new CVengefly(*this);
}

void CVengefly::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CVengefly::Load(FILE* File)
{
	CGameObject::Load(File);
}

void CVengefly::Idle(const CollisionResult& result)
{
	m_MonsterAnim = EVengefly_Animation::Idle;

	m_Chase = false;
} 

void CVengefly::Chase(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "Player")
	{
		m_Chase = true;
	}
}

void CVengefly::Damage(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "PlayerAttack")
	{
		AddWorldPositionX(m_Pos.x + 30.f);
		m_HP -= 5;
		++m_DamageCount;

		m_Scene->GetResource()->LoadSound("Effect", "Attack", false, "hero_damage.mp3", SOUND_PATH);
		m_Scene->GetResource()->SoundPlay("Attack");
	}
}

void CVengefly::Left()
{
	m_MonsterDir = 1.f;

	m_MonsterAnim = EVengefly_Animation::Idle;
}

void CVengefly::Right()
{
	m_MonsterDir = -1.f;

	m_MonsterAnim = EVengefly_Animation::Idle;
}
