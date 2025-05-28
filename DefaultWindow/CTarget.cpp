#include "pch.h"
#include "CTarget.h"

CTarget::CTarget()
{
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
    m_tOriginPolygon.Set_Size(36);
    m_tPolygon.Set_Size(36);
    m_tOriginPolygon.SyncToWorld(m_tPolygon);

    m_vRange[0] = { m_tInfo.vPos.x, m_tInfo.vPos.y - m_tOriginPolygon.m_vScale.y, 0.f };
    m_vRange[1] = { m_tInfo.vPos.x, m_tInfo.vPos.y + m_tOriginPolygon.m_vScale.y, 0.f };
}

int CTarget::Update()
{
    D3DXMATRIX  matScale;
    D3DXMATRIX  matRotZ;
    D3DXMATRIX  matTrans;

    /// Target
    D3DXMatrixScaling(&matScale, m_tOriginPolygon.m_vScale.x, m_tOriginPolygon.m_vScale.y, m_tOriginPolygon.m_vScale.z);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    for (int i = 0; i < m_tOriginPolygon.Size(); ++i)
        D3DXVec3TransformCoord(&m_tPolygon.m_vPoints[i], &m_tOriginPolygon.m_vPoints[i], &m_tInfo.matWorld);

	return 0;
}

void CTarget::Late_Update()
{
}

void CTarget::Render(HDC hDC)
{
    /// Target
    m_tPolygon.DrawPolyLine(hDC);

    MoveToEx(hDC, 100, 0, nullptr);
    LineTo(hDC, 100, 600);
}

void CTarget::Release()
{
}