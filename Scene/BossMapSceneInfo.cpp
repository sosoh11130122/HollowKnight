#include "BossMapSceneInfo.h"
#include "../UI/BossMapUI.h"
#include "../UI/Fade.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneViewport.h"
#include "../GameObject/Player2D.h"
#include "../GameObject/BrokenVessel.h"


CBossMapSceneInfo::CBossMapSceneInfo()
{
    m_ClassTypeName = "BossMapSceneInfo";

}

CBossMapSceneInfo::~CBossMapSceneInfo()
{
}

bool CBossMapSceneInfo::Init()
{
    CSceneInfo::Init();

    m_Owner->GetViewport()->CreateUIWindow<CFade>("Fade");

    m_Owner->GetViewport()->CreateUIWindow<CBossMapUI>("BossMapUI");

    m_PlayerObject = m_Owner->CreateObject<CPlayer2D>("Player2D");

    SetPlayerObject(m_PlayerObject);

    CBrokenVessel* BrokenVessel = m_Owner->CreateObject<CBrokenVessel>("BrokenVessel");

    return true;
}

void CBossMapSceneInfo::Update(float DeltaTime)
{
    CSceneInfo::Update(DeltaTime);

}

void CBossMapSceneInfo::SceneChangeComplete()
{
}
