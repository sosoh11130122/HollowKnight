#include "WallObj.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "Scene/Scene.h"

CWallObj::CWallObj()
{
    SetTypeID<CWallObj>();

    m_ObjectTypeName = "WallObj";
}

CWallObj::CWallObj(const CWallObj& Obj)
{
    m_Body = (CColliderBox2D*)FindComponent("Wall");
    m_Sprite = (CSpriteComponent*)FindComponent("sprite");
}

CWallObj::~CWallObj()
{
}

void CWallObj::Start()
{
    CGameObject::Start();

    m_Body = CreateComponent<CColliderBox2D>("Wall");


    //m_Sprite = CreateComponent<CSpriteComponent>("sprite");

    SetRootComponent(m_Body);

    m_Body->SetCollisionProfile("Wall");

    //m_Body->AddChild(m_Sprite);
    //m_Body->SetPivot(0.f, 0.f);

    m_Body->SetBoxSize(2200.f, 100.f);
    //m_Body->SetRelativeScale(15.f, 2.f);
    m_Body->SetWorldPosition(1100.f, 57.f);

    m_Body->SetCollisionCallback<CWallObj>(ECollision_Result::Collision, this, &CWallObj::CollisionBegin);
    // m_Sprite->GetMaterial(0);
    // m_Sprite->SetRelativeScale(1.f, 1.f);
    //m_Sprite->SetPivot(0.5f, 0.5f);

    // m_Sprite->SetInheritRotZ(true);
}

bool CWallObj::Init()
{
    CGameObject::Init();

    return true;
}

void CWallObj::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    m_Body->SetCollisionCallback<CWallObj>(ECollision_Result::Release, this, &CWallObj::CollisionEnd);
}

void CWallObj::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

//void CWallObj::CollisionBegin(CCollider* Src, CCollider* Dest)
//{
//    if (Dest->GetName() == "Player")
//        m_Ground = true;
//}

void CWallObj::CollisionBegin(const CollisionResult& result)
{
    //m_Scene->FindObject("Player2D")->SetPhysicsSimulate(false); 

}

void CWallObj::CollisionEnd(const CollisionResult& result)
{
    //m_Scene->FindObject("Player2D")->SetPhysicsSimulate(true);
}


CWallObj* CWallObj::Clone() const
{
    return new CWallObj(*this);
}
