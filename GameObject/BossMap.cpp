#include "BossMap.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Input.h"
#include "Component/TargetArm.h"
#include "Animation/Animation2D.h"

CBossMap::CBossMap()
{
    SetTypeID<CBossMap>();

    m_ObjectTypeName = "BossMap";
}

CBossMap::CBossMap(const CBossMap& Obj)
{
    m_Sprite = (CSpriteComponent*)FindComponent("Sprite");
}

CBossMap::~CBossMap()
{
}

void CBossMap::Start()
{
    CGameObject::Start();

    m_Sprite = CreateComponent<CSpriteComponent>("Sprite");

    //m_Body->SetWorldPosition(500.f, 500.f);
    //m_Body->SetBoxSize(1000.f, 1000.f);
    SetRootComponent(m_Sprite);

    m_Sprite->SetWorldPosition(0.f, 0.f);
    m_Sprite->SetWorldScale(1500.f, 845.f);
    //m_Sprite->SetMeshSize(1000.f, 563.f);
    m_Sprite->SetPivot(0.f, 0.f);

    m_Sprite->GetMaterial(0)->SetShader("TileMapBackShader");
    m_Sprite->GetMaterial(0)->SetRenderState("DepthLessEqual");
    m_Sprite->SetTexture("BossMap", TEXT("BossMap.png"));
}

bool CBossMap::Init()
{
    CGameObject::Init();

    return true;
}

void CBossMap::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
}

void CBossMap::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

CBossMap* CBossMap::Clone() const
{
    return new CBossMap(*this);
}

void CBossMap::Save(FILE* File)
{
    CGameObject::Save(File);
}

void CBossMap::Load(FILE* File)
{
    CGameObject::Load(File);

}

