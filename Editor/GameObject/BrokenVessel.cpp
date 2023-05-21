#include "BrokenVessel.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "Component/NavigationAgent.h"
#include "Component/CameraComponent.h"
#include "Resource/Material/Material.h"
#include "Scene/SceneInfo.h"
#include "Scene/Scene.h"
#include "Input.h"
#include "../GameObject/Player2D.h"
#include "Component/WallComponent.h"
#include "../GameObject/Effect.h"
#include "../GameObject/Bullet.h"

CBrokenVessel::CBrokenVessel() :
	m_MoveSpeed(0.1f),
	m_Time(0.f),
	m_Start(false),
	m_Roar(false),
	m_AttackStart(false),
	m_Jump(false),
	m_DashStart(false),
	m_Idle(false),
	m_EnableChase(true),
	m_DownStab(false),
	m_DownStabLand(false),
	m_HeadBanging(false),
	m_Walk(false),
	m_Stun(false),
	m_EndRoar(false),
	m_Death(false),
	m_HP(25.f),
	m_PlayTime(0.f)
{
	SetTypeID<CBrokenVessel>();

	m_ObjectTypeName = "BrokenVessel";

	m_MonsterAnim = EBrokenVessel_Animation::Sleep;
	m_PrevMonsterAnim = EBrokenVessel_Animation::Sleep;
}

CBrokenVessel::CBrokenVessel(const CBrokenVessel& Obj) :
	CGameObject(Obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_Radar = (CColliderBox2D*)FindComponent("Radar");
	//m_Dash = (CColliderBox2D*)FindComponent("Dash"); 
	m_Sprite = (CSpriteComponent*)FindComponent("sprite");
	m_WallComponent = (CWallComponent*)FindComponent("WallComponent");
}

CBrokenVessel::~CBrokenVessel()
{
}

