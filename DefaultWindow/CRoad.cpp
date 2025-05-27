#include "pch.h"
#include "CRoad.h"

CRoad::CRoad()
{
}

CRoad::~CRoad()
{
}

void CRoad::Initialize()
{
    m_Horizon.fHeight = 35.f;
    m_Horizon.fWidth = WINCX;
    m_Horizon.vCenter = { 400,300,0.f };
    m_Horizon.Set_Points(40);
}

int CRoad::Update()
{
    return 0;
}

void CRoad::Late_Update()
{
}

void CRoad::Render(HDC hDC)
{
    RenderHorizon(hDC);
}

void CRoad::Release()
{
}

void CRoad::RenderHorizon(HDC hDC)
{
    D3DXMATRIX worldMat, scaleMat, transMat;
    D3DXMatrixIdentity(&worldMat);
    D3DXMatrixScaling(&scaleMat, 1.f, 1.f, 1.f);
    D3DXMatrixTranslation(&transMat, m_Horizon.vCenter.x, m_Horizon.vCenter.y, m_Horizon.vCenter.z);

    worldMat = scaleMat * transMat;

    tagLine tmpLine;
    tmpLine.Sync(m_Horizon);
    tmpLine.Set_Points(m_Horizon.Size());

    for (int i = 0; i < m_Horizon.Size(); ++i) {
        D3DXVec3TransformCoord(&tmpLine.Points[i], &m_Horizon.Points[i], &worldMat);
    }
    tmpLine.Render(hDC);
}

