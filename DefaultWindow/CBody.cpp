#include "pch.h"
#include "CBody.h"
#include "CKeyMgr.h"

CBody::CBody()
{
}

CBody::~CBody()
{
}

void CBody::Init_Angle()
{
	m_fLAngle = 0.f;
	m_fRAngle = 0.f;
	m_ePlayerBType = BEND;
	m_ePlayerWType = WEND;
}

void CBody::Initialize()
{
	Body.LPoly.m_vCenter = { 0, 0, 0 };
	Body.LPoly.m_vScale = D3DXVECTOR3(1.f, 1.f, 1.f);
	Body.LPoly.Set_Size(50);

	Arm[0].LPoly = D3DXVECTOR3(-50, -30, 0);
	Arm[1].LPoly = D3DXVECTOR3(50, -30, 0);
	Hand[0].LPoly = D3DXVECTOR3(-50, -15, 0);
	Hand[1].LPoly = D3DXVECTOR3(50, -15, 0);
	Leg[0].LPoly = D3DXVECTOR3(-30, 120, 0);
	Leg[1].LPoly = D3DXVECTOR3(30, 120, 0);

	WhiteFlag.LPoly.m_vCenter = { 0,0,0 };
	WhiteFlag.LPoly.m_vScale = D3DXVECTOR3(40.f, 40.f, 1.f);
	WhiteFlag.LPoly.Set_Size(4);

	BlueFlag.LPoly.m_vCenter = { 0,0,0 };
	BlueFlag.LPoly.m_vScale = D3DXVECTOR3(40.f, 40.f, 1.f);
	BlueFlag.LPoly.Set_Size(4);

	m_fLAngle = 0.f;
	m_fRAngle = 0.f;
}

int CBody::Update()
{

	return 0;
}

void CBody::Late_Update()
{
	{
		D3DXMATRIX matScale, matRotZ, matTrans;
		D3DXMatrixScaling(&matScale, 0.f, 90.f, 1.f);

		D3DXMatrixRotationZ(&matRotZ, 0.f);

		D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.0f);

		Body.matWorld = matScale * matRotZ * matTrans;

		BodyMatWorld = matRotZ * matTrans;

		Body.WPoly.Set_Size(50);
		for (int i = 0; i < Body.LPoly.Size(); ++i)
		{
			D3DXVec3TransformCoord(&Body.WPoly.m_vPoints[i], &Body.LPoly.m_vPoints[i], &Body.matWorld);
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		D3DXMATRIX matScale, matRotZ, matTrans;
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

		if(i == 0) D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fLAngle));

		else D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fRAngle));

		D3DXMatrixTranslation(&matTrans, Arm[i].LPoly.x, Arm[i].LPoly.y, 0.0f);

		Arm[i].matWorld = matScale * matRotZ * matTrans * BodyMatWorld;

		if (i == 0) LArmMatWorld = matRotZ * matTrans * BodyMatWorld;
		else RArmMatWorld = matRotZ * matTrans * BodyMatWorld;

		D3DXVec3TransformCoord(&Arm[i].WPoly, &Arm[i].LPoly, &Arm[i].matWorld);
	}

	for (int i = 0; i < 2; ++i)
	{
		D3DXMATRIX matScale, matRotZ, matTrans;
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

		if (i == 0) D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fLAngle));

		else D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fRAngle));

		D3DXMatrixTranslation(&matTrans, Hand[i].LPoly.x + Arm[i].LPoly.x, Hand[i].LPoly.y + Arm[i].LPoly.y, 0.0f);

		if(i ==0) Hand[i].matWorld = matScale * matRotZ * matTrans * LArmMatWorld;
		else Hand[i].matWorld = matScale * matRotZ * matTrans * RArmMatWorld;

		D3DXVec3TransformCoord(&Hand[i].WPoly, &Hand[i].LPoly, &Hand[i].matWorld);
	}

	for (int i = 0; i < 2; ++i)
	{
		D3DXMATRIX matScale, matRotZ, matTrans;
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

		D3DXMatrixRotationZ(&matRotZ, 0.f);

		D3DXMatrixTranslation(&matTrans, Leg[i].LPoly.x, Leg[i].LPoly.y, 0.0f);

		Leg[i].matWorld = matScale * matRotZ * matTrans * BodyMatWorld;

		D3DXVec3TransformCoord(&Leg[i].WPoly, &Leg[i].LPoly, &Leg[i].matWorld);
	}

	{
		D3DXMATRIX matScale, matRotZ, matTrans;
		D3DXMatrixScaling(&matScale, WhiteFlag.LPoly.m_vScale.x, WhiteFlag.LPoly.m_vScale.y, 1.f);

		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fLAngle));

		D3DXMatrixTranslation(&matTrans, Hand[0].LPoly.x, Hand[0].LPoly.y, 0.0f);

		WhiteFlag.matWorld = matScale * matRotZ * matTrans * Hand[0].matWorld;

		WhiteFlag.WPoly.Set_Size(4);
		for (int i = 0; i < WhiteFlag.LPoly.Size(); ++i)
		{
			D3DXVec3TransformCoord(&WhiteFlag.WPoly.m_vPoints[i], &WhiteFlag.LPoly.m_vPoints[i], &WhiteFlag.matWorld);
		}
	}

	{
		D3DXMATRIX matScale, matRotZ, matTrans;
		D3DXMatrixScaling(&matScale, BlueFlag.LPoly.m_vScale.x, BlueFlag.LPoly.m_vScale.y, 1.f);

		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fRAngle));

		D3DXMatrixTranslation(&matTrans, Hand[1].LPoly.x, Hand[1].LPoly.y, 0.0f);

		BlueFlag.matWorld = matScale * matRotZ * matTrans * Hand[1].matWorld;

		BlueFlag.WPoly.Set_Size(4);
		for (int i = 0; i < BlueFlag.LPoly.Size(); ++i)
		{
			D3DXVec3TransformCoord(&BlueFlag.WPoly.m_vPoints[i], &BlueFlag.LPoly.m_vPoints[i], &BlueFlag.matWorld);
		}
	}
	Key_Input();
}

