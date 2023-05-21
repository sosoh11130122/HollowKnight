#include "FirstSceneUI.h"
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

CFirstSceneUI::CFirstSceneUI() :
    m_CurHP(5)
{
    m_WindowTypeName = "FirstSceneUI";

}

CFirstSceneUI::CFirstSceneUI(const CFirstSceneUI& Window) :
    CUIWindow(Window)
{
    m_Number = FindWidget<CUINumber>("Number");

    for (int i = 0; i < m_CurHP; ++i)
    {
        m_HP[i] = FindWidget<CUIImage>("HP" + std::to_string(i));
    }
    m_HPBack = FindWidget<CUIImage>("HPBack");
    m_Life = FindWidget<CUIImage>("Life");

}

CFirstSceneUI::~CFirstSceneUI()
{
}

void CFirstSceneUI::SetHP(int HP)
{
    for (int i = 0; i < 5; ++i)
    {
        if (HP > i)
        {
            m_HP[i]->SetEnable(true);
        }
        else
        {
            m_HP[i]->SetEnable(false);
        }
    }
}

void CFirstSceneUI::Start()
{
    CUIWindow::Start();
    
    m_Scene->GetResource()->LoadSound("BGM", "CrossRoads", false, "CrossRoads.mp3", SOUND_PATH);
    m_Scene->GetResource()->SoundPlay("CrossRoads");
 
    //m_Button->SetSound(EButtonEventState::Hovered, "UI", "ButtonHovered", false, "Demasia.mp3");
    
    //m_Scene->GetResource()->CreateSoundChannel("FirstSceneBGM");

    //m_Scene->GetResource()->FindSound("")

    //m_Button->SetCallback<CFirstSceneUI>(EButtonEventState::Click,
        //this, &CFirstSceneUI::StartButtonClick);
}

