#include "pch.h"
#include "CSki.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"


using namespace Boogi;

CSki::CSki()
	:m_fArmDir(-1.f),m_bLanded(false), fNow_Angle(0.f), fPrev_Angle(0.f)
{
}

CSki::~CSki()
{
}

void CSki::Initialize()
{
	m_vCenter = { 200.f,200.f,0.f };
	m_vRotate = { 0,0,0 };
	m_vScale = { 1.f,1.f,1.f };
	m_pBody.Set_Scale({ 1.f, 1.f, 1.f });
	m_pBody.Set_Rotate({ 0.f, 0.f, 0.f });
	m_pBody.Set_Offset(10.f, 10.f, 20.f, 20.f);

	m_pRight.Set_Parent(m_pRightLeg.Get_World());
	m_pLeft.Set_Parent(m_pLeftLeg.Get_World());
	m_Head.Set_Parent(m_pBody.Get_World());
	m_pLeftArm.Set_Parent(m_pBody.Get_World());
	m_pRightArm.Set_Parent(m_pBody.Get_World());
	m_pLeftLeg.Set_Parent(m_pBody.Get_World());
	m_pRightLeg.Set_Parent(m_pBody.Get_World());

	m_Head.Set_Center({ 0.f,- 30.f, 0.f });
	m_Head.Set_Radius(10);
	m_Head.Set_Size(20);

	m_pLeftArm.Set_Scale({ 1.f, 1.f, 1.f });
	m_pLeftArm.Set_Rotate({ 0.f, 0.f, 0.f });
	m_pLeftArm.Set_Offset(5.f, 5.f, 30.f, 10.f);
	m_pLeftArm.Set_Center({0.f,5.f, 0.f });
	m_pLeftArm.Set_Pivot({ 0.f, - 15, 0.f });

	m_pRightArm.Set_Scale({ 1.f, 1.f, 1.f });
	m_pRightArm.Set_Rotate({ 0.f, 0.f, 0.f });
	m_pRightArm.Set_Offset(5.f, 5.f, 30.f, 10.f);
	m_pRightArm.Set_Center({ 0.f,5.f, 0.f });
	m_pRightArm.Set_Pivot({ 0,-15, 0.f });

	m_pRightLeg.Set_Center({ 0.f,45.f, 0.f });
	m_pRightLeg.Set_Scale({ 1.f, 1.f, 1.f });
	m_pRightLeg.Set_Orbit({ 0.f, 0.f, 10.f });
	m_pRightLeg.Set_Offset(5.f, 5.f, 30.f, 10.f);

	
	m_pRight.Set_Center({ 0.f, 5.f, 0.f });
	m_pRight.Set_Rotate({ 0.f, 0.f, -0.f });
	m_pRight.Set_Scale({ 1.f, 1.f, 1.f });
	m_pRight.Set_Offset(20.f, 35.f, 5.f, 5.f);

	m_pLeftLeg.Set_Center({ 0.f,45.f, 0.f });
	m_pLeftLeg.Set_Scale({ 1.f, 1.f, 1.f });
	m_pLeftLeg.Set_Orbit({ 0.f, 0.f, -10.f });
	m_pLeftLeg.Set_Offset(5.f, 5.f, 30.f, 10.f);

	m_pLeft.Set_Center({ 0.f, 5.f, 0.f });
	m_pLeft.Set_Rotate({ 0.f, 0.f, 0.f });
	m_pLeft.Set_Scale({ 1.f, 1.f, 1.f });
	m_pLeft.Set_Offset(20.f, 35.f, 5.f, 5.f);
}

int CSki::Update()
{
	m_pBody.Set_Center(m_vCenter);
	m_pBody.Compute_Corners();

	m_pLeft.Compute_Corners();
	m_pRight.Compute_Corners();
	m_pLeftArm.Compute_Corners();
	m_pRightArm.Compute_Corners();
	m_pLeftLeg.Compute_Corners();
	m_pRightLeg.Compute_Corners();

	m_pLeft.Update_World();
	m_pRight.Update_World();
	m_pBody.Update_World();
	m_Head.Update_World();
	m_pLeftArm.Update_World();
	m_pRightArm.Update_World();
	m_pLeftLeg.Update_World();
	m_pRightLeg.Update_World();

	//m_pBody.Set_Rotate(m_vRotate);
	m_pBody.Set_Rotate({ 0,0, fNow_Angle});

	m_pBody.Set_Scale(m_vScale);
	Key_Check();
	return 0;
}

void CSki::Late_Update()
{
	m_pLeftArm.Add_Orbit( m_fArmDir);
	m_pRightArm.Add_Orbit(-m_fArmDir);

	if (m_pRightArm.Get_Orbit().z > 60 || m_pRightArm.Get_Orbit().z < -60) {
		m_fArmDir *= -1;
	}

	if (!m_bLanded)
		m_vCenter.y += 1.f;
	else {
		m_vCenter.y = fLandingPoint-20;
	}

	m_SkiFloor = {
		m_pLeft.Get_WorldLB().x,
		m_pRight.Get_WorldLT().y,
		m_pLeft.Get_WorldRB().x,
		m_pRight.Get_WorldLB().y
	};


}
void CSki::Render(HDC hDC)
{
	// 1. 브러시 만들기 (RGB 색상)
	HBRUSH hBrushBody = CreateSolidBrush(RGB(255, 235, 250));    // 빨간색
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrushBody);

	m_pLeftArm.Render(hDC);
	m_pLeftLeg.Render(hDC);
	m_pLeft.Render(hDC);
	
	m_pBody.Render(hDC);
	
	m_pRightArm.Render(hDC);
	m_pRightLeg.Render(hDC);
	m_pRight.Render(hDC);

	m_Head.Render(hDC);

	// 6. 이전 브러시 복원 + 브러시 삭제
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrushBody);

	//Rectangle(hDC,
	//m_SkiFloor.left,
	//m_SkiFloor.top,
	//m_SkiFloor.right,
	//m_SkiFloor.bottom);
	TCHAR szAngle[64];
	_stprintf_s(szAngle, _T("fAngle : %.2f"), fNow_Angle);
	TextOut(hDC, 10, 10, szAngle, lstrlen(szAngle));
}


void CSki::Release()
{
}

void CSki::Key_Check()
{
	float delta = CTimeMgr::Get_Instance()->Get_Delta() * 1.f; // 속도 조절용

	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP)) {
		m_vScale.x += delta*0.3;
		m_vScale.y += delta*0.3;
		m_vScale.z += delta*0.3;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN)) {
		m_vScale.x -= delta *0.3;
		m_vScale.y -= delta *0.3;
		m_vScale.z -= delta *0.3;
	}
}

RECT* CSki::Get_Rect()
{
	return &m_SkiFloor;
}

float* CSki::Get_AnglePt()
{
	return &fNow_Angle;
}

float* CSki::Get_LandinfPt()
{
	return &fLandingPoint;
}

void CSki::Set_Landed(bool landed)
{
	m_bLanded = landed;
}
