#pragma once

#include "Scene\SceneInfo.h"

class CSecondSceneInfo  :
    public CSceneInfo
{
public:
    CSecondSceneInfo();
    ~CSecondSceneInfo();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};


