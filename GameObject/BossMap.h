#pragma once

#include "GameObject/GameObject.h"

class CBossMap :
	public CGameObject
{
	friend class CScene;

protected:
	CBossMap();
	CBossMap(const CBossMap& Obj);
	virtual ~CBossMap();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CMaterial>	m_Material;
	CSharedPtr<class CAnimation2D> m_Animation;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBossMap* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

};

