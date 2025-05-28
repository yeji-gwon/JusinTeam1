#pragma once
#include "CObj.h"

class CArcher :
    public CObj
{
public:
    CArcher();
    virtual ~CArcher();

public:
    void            Set_Bow(CObj* pBow) { m_pBow = pBow; }
    void            Add_Point(int iPoint) { m_iPoint += iPoint; }

public:
    void            Initialize() override;
    int             Update() override;
    void            Late_Update() override;
    void            Render(HDC hDC) override;
    void            Release() override;

private:
    void            Key_Input();

private:
    D3DXVECTOR3     m_vBodyPoint[4];
    D3DXVECTOR3     m_vOriginBodyPoint[4];

    D3DXVECTOR3     m_vUpperArmPoint[4];
    D3DXVECTOR3     m_vOriginUpperArmPoint[4];

    D3DXVECTOR3     m_vForeArmPoint[4];
    D3DXVECTOR3     m_vOriginForeArmPoint[4];

    D3DXVECTOR3     m_vLegPoint[7];
    D3DXVECTOR3     m_vOriginLegPoint[7];

    CObj*           m_pBow;

    int             m_iMaxArrow;
    int             m_iArrow;

    int             m_iPoint;
};