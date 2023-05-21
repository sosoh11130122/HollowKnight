#pragma once

#include "Scene\SceneInfo.h"

class CFirstSceneInfo :
    public CSceneInfo
{
public:
    CFirstSceneInfo();
    ~CFirstSceneInfo();

private:
    CSharedPtr<class CUIImage>	m_Back;
    CSharedPtr<class CGrimm>	m_Grimm;


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

