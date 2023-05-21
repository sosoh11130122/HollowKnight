#pragma once

#include "Scene\SceneInfo.h"

class CBossMapSceneInfo :
    public CSceneInfo
{
public:
    CBossMapSceneInfo();
    ~CBossMapSceneInfo();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

