#include "pch.h"
#include "CArrow.h"
#include "CTarget.h"

CArrow::CArrow()	: m_bFire(false), m_fShootAngle(0.f), m_fTime(0.f), m_pTarget(nullptr), m_bHit(false), m_bActive(false), m_iPoint(0)
{
	ZeroMemory(&m_vPoint, sizeof(m_vPoint));
	ZeroMemory(&m_vOriginPoint, sizeof(m_vOriginPoint));
	ZeroMemory(&m_vStartPos, sizeof(m_vStartPos));
}

CArrow::~CArrow()
{
	Release();
}

void CArrow::Initialize()
{
	m_vOriginPoint[0] = { -60.f, 0.f, 0.f };
	m_vOriginPoint[1] = { 0.f, 0.f, 0.f };

	m_bActive = true;
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
		m_vStartPos = m_tInfo.vPos;
		m_fShootAngle = m_fAngle;
		m_fTime = 0.f;
	}
	else
	{ 
		m_tInfo.vPos.y -= m_fSpeed * sinf(D3DXToRadian(m_fShootAngle)) * m_fTime - (9.8f * m_fTime * m_fTime * 0.5f);
		m_tInfo.vPos.x -= m_fSpeed * cosf(D3DXToRadian(m_fShootAngle)) * m_fTime;

		m_fTime += 0.2f;

		m_fAngle -= 5.f * sinf(D3DXToRadian(m_fShootAngle));

		float fX = dynamic_cast<CTarget*>(m_pTarget)->Get_RangeMin().x;
		float fMinY = dynamic_cast<CTarget*>(m_pTarget)->Get_RangeMin().y;
		float fMaxY = dynamic_cast<CTarget*>(m_pTarget)->Get_RangeMax().y;

		if (m_tInfo.vPos.x - 60.f * cosf(D3DXToRadian(m_fAngle)) <= fX &&
			m_tInfo.vPos.y - 60.f * sinf(D3DXToRadian(m_fAngle)) >= fMinY &&
			m_tInfo.vPos.y - 60.f * sinf(D3DXToRadian(m_fAngle)) <= fMaxY)
		{
			m_tInfo.vPos.x = fX + 60.f * cosf(D3DXToRadian(m_fAngle));
			m_bFire = false;
			m_bHit = true;

			if (m_tInfo.vPos.y - 60.f * sinf(D3DXToRadian(m_fAngle)) >= fMinY + 40.f &&
				m_tInfo.vPos.y - 60.f * sinf(D3DXToRadian(m_fAngle)) <= fMaxY - 40.f)
				m_iPoint = 3;
			else if (m_tInfo.vPos.y - 60.f * sinf(D3DXToRadian(m_fAngle)) >= fMinY + 20.f &&
				m_tInfo.vPos.y - 60.f * sinf(D3DXToRadian(m_fAngle)) <= fMaxY - 20.f)
				m_iPoint = 2;
			else
				m_iPoint = 1;
			return 0;
		}
		if (m_tInfo.vPos.y - 60.f * sinf(D3DXToRadian(m_fAngle)) >= 500.f)
		{
			m_tInfo.vPos.y = 500.f + 60.f * sinf(D3DXToRadian(m_fAngle));
			m_bFire = false;
			return 0;
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

	//TCHAR szText[32];
	//swprintf_s(szText, L"%f", m_vPoint[0].x);
	//TextOut(hDC, 700, 100, szText, lstrlen(szText));
	//swprintf_s(szText, L"%f", m_vPoint[0].y);
	//TextOut(hDC, 700, 120, szText, lstrlen(szText));
	//swprintf_s(szText, L"%f", m_vPoint[1].x);
	//TextOut(hDC, 700, 140, szText, lstrlen(szText));
	//swprintf_s(szText, L"%f", m_vPoint[1].y);
	//TextOut(hDC, 700, 160, szText, lstrlen(szText));
	//swprintf_s(szText, L"%f", m_tInfo.vPos.x);
	//TextOut(hDC, 700, 80, szText, lstrlen(szText));
}

void CArrow::Release()
{
}