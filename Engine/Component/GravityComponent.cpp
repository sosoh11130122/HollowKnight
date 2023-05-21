#include "GravityComponent.h"
#include "SceneComponent.h"
#include "../GameObject/GameObject.h"
#include "../Scene/Scene.h"
#include "ColliderBox2D.h"
#include "ColliderSphere2D.h"
#include "../CollisionManager.h"

CGravityComponent::CGravityComponent() :
    m_PhysicsSimulate(true),
    m_Ground(false),
    m_GravityAccel(10.f),
    m_FallTime(0.f),
    m_FallStartY(0.f),
    m_Jump(false),
    m_JumpVelocity(0.f),
    m_SideWallCheck(true)
{
    m_ComponentType = ComponentType::Object;

    SetTypeID<CGravityComponent>();

    m_ComponentTypeName = "GravityAgent";
}

CGravityComponent::CGravityComponent(const CGravityComponent& Obj) :
    CObjectComponent(Obj)
{
    m_PhysicsSimulate = Obj.m_PhysicsSimulate;
    m_Ground = Obj.m_Ground;
    m_GravityAccel = Obj.m_GravityAccel;
    m_FallTime = Obj.m_FallTime;
    m_FallStartY = Obj.m_FallStartY;
    m_Jump = Obj.m_Jump;
    m_JumpVelocity = Obj.m_JumpVelocity;
    m_SideWallCheck = Obj.m_SideWallCheck;
}

CGravityComponent::~CGravityComponent()
{
}

void CGravityComponent::SetUpdateComponent(CSceneComponent* Component)
{
    m_UpdateComponent = Component;
}

void CGravityComponent::CheckMoveRight()
{
   // float PosX = m_Pos.x + (m_BodySize.x * 0.5f); //오른쪽 좌표
   // float PosY = m_Pos.y;


   // if (PosY - (m_BodySize.y * 0.5f) < m_WallInfo.Top && PosY + (m_BodySize.y * 0.5f) > (int)m_WallInfo.Bottom)
   //{
   //     if (PosX >= m_WallInfo.Left)
   //     {

   //         //m_UpdateComponent->SetWorldPositionX(- (PosX - m_WallInfo.Left));
   //         m_UpdateComponent->AddWorldPositionX(-(PosX - m_WallInfo.Left));
   //         m_SideWallCollision = true;
   //     }
   // }

   // else
   //     m_SideWallCollision = false;

    float PosX = m_Pos.x + m_BodySize.x; //오른쪽 좌표

    if (PosX >= (m_WallInfo.Left))
    {
        m_UpdateComponent->SetWorldPositionX(m_Pos.x - (PosX - m_WallInfo.Left));
        m_SideWallCollision = true;
    }


    m_SideWallCollision = false;


}

void CGravityComponent::CheckMoveLeft()
{  
    //float PosX = m_Pos.x - (m_BodySize.x * 0.5f); //오른쪽 좌표
    //float PosY = m_Pos.y;


    //if (PosY - (m_BodySize.y * 0.5f) < m_WallInfo.Top && PosY + (m_BodySize.y * 0.5f) > (int)m_WallInfo.Bottom)
    //{
    //    if (PosX <= m_WallInfo.Right)
    //    {

    //        //m_UpdateComponent->SetWorldPositionX(m_Pos.x + (m_WallInfo.Right - PosX));
    //        m_UpdateComponent->AddWorldPositionX(PosX - m_WallInfo.Right);
    //        m_SideWallCollision = true;
    //    }
    //}

    //else
    //    m_SideWallCollision = false;

    float LeftPosX = m_Pos.x - m_BodySize.x; //왼쪽 좌표

    if (LeftPosX <= m_WallInfo.Right)
    {
        m_UpdateComponent->SetWorldPositionX(m_Pos.x + (m_WallInfo.Right - LeftPosX));
        m_SideWallCollision = true;
    }

    m_SideWallCollision = false;

}

void CGravityComponent::Destroy()
{
    CObjectComponent::Destroy();
}

void CGravityComponent::Start()
{
    CObjectComponent::Start();

    if (!m_UpdateComponent)
        m_UpdateComponent = m_Owner->GetRootComponent();

    //!!주의, 오브젝트에 중력 적용하려면 루트컴포넌트를 콜라이더로 만들기
    std::string OwnerName = m_UpdateComponent->GetName(); 
    //TODO
    //충돌 비교할 재료 들고오기

    //둘 다 콜라이더 박스로 사용
    //** 콜라이더는 가운데 피봇

    

    //주체
    m_Body = (CCollider2D*)m_Owner->FindComponent(OwnerName);
    //1209
    m_Body->GetCollisionProfile();
    //

    if (m_Body)
    {
        m_BodySize = ((CColliderBox2D*)m_Body.Get())->GetBoxSize();
        m_BodyInfo = ((CColliderBox2D*)m_Body.Get())->GetInfo();

        m_Pos = m_Body->GetWorldPos();
        m_Pos.y = m_Pos.y - (m_BodySize.y * 0.5f); //Center 기준에서 하단 피봇으로 바꿔줌
        m_PrevPos = m_Pos;
    }

    //맨 처음 FallStartY 세팅해주기
    SetFallStartY(m_Pos.y);
}

