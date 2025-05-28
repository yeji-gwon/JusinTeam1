#pragma once
#include "CObj.h"

class CArrow :
    public CObj
{
public:
    CArrow();
    virtual ~CArrow();

public:
    void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    D3DXVECTOR3     m_vPoint[2];
    D3DXVECTOR3     m_vOriginPoint[2];
};