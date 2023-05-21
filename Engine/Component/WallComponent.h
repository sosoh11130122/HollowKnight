#pragma once

#include "ObjectComponent.h"

class CWallComponent :
    public CObjectComponent
{
    friend class CGameObject;
    friend class CScene;

protected:
    CWallComponent();
    CWallComponent(const CWallComponent& Obj);
    virtual ~CWallComponent();

private:
    CSharedPtr<class CSceneComponent> m_UpdateComponent;

public:
    //[���� �ҽ�]
    void SetUpdateComponent(class CSceneComponent* Component);

    //[�߷� �ҽ�]
    void SetFallStartY(float y)
    {
        m_FallStartY = y;
    }

    void SetSideWallCheck(bool Check)
    {
        m_SideWallCheck = Check;
    }

    void SetPhysicsSimulate(bool Physics)
    {
        m_PhysicsSimulate = Physics;
    }

    void SetGravityAccel(float Accel)
    {
        m_GravityAccel = Accel;
    }

    void SetJumpVelocity(float JumpVelocity)
    {
        m_JumpVelocity = JumpVelocity;
    }

    void SetFallTime(float FallTime)
    {
        m_FallTime = FallTime;
    }

    void SetMiniJumpOn(bool MiniJumpOn)
    {
        m_MiniJumpOn = MiniJumpOn;
    }

    bool GetGround()   
    {
        return m_Ground;
    }

    bool GetJump()
    {
        return m_Jump;
    }

    bool GetFalling()
    {
        return m_FallingStart;
    }

    bool GetSideWallCheck()
    {
        return m_SideWallCollision;
    }

    bool GetMiniJumpOn()
    {
        return m_MiniJumpOn;
    }

public:
    //�÷��̾� ����
    void Jump()
    {
        ++m_JumpCount;
         
        if (m_JumpCount == 2)
            MiniJump(); // return;

        else if (m_JumpCount == 1)
        {
            m_MiniJumpOn = false;

            SetJumpVelocity(60.f);
            m_FallTime = 0.f;
            m_FallStartY = m_Pos.y;
        }

        if (!m_Jump)
        {
            m_MiniJumpOn = false;

            SetJumpVelocity(45.f);
            m_Jump = true;
            m_Ground = false;
            m_PhysicsSimulate = true;

            m_FallTime = 0.f;
            m_FallStartY = m_Pos.y;
        }
    }

    //�÷��̾� ����
    void MiniJump()
    {
        m_MiniJumpOn = true;

        SetJumpVelocity(60.f);
        //m_JumpCount = 1; // �̰�Ǯ�� ���� ����.
        m_FallTime = 0.f;
        m_FallStartY = m_Pos.y;
    }

    void ObjectJump()
    {
        m_Jump = true;
        m_Ground = false;
        m_PhysicsSimulate = true;

        m_FallTime = 0.f;
        m_FallStartY = m_Pos.y;
    }

    //������ �߶�
    void FallingStartOn(float PosY)
    {
        m_FallingStart = true;
        m_FallStartY = PosY;
        m_JumpVelocity = 0.f;
    }


public:
    class CSceneComponent* GetUpdateComponent() const
    {
        return m_UpdateComponent;
    }

protected:
    Vector2		m_PrevPos;
    Vector2		m_Move;
    Vector2		m_Pos;
    Vector2		m_Size;
    Vector2		m_Pivot;
    bool		m_PhysicsSimulate;
    bool		m_Ground;	// ���� ��� �ִ� �������� �ƴ���
    float		m_GravityAccel;
    float		m_FallTime;
    float		m_FallStartY;
    bool		m_Jump;
    float		m_JumpVelocity;
    bool		m_SideWallCheck;
    bool		m_Start;
    int			m_JumpCount;
    bool        m_MiniJumpOn;

    bool      m_FallingStart; //��ü�� �������� �����Ҷ� true
    bool      m_SideWallCollision;//�� üũ,


    CSharedPtr<class CCollider2D> m_Body;

public:
    virtual void Destroy();
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CWallComponent* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);


private:
    void CheckMoveRight();
    void CheckMoveLeft();

};