bool CGravityComponent::Init()
{
    if (!CObjectComponent::Init())
        return false;

    return true;
}

void CGravityComponent::Update(float DeltaTime)
{
    CObjectComponent::Update(DeltaTime);

    //씬에 있는 콜라이더 가져오기
    if (m_Scene)
    m_Wall = (CCollider2D*)(m_Scene->FindObject("WallObj")->FindComponent("Wall"));

    if (m_Wall)
    {
        m_WallSize = ((CColliderBox2D*)m_Wall.Get())->GetBoxSize();
        m_WallInfo = ((CColliderBox2D*)m_Wall.Get())->GetInfo();
    }
     
    //중력 적용
    if (m_UpdateComponent)
    {
        if (!m_Ground && m_PhysicsSimulate)
        {
            //떨어지는 시간 누적
            m_FallTime += DeltaTime * m_GravityAccel;

            // 9.8 m/s^2
            // t초 후 y값
            // V:속도 A:가속도 G:중력
            // y = V * A - 0.5f * G * t * t
            // 0 = -0.5fGA^2 VA - y
            //이차 방정식이 나오니 근의 공식을 이용해서 해를 구하면 좋음
            float Velocity = 0.f;

            if (m_Jump)
                Velocity = m_JumpVelocity * m_FallTime;

            //중력 식
            float Gravity = (Velocity - 0.5f * GRAVITY * m_FallTime * m_FallTime);

            float Y = m_FallStartY + Gravity; //현재 떨어지는 위치

            m_UpdateComponent->SetWorldPositionY(Y);
        }

    
        //코드추가한것
        //bool check = false;
        ////땅에 닿을 때
        //float Y = m_Pos.y - (m_BodySize.y * 0.5f);
        //if (Y <= m_WallInfo.Top)
        //{
        //    float MoveY = Y - m_WallInfo.Top;

        //    check = true;
        //    m_FallTime = 0.f;
        //    m_JumpCount = 0;
        //    m_Ground = true;
        //    m_FallingStart = false;

        //    m_Jump = false;
        //    if (Y < m_WallInfo.Top)
        //    {
        //        m_Owner->SetWorldPositionY(m_WallInfo.Top - MoveY);
        //    }

        //}
        //코드추가한것
    }
}

void CGravityComponent::PostUpdate(float DeltaTime)
{
    CObjectComponent::PostUpdate(DeltaTime);

    m_Pos = m_Body->GetWorldPos();
    m_Pos.y = m_Pos.y;
    m_Move = m_Pos - m_PrevPos; //이동 거리. m_Move.y는 떨어지기 시작하면 음수가 나옴 
    
    //현재 y가 이전 y의 위치보다 값이 작아지면(떨어지기 시작했다는 의미)
    if (m_Move.y < 0)
        m_FallingStart = true;



    ////바닥에 착지시킨다.
    //if (m_PhysicsSimulate && m_Move.y <= 0.f)
    //{
    //    bool check = false;

    //    //땅에 닿을 때
    //    float LandPosY = m_Pos.y - (m_BodySize.y * 0.5f);

    //    if ((int)m_Pos.x + (m_BodySize.x * 0.5f) <= m_WallInfo.Right && ((int)m_Pos.x - (m_BodySize.x * 0.5f) >= m_WallInfo.Left))
    //    {
    //        if ((int)LandPosY <= (int)m_WallInfo.Top && (int)LandPosY > m_WallInfo.Top - 5)
    //        {
    //            m_Owner->SetWorldPositionY(m_WallInfo.Top + m_BodySize.y * 0.5f);

    //            m_FallTime = 0.f;
    //            m_JumpCount = 0;
    //            m_Ground = true;
    //            m_FallingStart = false;

    //            m_Jump = false;
    //        }

    //          
    //        

    //    }

    //    else
    //    {
    //        if (m_Move.x != 0.f && m_SideWallCheck)
    //        {
    //            //if (m_Move.x > 0.f)
    //            if (m_Pos.x + (m_BodySize.x * 0.5f) >= m_WallInfo.Left)

    //            {
    //                CheckMoveRight();
    //            }

    //            else if (m_Pos.x - (m_BodySize.x * 0.5f) <= m_WallInfo.Right)
    //                CheckMoveLeft();
    //        }
    //    }

    //}

    if (m_PhysicsSimulate && m_Move.y <= 0.f)
    {
        bool check = false;
        //땅에 닿을 때
        float Y = m_Pos.y - (m_BodySize.y * 0.5f);

        if ((m_Pos.x - (m_BodySize.x * 0.5f)) > m_WallInfo.Left && (m_Pos.x + (m_BodySize.x * 0.5f)) < m_WallInfo.Right)
        {
            if ((int)Y <= (int)m_WallInfo.Top && (int)Y > (int)m_WallInfo.Top - 50.f)
            {
                check = true;
                m_FallTime = 0.f;
                m_JumpCount = 0;
                m_Ground = true;
                m_FallingStart = false;

                m_Owner->SetWorldPositionY(m_WallInfo.Top + (m_BodySize.y * 0.5f));

                m_Jump = false;
            }

            //바닥이 없을 경우
            if (!check)
            {
                if (m_Ground)
                {
                    m_FallTime = 0.f;
                    m_FallStartY = m_Pos.y;
                }

                m_Ground = false;
            }
        }

        else if ((m_Pos.x - (m_BodySize.x * 0.5f)) > m_WallInfo.Right)
        {
            if (m_Pos.y - (m_BodySize.y * 0.5f) < m_WallInfo.Top && m_Pos.y + (m_BodySize.y * 0.5f) > m_WallInfo.Bottom)
            {
                CheckMoveLeft();
            }

            else
                m_SideWallCollision = false;
        }


        else if ((m_Pos.x + (m_BodySize.x * 0.5f)) < m_WallInfo.Left)
        {
            if (m_Pos.y - (m_BodySize.y * 0.5f) < m_WallInfo.Top && m_Pos.y + (m_BodySize.y * 0.5f) > m_WallInfo.Bottom)
            {
                CheckMoveRight();
            }

            else
                m_SideWallCollision = false;
        }
    }
}

