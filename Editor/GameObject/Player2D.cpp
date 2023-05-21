
#include "Player2D.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "Component/NavigationAgent.h"
#include "Component/WallComponent.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Device.h"
#include "Bullet.h"
#include "Resource/Material/Material.h"
#include "Animation/Animation2D.h"
#include "Animation/Animation2DData.h" // 1127
#include "Component/GravityComponent.h"
#include "../UI/FirstSceneUI.h"
#include "../Scene/FirstSceneInfo.h"
#include "UI/UIImage.h"
#include "UI/UIWindow.h"
#include "BackObj.h"
#include "SecondBackObj.h"
#include "BossMap.h"
#include "Effect.h"
#include "Component/TileMapComponent.h"
#include "Component/Tile.h"

CPlayer2D::CPlayer2D()	:
	m_Attack(false),
	m_Dash(false),
	m_Fall(false),
	m_Jump(false),
	m_Idle(true),
	m_Move(false),
	m_Up(false),
	m_Down(false),
	m_Hurt(false),
	m_Focus(false)
{
	SetTypeID<CPlayer2D>();

	m_ObjectTypeName = "Player2D";

	m_PlayerAnim = EPlayer_Animation::Idle;
	m_PrevPlayerAnim = EPlayer_Animation::Idle;
}

CPlayer2D::CPlayer2D(const CPlayer2D& Obj) :
	CGameObject(Obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("sprite");
	m_Camera = (CCameraComponent*)FindComponent("Camera");
	m_Arm = (CTargetArm*)FindComponent("Arm");
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_NavAgent = (CNavigationAgent*)FindComponent("NavAgent");
	//m_Gravity = (CGravityComponent*)FindComponent("Gravity");
	m_Wall = (CWallComponent*)FindComponent("Wall");

}

CPlayer2D::~CPlayer2D()
{
}

