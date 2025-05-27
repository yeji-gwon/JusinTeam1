#pragma once
#include "CScene.h"

class CObj;

class CStage3 :
    public CScene
{
public:
    CStage3();
    virtual ~CStage3();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    CObj* m_pHandle;
    CObj* m_pDriver;
    CObj* m_pRoad;
};