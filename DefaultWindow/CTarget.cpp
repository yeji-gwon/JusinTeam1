#include "pch.h"
#include "CTarget.h"

CTarget::CTarget()
{
    ZeroMemory(&m_bColor, sizeof(m_bColor));
}

CTarget::~CTarget()
{
    Release();
}

void CTarget::Initialize()
{
    m_tInfo.vPos = { 100.f, 400.f, 0.f };

    m_tOriginPolygon.m_vCenter = { 0.f, 0.f, 0.f };
    m_tOriginPolygon.m_vScale = { 30.f, 60.f, 1.f };
    int iSize = 36;
    m_tOriginPolygon.Set_Size(iSize);
    for (int i = 0; i < sizeof(m_tPolygon) / sizeof(tagPolygon); ++i)
        m_tPolygon[i].Set_Size(iSize);
    m_tOriginPolygon.SyncToWorld(m_tPolygon[0]);

    m_vRange[0] = { m_tInfo.vPos.x - m_tOriginPolygon.m_vScale.x, m_tInfo.vPos.y - m_tOriginPolygon.m_vScale.y, 0.f };
    m_vRange[1] = { m_tInfo.vPos.x, m_tInfo.vPos.y + m_tOriginPolygon.m_vScale.y, 0.f };
    
    BYTE temp[3][3] = {
        { 252, 212, 63 },
        { 216, 50, 39 },
        { 0, 157, 202 }
    };

    memcpy(m_bColor, temp, sizeof(m_bColor));
}

int CTarget::Update()
{
    D3DXMATRIX  matScale;
    D3DXMATRIX  matRotZ;
    D3DXMATRIX  matTrans;

    /// Target
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
    
    for (int i = 0; i < sizeof(m_tPolygon) / sizeof(tagPolygon); ++i)
    {
        D3DXMatrixScaling(&matScale, m_tOriginPolygon.m_vScale.x * (i + 1) * 0.3f, m_tOriginPolygon.m_vScale.y * (i + 1) * 0.3f, m_tOriginPolygon.m_vScale.z);
        
        m_tInfo.matWorld = matScale * matRotZ * matTrans;

        for (int j = 0; j < m_tOriginPolygon.Size(); ++j)
        {             
            D3DXVec3TransformCoord(&m_tPolygon[i].m_vPoints[j], &m_tOriginPolygon.m_vPoints[j], &m_tInfo.matWorld);
        }
    } 

	return 0;
}

void CTarget::Late_Update()
{
}

void CTarget::Render(HDC hDC)
{
    /// Target 
    for (int i = sizeof(m_tPolygon) / sizeof(tagPolygon) - 1; i >= 0; --i)
    {
        HBRUSH  hBrushBlue = CreateSolidBrush(RGB(m_bColor[i][0], m_bColor[i][1], m_bColor[i][2]));
        HBRUSH  hOldBrush = (HBRUSH)SelectObject(hDC, hBrushBlue);
        m_tPolygon[i].DrawPolygon(hDC);
        SelectObject(hDC, hOldBrush);
        DeleteObject(hBrushBlue);
    }
}

void CTarget::Release()
{
}