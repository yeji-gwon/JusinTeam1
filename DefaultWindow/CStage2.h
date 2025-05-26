#pragma once
#include "CScene.h"

class CStage2 :
    public CScene
{
public:
    CStage2();
    virtual ~CStage2();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};