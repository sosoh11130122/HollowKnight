#include "DefaultSetting.h"
#include "../GameObject/Player2D.h"
#include "../GameObject/Monster.h"
#include "../GameObject/Bullet.h"
#include "../GameObject/BackObj.h"
#include "../GameObject/WallObj.h"
#include "../GameObject/Effect.h"
#include "../GameObject/PortalObject.h"
#include "../GameObject/Grimm.h"
#include "../GameObject/SecondBackObj.h"
#include "../GameObject/GrimmTroupeBackObj.h"
#include "../GameObject/GrimmChild.h"
#include "../GameObject/BrokenVessel.h"
#include "../GameObject/BossMap.h"
#include "../GameObject/Vengefly2.h"
#include "../GameObject/PortalObject2.h"
#include "../GameObject/Vengefly.h"


#include "../UI/StartSceneUI.h"
#include "../UI/FirstSceneUI.h"
#include "../UI/SecondSceneUI.h"
#include "Scene/Scene.h"
#include "Input.h"
#include "CollisionManager.h"

CDefaultSetting::CDefaultSetting()
{
}

CDefaultSetting::~CDefaultSetting()
{
}

void CDefaultSetting::Init()
{
    LoadResource();

    CreateCDO();

    SetInput();

    SetCollision();
}

void CDefaultSetting::CreateCDO()
{
    CScene::CreateObjectCDO<CPlayer2D>("Player2D");
    CScene::CreateObjectCDO<CMonster>("Monster");
    CScene::CreateObjectCDO<CBullet>("Bullet");
    CScene::CreateObjectCDO<CBackObj>("BackObj");
    CScene::CreateObjectCDO<CWallObj>("WallObj");
    CScene::CreateObjectCDO<CSecondBackObj>("SecondBackObj");
    CScene::CreateObjectCDO<CEffect>("Effect");
    CScene::CreateObjectCDO<CPortalObject>("Portal");
    CScene::CreateObjectCDO<CGrimm>("Grimm");
    CScene::CreateObjectCDO<CGrimmTroupeBackObj>("GrimmTroupeBackObj");
    CScene::CreateObjectCDO<CGrimmChild>("GrimmChild");
    CScene::CreateObjectCDO<CBrokenVessel>("BrokenVessel");
    CScene::CreateObjectCDO<CBossMap>("BossMap");
    CScene::CreateObjectCDO<CVengefly>("Vengefly");
    CScene::CreateObjectCDO<CVengefly2>("Vengefly2");
    CScene::CreateObjectCDO<CPortalObject2>("PortalObject2");


    CScene::CreateUIWindowCDO<CStartSceneUI>("StartSceneUI");
    CScene::CreateUIWindowCDO<CFirstSceneUI>("FirstSceneUI");
    CScene::CreateUIWindowCDO<CSecondSceneUI>("SecondSceneUI");
}