void CPlayer2D::Start()
{
	CGameObject::Start();

	if (m_Scene)
		m_Scene->GetCameraManager()->SetCurrentCamera(m_Camera);

	m_Wall->SetFallStartY(GetWorldPos().y);

	
	// 키 세팅
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Up", Input_Type::Down,
		this, &CPlayer2D::Up, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Up", Input_Type::Up,
		this, &CPlayer2D::UpKeyUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Down", Input_Type::Down,
		this, &CPlayer2D::Down, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Down", Input_Type::Up,
		this, &CPlayer2D::DownKeyUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Left", Input_Type::Push,
		this, &CPlayer2D::Left, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Right", Input_Type::Push,
		this, &CPlayer2D::Right, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Jump", Input_Type::Down,
		this, &CPlayer2D::Jump, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Attack", Input_Type::Down,
		this, &CPlayer2D::Attack, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Dash", Input_Type::Down,
		this, &CPlayer2D::Dash, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Jump", Input_Type::Up,
		this, &CPlayer2D::JumpKeyUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Attack", Input_Type::Up,
		this, &CPlayer2D::AttackKeyUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Dash", Input_Type::Up,
		this, &CPlayer2D::DashKeyUp, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Focus/Cast", Input_Type::Down,
		this, &CPlayer2D::Focus, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Focus/Cast", Input_Type::Up,
		this, &CPlayer2D::FocusKeyUp, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("QuickMap", Input_Type::Down,
		this, &CPlayer2D::QuickMap, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("SuperDash", Input_Type::Down,
		this, &CPlayer2D::SuperDash, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("DreamNail", Input_Type::Down,
		this, &CPlayer2D::DreamNail, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("QuickCast", Input_Type::Down,
		this, &CPlayer2D::QuickCast, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Inventory", Input_Type::Down,
		this, &CPlayer2D::Inventory, m_Scene);


	// 애니메이션 
	m_Animation = m_Sprite->SetAnimation<CAnimation2D>("Player");


	m_Animation->AddAnimation("IdleLeft", "IdleLeft", 1.f, 1.f, true);
	m_Animation->AddAnimation("IdleRight", "IdleRight", 1.f, 1.f, true);

	m_Animation->AddAnimation("UpLeft", "UpLeft", 1.f, 1.f);
	m_Animation->AddAnimation("UpRight", "UpRight", 1.f, 1.f);

	m_Animation->AddAnimation("DownLeft", "DownLeft", 1.f, 1.f);
	m_Animation->AddAnimation("DownRight", "DownRight", 1.f, 1.f);

	m_Animation->AddAnimation("Left", "Left", 1.f, 1.f, true);
	m_Animation->AddAnimation("Right", "Right", 1.f, 1.f, true);
	m_Animation->AddAnimation("JumpLeft", "JumpLeft", 1.f, 1.f, true);
	m_Animation->AddAnimation("JumpRight", "JumpRight", 1.f, 1.f, true);
	m_Animation->AddAnimation("AttackLeft", "AttackLeft", 1.f, 1.7f, true);
	m_Animation->AddAnimation("AttackRight", "AttackRight", 1.f, 1.7f, true);
	m_Animation->AddAnimation("DashLeft", "DashLeft", 1.f, 1.5f, true);
	m_Animation->AddAnimation("DashRight", "DashRight", 1.f, 1.5f, true);


	m_Animation->AddAnimation("DoubleJumpLeft", "DoubleJumpLeft", 1.f, 1.f, true);
	m_Animation->AddAnimation("DoubleJumpRight", "DoubleJumpRight", 1.f, 1.f, true);
	m_Animation->AddAnimation("AttackUpLeft", "AttackUpLeft", 1.f, 1.7f);
	m_Animation->AddAnimation("AttackUpRight", "AttackUpRight", 1.f, 1.7f);
	m_Animation->AddAnimation("AttackDownLeft", "AttackDownLeft", 1.f, 1.7f, true);
	m_Animation->AddAnimation("AttackDownRight", "AttackDownRight", 1.f, 1.7f, true);
	m_Animation->AddAnimation("DeathLeft", "DeathLeft", 1.f, 1.f, true);
	m_Animation->AddAnimation("DeathRight", "DeathRight", 1.f, 1.f, true);;
	m_Animation->AddAnimation("FocusLeft", "FocusLeft", 1.f, 1.f, true);
	m_Animation->AddAnimation("FocusRight", "FocusRight", 1.f, 1.f, true);
	m_Animation->AddAnimation("FallLeft", "FallLeft", 1.f, 1.f, true);
	m_Animation->AddAnimation("FallRight", "FallRight", 1.f, 1.f, true);





	m_vecSequenceKey[0].push_back("IdleLeft");
	m_vecSequenceKey[0].push_back("UpLeft");
	m_vecSequenceKey[0].push_back("DownLeft");
	m_vecSequenceKey[0].push_back("Left");
	m_vecSequenceKey[0].push_back("JumpLeft");
	m_vecSequenceKey[0].push_back("AttackLeft");
	m_vecSequenceKey[0].push_back("DashLeft");
	//m_vecSequenceKey[0].push_back("WoundedLeft");
	m_vecSequenceKey[0].push_back("DoubleJumpLeft");
	m_vecSequenceKey[0].push_back("AttackUpLeft");
	m_vecSequenceKey[0].push_back("AttackDownLeft");
	m_vecSequenceKey[0].push_back("DeathLeft");
	m_vecSequenceKey[0].push_back("FocusLeft");
	m_vecSequenceKey[0].push_back("FallLeft");

	m_vecSequenceKey[1].push_back("IdleRight");
	m_vecSequenceKey[1].push_back("UpRight");
	m_vecSequenceKey[1].push_back("DownRight");
	m_vecSequenceKey[1].push_back("Right");
	m_vecSequenceKey[1].push_back("JumpRight");
	m_vecSequenceKey[1].push_back("AttackRight");
	m_vecSequenceKey[1].push_back("DashRight");
	//m_vecSequenceKey[1].push_back("WoundedRight");
	m_vecSequenceKey[1].push_back("DoubleJumpRight");
	m_vecSequenceKey[1].push_back("AttackUpRight");
	m_vecSequenceKey[1].push_back("AttackDownRight");
	m_vecSequenceKey[1].push_back("DeathRight");
	m_vecSequenceKey[1].push_back("FocusRight");
	m_vecSequenceKey[1].push_back("FallRight");


	m_Body->SetCollisionCallback<CPlayer2D>(ECollision_Result::Collision, this, &CPlayer2D::CollisionBegin);
	m_Body->SetCollisionCallback<CPlayer2D>(ECollision_Result::Release, this, &CPlayer2D::CollisionEnd);

	m_PlayerUI = m_Scene->GetViewport()->CreateUIWindow<CFirstSceneUI>("PlayerUI");
}

bool CPlayer2D::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("sprite");
	m_Camera = CreateComponent<CCameraComponent>("Camera");
	m_Arm = CreateComponent<CTargetArm>("Arm");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_NavAgent = CreateComponent<CNavigationAgent>("NavAgent");
	//m_Gravity = CreateComponent<CGravityComponent>("Gravity");
	m_Wall = CreateComponent<CWallComponent>("Wall");


	SetRootComponent(m_Body);

	m_Body->SetCollisionProfile("Player");
	m_Body->AddChild(m_Sprite);
	m_Body->SetPivot(0.5f, 1.f);
	m_Body->SetBoxSize(40.f, 80.f);

	m_Sprite->AddChild(m_Arm);
	m_Arm->AddChild(m_Camera);

	Resolution RS = CDevice::GetInst()->GetResolution();

	float Width = (float)RS.Width / 2.f;
	float Height = (float)RS.Height / 4.f;

	m_Arm->SetTargetOffset(Vector3(-Width, -Height, 0.f));

	m_Body->SetWorldPosition(300.f, 600.f);
	//m_Body->SetPivot(0.5f, 0);

	// Player 세팅
	m_Sprite->SetRelativeScale(224.f, 120.f);
	m_Sprite->SetPivot(0.5f, 0.35f);
	
	// HP
	m_HP = 5;

	// 왼쪽이 1
	m_PlayerDir = -1;

	return true;
}

void CPlayer2D::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_BackObj = (CBackObj*)m_Scene->FindObject("BackObj");
	m_SecondBackObj = (CSecondBackObj*)m_Scene->FindObject("SecondBackObj");
	m_BossMapBackObj = (CBossMap*)m_Scene->FindObject("BossMap");

	if (m_BackObj)
	{
		m_WallObjSize = m_BackObj->GetWorldScale().x;
	}

	if (m_SecondBackObj)
	{
		m_WallObjSize = m_SecondBackObj->GetWorldScale().x;
	}

	if (m_BossMapBackObj)
	{
		m_WallObjSize = m_BossMapBackObj->GetWorldScale().x;
	}

	m_PrevPlayerAnim = m_PlayerAnim;

	// 걷기 끝나면 다시 Idle
	if (m_PlayerAnim == EPlayer_Animation::Move)
	{
		m_PlayerAnim = EPlayer_Animation::Idle;
	}

	if (m_Camera->GetWorldPos().x <= 0.f)
		m_Camera->SetWorldPositionX(0.f);

	if ((m_Camera->GetWorldPos().x + 1280.f) >= m_WallObjSize)
		m_Camera->SetWorldPositionX(m_WallObjSize - 1280.f);

}

void CPlayer2D::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	int	AnimDirectionIndex = 0;

	if (m_PlayerDir == -1)
		AnimDirectionIndex = 1;

	switch (m_PlayerAnim)
	{
		case EPlayer_Animation::Idle:
			m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][0]);
			break;

		case EPlayer_Animation::Up:
			m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][1]);
			break;
			
		case EPlayer_Animation::Down:
			m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][2]);
			break;

		case EPlayer_Animation::Move:
			m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][3]);
			break;

		case EPlayer_Animation::Jump:
			m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][4]);
			break;

		case EPlayer_Animation::Attack:
			m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][5]);
			break;

		case EPlayer_Animation::Dash:
			m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][6]);
			break;

		case EPlayer_Animation::Hurt:
			//m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][7]);
			break;

		case EPlayer_Animation::DoubleJump:
			m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][7]);
			break;

		case EPlayer_Animation::AttackUp:
			m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][8]);
			break;

		case EPlayer_Animation::AttackDown:
			m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][9]);
			break;

		case EPlayer_Animation::Death:
			m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][10]);
			break;

		case EPlayer_Animation::Focus:
			m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][11]);
			break;

		case EPlayer_Animation::Fall :
			m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][12]);
			break;
	}

	m_PrevPlayerAnim = m_PlayerAnim;

	//if (m_Wall->GetGround() == true && !m_Dash && !m_Move && !m_Attack && !m_Hurt && !m_Jump)
	//{
	//	m_PlayerAnim = EPlayer_Animation::Idle;
	//}

	/*if (m_Wall->GetGround() == true && !m_Dash && !m_Attack && !m_Hurt && !m_Jump && !m_Fall)
	{
		m_PlayerAnim = EPlayer_Animation::Move;
	}*/
	
	//if (!m_Dash && !m_Jump && m_Body->GetWorldPos().y != 0.f && !m_Attack && !m_Hurt &&
	//	m_PlayerAnim != EPlayer_Animation::Idle)
	//{
	//	m_Fall = true;

	//	Fall();

	//	//if (m_Move)
	//	//{
	//	//	m_PlayerAnim = EPlayer_Animation::Move;
	//	//	//if (m_Wall->GetGround() == true)
	//	//		//m_PlayerAnim = EPlayer_Animation::Move;
	//	//}

	//	if (m_Body->GetWorldPos().y == 0.f)
	//		m_PlayerAnim = EPlayer_Animation::Idle;

	//	if (m_Effect)
	//	{
	//		if (!m_Dash && !m_Attack)
	//		{
	//			m_Effect->Destroy();
	//		}
	//	}
	//}

	//else
	//	m_Fall = false;


	//if (m_Fall)
	//{
	//	if(m_Move)
	//		m_PlayerAnim = EPlayer_Animation::Fall;
	//}
}