void CBody::Render(HDC hDC)
{
	Body.WPoly.DrawPolygon(hDC);

	MoveToEx(hDC, 400, 270, nullptr);
	LineTo(hDC, Arm[0].WPoly.x, Arm[0].WPoly.y);
	LineTo(hDC, Hand[0].WPoly.x, Hand[0].WPoly.y);

	MoveToEx(hDC, 400, 270, nullptr);
	LineTo(hDC, Arm[1].WPoly.x, Arm[1].WPoly.y);
	LineTo(hDC, Hand[1].WPoly.x, Hand[1].WPoly.y);

	MoveToEx(hDC, 400, 390 , nullptr);
	LineTo(hDC, Leg[0].WPoly.x, Leg[0].WPoly.y);

	MoveToEx(hDC, 400, 390 , nullptr);
	LineTo(hDC, Leg[1].WPoly.x, Leg[1].WPoly.y);

	{
		HBRUSH hBrushBlue = CreateSolidBrush(RGB(65, 105, 225));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrushBlue);
		WhiteFlag.WPoly.DrawPolygon(hDC);
		SelectObject(hDC, hOldBrush);
		DeleteObject(hBrushBlue);
	}
	BlueFlag.WPoly.DrawPolygon(hDC);
}

void CBody::Release()
{
}

void CBody::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		m_fLAngle = -70.f;						//왼손 up
		m_ePlayerBType = BD;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		m_fLAngle = 0.f;
		m_ePlayerBType = BTYPE::BEND;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		m_fLAngle = 40.f;						//왼.손 down
		m_ePlayerBType = BTYPE::BU;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('I'))
	{
		m_fRAngle = 70.f;						//오른손 down
		m_ePlayerWType = WD;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('O'))
	{
		m_fRAngle = 0.f;						//오른손 up
		m_ePlayerWType = WEND;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('P'))
	{
		m_fRAngle = -40.f;						//오른손 down
		m_ePlayerWType = WU;
	}
}
