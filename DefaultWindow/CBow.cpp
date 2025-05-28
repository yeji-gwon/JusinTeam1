#include "pch.h"
#include "CBow.h"
#include "CKeyMgr.h"

CBow::CBow()    :   m_fOffset(0.f)
{
}

CBow::~CBow()
{
    Release();
}

void CBow::Initialize()
{
    m_vOriginPoint[0] = { 0.f, -120.f, 0.f };
    m_vOriginPoint[1] = { 0.f, 0.f, 0.f };
    m_vOriginPoint[2] = { 0.f, 120.f, 0.f };

    m_tOriginPolygon.m_vCenter = { 0.f, 0.f, 0.f };
    m_tOriginPolygon.m_vScale = { 60.f, 120.f, 1.f };
    m_tOriginPolygon.Set_Size(36);
    m_tPolygon.Set_Size(36);
    m_tOriginPolygon.SyncToWorld(m_tPolygon);
}

int CBow::Update()
{
    D3DXMATRIX  matScale;
    D3DXMATRIX  matRotZ;
    D3DXMATRIX  matTrans;

    D3DXMatrixScaling(&matScale, m_tOriginPolygon.m_vScale.x, m_tOriginPolygon.m_vScale.y , m_tOriginPolygon.m_vScale.z);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    for(int i = 0; i < m_tOriginPolygon.Size(); ++i)
        D3DXVec3TransformCoord(&m_tPolygon.m_vPoints[i], &m_tOriginPolygon.m_vPoints[i], &m_tInfo.matWorld);


    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    D3DXVec3TransformCoord(&m_vPoint[0], &m_vOriginPoint[0], &m_tInfo.matWorld);
    D3DXVec3TransformCoord(&m_vPoint[2], &m_vOriginPoint[2], &m_tInfo.matWorld);

    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + m_fOffset * cosf(D3DXToRadian(m_fAngle)), m_tInfo.vPos.y + m_fOffset * sinf(D3DXToRadian(m_fAngle)), m_tInfo.vPos.z);
    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    D3DXVec3TransformCoord(&m_vPoint[1], &m_vOriginPoint[1], &m_tInfo.matWorld);

    //for (int i = 0; i < 3; ++i)
    //    D3DXVec3TransformCoord(&m_vPoint[i], &m_vOriginPoint[i], &m_tInfo.matWorld);

    //if (CKeyMgr::Get_Instance()->Key_Hold(VK_SPACE))
    //    m_fOffset++;
    //else
    //    m_fOffset = 0.f;

    if (m_fOffset >= 100.f)
        m_fOffset = 100.f;

    return 0;
}

void CBow::Late_Update()
{
}

void CBow::Render(HDC hDC)
{
    m_tPolygon.DrawPolyLine(hDC, 8, 29);
    
    MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
    for (int i = 0; i < 3; ++i)
        LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);
}

void CBow::Release()
{
}