void CBrokenVessel::Start()
{
	CGameObject::Start();

	m_WallComponent->SetFallStartY(GetWorldPos().y);


	CInput::GetInst()->AddBindFunction<CBrokenVessel>("Up", Input_Type::Down,
		this, &CBrokenVessel::OverHeadAttack, m_Scene);


	/*SetRootComponent(m_Body);

	m_Body->SetCollisionProfile("Monster");
	m_Body->SetWorldPosition(200.f, 300.f);
	m_Body->AddChild(m_Sprite);
	m_Body->AddChild(m_Radar);

	m_Radar->SetWorldPosition(400.f, 300.f);
	m_Radar->SetCollisionProfile("MonsterAttack");

	m_Sprite->SetRelativeScale(100.f, 100.f);
	m_Sprite->SetPivot(0.5f, 0.5f);*/

	m_Animation = m_Sprite->SetAnimation<CAnimation2D>("BrokenVessel");

	m_Animation->AddAnimation("BossIdleLeft", "BossIdleLeft", 1.f, 1.f, true);
	m_Animation->AddAnimation("BossIdleRight", "BossIdleRight", 1.f, 1.f, true);
	m_Animation->AddAnimation("BossWalkLeft", "BossWalkLeft", 1.f, 0.7f, true);
	m_Animation->AddAnimation("BossWalkRight", "BossWalkRight", 1.f, 0.7f, true);
	m_Animation->AddAnimation("BossDashLeft", "BossDashLeft", 1.f, 1.5f, true);
	m_Animation->AddAnimation("BossDashRight", "BossDashRight", 1.f, 1.5f, true);

	m_Animation->AddAnimation("BossJumpLeft", "BossJumpLeft", 1.f, 1.f);
	m_Animation->AddAnimation("BossJumpRight", "BossJumpRight", 1.f, 1.f);
	m_Animation->AddAnimation("BossFallLeft", "BossFallLeft", 1.f, 1.f);
	m_Animation->AddAnimation("BossFallRight", "BossFallRight", 1.f, 1.f);

	m_Animation->AddAnimation("BossOverHeadAttackLeft", "BossOverHeadAttackLeft", 1.f, 1.f, true);
	m_Animation->AddAnimation("BossOverHeadAttackRight", "BossOverHeadAttackRight", 1.f, 1.f, true);

	m_Animation->AddAnimation("BossStunLeft", "BossStunLeft", 1.f, 1.f, true);
	m_Animation->AddAnimation("BossStunRight", "BossStunRight", 1.f, 1.f, true);

	m_Animation->AddAnimation("BossDeathLeft", "BossDeathLeft", 1.f, 1.f);
	m_Animation->AddAnimation("BossDeathRight", "BossDeathRight", 1.f, 1.f);

	m_Animation->AddAnimation("BossDownStabLeft", "BossDownStabLeft", 0.7f, 1.f);
	m_Animation->AddAnimation("BossDownStabRight", "BossDownStabRight", 0.7f, 1.f);
	m_Animation->AddAnimation("BossDownStabLandLeft", "BossDownStabLandLeft", 0.7f, 1.f);
	m_Animation->AddAnimation("BossDownStabLandRight", "BossDownStabLandRight", 0.7f, 1.f);


	m_Animation->AddAnimation("BossStartAnimation", "BossStartAnimation", 7.f, 1.f);

	m_Animation->AddAnimation("BossRoarLeft", "BossRoarLeft", 1.f, 1.f, true);
	m_Animation->AddAnimation("BossRoarRight", "BossRoarRight", 1.f, 1.f, true);


	m_Animation->AddAnimation("BossSleep", "BossSleep", 1.f, 1.f);




	// Left animation
	m_vecSequenceKey[0].push_back("BossIdleLeft");
	m_vecSequenceKey[0].push_back("BossWalkLeft");
	m_vecSequenceKey[0].push_back("BossDashLeft");

	m_vecSequenceKey[0].push_back("BossJumpLeft");
	m_vecSequenceKey[0].push_back("BossFallLeft");

	m_vecSequenceKey[0].push_back("BossOverHeadAttackLeft");
	m_vecSequenceKey[0].push_back("BossStunLeft");

	m_vecSequenceKey[0].push_back("BossRoarLeft");
	m_vecSequenceKey[0].push_back("BossDeathLeft");

	m_vecSequenceKey[0].push_back("BossDownStabLeft");
	m_vecSequenceKey[0].push_back("BossDownStabLandLeft");





	// Right Animation
	m_vecSequenceKey[1].push_back("BossIdleRight");
	m_vecSequenceKey[1].push_back("BossWalkRight");
	m_vecSequenceKey[1].push_back("BossDashRight");

	m_vecSequenceKey[1].push_back("BossJumpRight");
	m_vecSequenceKey[1].push_back("BossFallRight");

	m_vecSequenceKey[1].push_back("BossOverHeadAttackRight");
	m_vecSequenceKey[1].push_back("BossStunRight");

	m_vecSequenceKey[1].push_back("BossRoarRight");
	m_vecSequenceKey[1].push_back("BossDeathRight");

	m_vecSequenceKey[1].push_back("BossDownStabRight");
	m_vecSequenceKey[1].push_back("BossDownStabLandRight");

	m_vecSequenceKey[1].push_back("BossStartAnimation");

	m_vecSequenceKey[1].push_back("BossSleep"); //BossSleep


	m_Radar->SetCollisionCallback<CBrokenVessel>(ECollision_Result::Collision, this, &CBrokenVessel::StartAnimation);
	m_Body->SetCollisionCallback<CBrokenVessel>(ECollision_Result::Collision, this, &CBrokenVessel::Hurt);

}

bool CBrokenVessel::Init()
{
	CGameObject::Init();

	/*m_Pos = m_Body->GetWorldPos();
	m_PrevPos = m_Pos;*/

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Radar = CreateComponent<CColliderBox2D>("Radar");
	//m_Dash = CreateComponent<CColliderBox2D>("Dash");
	m_Sprite = CreateComponent<CSpriteComponent>("sprite");
	m_WallComponent = CreateComponent<CWallComponent>("WallComponent");


	SetRootComponent(m_Body);

	m_Body->SetCollisionProfile("Monster");
	m_Body->SetWorldPosition(1200.f, 300.f);
	m_Body->AddChild(m_Sprite);
	m_Body->AddChild(m_Radar);

	m_Radar->SetWorldPosition(400.f, 300.f);
	m_Radar->SetCollisionProfile("MonsterAttack");

	//m_Dash->SetBoxSize()

	m_Sprite->SetRelativeScale(378.f, 234.f);
	m_Sprite->SetPivot(0.5f, 0.5f);

	return true;
}

