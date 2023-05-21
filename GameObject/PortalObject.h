#pragma once

#include "GameObject\GameObject.h"

class CPortalObject :
    public CGameObject
{
	friend class CScene;

protected:
	CPortalObject();
	CPortalObject(const CPortalObject& Obj);
	virtual ~CPortalObject();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CColliderBox2D>	m_Body;
	CPlayer2D* m_Player;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CPortalObject* Clone()    const;
	void Scene1CollisionBegin(const CollisionResult& result);
	void Scene1CollisionEnd(const CollisionResult& result);
	void Scene2CollisionBegin(const CollisionResult& result);
	void Scene2CollisionEnd(const CollisionResult& result);
};

