#include "PortalObject.h"
#include "Player2D.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "../Scene/SecondSceneInfo.h"

CPortalObject::CPortalObject()
{
	SetTypeID<CPortalObject>();

	m_ObjectTypeName = "PortalObject";
}

CPortalObject::CPortalObject(const CPortalObject& Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Portal");
	m_Sprite = (CSpriteComponent*)FindComponent("sprite");
}

CPortalObject::~CPortalObject()
{
}

void CPortalObject::Start()
{
	CGameObject::Start();

	m_Body = CreateComponent<CColliderBox2D>("Portal");

	SetRootComponent(m_Body);

	m_Body->SetCollisionProfile("Portal");

	//m_Body->AddChild(m_Sprite);
	m_Body->SetPivot(0.5f, 0.5f);

	m_Body->SetBoxSize(50.f, 50.f);
	//m_Body->SetRelativeScale(15.f, 2.f);
	m_Body->SetWorldPosition(2620.f, 200.f);

	m_Body->SetCollisionCallback<CPortalObject>(ECollision_Result::Collision, this, &CPortalObject::Scene1CollisionBegin);
}

bool CPortalObject::Init()
{
	CGameObject::Init();


	return true;
}

void CPortalObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CPortalObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CPortalObject* CPortalObject::Clone() const
{
	return new CPortalObject(*this);
}

void CPortalObject::Scene1CollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "Player")
	{
		CSceneManager::GetInst()->CreateNextScene(true);

		CSceneManager::GetInst()->CreateSceneInfo<CSecondSceneInfo>(false); 

		CSceneManager::GetInst()->GetNextScene()->Load("Stage1.scn", SCENE_PATH);
	}
	//CSceneManager::GetInst()->CreateNextScene(true);

	//CSceneManager::GetInst()->CreateSceneInfo<CSecondSceneInfo>(false); 

	//CSceneManager::GetInst()->GetNextScene()->Load("realmap1.scn", SCENE_PATH);
}

void CPortalObject::Scene1CollisionEnd(const CollisionResult& result)
{
}

void CPortalObject::Scene2CollisionBegin(const CollisionResult& result)
{
}

void CPortalObject::Scene2CollisionEnd(const CollisionResult& result)
{
}
