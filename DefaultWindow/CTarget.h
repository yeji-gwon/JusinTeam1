#pragma once
#include "CObj.h"

class CTarget :
    public CObj
{
public:
    CTarget();
    virtual ~CTarget();

public:
    int             const Get_Size() { return sizeof(m_tPolygon) / sizeof(tagPolygon); }
    D3DXVECTOR3     const Get_RangeMin() { return m_vRange[0]; }
    D3DXVECTOR3     const Get_RangeMax() { return m_vRange[1]; }

public:
    void                Initialize() override;
    int                 Update() override;
    void                Late_Update() override;
    void                Render(HDC hDC) override;
    void                Release() override;

private:
    tagPolygon          m_tPolygon[3];
    tagPolygon          m_tOriginPolygon;

    D3DXVECTOR3         m_vRange[2];

    BYTE                m_bColor[3][3];
};