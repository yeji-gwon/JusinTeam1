#pragma once
#include "CScene.h"
#include "CObj.h"
#include "CHead.h"

class CStage4 :
    public CScene
{
public:
    CStage4();
    virtual ~CStage4();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    void    Spin_Sun();

private:
    CObj*   m_pPlayer;
    CObj*   m_pGameSystem;

    Poly<tagPolygon> Ground;
    Poly<tagPolygon> Back;
    Poly<tagPolygon> Sun;

    D3DXVECTOR3     m_vSunOrigin[8][4];
    D3DXVECTOR3     m_vSunPoint[4];


    D3DXMATRIX      m_SunMatrix[8];
    D3DXMATRIX      m_SunParent;

    float           m_fSpin;
};