float CPlayer2D::InflictDamage(float Damage)
{
	Damage = CGameObject::InflictDamage(Damage);

	m_HP -= (int)Damage;

	if (m_HP <= 0)
	{
		Destroy();
	}

	return Damage;
}

CPlayer2D* CPlayer2D::Clone() const
{
	return new CPlayer2D(*this);
}

void CPlayer2D::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CPlayer2D::Load(FILE* File)
{
	CGameObject::Load(File);
}

void CPlayer2D::CollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "Monster")
	{
		//Hurt();
		//m_Arm->AddRelativePositionX(30.f);

		/*for (int i = 0; i < 8; ++i)
		{
			if (i % 2 == 0)
				m_Camera->AddRelativePositionX(30.f * g_DeltaTime);

			else 
				m_Camera->AddRelativePositionX(-30.f * g_DeltaTime);
		}*/
			

	/*	CFirstSceneInfo* Window = m_Scene->GetViewport()->FindUIWindow<CFirstSceneInfo>("UIWindow");

		CUIWidget* HP = Window->FindWidget<CFirstSceneUI>("HP");*/

		//m_Hurt = true;

		//InflictDamage(20);

		--m_HP;
		m_PlayerUI->SetHP(m_HP);
	}
}

void CPlayer2D::CollisionEnd(const CollisionResult& result)
{
	m_Hurt = false;
}