void CDefaultSetting::LoadResource()
{
    // Player
    // Idle
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Idle/IdleLeft/Idle Wind_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "IdleLeft", "IdleLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("IdleLeft",
            5, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 0; i <= 4; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 4; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Idle/IdleRight/Idle Wind_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "IdleRight", "IdleRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("IdleRight",
            5, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 4; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // Left, Right
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Move/Left/Run_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "Left", "Left", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("Left",
            10, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 0; i <= 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();
    }

    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 9; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Move/Right/Run_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "Right", "Right", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("Right",
            10, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 9; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
    // Up, Down
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 5; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/LookUp/Left/LookUp_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "UpLeft", "UpLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("UpLeft",
            6, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 0; i <= 5; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 5; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/LookUp/Right/LookUp_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "UpRight", "UpRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("UpRight",
            6, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 5; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
    //
    {
        std::vector<const TCHAR*>   vecFileName;
        for (int i = 0; i <= 5; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/LookDown/Left/LookDown_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "DownLeft", "DownLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("DownLeft",
            6, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 0; i <= 5; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 5; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/LookDown/Right/LookDown_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "DownRight", "DownRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("DownRight",
            6, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 5; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
    // Jump
    {
        std::vector<const TCHAR*>   vecFileName;
        for (int i = 0; i <= 5; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Jump/Left/Airborne_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "JumpLeft", "JumpLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("JumpLeft",
            6, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 0; i <= 5; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 5; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Jump/Right/Airborne_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "JumpRight", "JumpRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("JumpRight",
            6, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 5; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
    // Dash
    {
        std::vector<const TCHAR*>   vecFileName;
        for (int i = 0; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Dash/Left/Dash_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "DashLeft", "DashLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("DashLeft",
            5, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 0; i <= 4; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 4; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Dash/Right/Dash_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "DashRight", "DashRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("DashRight",
            5, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 4; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
    //// Wounded
    //CResourceManager::GetInst()->CreateAnimationSequence2D("WoundedLeft", "WoundedLeft", TEXT("WoundedLeft.png"));

    //for (int i = 0; i < 5; ++i)
    //{
    //    CResourceManager::GetInst()->AddAnimationSequence2DFrame("WoundedLeft",
    //        Vector2(i * 132.2f, 0.f), Vector2((i + 1) * 132.2f, 121.f));
    //}

    //CResourceManager::GetInst()->CreateAnimationSequence2D("WoundedRight", "WoundedRight", TEXT("WoundedRight.png"));

    //for (int i = 0; i < 5; ++i)
    //{
    //    CResourceManager::GetInst()->AddAnimationSequence2DFrame("WoundedRight",
    //        Vector2(i * 132.2f, 0.f), Vector2((i + 1) * 132.2f, 121.f));
    //}

    // Attack
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Slash/Left/NA Big Slash_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "AttackLeft", "AttackLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("AttackLeft",
            8, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 0; i <= 7; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 7; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Slash/Right/NA Big Slash_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "AttackRight", "AttackRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("AttackRight",
            8, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 7; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
    // AttackUp
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 14; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Slash/Up/Left/UpSlash_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "AttackUpLeft", "AttackUpLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("AttackUpLeft",
            15, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 0; i <= 14; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 14; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Slash/Up/Right/UpSlash_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "AttackUpRight", "AttackUpRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("AttackUpRight",
            15, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 14; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
    // AttackDown
    {
        std::vector<const TCHAR*>   vecFileName;
        for (int i = 0; i <= 14; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Slash/Down/Left/DownSlash_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "AttackDownLeft", "AttackDownLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("AttackDownLeft",
            15, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 0; i <= 14; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 14; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Slash/Down/Right/DownSlash_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "AttackDownRight", "AttackDownRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("AttackDownRight",
            15, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 14; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // Double Jump
    {
        std::vector<const TCHAR*>   vecFileName;
        for (int i = 0; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/DoubleJump/Left/Double Jump_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "DoubleJumpLeft", "DoubleJumpLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("DoubleJumpLeft",
            8, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 0; i <= 7; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 7; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/DoubleJump/Right/Double Jump_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "DoubleJumpRight", "DoubleJumpRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("DoubleJumpRight",
            8, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 7; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // Death
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 17; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Death/Left/Death_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "DeathLeft", "DeathLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("DeathLeft",
            18, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 0; i <= 17; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 17; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Death/Right/Death_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "DeathRight", "DeathRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("DeathRight",
            18, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 17; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
    // Focus
    {
        std::vector<const TCHAR*>   vecFileName;
        for (int i = 0; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Focus/Left/Focus_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "FocusLeft", "FocusLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("FocusLeft",
            7, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 0; i <= 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 6; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Focus/Right/Focus_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "FocusRight", "FocusRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("FocusRight",
            7, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 6; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // Fall
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 5; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Fall/Left/Airborne_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "FallLeft", "FallLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("FallLeft",
            6, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 0; i <= 5; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 5; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Player/Fall/Right/Airborne_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "FallRight", "FallRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("FallRight",
            6, Vector2(0.f, 0.f), Vector2(349.f, 186.f));

        for (int i = 5; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    //============================================= Monster ===========================================================//


    // Idle
    CResourceManager::GetInst()->CreateAnimationSequence2D("MonsterIdleLeft", "MonsterIdleLeft", TEXT("Monster/IdleLeft.png"));

    for (int i = 0; i < 6; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("MonsterIdleLeft",
            Vector2(i * 121.f, 0.f), Vector2((i + 1) * 121.f, 198.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("MonsterIdleRight", "MonsterIdleRight", TEXT("Monster/IdleRight.png"));

    for (int i = 0; i < 6; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("MonsterIdleRight",
            Vector2(i * 121.f, 0.f), Vector2((i + 1) * 121.f, 198.f));
    }

    // Left, Right
    CResourceManager::GetInst()->CreateAnimationSequence2D("MonsterLeft", "MonsterLeft", TEXT("Monster/Left.png"));

    for (int i = 0; i < 7; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("MonsterLeft",
            Vector2(i * 141.857f, 0.f), Vector2((i + 1) * 141.857f, 190.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("MonsterRight", "MonsterRight", TEXT("Monster/Right.png"));

    for (int i = 0; i < 7; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("MonsterRight",
            Vector2(i * 141.857f, 0.f), Vector2((i + 1) * 141.857f, 190.f));
    }

    // Attack
    CResourceManager::GetInst()->CreateAnimationSequence2D("MonsterAttackLeft", "MonsterAttackLeft", TEXT("Monster/AttackLeft.png"));

    for (int i = 0; i < 5; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("MonsterAttackLeft",
            Vector2(i * 174.f, 0.f), Vector2((i + 1) * 174.f, 190.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("MonsterAttackRight", "MonsterAttackRight", TEXT("Monster/AttackRight.png"));

    for (int i = 0; i < 5; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("MonsterAttackRight",
            Vector2(i * 174.f, 0.f), Vector2((i + 1) * 174.f, 190.f));
    }

    // Dash
    CResourceManager::GetInst()->CreateAnimationSequence2D("MonsterDashLeft", "MonsterDashLeft", TEXT("Monster/DashLeft.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("MonsterDashLeft",
            Vector2(i * 185.25f, 0.f), Vector2((i + 1) * 185.25f, 119.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("MonsterDashRight", "MonsterDashRight", TEXT("Monster/DashRight.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("MonsterDashRight",
            Vector2(i * 185.25f, 0.f), Vector2((i + 1) * 185.25f, 119.f));
    }

    // Land
    CResourceManager::GetInst()->CreateAnimationSequence2D("MonsterLandLeft", "MonsterLandLeft", TEXT("Monster/LandLeft.png"));

    for (int i = 0; i < 5; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("MonsterLandLeft",
            Vector2(i * 192.8f, 0.f), Vector2((i + 1) * 192.8f, 127.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("MonsterLandRight", "MonsterLandRight", TEXT("Monster/LandRight.png"));

    for (int i = 0; i < 5; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("MonsterLandRight",
            Vector2(i * 192.8f, 0.f), Vector2((i + 1) * 192.8f, 127.f));
    }

    //============================================= Effect ===========================================================//

    CResourceManager::GetInst()->CreateAnimationSequence2D("SlashLeft", "SlashLeft", TEXT("SlashLeft.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("SlashLeft",
            Vector2(i * 157.f, 0.f), Vector2((i + 1) * 157.f, 114.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("SlashRight", "SlashRight", TEXT("SlashRight.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("SlashRight",
            Vector2(i * 157.f, 0.f), Vector2((i + 1) * 157.f, 114.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("SwordLeft", "SwordLeft", TEXT("Effect/Sword/SwordEffect.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("SwordLeft",
            Vector2(i * 219.f, 0.f), Vector2((i + 1) * 219.f, 106.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("SwordRight", "SwordRight", TEXT("Effect/Sword/SwordEffectRight.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("SwordRight",
            Vector2(i * 219.f, 0.f), Vector2((i + 1) * 219.f, 106.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("AttackDownLeftEffect", "AttackDownLeftEffect", TEXT("AttackDownLeftEffect.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AttackDownLeftEffect",
            Vector2(i * 183.f, 0.f), Vector2((i + 1) * 183.f, 210.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("AttackDownRightEffect", "AttackDownRightEffect", TEXT("AttackDownRightEffect.png"));

    for (int i = 3; i >= 0; --i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AttackDownRightEffect",
            Vector2(i * 183.f, 0.f), Vector2((i + 1) * 183.f, 210.f));
    }


    CResourceManager::GetInst()->CreateAnimationSequence2D("AttackUpLeftEffect", "AttackUpLeftEffect", TEXT("AttackUpLeftEffect.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AttackUpLeftEffect",
            Vector2(i * 170.f, 0.f), Vector2((i + 1) * 170.f, 189.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("AttackUpRightEffect", "AttackUpRightEffect", TEXT("AttackUpRightEffect.png"));

    for (int i = 3; i >= 0; --i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AttackUpRightEffect",
            Vector2(i * 170.f, 0.f), Vector2((i + 1) * 170.f, 189.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("DashLeftEffect", "DashLeftEffect", TEXT("DashLeftEffect.png"));

    for (int i = 0; i < 6; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("DashLeftEffect",
            Vector2(i * 424.f, 0.f), Vector2((i + 1) * 424.f, 236.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("DashRightEffect", "DashRightEffect", TEXT("DashRightEffect.png"));

    for (int i = 0; i < 6; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("DashRightEffect",
            Vector2(i * 424.f, 0.f), Vector2((i + 1) * 424.f, 236.f));
    }

    // Focus Effect
    CResourceManager::GetInst()->CreateAnimationSequence2D("FocusEffect", "FocusEffect", TEXT("FocusEffect.png"));

    for (int i = 0; i < 13; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("FocusEffect",
            Vector2(i * 91.f, 0.f), Vector2((i + 1) * 91.f, 182.f));
    }

    // Light
    CResourceManager::GetInst()->CreateAnimationSequence2D("Light", "Light", TEXT("Grimm/Light.png"));

    for (int i = 0; i < 2; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("Light",
            Vector2(i * 2048.f, 0.f), Vector2((i + 1) * 2048.f, 1228.f));
    }

    // GrimmChildInEffect
    CResourceManager::GetInst()->CreateAnimationSequence2D("GrimmChildInEffect", "GrimmChildInEffect", TEXT("Grimm/GrimmChildInEffect.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GrimmChildInEffect",
            Vector2(i * 283.5f, 0.f), Vector2((i + 1) * 283.5f, 189.f));
    }

    // FireBalls
    CResourceManager::GetInst()->CreateAnimationSequence2D("FireBalls", "FireBalls", TEXT("Grimm/FireBalls.png"));

    for (int i = 0; i < 8; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("FireBalls",
            Vector2(i * 94.5f, 0.f), Vector2((i + 1) * 94.5f, 95.f));
    }



    //============================================ HP=====================================================//
    CResourceManager::GetInst()->CreateAnimationSequence2D("HPFull", "HPFull", TEXT("HP.png"));

    for (int i = 0; i < 7; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("HPFull",
            Vector2(i * 57.f, 0.f), Vector2((i + 1) * 57.f, 70.f));
    }



    //======================================== Bat ==================================================//
    CResourceManager::GetInst()->CreateAnimationSequence2D("GrimmFireRight", "GrimmFireRight", TEXT("Grimm/GrimmFireRight.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GrimmFireRight",
            Vector2(i * 258.f, 0.f), Vector2((i + 1) * 258.f, 226.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("GrimmFireLeft", "GrimmFireLeft", TEXT("Grimm/GrimmFireLeft.png"));

    for (int i = 3; i >= 0; --i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GrimmFireLeft",
            Vector2(i * 258.f, 0.f), Vector2((i + 1) * 258.f, 226.f));
    }

    //======================================== Grimm ==================================================//

    // Start
    CResourceManager::GetInst()->CreateAnimationSequence2D("Start", "Start", TEXT("Grimm/Start.png"));

    for (int i = 0; i < 5; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("Start",
            Vector2(i * 238.2f, 0.f), Vector2((i + 1) * 238.2f, 430.f));
    }

    // WingsOn
    CResourceManager::GetInst()->CreateAnimationSequence2D("WingsOn", "WingsOn", TEXT("Grimm/Wings.png"));

    for (int i = 0; i < 9; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("WingsOn",
            Vector2(i * 418.8f, 0.f), Vector2((i + 1) * 418.8f, 621.f));
    }

    // Grimm2
    CResourceManager::GetInst()->CreateAnimationSequence2D("Grimm2", "Grimm2", TEXT("Grimm/Grimm2.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("Grimm2",
            Vector2(i * 419.5f, 0.f), Vector2((i + 1) * 419.5f, 568.f));
    }

    // Grimm3
    CResourceManager::GetInst()->CreateAnimationSequence2D("Grimm3", "Grimm3", TEXT("Grimm/Grimm3.png"));

    for (int i = 0; i < 3; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("Grimm3",
            Vector2(i * 417.f, 0.f), Vector2((i + 1) * 417.f, 568.f));
    }

    // BeforeRoar
    CResourceManager::GetInst()->CreateAnimationSequence2D("BeforeRoar", "BeforeRoarRoar", TEXT("Grimm/BeforeRoar.png"));

    for (int i = 0; i < 6; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BeforeRoar",
            Vector2(i * 281.5f, 0.f), Vector2((i + 1) * 281.5f, 441.f));
    }

    // Roar
    CResourceManager::GetInst()->CreateAnimationSequence2D("Roar", "Roar", TEXT("Grimm/Roar.png"));

    for (int i = 0; i < 3; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("Roar",
            Vector2(i * 385.f, 0.f), Vector2((i + 1) * 385.f, 329.f));
    }




    // Fight

    // Curtain
    CResourceManager::GetInst()->CreateAnimationSequence2D("CurtainLeft", "CurtainLeft", TEXT("Grimm/CurtainLeft.png"));

    for (int i = 0; i < 7; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("CurtainLeft",
            Vector2(i * 513.f, 0.f), Vector2((i + 1) * 513.f, 461.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("CurtainRight", "CurtainRight", TEXT("Grimm/CurtainRight.png"));

    for (int i = 6; i >= 0; --i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("CurtainRight",
            Vector2(i * 513.f, 0.f), Vector2((i + 1) * 513.f, 461.f));
    }

    // Dash
    CResourceManager::GetInst()->CreateAnimationSequence2D("GrimmDashLeft", "GrimmDashLeft", TEXT("Grimm/DashLeft.png"));

    for (int i = 0; i < 8; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GrimmDashLeft",
            Vector2(i * 743.625f, 0.f), Vector2((i + 1) * 743.625f, 354.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("GrimmDashRight", "GrimmDashRight", TEXT("Grimm/DashRight.png"));

    for (int i = 7; i >= 0; --i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GrimmDashRight",
            Vector2(i * 743.625f, 0.f), Vector2((i + 1) * 743.625f, 354.f));
    }

    // Spike
    CResourceManager::GetInst()->CreateAnimationSequence2D("GrimmSpikeLeft", "GrimmSpikeLeft", TEXT("Grimm/GrimmSpikeLeft.png"));

    for (int i = 0; i < 10; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GrimmSpikeLeft",
            Vector2(i * 343.f, 0.f), Vector2((i + 1) * 343.f, 414.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("GrimmSpikeRight", "GrimmSpikeRight", TEXT("Grimm/GrimmSpikeRight.png"));

    for (int i = 9; i >= 0; --i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GrimmSpikeRight",
            Vector2(i * 343.f, 0.f), Vector2((i + 1) * 343.f, 414.f));
    }

    // Attack
    CResourceManager::GetInst()->CreateAnimationSequence2D("AttackEndLeft", "AttackEndLeft", TEXT("Grimm/AttackEndLeft.png"));

    for (int i = 0; i < 5; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AttackEndLeft",
            Vector2(i * 238.2f, 0.f), Vector2((i + 1) * 238.2f, 430.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("AttackEndRight", "AttackEndRight", TEXT("Grimm/AttackEndRight.png"));

    for (int i = 4; i >= 0; --i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AttackEndRight",
            Vector2(i * 238.2f, 0.f), Vector2((i + 1) * 238.2f, 414.f));
    }

    // HitDown
    CResourceManager::GetInst()->CreateAnimationSequence2D("HitDownLeft", "HitDownLeft", TEXT("Grimm/HitDownLeft.png"));

    for (int i = 0; i < 5; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("HitDownLeft",
            Vector2(i * 283.44f, 0.f), Vector2((i + 1) * 283.44f, 446.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("HitDownRight", "HitDownRight", TEXT("Grimm/HitDownRight.png"));

    for (int i = 4; i >= 0; --i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("HitDownRight",
            Vector2(i * 283.44f, 0.f), Vector2((i + 1) * 283.44f, 446.f));
    }


    // Idle
    CResourceManager::GetInst()->CreateAnimationSequence2D("GrimmIdleLeft", "GrimmIdleLeft", TEXT("Grimm/GrimmIdleLeft.png"));

    for (int i = 0; i < 12; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GrimmIdleLeft",
            Vector2(i * 204.2f, 0.f), Vector2((i + 1) * 204.2, 417.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("GrimmIdleRight", "GrimmIdleRight", TEXT("Grimm/GrimmIdleRight.png"));

    for (int i = 0; i < 12; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GrimmIdleRight",
            Vector2(i * 202.3f, 0.f), Vector2((i + 1) * 202.3f, 410.f));
    }

    // Teleport
    CResourceManager::GetInst()->CreateAnimationSequence2D("Teleport", "Teleport", TEXT("Grimm/Teleport.png"));

    for (int i = 0; i < 12; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("Teleport",
            Vector2(i * 283.45f, 0.f), Vector2((i + 1) * 283.45f, 922.f));
    }

    // ReverseTeleport
    CResourceManager::GetInst()->CreateAnimationSequence2D("ReverseTeleport", "ReverseTeleport", TEXT("Grimm/ReverseTeleport.png"));

    for (int i = 11; i >= 0; --i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ReverseTeleport",
            Vector2(i * 283.45f, 0.f), Vector2((i + 1) * 283.45f, 922.f));
    }

    // Bomb
    CResourceManager::GetInst()->CreateAnimationSequence2D("GrimmBomb", "GrimmBomb", TEXT("Grimm/GrimmBomb.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GrimmBomb",
            Vector2(i * 401.5f, 0.f), Vector2((i + 1) * 401.5f, 449.f));
    }








    //======================================== GrimmChild ==================================================//

    // Fly
    CResourceManager::GetInst()->CreateAnimationSequence2D("GrimmChildLeft", "GrimmChildLeft", TEXT("GrimmChildLeft.png"));

    for (int i = 0; i < 7; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GrimmChildLeft",
            Vector2(i * 174.f, 0.f), Vector2((i + 1) * 174.f, 158.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("GrimmChildRight", "GrimmChildRight", TEXT("GrimmChildRight.png"));

    for (int i = 5; i >= 0; --i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GrimmChildRight",
            Vector2(i * 174.f, 0.f), Vector2((i + 1) * 174.f, 158.f));
    }


    // BrokenVessel ==================================================================

      // idle
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 7; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Idle/LeftIdle_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossIdleLeft", "BossIdleLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossIdleLeft",
            8, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 7; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 0; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Idle/Idle_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossIdleRight", "BossIdleRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossIdleRight",
            8, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 0; i <= 7; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }


    // walk
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Walk/Walk_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossWalkRight", "BossWalkRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossWalkRight",
            7, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 0; i <= 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 6; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Walk/LeftWalk_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossWalkLeft", "BossWalkLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossWalkLeft",
            7, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 6; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // dash
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Dash/Dash00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossDashRight", "BossDashRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossDashRight",
            3, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 0; i <= 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 2; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Dash/DashLeft00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossDashLeft", "BossDashLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossDashLeft",
            3, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 2; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // dasheffect
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Dash/DashSlash00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossDashRightEffect", "BossDashRightEffect", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossDashRightEffect",
            5, Vector2(0.f, 0.f), Vector2(554.f, 222.f));

        for (int i = 0; i <= 4; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 4; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Dash/DashSlashLeft_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossDashEffectLeft", "BossDashEffectLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossDashEffectLeft",
            5, Vector2(0.f, 0.f), Vector2(554.f, 222.f));

        for (int i = 4; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // Jump
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 7; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Jump/LeftJump_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossJumpLeft", "BossJumpLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossJumpLeft",
            8, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 7; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 0; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Jump/Jump_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossJumpRight", "BossJumpRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossJumpRight",
            8, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 0; i <= 7; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }


    // Fall
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Fall/Fall_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossFallRight", "BossFallRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossFallRight",
            5, Vector2(0.f, 0.f), Vector2(554.f, 222.f));

        for (int i = 0; i <= 4; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 4; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Fall/LeftFall_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossFallLeft", "BossFallLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossFallLeft",
            5, Vector2(0.f, 0.f), Vector2(554.f, 222.f));

        for (int i = 4; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }



    // OverHeadAttack
    CResourceManager::GetInst()->CreateAnimationSequence2D("BossOverHeadAttackLeft", "BossOverHeadAttackLeft", TEXT("Broken/OverHeadAttackLeft.png"));

    for (int i = 9; i >= 0; --i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossOverHeadAttackLeft",
            Vector2(i * 1001.4, 0.f), Vector2((i + 1) * 1001.4, 480.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("BossOverHeadAttackRight", "BossOverHeadAttackRight", TEXT("Broken/OverHeadAttack.png"));

    for (int i = 0; i < 10; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossOverHeadAttackRight",
            Vector2(i * 1001.4, 0.f), Vector2((i + 1) * 1001.4, 480.f));
    }

    // HeadBanging
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Roar/Roar Start_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossRoarRight", "BossRoarRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossRoarRight",
            3, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 0; i <= 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 2; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Roar/LeftRoar Start_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossRoarLeft", "BossRoarLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossRoarLeft",
            3, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 2; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }



    // StartAnimation
    CResourceManager::GetInst()->CreateAnimationSequence2D("BossStartAnimation", "BossStartAnimation", TEXT("Broken/StartAnimation.png"));

    for (int i = 8; i >= 0; --i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStartAnimation",
            Vector2(i * 181.111f, 0.f), Vector2((i + 1) * 181.111f, 136.f));
    }


    // Stun

    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Stun/Stun_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossStunRight", "BossStunRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossStunRight",
            4, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 0; i <= 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 3; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Stun/LeftStun_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossStunLeft", "BossStunLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossStunLeft",
            4, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 3; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }



    // StartRoar
    CResourceManager::GetInst()->CreateAnimationSequence2D("BossStartRoar", "BossStartRoar", TEXT("Broken/StartRoar.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStartRoar",
            Vector2(i * 253.5, 0.f), Vector2((i + 1) * 253.5, 222.f));
    }

    // EndRoar
    CResourceManager::GetInst()->CreateAnimationSequence2D("BossEndRoarLeft", "BossEndRoarLeft", TEXT("Broken/RoarLeft.png"));

    for (int i = 1; i >= 0; --i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossEndRoarLeft",
            Vector2(i * 253.5, 0.f), Vector2((i + 1) * 253.5, 222.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("BossEndRoarRight", "BossEndRoarRight", TEXT("Broken/Roar.png"));

    for (int i = 0; i < 2; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossEndRoarRight",
            Vector2(i * 253.5, 0.f), Vector2((i + 1) * 253.5, 222.f));
    }

    // Death

    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 53; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Death/Death 2_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossDeathRight", "BossDeathRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossDeathRight",
            54, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 0; i <= 53; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 0; i <= 53; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Death/Death 2_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossDeathLeft", "BossDeathLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossDeathLeft",
            4, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 0; i <= 53; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    

    // start
    CResourceManager::GetInst()->CreateAnimationSequence2D("BossSleep", "BossSleep", TEXT("Broken/Start.png"));

    for (int i = 0; i < 2; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossSleep",
            Vector2(i * 200.f, 0.f), Vector2((i + 1) * 200.f, 135.f));
    }


    // DownStab

    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 5; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/DownStab/Downstab Antic_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossDownStabRight", "BossDownStabRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossDownStabRight",
            6, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 0; i <= 5; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 5; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/DownStab/LeftDownstab Antic_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossDownStabLeft", "BossDownStabLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossDownStabLeft",
            6, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 5; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // DownStabLand

    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/DownStab/Downstab Land_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossDownStabLandRight", "BossDownStabLandRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossDownStabLandRight",
            7, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 0; i <= 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 6; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/DownStab/LeftDownstab Land_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossDownStabLandLeft", "BossDownStabLandLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossDownStabLandLeft",
            7, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 6; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }


    // overattackeffect

    CResourceManager::GetInst()->CreateAnimationSequence2D("OverAttackEffect", "OverAttackEffect", TEXT("Broken/OverSlash.png"));

    for (int i = 0; i < 6; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("OverAttackEffect",
            Vector2(i * 471.666f, 0.f), Vector2((i + 1) * 471.666f, 286.f));
    }

    // DownStabEffect
    CResourceManager::GetInst()->CreateAnimationSequence2D("DownStabEffect", "DownStabEffect", TEXT("Broken/Orange.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("DownStabEffect",
            Vector2(i * 168.f, 0.f), Vector2((i + 1) * 168.f, 170.f));
    }

    // downstablandeffect
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/DownStab/Downstab Slam_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossDownStabLandEffect", "BossDownStabLandEffect", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossDownStabLandEffect",
            5, Vector2(0.f, 0.f), Vector2(524.f, 325.f));

        for (int i = 0; i <= 4; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();
    }

    // Vengefly ===================================================================================



    // idle
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Vengefly/Idle/Idle_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "VengeflyIdleLeft", "VengeflyIdleLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("VengeflyIdleLeft",
            5, Vector2(0.f, 0.f), Vector2(188.f, 177.f));

        for (int i = 0; i <= 4; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 4; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Vengefly/Idle/RightIdle_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "VengeflyIdleRight", "VengeflyIdleRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("VengeflyIdleRight",
            5, Vector2(0.f, 0.f), Vector2(188.f, 177.f));

        for (int i = 4; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // Chase
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Vengefly/Chase/Chase_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "VengeflyChaseLeft", "VengeflyChaseLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("VengeflyChaseLeft",
            4, Vector2(0.f, 0.f), Vector2(188.f, 177.f));

        for (int i = 0; i <= 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();


        for (int i = 3; i >= 0; --i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Vengefly/Chase/RightChase_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "VengeflyChaseRight", "VengeflyChaseRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("VengeflyChaseRight",
            4, Vector2(0.f, 0.f), Vector2(188.f, 177.f));

        for (int i = 3; i >= 0; --i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // Startle
    CResourceManager::GetInst()->CreateAnimationSequence2D("VengeflyStartleLeft", "VengeflyStartleLeft", TEXT("Vengefly/MonsterStartleLeft.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("VengeflyStartleLeft",
            Vector2(i * 149.f, 0.f), Vector2((i + 1) * 149.f, 157.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("VengeflyStartleRight", "VengeflyStartleRight", TEXT("Vengefly/MonsterStartleRight.png"));

    for (int i = 0; i < 4; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("VengeflyStartleRight",
            Vector2(i * 149.f, 0.f), Vector2((i + 1) * 149.f, 157.f));
    }

    // Turn
    CResourceManager::GetInst()->CreateAnimationSequence2D("VengeflyTurnLeft", "VengeflyTurnLeft", TEXT("Vengefly/MonsterTurnLeft.png"));

    for (int i = 0; i < 2; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("VengeflyTurnLeft",
            Vector2(i * 120.5f, 0.f), Vector2((i + 1) * 120.5f, 153.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("VengeflyTurnRight", "VengeflyTurnRight", TEXT("Vengefly/MonsterTurnRight.png"));

    for (int i = 0; i < 2; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("VengeflyTurnRight",
            Vector2(i * 120.5f, 0.f), Vector2((i + 1) * 120.5f, 153.f));
    }

    // Death
    CResourceManager::GetInst()->CreateAnimationSequence2D("VengeflyDeathLeft", "VengeflyDeathLeft", TEXT("Vengefly/MonsterDeathLeft.png"));

    for (int i = 0; i < 3; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("VengeflyDeathLeft",
            Vector2(i * 143.666f, 0.f), Vector2((i + 1) * 143.666f, 112.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("VengeflyDeathRight", "VengeflyDeathRight", TEXT("Vengefly/MonsterDeathRight.png"));

    for (int i = 0; i < 3; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("VengeflyDeathRight",
            Vector2(i * 143.666f, 0.f), Vector2((i + 1) * 143.666f, 112.f));
    }


    // swordeffect
    CResourceManager::GetInst()->CreateAnimationSequence2D("SwordEffectRight", "SwordEffectRight", TEXT("Effect/Sword/SwordEffectRight.png"));

    for (int i = 2; i >= 0; --i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("SwordEffectRight",
            Vector2(i * 219.f, 0.f), Vector2((i + 1) * 219.f, 106.f));
    }

    CResourceManager::GetInst()->CreateAnimationSequence2D("SwordEffectLeft", "SwordEffectLeft", TEXT("Effect/Sword/SwordEffect.png"));

    for (int i = 0; i < 3; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("SwordEffectLeft",
            Vector2(i * 219.f, 0.f), Vector2((i + 1) * 219.f, 106.f));
    }


    // 
    {
        std::vector<const TCHAR*>   vecFileName;

        for (int i = 0; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

            wsprintf(FileName, TEXT("Broken/Effect/Death_00%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(
            "BossOrangeEffect", "BossOrangeEffect", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("BossOrangeEffect",
            4, Vector2(0.f, 0.f), Vector2(222.f, 182.f));

        for (int i = 0; i <= 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }

        vecFileName.clear();
    }
    ////////////////////////////

    CResourceManager::GetInst()->LoadSound("Effect", "Attack", false, "hero_damage.mp3", SOUND_PATH);
    CResourceManager::GetInst()->LoadSound("Effect", "Dash", false, "hero_dash.mp3", SOUND_PATH);

}

void CDefaultSetting::SetInput()
{
    // 키 등록

    CInput::GetInst()->AddBindKey("Up", VK_UP);
    CInput::GetInst()->AddBindKey("Down", VK_DOWN);
    CInput::GetInst()->AddBindKey("Left", VK_LEFT);
    CInput::GetInst()->AddBindKey("Right", VK_RIGHT);


    CInput::GetInst()->AddBindKey("Jump", 'Z');
    CInput::GetInst()->AddBindKey("Attack", 'X');
    CInput::GetInst()->AddBindKey("Dash", 'C');
    CInput::GetInst()->AddBindKey("Focus/Cast", 'A'); // 집중, 시전

    CInput::GetInst()->AddBindKey("QuickMap", VK_TAB); // 빠른지도
    CInput::GetInst()->AddBindKey("SuperDash", 'S'); // 슈퍼 대시
    CInput::GetInst()->AddBindKey("DreamNail", 'D'); // 몽환의 대못

    CInput::GetInst()->AddBindKey("QuickCast", 'F'); // 빠른 시전
    CInput::GetInst()->AddBindKey("Inventory", 'I'); // 소지품
}

void CDefaultSetting::SetCollision()
{
    CCollisionManager::GetInst()->CreateChannel("Player", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("PlayerAttack", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("Monster", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("MonsterAttack", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("Wall", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("PlayerEffect", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("Portal", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("MonsterRange", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("GrimmChild", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("GrimmLandPoint", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("Effect", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("Bullet", ECollision_Interaction::Collision);


    CCollisionManager::GetInst()->CreateProfile("Player", "Player", true);
    CCollisionManager::GetInst()->CreateProfile("PlayerAttack", "PlayerAttack", true);
    CCollisionManager::GetInst()->CreateProfile("Monster", "Monster", true);
    CCollisionManager::GetInst()->CreateProfile("MonsterAttack", "MonsterAttack", true);
    CCollisionManager::GetInst()->CreateProfile("Wall", "Wall", true);
    CCollisionManager::GetInst()->CreateProfile("PlayerEffect", "PlayerEffect", true);
    CCollisionManager::GetInst()->CreateProfile("Portal", "Portal", true);
    CCollisionManager::GetInst()->CreateProfile("MonsterRange", "MonsterRange", true);
    CCollisionManager::GetInst()->CreateProfile("GrimmChild", "GrimmChild", true);
    CCollisionManager::GetInst()->CreateProfile("GrimmLandPoint", "GrimmLandPoint", true);
    CCollisionManager::GetInst()->CreateProfile("Effect", "Effect", true);
    CCollisionManager::GetInst()->CreateProfile("Bullet", "Bullet", true);


    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "Player", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "Player", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "PlayerAttack", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "Monster", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "PlayerAttack", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("Wall", "Wall", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerEffect", "PlayerEffect", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("Portal", "Portal", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterRange", "MonsterRange", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("GrimmChild", "GrimmChild", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("GrimmLandPoint", "GrimmLandPoint", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("Effect", "Effect", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("Bullet", "Bullet", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Bullet", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Bullet", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Bullet", "Portal", ECollision_Interaction::Ignore);




}
