#pragma once
#include "CObj.h"
#include "CBow.h"

class CArcher :
    public CObj
{
public:
    CArcher();
    virtual ~CArcher();

public:
    void Set_Bow(CObj* _pBow) { m_pBow = _pBow; }
    void Set_VecArrow(vector<CObj*>* _pVecArrow) { m_pVecArrow = _pVecArrow; }

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    void    Key_Input();

private:
    D3DXVECTOR3     m_vBodyPoint[4];
    D3DXVECTOR3     m_vOriginBodyPoint[4];

    D3DXVECTOR3     m_vUpperArmPoint[4];
    D3DXVECTOR3     m_vOriginUpperArmPoint[4];

    D3DXVECTOR3     m_vForeArmPoint[4];
    D3DXVECTOR3     m_vOriginForeArmPoint[4];

    CObj* m_pBow;
    vector<CObj*>* m_pVecArrow;

    bool            m_bArrow;
};