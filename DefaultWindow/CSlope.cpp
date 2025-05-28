#include "pch.h"
#include "CSlope.h"
#include "CKeyMgr.h"
#include "CSki.h"
using namespace Boogi;

CSlope::CSlope()
	:m_pTarget(nullptr)
{
}

CSlope::~CSlope()
{
}

void CSlope::Initialize()
{
	m_Slope.Initialize(150, 8.f);
}

int CSlope::Update()
{

	float delta = CTimeMgr::Get_Instance()->Get_Delta(); // 속도 조절용
	ChangeDir(delta);

	m_Slope.Update();

	m_Slope.vPos.x -= 50*55 * delta;
	
	return 0;
}

void CSlope::Late_Update()
{
	bool collision = m_Slope.CheckCollision(*m_pTarget->Get_Rect(), m_pTarget->Get_LandinfPt(), m_pTarget->Get_AnglePt());
	m_pTarget->Set_Landed(collision);
}

void CSlope::Render(HDC hDC)
{
	m_Slope.Render(hDC);
}

void CSlope::Release()
{
}

void CSlope::Set_Target(CSki* target)
{
	m_pTarget = target;
}