void CBrokenVessel::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_WallComponent->SetJumpVelocity(80.f);

	m_Player = m_Scene->FindObject("Player2D");

	if (m_Player)
	{
		m_PlayerPos = m_Player->GetWorldPos();
	}

	m_Pos = m_Body->GetWorldPos();

	m_Dir = m_Pos.x - m_PlayerPos.x;

	m_PrevMonsterDir = m_MonsterDir;

	if (m_Dir.x > 0.f)
		m_MonsterDir = -1;

	else
		m_MonsterDir = 1;

	//AddWorldPosition(m_Pos * DeltaTime * m_MoveSpeed * GetWorldAxis(AXIS_X));

	//m_Animation->SetCurrentAnimation("BossSleep");

	int	AnimDirectionIndex = 0;

	if (m_MonsterDir == 1)
		AnimDirectionIndex = 1;



	/*	m_vecSequenceKey[0].push_back("BossIdleLeft");
	m_vecSequenceKey[0].push_back("BossWalkLeft");
	m_vecSequenceKey[0].push_back("BossDashLeft");

	m_vecSequenceKey[0].push_back("BossJumpLeft");
	m_vecSequenceKey[0].push_back("BossFallLeft");

	m_vecSequenceKey[0].push_back("BossOverHeadAttackLeft");
	m_vecSequenceKey[0].push_back("BossStunLeft");

	m_vecSequenceKey[0].push_back("BossRoarLeft");
	m_vecSequenceKey[0].push_back("BossDeathLeft");

	m_vecSequenceKey[0].push_back("BossDownStabLeft");
	m_vecSequenceKey[0].push_back("BossDownStabLandLeft");*/

	switch (m_MonsterAnim)
	{
	case EBrokenVessel_Animation::Idle:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][0]);
		m_Sprite->SetRelativeScale(378.f, 234.f);
		break;

	case EBrokenVessel_Animation::Walk:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][1]);
		m_Sprite->SetRelativeScale(378.f, 234.f);
		break;

	case EBrokenVessel_Animation::Dash:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][2]);
		m_Sprite->SetRelativeScale(378.f, 234.f);
		//m_Sprite->SetRelativeScale(100.f, 100.f);
		break;

	case EBrokenVessel_Animation::Jump:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][3]);
		m_Sprite->SetRelativeScale(378.f, 234.f);
		//m_Sprite->SetRelativeScale(100.f, 100.f);
		break;

	case EBrokenVessel_Animation::Fall:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][4]);
		m_Sprite->SetRelativeScale(378.f, 234.f);
		break;

	case EBrokenVessel_Animation::OverHeadAttack:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][5]);
		break;

	case EBrokenVessel_Animation::Stun:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][6]);
		m_Sprite->SetRelativeScale(378.f, 234.f);
		break;

	case EBrokenVessel_Animation::Roar:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][7]);
		m_Sprite->SetRelativeScale(378.f, 234.f);
		break;
	case EBrokenVessel_Animation::Death:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][8]);
		m_Sprite->SetRelativeScale(378.f, 234.f);
		break;

	case EBrokenVessel_Animation::DownStab:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][9]);
		m_Sprite->SetRelativeScale(378.f, 234.f);
		break;

	case EBrokenVessel_Animation::DownStabLand:
		m_Animation->ChangeAnimation(m_vecSequenceKey[AnimDirectionIndex][10]);
		m_Sprite->SetRelativeScale(378.f, 234.f);
		break;

	case EBrokenVessel_Animation::StartAnimation:
		m_Animation->ChangeAnimation("BossStartAnimation");
		m_Sprite->SetRelativeScale(110.f, 110.f);
		break;

	case EBrokenVessel_Animation::Sleep:
		m_Animation->ChangeAnimation("BossSleep");
		m_Sprite->SetRelativeScale(110.f, 110.f);
		break;
	}

	m_PrevMonsterAnim = m_MonsterAnim;
}

