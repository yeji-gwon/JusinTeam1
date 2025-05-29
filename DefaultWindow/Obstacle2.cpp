#include "pch.h"
#include "Obstacle2.h"

Obstacle2::Obstacle2(int _i)
{
	iSeed = _i;
}

Obstacle2::~Obstacle2()
{
	Release();
}

void Obstacle2::Initialize()
{
	m_tInfo.vPos.x = WINCX;
	m_tInfo.vDir = { -1.f, 0.f, 0.f };
}

int Obstacle2::Update()
{
	if (m_bDead)	return 1;
	m_tInfo.vPos.x += m_tInfo.vDir.x * 2.f * iSeed;
	if (m_tInfo.vPos.x <= 0.f)
	{
		return 1;
	}

	return 0;
}

void Obstacle2::Late_Update()
{
	
}

void Obstacle2::Render(HDC hDC)
{
	Rectangle(hDC, m_tInfo.vPos.x - 10 * iSeed, 0, m_tInfo.vPos.x + 10 * iSeed, WINCY);
}


void Obstacle2::Release()
{
}
