#include "pch.h"
#include "CMonster.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_fSpeed = 2.f;
}

void CMonster::Update()
{
	m_tInfo.vDir = m_pPlayer->Get_Info().vPos - m_tInfo.vPos;
	 
	float	fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;


	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
}

void CMonster::Render(HDC hDC)
{
	Ellipse(hDC,
		long(m_tInfo.vPos.x - 50.f),
		long(m_tInfo.vPos.y - 50.f),
		long(m_tInfo.vPos.x + 50.f),
		long(m_tInfo.vPos.y + 50.f));
}

void CMonster::Release()
{
}
