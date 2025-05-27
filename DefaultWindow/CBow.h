#pragma once
#include "CObj.h"

class CBow :
    public CObj
{
public:
    CBow();
    virtual ~CBow();

public:
    void Set_Pos(D3DXVECTOR3 _vPos) { m_tInfo.vPos = _vPos; }
    void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
    void Set_Offset(float _fOffset) { m_fOffset = _fOffset; }

    float   Get_Offset() { return m_fOffset; }

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    float               m_fOffset;

    D3DXVECTOR3         m_vPoint[3];
    D3DXVECTOR3         m_vOriginPoint[3];

    struct tagPolygon   m_tPolygon;
    struct tagPolygon   m_tOriginPolygon;
};