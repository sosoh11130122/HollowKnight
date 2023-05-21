
#pragma once

#include "GameObject/GameObject.h"

class CBackObj :
    public CGameObject
{
	friend class CScene;

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;

protected:
	CBackObj();
	CBackObj(const CBackObj& Obj);
	virtual ~CBackObj();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
};