void CBrokenVessel::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	m_PlayTime += DeltaTime;

	m_Player = m_Scene->FindObject("Player2D");

	if (m_Player)
		m_PlayerPos = m_Player->GetWorldPos();

	if (m_Start)
	{
		m_MonsterAnim = EBrokenVessel_Animation::StartAnimation;

		m_Radar->Destroy();

		m_Animation->SetCurrentEndFunction("BossStartAnimation", this, &CBrokenVessel::StartRoar);
	}

	CCameraComponent* Camera = m_Scene->GetCameraManager()->GetCurrentCamera();

	if (m_Roar)
	{
		m_Time += DeltaTime;

		if (m_Time >= 0.25f)
		{
			Camera->AddWorldPositionX(-600.f * DeltaTime);

			if (m_Time >= 0.5f)
			{
				Camera->AddWorldPositionX(1000.f * DeltaTime);

				if (m_Time >= 0.75f)
				{
					Camera->AddWorldPositionX(-1000.f * DeltaTime);

					if (m_Time >= 1.f)
					{
						Camera->AddWorldPositionX(1200.f * DeltaTime);
						{
							if (m_Time >= 1.25f)
							{
								Camera->AddWorldPositionX(-1000.f * DeltaTime);

								if (m_Time >= 1.5f)
								{
									Camera->AddWorldPositionX(800.f * DeltaTime);

									if (m_Time >= 1.75)
									{
										Camera->AddWorldPositionX(-600.f * DeltaTime);

										if (m_Time >= 2.f)
										{
											Camera->AddWorldPositionX(600.f * DeltaTime);

											if (m_Time >= 2.25f)
												Camera->SetWorldPositionX(m_PlayerPos.x * DeltaTime);

										}
									}
								}
							}
						}
					}
				}
			}
		}
	

		if (m_Time >= 3.f)
		{
			m_Time = 0.f;

			m_Idle = true;

			m_Roar = false;

		}
		/*m_Animation->AddCurrentNotify<CBrokenVessel>("BossStartRoar", "BossStartRoar", 2, this, &CBrokenVessel::Idle);*/
	}

	if (m_Idle)
	{
		m_Time += DeltaTime;

		if (m_Time >= 2.f)
		{
			Idle();

			m_Time = 0.f;

			m_Idle = false;

			m_DashStart = true;
		}

		//m_Animation->AddCurrentNotify("BossIdleRight", "BossIdleRight", 3, this, &CBrokenVessel::Dash);
	}

	if (m_DashStart)
	{
		m_Time += DeltaTime;

		DashStart();
		
		Vector3 Dir = m_PlayerPos - m_Pos;

		Dir.Normalize();
		Dir.y = 0.f;
		Dir.Normalize();
		m_Body->AddWorldPosition(Dir * 300.f * DeltaTime);


		// 대쉬해서 플레이어 지나가도록
		if (m_Pos == m_PlayerPos)
		{
			if (m_MonsterDir = 1)
				m_Body->AddWorldPositionX(300.f * DeltaTime);

			else
				m_Body->AddWorldPositionX(-300.f * DeltaTime);
		}


		if (m_Time >= 1.5f)
		{
			m_MonsterAnim = EBrokenVessel_Animation::Walk;
			//m_Sprite->SetRelativeScale(110.f, 100.f);

			m_Body->SetWorldPosition(m_Pos);

			m_DashStart = false;

			m_DownStab = true;
		}
	}

	if (m_DownStab)
	{
		m_Time += DeltaTime;

		if (m_Time >= 2.f)
		{
			DownStab();

			m_Time = 0.f;

			m_DownStabLand = true;

			m_DownStab = false;
			//m_OverHeadAttack = true;
		}

	}

	if (m_DownStabLand)
	{
		m_Time += DeltaTime;

		if (m_Time >= 2.f)
		{
			DownStabLand();

			m_Time = 0.f;

			m_Jump = true;

			m_DownStabLand = false;
	
		}

		if (m_Time >= 2.25f)
		{
			Camera->AddWorldPositionX(-400.f * DeltaTime);

			if (m_Time >= 2.5f)
			{
				Camera->AddWorldPositionX(1000.f * DeltaTime);

				if (m_Time >= 2.75f)
				{
					Camera->AddWorldPositionX(-1000.f * DeltaTime);

					if (m_Time >= 3.f)
					{
						Camera->AddWorldPositionX(1200.f * DeltaTime);
						{
							if (m_Time >= 3.25f)
							{
								Camera->AddWorldPositionX(-1000.f * DeltaTime);

								if (m_Time >= 3.5f)
								{
									Camera->AddWorldPositionX(800.f * DeltaTime);

									if (m_Time >= 3.75)
									{
										Camera->SetWorldPositionX(m_PlayerPos.x * DeltaTime);

									}
								}
							}
						}
					}
				}
			}
		}
	}



	if (m_Jump)
	{
		m_Time += DeltaTime;

		if (m_Time >= 5.f)
		{
			Jump();

			Vector3 Dir = m_PlayerPos - m_Pos;
			Dir.y = 0.f;
			Dir.Normalize();

			m_Body->AddWorldPosition(Dir * 100.f * g_DeltaTime);

			if (m_Time >= 6.5f)
			{
				Fall();

				if (m_Time >= 7.f)
				{
					m_MonsterAnim = EBrokenVessel_Animation::Walk;
					//m_Sprite->SetRelativeScale(110.f, 100.f);

					m_Time = 0.f;

					m_Jump = false;

					m_HeadBanging = true;
				}

			}
		}

	}


	if (m_HeadBanging)
	{
		m_Time += DeltaTime;

		if (m_Time >= 2.f)
		{
			HeadBanging();

			//m_MonsterAnim = EBrokenVessel_Animation::Walk;

			m_Time = 0.f;

			m_HeadBanging = false;

			m_Walk = true;
		}

		if (m_Time >= 2.25f)
		{
			Camera->AddWorldPositionX(-400.f * DeltaTime);

			if (m_Time >= 2.5f)
			{
				Camera->AddWorldPositionX(1000.f * DeltaTime);

				if (m_Time >= 2.75f)
				{
					Camera->AddWorldPositionX(-1000.f * DeltaTime);

					if (m_Time >= 3.f)
					{
						Camera->AddWorldPositionX(1200.f * DeltaTime);
						{
							if (m_Time >= 3.25f)
							{
								Camera->AddWorldPositionX(-1000.f * DeltaTime);

								if (m_Time >= 3.5f)
								{
									Camera->AddWorldPositionX(800.f * DeltaTime);

									if (m_Time >= 3.75)
									{
										Camera->SetWorldPositionX(m_PlayerPos.x * DeltaTime);

									}
								}
							}
						}
					}
				}
			}
		}
	}

	if (m_Walk)
	{
		m_Time += DeltaTime;

		if (m_Time >= 2.f)
		{
			if (m_MonsterDir = 1)
				Right();

			else
				Left();

			if (m_Time >= 5.f)
			{
				m_Time = 0.f;

				m_Walk = false;

				m_Idle = true;
			}
		}
	}

	if (m_Death)
	{
		m_Idle = false;
		m_DashStart = false;
		m_Jump = false;
		m_DownStab = false;
		m_DownStabLand = false;
		m_Walk = false;
		m_HeadBanging = false;

		m_MonsterAnim = EBrokenVessel_Animation::Death;

		m_PlayTime = 0.f;
	}

}

