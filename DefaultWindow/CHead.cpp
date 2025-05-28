#include "pch.h"
#include "CHead.h"

CHead::CHead()
{
}

CHead::~CHead()
{
}

void CHead::Initialize()
{
	Head.LPoly.m_vCenter = D3DXVECTOR3(0.f, 0.f, 0.f);
	Head.LPoly.m_vScale = D3DXVECTOR3(60.f, 60.f, 60.f);
	Head.LPoly.Set_Size(50);

	Eyes[0].LPoly = D3DXVECTOR3(-20, -10, 0);
	Eyes[1].LPoly = D3DXVECTOR3(20, -10, 0);
}

int CHead::Update()
{
	return 0;
}

void CHead::Late_Update()
{
	{
		D3DXMATRIX matScale, matRotZ, matTrans;
		D3DXMatrixScaling(&matScale, Head.LPoly.m_vScale.x, Head.LPoly.m_vScale.y, Head.LPoly.m_vScale.z);

		D3DXMatrixRotationZ(&matRotZ, 0.f);

		D3DXMatrixTranslation(&matTrans, 400.f, 150.f, 0.0f);

		Head.matWorld = matScale * matRotZ * matTrans;

		m_tInfo.matWorld = matRotZ * matTrans;

		Head.WPoly.Set_Size(50);
		for (int i = 0; i < Head.LPoly.Size(); ++i)
		{
			D3DXVec3TransformCoord(&Head.WPoly.m_vPoints[i], &Head.LPoly.m_vPoints[i], &Head.matWorld);
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		D3DXMATRIX matScale, matRotZ, matTrans;
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

		D3DXMatrixRotationZ(&matRotZ, 0.f);

		D3DXMatrixTranslation(&matTrans, Eyes[i].LPoly.x, Eyes[i].LPoly.y, 0.0f);

		Eyes[i].matWorld = matScale * matRotZ * matTrans * m_tInfo.matWorld;

		D3DXVec3TransformCoord(&Eyes[i].WPoly, &Eyes[i].LPoly, &Eyes[i].matWorld);
	}


}

void CHead::Render(HDC hDC)
{
	Head.WPoly.DrawPolygon(hDC);

	MoveToEx(hDC, 380, 140, nullptr);
	LineTo(hDC, Eyes[0].WPoly.x, Eyes[0].WPoly.y);

	MoveToEx(hDC, 420, 140, nullptr);
	LineTo(hDC, Eyes[1].WPoly.x, Eyes[1].WPoly.y);
}

void CHead::Release()
{
}
