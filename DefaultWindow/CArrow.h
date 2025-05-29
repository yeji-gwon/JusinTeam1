#pragma once
#include "CObj.h"

class CArrow :
    public CObj
{
public:
    CArrow();
    virtual ~CArrow();

public:
    void            Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
    void            Set_Fire() { m_bFire = true; }
    void            Set_InActive() { m_bActive = false; }

    bool            Check_Active() { return m_bActive; }
    bool            Check_Hit() { return m_bHit; } 
    int             Get_Point() { return m_iPoint; }

public:
    void            Initialize() override;
    int             Update() override;
    void            Late_Update() override;
    void            Render(HDC hDC) override;
    void            Release() override;

private:
    D3DXVECTOR3     m_vPoint[2];
    D3DXVECTOR3     m_vOriginPoint[2];
    D3DXVECTOR3     m_vStartPos;

    bool            m_bFire;
    float           m_fShootAngle;
    float           m_fTime;

    CObj*           m_pTarget;

    bool            m_bHit;
    bool            m_bActive;

    int             m_iPoint;
};