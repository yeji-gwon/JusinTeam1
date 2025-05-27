#include "pch.h"
#include "CArrow.h"

CArrow::CArrow()
{
	ZeroMemory(&m_vPoint, sizeof(m_vPoint));
	ZeroMemory(&m_vOriginPoint, sizeof(m_vOriginPoint));
}

CArrow::~CArrow()
{
	Release();
}

void CArrow::Initialize()
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 1.f, 1.f, 1.f };

	m_vOriginPoint[0] = { -50.f, 0.f, 0.f };
	m_vOriginPoint[1] = {  50.f, 0.f, 0.f };
}

int CArrow::Update()
{
	D3DXMATRIX	matScale;
	D3DXMATRIX	matRotZ;
	D3DXMATRIX	matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 2; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vOriginPoint[i], &m_tInfo.matWorld);

	return 0;
}

void CArrow::Late_Update()
{
}

void CArrow::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
	LineTo(hDC, (int)m_vPoint[1].x, (int)m_vPoint[1].y);
}

void CArrow::Release()
{
}