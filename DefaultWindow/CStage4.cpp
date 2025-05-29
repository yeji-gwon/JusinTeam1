#include "pch.h"
#include "CStage4.h"
#include "CPlayer4.h"
#include "CKeyMgr.h"
#include "CGameSystem4.h"

CStage4::CStage4()
{
}

CStage4::~CStage4()
{
	Release();
}

void CStage4::Initialize()
{
	m_pPlayer = new CPlayer4;
	m_pPlayer->Initialize();

	m_pGameSystem = new CGameSystem4;
	m_pGameSystem->Initialize();

	Ground.LPoly.m_vCenter = D3DXVECTOR3(0.f, 0.f, 0.f);
	Ground.LPoly.m_vScale = D3DXVECTOR3(600.f, 300.f, 300.f);
	Ground.LPoly.Set_Size(50);

	Back.LPoly.m_vCenter = D3DXVECTOR3(0.f, 0.f, 0.f);
	Back.LPoly.m_vScale = D3DXVECTOR3(900.f, 900.f, 900.f);
	Back.LPoly.Set_Size(50);

	Sun.LPoly.m_vCenter = D3DXVECTOR3(0.f, 0.f, 0.f);
	Sun.LPoly.m_vScale = D3DXVECTOR3(50.f, 50.f, 50.f);
	Sun.LPoly.Set_Size(50);

	m_vSunPoint[0] = { -10,5,0 };
	m_vSunPoint[1] = { -10,-5,0 };
	m_vSunPoint[2] = { 10,-5,0 };
	m_vSunPoint[3] = { 10,5,0 };
}

int CStage4::Update()
{
	m_pPlayer->Update();
	m_pGameSystem->Update();
	CKeyMgr::Get_Instance()->Update();
	Spin_Sun();
	return 0;
}

void CStage4::Late_Update()
{
	m_pPlayer->Late_Update();
	m_pGameSystem->Late_Update();

	dynamic_cast<CGameSystem4*> (m_pGameSystem)->Get_PlayerType(
		dynamic_cast<CPlayer4*>(m_pPlayer)->Get_BType(),
		dynamic_cast<CPlayer4*>(m_pPlayer)->Get_WType());

	if (dynamic_cast<CGameSystem4*> (m_pGameSystem)->Get_ResultTime() < 0)
	{
		dynamic_cast<CPlayer4*>(m_pPlayer)->Init_Type();
	}

	{
		D3DXMATRIX matScale, matRotZ, matTrans;
		D3DXMatrixScaling(&matScale, Ground.LPoly.m_vScale.x, Ground.LPoly.m_vScale.y, Ground.LPoly.m_vScale.z);

		D3DXMatrixRotationZ(&matRotZ, 0.f);

		D3DXMatrixTranslation(&matTrans, 400.f, 600.f, 0.0f);

		Ground.matWorld = matScale * matRotZ * matTrans;

		Ground.WPoly.Set_Size(50);
		for (int i = 0; i < Ground.LPoly.Size(); ++i)
		{
			D3DXVec3TransformCoord(&Ground.WPoly.m_vPoints[i], &Ground.LPoly.m_vPoints[i], &Ground.matWorld);
		}
	}

	{
		D3DXMATRIX matScale, matRotZ, matTrans;
		D3DXMatrixScaling(&matScale, Back.LPoly.m_vScale.x, Back.LPoly.m_vScale.y, Back.LPoly.m_vScale.z);

		D3DXMatrixRotationZ(&matRotZ, 0.f);

		D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.0f);

		Back.matWorld = matScale * matRotZ * matTrans;

		Back.WPoly.Set_Size(50);
		for (int i = 0; i < Back.LPoly.Size(); ++i)
		{
			D3DXVec3TransformCoord(&Back.WPoly.m_vPoints[i], &Back.LPoly.m_vPoints[i], &Back.matWorld);
		}
	}


	{
		D3DXMATRIX matScale, matRotZ, matTrans;
		D3DXMatrixScaling(&matScale, Sun.LPoly.m_vScale.x, Sun.LPoly.m_vScale.y, Sun.LPoly.m_vScale.z);

		D3DXMatrixRotationZ(&matRotZ, 0.f);

		D3DXMatrixTranslation(&matTrans, 100.f, 100.f, 0.0f);

		Sun.matWorld = matScale * matRotZ * matTrans;
		m_SunParent = matRotZ * matTrans;
		Sun.WPoly.Set_Size(50);
		for (int i = 0; i < Sun.LPoly.Size(); ++i)
		{
			D3DXVec3TransformCoord(&Sun.WPoly.m_vPoints[i], &Sun.LPoly.m_vPoints[i], &Sun.matWorld);
		}
	}

	for (int i = 0; i < 8; ++i)
	{
		D3DXMATRIX matScale, matRotZ, matOrbit, matTrans;
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0));

		D3DXMatrixTranslation(&matTrans, 80.f, 0.f, 0.0f);

		D3DXMatrixRotationZ(&matOrbit, D3DXToRadian(45.f* i + m_fSpin));

		m_SunMatrix[i] = matScale * matRotZ * matTrans * matOrbit * m_SunParent;

		for (int j = 0; j < 4; ++j)
		{
			D3DXVec3TransformCoord(&m_vSunOrigin[i][j], &m_vSunPoint[j], &m_SunMatrix[i]);
		}
	}
}

void CStage4::Render(HDC hDC)
{
	{
		HBRUSH hBrushSky = CreateSolidBrush(RGB(80, 188, 223));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrushSky);
		Back.WPoly.DrawPolygon(hDC);
		SelectObject(hDC, hOldBrush);
		DeleteObject(hBrushSky);
	}
	{
		HBRUSH hBrushGreen = CreateSolidBrush(RGB(102, 255, 0));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrushGreen);
		Ground.WPoly.DrawPolygon(hDC);
		SelectObject(hDC, hOldBrush);
		DeleteObject(hBrushGreen);
	}
	{
		HBRUSH hBrushSun = CreateSolidBrush(RGB(255, 127, 0));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrushSun);
		Sun.WPoly.DrawPolygon(hDC);

		for (int i = 0; i < 8; ++i)
		{
			vector<POINT> pts;
			for (const auto& v : m_vSunOrigin[i])
			{
				pts.push_back({ LONG(v.x), LONG(v.y) });
			}
			Polygon(hDC, pts.data(), static_cast<int>(pts.size()));
		}
		SelectObject(hDC, hOldBrush);
		DeleteObject(hBrushSun);
	}
	m_pPlayer->Render(hDC);
	m_pGameSystem->Render(hDC);

}

void CStage4::Release()
{
}

void CStage4::Spin_Sun()
{
	if (m_fSpin == 360) m_fSpin = 0;
	++m_fSpin;
}