void CPlayer2D::Up()
{
	m_Up = true;

	m_PlayerAnim = EPlayer_Animation::Up;

	m_Arm->AddRelativePositionY(1.f);

	if (m_Attack)
	{
		Attack();
	}
}

void CPlayer2D::UpKeyUp()
{
	m_Up = false;

	m_PlayerAnim = EPlayer_Animation::Idle;

}

void CPlayer2D::Down()
{
	m_Down = true;

	m_PlayerAnim = EPlayer_Animation::Down;

	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_Y) * -300.f * g_DeltaTime);

	m_Arm->AddRelativePositionY(-1.f);

	if (m_Arm->GetRelativePos().y == -10.f)
		m_Arm->AddRelativePositionY(1.f);

	if (m_Attack)
	{
		Attack();
	}
}

void CPlayer2D::DownKeyUp()
{
	m_Down = false;
	m_PlayerAnim = EPlayer_Animation::Idle;
	//m_Effect->Destroy();
}

void CPlayer2D::Left()
{
	m_PlayerDir = 1;

	m_Move = true;

	m_PlayerAnim = EPlayer_Animation::Move;

	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * -300.f * g_DeltaTime);

	if (m_Dash)
	{
		m_PlayerAnim = EPlayer_Animation::Dash;

		//m_Effect->GetAnimation()->ChangeAnimation("DashLeftEffect");

		//m_Effect->SetWorldPosition(GetWorldPos() + Vector3(50.f, 0.f, 0.f));

		m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * -800.f * g_DeltaTime);
	}

	else if (m_Jump)
	{
		m_PlayerAnim = EPlayer_Animation::Jump;

		if (m_Wall->GetMiniJumpOn() == true)
			m_PlayerAnim = EPlayer_Animation::DoubleJump;
	}

	else if (m_Fall)
	{
		m_PlayerAnim = EPlayer_Animation::Fall;

		if (m_Body->GetWorldPos().y == 0.f)
			m_Fall = false;
			m_PlayerAnim = EPlayer_Animation::Move;
	}

	else if (m_Attack)
	{
		m_PlayerAnim = EPlayer_Animation::Attack;

		//m_Effect->GetAnimation()->ChangeAnimation("SlashLeft");

		//m_Effect->SetWorldPosition(GetWorldPos() + Vector3(-30.f, -10.f, 0.f));
	}

	//else
	//{
	//	m_PlayerAnim = EPlayer_Animation::Move;

	//	m_Fall = false;
	//}


	/*if (!m_Dash)
	{
		
		if (m_Jump)
		{
			m_PlayerAnim = EPlayer_Animation::Jump;
		
			if (m_Wall->GetMiniJumpOn() == true)
				m_PlayerAnim = EPlayer_Animation::DoubleJump;
		}

		if (m_Fall) 
		{d
			m_PlayerAnim = EPlayer_Animation::Fall;
		}

		else if (m_Attack)
		{
			m_PlayerAnim = EPlayer_Animation::Attack;
		}

		m_PlayerAnim = EPlayer_Animation::Move;


		m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * -300.f * g_DeltaTime);
	}

	if(m_Dash)
		m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * -900.f * g_DeltaTime);*/
}

