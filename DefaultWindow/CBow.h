#pragma once
#include "CObj.h"

class CBow :
    public CObj
{
public:
    CBow();
    virtual ~CBow();

public:
    void                Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
    void                Set_VecArrow(vector<CObj*>* pVecArrow) { m_pVecArrow = pVecArrow; }
    void                Set_Offset(float fOffset) { m_fOffset = fOffset; }
    void                Add_Offset(float fOffset) { m_fOffset += fOffset; }
     
    void                Set_Fire() { m_bFire = true; }

public:
    void                Initialize() override;
    int                 Update() override;
    void                Late_Update() override;
    void                Render(HDC hDC) override;
    void                Release() override;

private:
    float               m_fOffset;

    D3DXVECTOR3         m_vPoint[3];
    D3DXVECTOR3         m_vOriginPoint[3];

    tagPolygon          m_tPolygon;
    tagPolygon          m_tOriginPolygon;

    vector<CObj*>*      m_pVecArrow;

    bool                m_bReload;
    bool                m_bFire;

    CObj*               m_pTarget;
};