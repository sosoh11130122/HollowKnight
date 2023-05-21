#include "BossMapUI.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"
#include "UI/UIImage.h"
#include "UI/UIProgressBar.h"
#include "UI/UINumber.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "../Scene/LoadingSceneInfo.h"
#include "../Scene/FirstSceneInfo.h"
#include "Engine.h"
#include "../GameObject/BackObj.h"
#include "../GameObject/Player2D.h"
#include "Animation/Animation2D.h"

CBossMapUI::CBossMapUI()
{
    m_WindowTypeName = "BossMapUI";
}

CBossMapUI::CBossMapUI(const CBossMapUI& Window)
{
}

CBossMapUI::~CBossMapUI()
{
}

void CBossMapUI::Start()
{
    CUIWindow::Start();

    m_Scene->GetResource()->LoadSound("BGM", "BossMap", true, "BrokenVessel.mp3", SOUND_PATH);
    m_Scene->GetResource()->SoundPlay("BossMap");

}

bool CBossMapUI::Init()
{
    CUIWindow::Init();
    m_Life = CreateWidget<CUIImage>("Life");
    m_Life->SetPos(10.f, 570.f);
    m_Life->SetSize(240.f, 145.f);
    m_Life->SetTexture("Life", TEXT("UI/life.png"));

    m_HPBack = CreateWidget<CUIImage>("HPBack");
    m_HPBack->SetPos(150.f, 570.f);
    m_HPBack->SetSize(350.f, 70.f);
    m_HPBack->SetTexture("HPBack", TEXT("UI/lifeback.png"));

    //== HP
    m_HP = CreateWidget<CUIImage>("HP1");
    m_HP->SetPos(435.f, 570.f);
    m_HP->SetSize(57.f, 70.f);
    m_HP->SetTexture("HP", TEXT("HP1.png"));

    m_HP = CreateWidget<CUIImage>("HP2");
    m_HP->SetPos(365.f, 570.f);
    m_HP->SetSize(57.f, 70.f);
    m_HP->SetTexture("HP", TEXT("HP1.png"));

    m_HP = CreateWidget<CUIImage>("HP3");
    m_HP->SetPos(295.f, 570.f);
    m_HP->SetSize(57.f, 70.f);
    m_HP->SetTexture("HP", TEXT("HP1.png"));

    m_HP = CreateWidget<CUIImage>("HP4");
    m_HP->SetPos(225.f, 570.f);
    m_HP->SetSize(57.f, 70.f);
    m_HP->SetTexture("HP", TEXT("HP1.png"));

    m_HP = CreateWidget<CUIImage>("HP5");
    m_HP->SetPos(155.f, 570.f);
    m_HP->SetSize(57.f, 70.f);
    m_HP->SetTexture("HP", TEXT("HP1.png"));

    m_HPFront = CreateWidget<CUIImage>("HPFront");
    m_HPFront->SetPos(10.f, 570.f);
    m_HPFront->SetSize(240.f, 145.f);
    m_HPFront->SetTexture("HPFront", TEXT("UI/bar4.png"));
    return true;
}

void CBossMapUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);
}

void CBossMapUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);

}

void CBossMapUI::Render()
{
    CUIWindow::Render();

}

CBossMapUI* CBossMapUI::Clone()
{
    return new CBossMapUI(*this);
}

void CBossMapUI::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CBossMapUI::Load(FILE* File)
{
    CUIWindow::Load(File);

}

void CBossMapUI::StartButtonClick()
{
}
