#pragma once

#include "UI\UIWindow.h"

class CSecondSceneUI	:

public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CSecondSceneUI();
	CSecondSceneUI(const CSecondSceneUI& Window);
	virtual ~CSecondSceneUI();

protected:
	CSharedPtr<class CUIButton>	m_Button;
	CSharedPtr<class CUIText>	m_Title;
	CSharedPtr<class CUIProgressBar>	m_ProgressBar;
	CSharedPtr<class CUINumber>	m_Number;

private:
	CSharedPtr<class CUIImage>	m_Back;
	CSharedPtr<class CBackObj>	m_BackObj;
	//CSharedPtr<class CUIImage>	m_HP;
	CSharedPtr<class CPlayer2D>	m_Player;

public:
	CSharedPtr<class CUIImage>	m_HP;
	CSharedPtr<class CUIImage>	m_HPFront;
	CSharedPtr<class CUIImage>	m_HPBack;
	CSharedPtr<class CUIImage>	m_Life;


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CSecondSceneUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	
private:
	void StartButtonClick();
};