CBrokenVessel* CBrokenVessel::Clone() const
{
	return new CBrokenVessel(*this);
}

void CBrokenVessel::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CBrokenVessel::Load(FILE* File)
{
	CGameObject::Load(File);
}

void CBrokenVessel::Idle()
{
	m_MonsterAnim = EBrokenVessel_Animation::Idle;

	float Move = m_Pos.x - m_PlayerPos.x;

	//if (Move < 0.f)
	//	Right();

	//else
	//	Left();
}

void CBrokenVessel::Left()
{
	m_MonsterDir = 1;

	m_MonsterAnim = EBrokenVessel_Animation::Walk;
	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * -100.f * g_DeltaTime);
	//m_Sprite->SetRelativeScale(110.f, 100.f);
}

void CBrokenVessel::Right()
{
	m_MonsterDir = -1;
	
	m_Body->AddWorldPosition(m_Body->GetWorldAxis(AXIS_X) * 100.f * g_DeltaTime);
	m_MonsterAnim = EBrokenVessel_Animation::Walk;
	//m_Sprite->SetRelativeScale(110.f, 100.f);
}

void CBrokenVessel::DashStart()
{
	m_MonsterAnim = EBrokenVessel_Animation::Dash;
	//m_Sprite->SetRelativeScale(140.f, 130.f);
}

void CBrokenVessel::Jump()
{
	m_MonsterAnim = EBrokenVessel_Animation::Jump;

	m_WallComponent->Jump();

	//m_Sprite->SetRelativeScale(165.f, 165.f);
	//m_Sprite->SetPivot(0.5f, 0.5f);
}

