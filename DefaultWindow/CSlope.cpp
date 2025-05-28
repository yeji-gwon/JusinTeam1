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

	float delta = CTimeMgr::Get_Instance()->Get_Delta() * 3.f; // 속도 조절용
	ChangeDir(delta);

	m_Slope.Update();
	bool collision = m_Slope.CheckCollision(*m_pTarget->Get_Rect(), m_pTarget->Get_LandinfPt(), m_pTarget->Get_AnglePt());
	m_pTarget->Set_Landed(collision);

	m_Slope.vPos.x -= 250 * delta;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP)) {
		m_Slope.vScale.x += delta*0.3;
		m_Slope.vScale.y += delta*0.3;
		m_Slope.vScale.z += delta*0.3;
	}
	if (CKeyMgr::Get_Instance()->Key_Tap(VK_DOWN)) {
		m_Slope.vScale.x -= delta * 0.3;
		m_Slope.vScale.y -= delta * 0.3;
		m_Slope.vScale.z -= delta * 0.3;
	}
	return 0;
}

void CSlope::Late_Update()
{
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