bool CFirstSceneUI::Init()
{
    CUIWindow::Init();

    //CUIImage* Logo = CreateWidget<CUIImage>("Logo");
    //Logo->SetTexture("Logo",TEXT("HollowKnightLogo_White.png"));
    //Logo->SetSize(500.f, 208.f);
    //Logo->SetPos(100.f, 100.f);


    //m_Button = CreateWidget<CUIButton>("Button");
    //m_Button->SetSize(100.f, 100.f);
    //m_Button->SetPos(300.f, 300.f);
    //m_Button->SetTint(255, 0, 0, 255);

    //m_Button->SetTexture(EButtonState::Normal, "StartButton", TEXT("Start.png"));
    //m_Button->SetTexture(EButtonState::Hovered, "StartButton", TEXT("Start.png"));
    //m_Button->SetTexture(EButtonState::Click, "StartButton", TEXT("Start.png"));
    //m_Button->SetTexture(EButtonState::Disable, "StartButton", TEXT("Start.png"));

    //m_Button->SetSound(EButtonEventState::Hovered, "UI", "ButtonHovered", false, "Demasia.mp3");
    //m_Button->SetSound(EButtonEventState::Click, "UI", "ButtonClick", false, "TeemoSmile.mp3");

   /* m_Title = CreateWidget<CUIText>("Title");

    m_Title->SetSize(300.f, 100.f);
    m_Title->SetPos(200.f, 500.f);

    m_Title->SetFontSize(50.f);
    m_Title->SetText(TEXT("Hollow Knight"));
    m_Title->SetColor(255, 255, 0);
    m_Title->SetTransparency(true);
    m_Title->SetOpacity(0.8f);

    m_Title->SetShadowEnable(true);
    m_Title->SetShadowColor(128, 128, 128);
    m_Title->SetShadowTransparency(true);
    m_Title->SetShadowOpacity(0.5f);*/


    m_Life = CreateWidget<CUIImage>("Life");
    m_Life->SetPos(10.f, 570.f);
    m_Life->SetSize(240.f, 145.f);
    m_Life->SetTexture("Life", TEXT("UI/life.png"));

    m_HPBack = CreateWidget<CUIImage>("HPBack");
    m_HPBack->SetPos(150.f, 570.f);
    m_HPBack->SetSize(350.f, 70.f);
    m_HPBack->SetTexture("HPBack", TEXT("UI/lifeback.png"));

    //== HP
    //m_HP = CreateWidget<CUIImage>("HP1");
    //m_HP->SetPos(435.f, 570.f);
    //m_HP->SetSize(57.f, 70.f);
    //m_HP->SetTexture("HP", TEXT("HP1.png"));

    //m_HP = CreateWidget<CUIImage>("HP2");
    //m_HP->SetPos(365.f, 570.f);
    //m_HP->SetSize(57.f, 70.f);
    //m_HP->SetTexture("HP", TEXT("HP1.png"));

    //m_HP = CreateWidget<CUIImage>("HP3");
    //m_HP->SetPos(295.f, 570.f);
    //m_HP->SetSize(57.f, 70.f);
    //m_HP->SetTexture("HP", TEXT("HP1.png"));

    //m_HP = CreateWidget<CUIImage>("HP4");
    //m_HP->SetPos(225.f, 570.f);
    //m_HP->SetSize(57.f, 70.f);
    //m_HP->SetTexture("HP", TEXT("HP1.png"));

    //m_HP = CreateWidget<CUIImage>("HP5");
    //m_HP->SetPos(155.f, 570.f);
    //m_HP->SetSize(57.f, 70.f);
    //m_HP->SetTexture("HP", TEXT("HP1.png"));

    for (size_t i = 0; i < m_CurHP; ++i)
    {
        m_HP[i] = CreateWidget<CUIImage>("HP" + std::to_string(i));
        m_HP[i]->SetPos(i * 70.f + 155.f, 570.f);
        m_HP[i]->SetSize(57.f, 70.f);
        m_HP[i]->SetTexture("HP", TEXT("HP1.png"));
    }

    m_HPFront = CreateWidget<CUIImage>("HPFront");
    m_HPFront->SetPos(10.f, 570.f);
    m_HPFront->SetSize(240.f, 145.f);
    m_HPFront->SetTexture("HPFront", TEXT("UI/bar4.png"));
 


    //    TEXT("HPFull.png"));
    //m_ProgressBar = CreateWidget<CUIProgressBar>("ProgressBar");

    //m_ProgressBar->SetPos(50.f, 600.f);
    //m_ProgressBar->SetSize(630.f, 70.f);

    ////m_ProgressBar->SetImageTint(EProgressBarTextureType::Back, 100, 100, 100, 255);
    ////m_ProgressBar->SetImageTint(EProgressBarTextureType::Bar, 255, 255, 255, 255);

    //m_ProgressBar->SetTexture(EProgressBarTextureType::Bar, "HPBar",
    //    TEXT("HPFull.png"));
    //m_ProgressBar->SetTexture(EProgressBarTextureType::Back, "HPBarBack",
    //    TEXT("HPEmpty.png"));

    //m_ProgressBar->SetProgressBarMin(0.f);
    //m_ProgressBar->SetProgressBarMax(100.f);
    //m_ProgressBar->SetValue(50.f);
    //m_ProgressBar->SetBarDir(EProgressBarDir::LeftToRight);


    /*m_Number = CreateWidget<CUINumber>("Number");

    m_Number->SetPos(1000.f, 700.f);
    m_Number->SetSize(20.f, 30.f);

    m_Number->SetNumber(2392);

    m_Number->SetTexture("Number", TEXT("Number.png"));

    for (int i = 0; i < 10; ++i)
    {
        m_Number->AddFrameData(Vector2(i * 46.4f, 0.f), Vector2((i + 1) * 46.4f, 68.5f));
    }*/


    return true;

}

void CFirstSceneUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);

    //float FPS = CEngine::GetInst()->GetFPS();

    //m_Number->SetNumber((unsigned int)FPS);
    
    m_Player = (CPlayer2D*)m_Scene->FindObject("Player2D");

    m_CurHP = m_Player->GetHP();

    for (size_t i = 0; i < m_CurHP; ++i)
    {
        SetHP(m_CurHP);
    }


}

void CFirstSceneUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);

    /*if (m_Player)
    {
        m_Player = (CPlayer2D*)m_Scene->FindObject("Player2D");
        int PlayerHP = m_Scene->GetPlayer()->GetHP();

        if (PlayerHP <= 0)
        {
           m_HP->Destroy();
        }
    }*/
}

void CFirstSceneUI::Render()
{
    CUIWindow::Render();
}

CFirstSceneUI* CFirstSceneUI::Clone()
{
    return new CFirstSceneUI(*this);
}

void CFirstSceneUI::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CFirstSceneUI::Load(FILE* File)
{
    CUIWindow::Load(File);

    m_Button = FindWidget<CUIButton>("Button");
    m_Title = FindWidget<CUIText>("Title");
    m_Number = FindWidget<CUINumber>("Number");
    m_Back = FindWidget<CUIImage>("Back");
}

void CFirstSceneUI::StartButtonClick()
{
//    // 로딩 Scene을 생성한다.
//    CSceneManager::GetInst()->CreateNextScene(true);
//
//    CSceneManager::GetInst()->CreateSceneInfo<CFirstSceneInfo>(false); // 이거다
//    
//    CSceneManager::GetInst()->GetNextScene()->Load("realmap1.scn", SCENE_PATH);
}
