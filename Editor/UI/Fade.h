#pragma once

#include "UI/UIWindow.h"

class CFade :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CFade();
	CFade(const CFade& Window);
	virtual ~CFade();

protected:
	CSharedPtr<class CUIImage>	m_Fade;
	float m_Opacity;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CFade* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