void CPlayer2D::LeftKeyUp()
{
	m_Move = false;
}

void CPlayer2D::Right()
{
	m_PlayerDir = -1;

	m_Move = true;


	m_PlayerAnim = EPlayer_Animation::Move;
	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * 300.f * g_DeltaTime);

	if (m_Dash)
	{
		m_PlayerAnim = EPlayer_Animation::Dash;

		//m_Effect->GetAnimation()->ChangeAnimation("DashLeftEffect");

		//m_Effect->SetWorldPosition(GetWorldPos() + Vector3(50.f, 0.f, 0.f));

		m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * 800.f * g_DeltaTime);
	}

	else if (m_Jump)
	{
		m_PlayerAnim = EPlayer_Animation::Jump;

		if (m_Wall->GetMiniJumpOn() == true)
			m_PlayerAnim = EPlayer_Animation::DoubleJump;
	}

	else if (m_Fall)
	{
		m_PlayerAnim = EPlayer_Animation::Fall;

		if (m_Body->GetWorldPos().y == 0.f)
			m_Fall = false;
		m_PlayerAnim = EPlayer_Animation::Move;
	}

	else if (m_Attack)
	{
		m_PlayerAnim = EPlayer_Animation::Attack;
	}
	

	//if (m_Dash)
	//	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * 900.f * g_DeltaTime);


}

void CPlayer2D::RightKeyUp()
{
	m_Move = false;
}

void CPlayer2D::Jump() // Z
{
	m_Jump = true;

	m_Wall->Jump();
	
	if (m_Wall->GetMiniJumpOn() == true)
	{
		m_PlayerAnim = EPlayer_Animation::DoubleJump;
	}

	else
		m_PlayerAnim = EPlayer_Animation::Jump;
	
}

void CPlayer2D::JumpKeyUp()
{
	m_Jump = false;

	m_Wall->SetMiniJumpOn(false);

	//m_PlayerAnim = EPlayer_Animation::Fall;

	Fall();

	//m_Gravity->FallingStartOn(m_Pos.y); // 강제추락. 낙사사고.
}

void CPlayer2D::Fall()
{
	m_Fall = true;
	
	m_PlayerAnim = EPlayer_Animation::Fall;
	
}