void CGravityComponent::Render()
{
    CObjectComponent::Render();
}

CGravityComponent* CGravityComponent::Clone() const
{
    return new CGravityComponent(*this);
}

void CGravityComponent::Save(FILE* File)
{
    CObjectComponent::Save(File);

    /*
   bool   m_PhysicsSimulate;
   bool   m_Ground;          
   float   m_GravityAccel;
   float   m_FallTime;
   float   m_FallStartY;
   bool   m_Jump;
   float   m_JumpVelocity;
   bool   m_SideWallCheck;
  */

  int Length = (int)m_UpdateComponent->GetName().length();
  fwrite(&Length, sizeof(int), 1, File);

  fwrite(m_UpdateComponent->GetName().c_str(), 1, Length, File);

  fwrite(&m_PhysicsSimulate, sizeof(bool), 1, File);
  fwrite(&m_Ground, sizeof(bool), 1, File);
  fwrite(&m_GravityAccel, sizeof(float), 1, File);
  fwrite(&m_FallTime, sizeof(float), 1, File);
  fwrite(&m_FallStartY, sizeof(float), 1, File);
  fwrite(&m_Jump, sizeof(bool), 1, File);
  fwrite(&m_JumpVelocity, sizeof(float), 1, File);
  fwrite(&m_SideWallCheck, sizeof(bool), 1, File);
  fwrite(&m_WallInfo.Bottom, sizeof(Box2DInfo), 1, File);
  fwrite(&m_WallInfo.Top, sizeof(Box2DInfo), 1, File);
  fwrite(&m_WallInfo.Left, sizeof(Box2DInfo), 1, File);
  fwrite(&m_WallInfo.Right, sizeof(Box2DInfo), 1, File);


 // fwrite(m_Body->GetCollisionProfile().c_str(), 1, Length, File); 1209

}

void CGravityComponent::Load(FILE* File)
{
    CObjectComponent::Load(File);

    int Length = 0;
    fread(&Length, sizeof(int), 1, File);

    char   ComponentName[256] = {};
    fread(ComponentName, 1, Length, File);

    CSceneComponent* UpdateComponent = (CSceneComponent*)m_Owner->FindComponent(ComponentName);
    SetUpdateComponent(UpdateComponent);

    fread(&m_PhysicsSimulate, sizeof(bool), 1, File);
    fread(&m_Ground, sizeof(bool), 1, File);
    fread(&m_GravityAccel, sizeof(float), 1, File);
    fread(&m_FallTime, sizeof(float), 1, File);
    fread(&m_FallStartY, sizeof(float), 1, File);
    fread(&m_Jump, sizeof(bool), 1, File);
    fread(&m_JumpVelocity, sizeof(float), 1, File);
    fread(&m_SideWallCheck, sizeof(bool), 1, File);
    fread(&m_WallInfo.Bottom, sizeof(Box2DInfo), 1, File);
    fread(&m_WallInfo.Top, sizeof(Box2DInfo), 1, File);
    fread(&m_WallInfo.Left, sizeof(Box2DInfo), 1, File);
    fread(&m_WallInfo.Right, sizeof(Box2DInfo), 1, File);

}