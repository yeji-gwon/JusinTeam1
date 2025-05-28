#include "pch.h"
#include "CArrow.h"

CArrow::CArrow()	: m_bFire(false), m_fShootAngle(0.f), m_fTime(0.f)
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
	m_vOriginPoint[0] = { -60.f, 0.f, 0.f };
	m_vOriginPoint[1] = { 0.f, 0.f, 0.f };
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

	if (!m_bFire)
	{
		m_fShootAngle = m_fAngle;
		m_fTime = 0.f;
	
	}
	else
	{
		if (m_tInfo.vPos.y - 60.f * sinf(D3DXToRadian(m_fAngle)) >= 500.f)
		{
			m_tInfo.vPos.y = 500.f + 60.f * sinf(D3DXToRadian(m_fAngle));
			m_bFire = false;
			//m_tInfo.vPos.y = 500.f; 
		}
		else
		{
			m_tInfo.vPos.y -= m_fSpeed * sinf(D3DXToRadian(m_fShootAngle)) * m_fTime - (9.8f * m_fTime * m_fTime * 0.5f);
			m_tInfo.vPos.x -= m_fSpeed * cosf(D3DXToRadian(m_fShootAngle)) * m_fTime;
			m_fTime += 0.2f;
	
			m_fAngle -= 5.f * sinf(D3DXToRadian(m_fShootAngle)); 
		}
	}

	return 0;
}

void CArrow::Late_Update()
{
}

void CArrow::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
	LineTo(hDC, (int)m_vPoint[1].x, (int)m_vPoint[1].y);

	Ellipse(hDC, (int)m_vPoint[0].x - 5, (int)m_vPoint[0].y - 5, (int)m_vPoint[0].x + 5, (int)m_vPoint[0].y + 5);
}

void CArrow::Release()
{
}