void CPlayer2D::Attack() // X
{
	m_Attack = true;

	m_Effect = m_Scene->CreateObject<CEffect>("Effect");

	m_Effect->SetCollisionProfileName("PlayerAttack");

	if (m_Up)
	{
		m_PlayerAnim = EPlayer_Animation::AttackUp;

		m_Effect->SetWorldPosition(GetWorldPos() + Vector3(0.f, 50.f, 0.f));

		if (m_PlayerDir == 1)
			m_Effect->GetAnimation()->ChangeAnimation("AttackUpLeftEffect");

		else
			m_Effect->GetAnimation()->ChangeAnimation("AttackUpRightEffect");
	}
	
	else if (m_Down)
	{
		m_PlayerAnim = EPlayer_Animation::AttackDown;

		m_Effect->SetWorldPosition(GetWorldPos() + Vector3(0.f, -50.f, 0.f));

		if (m_PlayerDir == 1)
			m_Effect->GetAnimation()->ChangeAnimation("AttackDownLeftEffect");

		else
			m_Effect->GetAnimation()->ChangeAnimation("AttackDownRightEffect");
	}

	else
	{
		m_PlayerAnim = EPlayer_Animation::Attack;

		if (m_PlayerDir == 1)
		{
			m_Effect->GetAnimation()->ChangeAnimation("SlashLeft");
			m_Effect->SetWorldPosition(GetWorldPos() + Vector3(-60.f, 7.f, 0.f));
		}

		else 
		{
			m_Effect->GetAnimation()->ChangeAnimation("SlashRight");
			m_Effect->SetWorldPosition(GetWorldPos() + Vector3(60.f, 7.f, 0.f));
		}
	}
}

void CPlayer2D::AttackKeyUp()
{
	m_Attack = false;

	m_PlayerAnim = EPlayer_Animation::Idle;

	m_Effect->Destroy();
}

void CPlayer2D::Dash()
{
	m_PlayerAnim = EPlayer_Animation::Dash;

	m_Dash = true;

	m_Wall->SetPhysicsSimulate(false);

	m_Effect = m_Scene->CreateObject<CEffect>("Effect");
	m_Effect->SetCollisionProfileName("PlayerEffect");

	if (m_PlayerDir == 1)
	{
		m_Effect->GetAnimation()->ChangeAnimation("DashLeftEffect");
		m_Effect->SetWorldPosition(GetWorldPos() + Vector3(100.f, 10.f, 0.f));
	}

	else
	{
		m_Effect->GetAnimation()->ChangeAnimation("DashRightEffect");
		m_Effect->SetWorldPosition(GetWorldPos() + Vector3(-100.f, 10.f, 0.f));
	}
}

void CPlayer2D::DashKeyUp()
{
	m_Dash = false;

	m_Wall->SetPhysicsSimulate(true);

	m_PlayerAnim = EPlayer_Animation::Idle;

	m_Effect->Destroy();

}

void CPlayer2D::Focus()
{
	m_PlayerAnim = EPlayer_Animation::Focus;

	m_Focus = true;

	m_Effect = m_Scene->CreateObject<CEffect>("Effect");

	m_Effect->SetCollisionProfileName("PlayerEffect");	
	m_Effect->GetAnimation()->ChangeAnimation("FocusEffect");
	m_Effect->SetWorldPosition(GetWorldPos() + Vector3(0.f, 15.f, 0.f));

	if (m_Focus)
	{
		m_Time += g_DeltaTime;

		if (m_Time >= 0.25f)
		{
			m_Camera->AddRelativePosition(-30.f, 0.f);

			if (m_Time >= 0.5f)
			{
				m_Camera->AddRelativePosition(60.f, 0.f);

				if (m_Time >= 0.75f)
				{
					m_Camera->AddRelativePosition(-90.f, 0.f);

					if (m_Time >= 1.f)
					{
						m_Camera->AddRelativePosition(60.f, 0.f);
						{
							if (m_Time >= 1.25f)
							{
								m_Camera->AddRelativePosition(-30.f, 0.f);

								if (m_Time >= 1.5f)
								{
									m_Camera->AddRelativePosition(0.f, 0.f);

									m_Time = 0.f;
								}
							}
						}
					}
				}
			}
		}
	}
}

void CPlayer2D::FocusKeyUp()
{
	m_Effect->Destroy();

	m_PlayerAnim = EPlayer_Animation::Idle;
}

void CPlayer2D::Hurt()
{
	m_Hurt = true;

	m_PlayerAnim = EPlayer_Animation::Hurt;

}

void CPlayer2D::QuickMap()
{
}

void CPlayer2D::SuperDash()
{
}

void CPlayer2D::DreamNail()
{
}

void CPlayer2D::QuickCast()
{
}

void CPlayer2D::Inventory()
{
}

