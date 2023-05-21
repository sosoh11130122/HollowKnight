#include "StartSceneUI.h"
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

CStartSceneUI::CStartSceneUI()
{
    m_WindowTypeName = "StartSceneUI";
}

CStartSceneUI::CStartSceneUI(const CStartSceneUI& Window) :
    CUIWindow(Window)
{
    m_Button = FindWidget<CUIButton>("Button");
    m_Title = FindWidget<CUIText>("Title");
    m_Number = FindWidget<CUINumber>("Number");
    m_Back = FindWidget<CUIImage>("Back");


}

CStartSceneUI::~CStartSceneUI()
{
}

void CStartSceneUI::Start()
{
    CUIWindow::Start();

    m_Button->SetCallback<CStartSceneUI>(EButtonEventState::Click,
        this, &CStartSceneUI::StartButtonClick);

    m_Scene->GetResource()->LoadSound("BGM", "Start", false, "EnterHallownest.mp3", SOUND_PATH);
    m_Scene->GetResource()->SoundPlay("Start");

}

bool CStartSceneUI::Init()
{
    CUIWindow::Init();

    m_Back = CreateWidget<CUIImage>("Back");

    m_Back->SetSize(1280.f, 720.f);
    m_Back->SetTexture("Back", TEXT("UI/StartScene.jpg"));
    
    m_Button = CreateWidget<CUIButton>("StartButton");

    m_Button->SetSize(260.f, 35.f);
    m_Button->SetPos(510.f, 250.f);

    m_Button->SetTexture(EButtonState::Normal, "StartButton", TEXT("UI/StartGame.png"));
    m_Button->SetTexture(EButtonState::Hovered, "StartButton", TEXT("UI/StartGame.png"));
    m_Button->SetTexture(EButtonState::Click, "StartButton", TEXT("UI/StartGame.png"));
    m_Button->SetTexture(EButtonState::Disable, "StartButton", TEXT("UI/StartGame.png"));

    //mButton->SetSound(EButtonEventState::Hovered, "UI", "ButtonHovered", false, "Demasia.mp3");
    //mButton->SetSound(EButtonEventState::Click, "UI", "ButtonClick", false, "TeemoSmile.mp3");

    CUIButton* OptionsButton = CreateWidget<CUIButton>("OptionsButton");

    OptionsButton->SetSize(260.f, 35.f);
    OptionsButton->SetPos(510.f, 200.f);

    OptionsButton->SetTexture(EButtonState::Normal, "OptionsButton", TEXT("UI/Options.png"));
    OptionsButton->SetTexture(EButtonState::Hovered, "OptionsButton", TEXT("UI/Options.png"));
    OptionsButton->SetTexture(EButtonState::Click, "OptionsButton", TEXT("UI/Options.png"));
    OptionsButton->SetTexture(EButtonState::Disable, "OptionsButton", TEXT("UI/Options.png"));

    CUIButton* AchievementsButton = CreateWidget<CUIButton>("AchievementsButton");

    AchievementsButton->SetSize(260.f, 35.f);
    AchievementsButton->SetPos(510.f, 150.f);

    AchievementsButton->SetTexture(EButtonState::Normal, "AchievementsButton", TEXT("UI/Achievements.png"));
    AchievementsButton->SetTexture(EButtonState::Hovered, "AchievementsButton", TEXT("UI/Achievements.png"));
    AchievementsButton->SetTexture(EButtonState::Click, "AchievementsButton", TEXT("UI/Achievements.png"));
    AchievementsButton->SetTexture(EButtonState::Disable, "AchievementsButton", TEXT("UI/Achievements.png"));

    CUIButton* ExtrasButton = CreateWidget<CUIButton>("ExtrasButton");

    ExtrasButton->SetSize(260.f, 35.f);
    ExtrasButton->SetPos(510.f, 100.f);

    ExtrasButton->SetTexture(EButtonState::Normal, "ExtrasButton", TEXT("UI/Extras.png"));
    ExtrasButton->SetTexture(EButtonState::Hovered, "ExtrasButton", TEXT("UI/Extras.png"));
    ExtrasButton->SetTexture(EButtonState::Click, "ExtrasButton", TEXT("UI/Extras.png"));
    ExtrasButton->SetTexture(EButtonState::Disable, "ExtrasButton", TEXT("UI/Extras.png"));
    
    CUIButton* QuitGameButton = CreateWidget<CUIButton>("QuitGameButton");

    QuitGameButton->SetSize(260.f, 35.f);
    QuitGameButton->SetPos(510.f, 50.f);

    QuitGameButton->SetTexture(EButtonState::Normal, "QuitGameButton", TEXT("UI/QuitGame.png"));
    QuitGameButton->SetTexture(EButtonState::Hovered, "QuitGameButton", TEXT("UI/QuitGame.png"));
    QuitGameButton->SetTexture(EButtonState::Click, "QuitGameButton", TEXT("UI/QuitGame.png"));
    QuitGameButton->SetTexture(EButtonState::Disable, "QuitGameButton", TEXT("UI/QuitGame.png"));

    m_Number = CreateWidget<CUINumber>("Number");

    m_Number->SetPos(100.f, 600.f);
    m_Number->SetSize(20.f, 30.f);

    m_Number->SetNumber(2392);

    m_Number->SetTexture("Number", TEXT("Number.png"));

    for (int i = 0; i < 10; ++i)
    {
        m_Number->AddFrameData(Vector2(i * 46.4f, 0.f), Vector2((i + 1) * 46.4f, 68.5f));
    }

    return true;
}

void CStartSceneUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);

    float FPS = CEngine::GetInst()->GetFPS();

    m_Number->SetNumber((unsigned int)FPS);
}

void CStartSceneUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);
}

void CStartSceneUI::Render()
{
    CUIWindow::Render();
}

CStartSceneUI* CStartSceneUI::Clone()
{
    return new CStartSceneUI(*this);
}

void CStartSceneUI::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CStartSceneUI::Load(FILE* File)
{
    CUIWindow::Load(File);

    m_Button = FindWidget<CUIButton>("Button");
    m_Title = FindWidget<CUIText>("Title");
    m_Number = FindWidget<CUINumber>("Number");
    m_Back = FindWidget<CUIImage>("Back");
}

void CStartSceneUI::StartButtonClick()
{
    // 로딩 Scene을 생성한다.
    CSceneManager::GetInst()->CreateNextScene(true);

    CSceneManager::GetInst()->CreateSceneInfo<CFirstSceneInfo>(false); // 이거다

    //CSceneManager::GetInst()->GetNextScene()->Load("troupe2.scn", SCENE_PATH); 
    CSceneManager::GetInst()->GetNextScene()->Load("Main.scn", SCENE_PATH);
}

