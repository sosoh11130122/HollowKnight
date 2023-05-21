
#pragma once

#include "GameObject/GameObject.h"
#include "Player2D.h"

class CWallObj :
    public CGameObject
{
	friend class CScene;

protected:
	CWallObj();
	CWallObj(const CWallObj& Obj);
	virtual ~CWallObj();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CColliderBox2D>	m_Body;
	CPlayer2D* m_Player;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CWallObj* Clone()    const;

	//void CollisionBegin(CCollider* Src, CCollider* Dest);//1129
	void CollisionBegin(const CollisionResult& result);
	void CollisionEnd(const CollisionResult& result);

};

