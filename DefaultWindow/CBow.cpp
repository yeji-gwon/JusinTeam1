#include "pch.h"
#include "CBow.h"
#include "CKeyMgr.h"
#include "CArrow.h"

CBow::CBow()    :   m_fOffset(0.f), m_pVecArrow(nullptr), m_bReload(false), m_bFire(false)
{
}

CBow::~CBow()
{
    Release();
}

void CBow::Initialize()
{
    m_vOriginPoint[0] = { 0.f, -1.f, 0.f };
    m_vOriginPoint[1] = { 0.f, 0.f, 0.f };
    m_vOriginPoint[2] = { 0.f, 1.f, 0.f };

    m_tOriginPolygon.m_vCenter = { 0.f, 0.f, 0.f };
    m_tOriginPolygon.m_vScale = { 30.f, 60.f, 1.f };
    m_tOriginPolygon.Set_Size(36);
    m_tPolygon.Set_Size(36);
    m_tOriginPolygon.SyncToWorld(m_tPolygon);
}

int CBow::Update()
{
    D3DXMATRIX  matScale;
    D3DXMATRIX  matRotZ;
    D3DXMATRIX  matTrans;


    /// Bow
    D3DXMatrixScaling(&matScale, m_tOriginPolygon.m_vScale.x, m_tOriginPolygon.m_vScale.y , m_tOriginPolygon.m_vScale.z);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    for(int i = 0; i < m_tOriginPolygon.Size(); ++i)
        D3DXVec3TransformCoord(&m_tPolygon.m_vPoints[i], &m_tOriginPolygon.m_vPoints[i], &m_tInfo.matWorld);


    /// Bow String - 0, 2
    D3DXMatrixScaling(&matScale, m_tOriginPolygon.m_vScale.x, m_tOriginPolygon.m_vScale.y, m_tOriginPolygon.m_vScale.z);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    D3DXVec3TransformCoord(&m_vPoint[0], &m_vOriginPoint[0], &m_tInfo.matWorld);
    D3DXVec3TransformCoord(&m_vPoint[2], &m_vOriginPoint[2], &m_tInfo.matWorld);


    /// Bow String - 1
    D3DXMatrixScaling(&matScale, m_tOriginPolygon.m_vScale.x, m_tOriginPolygon.m_vScale.y, m_tOriginPolygon.m_vScale.z);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + m_fOffset * cosf(D3DXToRadian(m_fAngle)), m_tInfo.vPos.y + m_fOffset * sinf(D3DXToRadian(m_fAngle)), m_tInfo.vPos.z);
    
    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    D3DXVec3TransformCoord(&m_vPoint[1], &m_vOriginPoint[1], &m_tInfo.matWorld);


    /// Limit Offset
    if (m_fOffset >= m_tOriginPolygon.m_vScale.x)
        m_fOffset = m_tOriginPolygon.m_vScale.x;

    if (!m_bFire)
    {
        if (!m_bReload)
        {
            CObj* pArrow = new CArrow;
            pArrow->Initialize();
            m_pVecArrow->push_back(pArrow);

            m_bReload = true;
        }

        D3DXVECTOR3 vPos = { m_tInfo.vPos.x + m_fOffset * cosf(D3DXToRadian(m_fAngle)), m_tInfo.vPos.y + m_fOffset * sinf(D3DXToRadian(m_fAngle)), m_tInfo.vPos.z };
        m_pVecArrow->back()->Set_Pos(vPos);
        m_pVecArrow->back()->Set_Angle(m_fAngle);
        m_pVecArrow->back()->Set_Speed(m_fOffset * 0.7f);
    } 
    else
    { 
        dynamic_cast<CArrow*>(m_pVecArrow->back())->Set_Fire();
        m_bReload = false;
        m_bFire = false;
    }


    return 0;
}

void CBow::Late_Update()
{
}

void CBow::Render(HDC hDC)
{
    /// Bow
    m_tPolygon.DrawPolyLine(hDC, 8, 29);
    
    /// Bow String
    MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
    for (int i = 0; i < 3; ++i)
        LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);


    /// 
    TCHAR   szText[32];
    swprintf_s(szText, (m_bFire) ? L"True" : L"False");
    TextOut(hDC, 100, 100, szText, lstrlen(szText));
    swprintf_s(szText, (m_bReload) ? L"True" : L"False");
    TextOut(hDC, 100, 120, szText, lstrlen(szText));
    swprintf_s(szText, L"%d", m_pVecArrow->size());
    TextOut(hDC, 100, 140, szText, lstrlen(szText));
}

void CBow::Release()
{
}