void CBrokenVessel::Fall()
{
	m_MonsterAnim = EBrokenVessel_Animation::Fall;
	//m_Sprite->SetRelativeScale(150.f, 150.f);

	//m_WallComponent->FallingStartOn(m_Pos.y);
}

void CBrokenVessel::OverHeadAttack()
{
	//m_MonsterAnim = EBrokenVessel_Animation::OverHeadAttack;
	m_Sprite->SetRelativeScale(240.f, 170.f);
	m_Sprite->SetPivot(0.5f, 0.3f);

	m_Effect = m_Scene->CreateObject<CEffect>("Effect");
	m_Effect->SetCollisionProfileName("Monster");

	m_DashStart = false;

	//m_OverHeadAttack = true;
}

void CBrokenVessel::HeadBanging()
{
	m_MonsterAnim = EBrokenVessel_Animation::Roar;
	//m_Sprite->SetRelativeScale(150.f, 150.f);

	for (int i = 0; i < 4; ++i)
	{
		m_Bullet[i] = m_Scene->CreateObject<CBullet>("Bullet");
		m_Bullet[i]->SetWorldPositionX(m_Body->GetWorldPos().x + i * -100.f);
		m_Bullet[i]->SetWorldRotationX(m_Body->GetWorldRot().x + i * -20.f);
		m_Bullet[i]->SetCollisionProfileName("Monster");
	}

	for (int j = 1; j < 5; ++j)
	{
		m_Bullet[j] = m_Scene->CreateObject<CBullet>("Bullet");
		m_Bullet[j]->SetWorldPositionX(m_Body->GetWorldPos().x + j * 100.f);
		m_Bullet[j]->SetWorldRotationX(m_Body->GetWorldRot().x + j * 20.f);
		m_Bullet[j]->SetCollisionProfileName("Monster");
	}


}

void CBrokenVessel::Stun()
{
	m_MonsterAnim = EBrokenVessel_Animation::Stun;
}

void CBrokenVessel::StartAnimation()
{
	m_MonsterAnim = EBrokenVessel_Animation::StartAnimation;
}

void CBrokenVessel::StartRoar()
{
	m_MonsterAnim = EBrokenVessel_Animation::Roar;
	//m_Sprite->SetRelativeScale(140.f, 140.f);

	m_Start = false;

	m_Roar = true;

	//Camera->AddWorldPositionX(400.f * g_DeltaTime);
}


void CBrokenVessel::Death()
{
	m_MonsterAnim = EBrokenVessel_Animation::Death;
}

void CBrokenVessel::DownStab()
{
	m_MonsterAnim = EBrokenVessel_Animation::DownStab;

	m_WallComponent->Jump();
}

void CBrokenVessel::DownStabLand()
{
	m_DownStabLand = true;

	m_MonsterAnim = EBrokenVessel_Animation::DownStabLand;

	m_WallComponent->FallingStartOn(m_Pos.y);

	for (int i = 0; i < 2; ++i)
	{
		m_Bullet[i] = m_Scene->CreateObject<CBullet>("Bullet");
		m_Bullet[i]->SetWorldPositionX(m_Body->GetWorldPos().x + i * -150.f);
		m_Bullet[i]->SetWorldRotation(m_Body->GetWorldRot() + i * -20.f);
		m_Bullet[i]->SetCollisionProfileName("Monster");
	}

	for (int i = 1; i < 3; ++i)
	{
		m_Bullet[i] = m_Scene->CreateObject<CBullet>("Bullet");
		m_Bullet[i]->SetWorldPositionX(m_Body->GetWorldPos().x + i * 150.f);
		m_Bullet[i]->SetWorldRotation(m_Body->GetWorldRot() + i * 20.f);
		m_Bullet[i]->SetCollisionProfileName("Monster");
	}

}

void CBrokenVessel::StartAnimation(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "Player")
	{
		m_Start = true;
	}
}

void CBrokenVessel::Hurt(const CollisionResult& result)
{	
	if (result.Dest->GetCollisionProfile()->Name == "PlayerAttack")
	{
		m_Death = true;
	}
}

void CBrokenVessel::HurtEnd(const CollisionResult& result)
{
	//m_Effect->Destroy();
}
