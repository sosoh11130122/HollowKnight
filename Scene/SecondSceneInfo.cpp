#include "SecondSceneInfo.h"
#include "../GameObject/BackObj.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneViewport.h"
#include "../UI/SecondSceneUI.h"
#include "../UI/FirstSceneUI.h"
#include "../UI/Fade.h"
#include "Component/SpriteComponent.h"
#include "../GameObject/Player2D.h"
#include "../GameObject/Monster.h"
#include "../GameObject/BackObj.h"
#include "../GameObject/Vengefly.h"
#include "../GameObject/Vengefly2.h"
#include "../GameObject/PortalObject2.h"

CSecondSceneInfo::CSecondSceneInfo()
{
	m_ClassTypeName = "SecondSceneInfo";
}

CSecondSceneInfo::~CSecondSceneInfo()
{
}

bool CSecondSceneInfo::Init()
{
	CSceneInfo::Init();

	m_Owner->GetViewport()->CreateUIWindow<CFade>("Fade");

	//m_Owner->GetViewport()->CreateUIWindow<CFirstSceneUI>("FirstSceneUI");
	m_Owner->GetViewport()->CreateUIWindow<CSecondSceneUI>("SecondSceneUI");

	m_PlayerObject = m_Owner->CreateObject<CPlayer2D>("Player2D");

	SetPlayerObject(m_PlayerObject);

	CVengefly* Vengefly = m_Owner->CreateObject<CVengefly>("Vengefly");

	CVengefly2* Vengefly2 = m_Owner->CreateObject<CVengefly2>("Vengefly2");

	CPortalObject2* Portal = m_Owner->CreateObject<CPortalObject2>("PortalObject2");

    return true;
}

void CSecondSceneInfo::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);
}

void CSecondSceneInfo::SceneChangeComplete()
{
}
