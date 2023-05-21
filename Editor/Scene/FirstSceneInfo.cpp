#include "FirstSceneInfo.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneViewport.h"
#include "../UI/FirstSceneUI.h"
#include "../UI/StartSceneUI.h"
#include "../UI/Fade.h"
#include "../GameObject/Player2D.h"
#include "../GameObject/Monster.h"
#include "../GameObject/BackObj.h"
#include "../GameObject/Vengefly.h"
#include "../GameObject/WallObj.h"
#include "../GameObject/Effect.h"
#include "../GameObject/PortalObject.h"
#include "../GameObject/GrimmLandPoint.h"
#include "../GameObject/Grimm.h"

CFirstSceneInfo::CFirstSceneInfo()
{
	m_ClassTypeName = "FirstSceneInfo";
}

CFirstSceneInfo::~CFirstSceneInfo()
{
}

bool CFirstSceneInfo::Init()
{
	CSceneInfo::Init();

	m_Owner->GetViewport()->CreateUIWindow<CFade>("Fade");

	m_Owner->GetViewport()->CreateUIWindow<CFirstSceneUI>("FirstSceneUI");

	CPlayer2D* Player = m_Owner->CreateObject<CPlayer2D>("Player2D");

	SetPlayerObject(Player);

	//m_Vengefly = m_Owner->CreateObject<CVengefly>("Vengefly");

	CPortalObject* Portal = m_Owner->CreateObject<CPortalObject>("Portal");

	//m_Grimm = m_Owner->CreateObject<CGrimm>("Grimm");
	//CGrimmLandPoint* GrimmLandPoint = m_Owner->CreateObject<CGrimmLandPoint>("GrimmLandPoint");

	return true;
}

void CFirstSceneInfo::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);

	//m_Vengefly->SetWorldPosition()
}

void CFirstSceneInfo::SceneChangeComplete()
{
}
