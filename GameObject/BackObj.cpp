#include "BackObj.h"
#include "Component/SpriteComponent.h"
#include "Resource/Material/Material.h"

CBackObj::CBackObj()
{
	SetTypeID<CBackObj>();

	m_ObjectTypeName = "BackObj";
}

CBackObj::CBackObj(const CBackObj& Obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("sprite");
}

CBackObj::~CBackObj()
{
}

bool CBackObj::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("sprite");
	m_Sprite->GetMaterial(0)->SetShader("TileMapBackShader");
	m_Sprite->GetMaterial(0)->SetRenderState("DepthLessEqual");
	m_Sprite->SetWorldScale(2793.f, 817.f);
	m_Sprite->SetWorldPosition(0.f, 0.f);
	m_Sprite->SetPivot(0.f, 0.f);

	return true;
}

void CBackObj::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

