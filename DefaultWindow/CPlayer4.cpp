#include "pch.h"
#include "CPlayer4.h"

CPlayer4::CPlayer4()
{
}

CPlayer4::~CPlayer4()
{
}

void CPlayer4::Initialize()
{
	L_Head.m_vCenter = { 0.f, 0.f, 0.f };
	L_Head.Set_Size(50);

	L_Body.m_vCenter = { 0.f, 0.f , 0.f };
	L_Body.Set_Size(4);

	L_Arm.m_vCenter = { 0.f, 0.f , 0.f };
	L_Arm.Set_Size(4);

	L_LHand.m_vCenter = { 0.f, 0.f , 0.f };
	L_LHand.Set_Size(4);

	L_RHand.m_vCenter = { 0.f, 0.f , 0.f };
	L_RHand.Set_Size(4);
}

int CPlayer4::Update()
{
    return 0;
}

void CPlayer4::Late_Update()
{
	{
		D3DXMATRIX matScale, matRotZ, matTrans;

		D3DXMatrixScaling(&matScale, 60.f, 60.f, 30.f);
		D3DXMatrixRotationZ(&matRotZ, 0.f);
		D3DXMatrixTranslation(&matTrans, 400.f, 150.f, 0.f);
		m_tInfo.matWorld = matScale * matRotZ * matTrans;

		W_Head.Set_Size(50);
		for (int i = 0; i < L_Head.Size(); ++i)
		{
			D3DXVec3TransformCoord(&W_Head.m_vPoints[i], &L_Head.m_vPoints[i], &m_tInfo.matWorld);
		}
	}

	{
		D3DXMATRIX matScale, matRotZ, matTrans;

		D3DXMatrixScaling(&matScale, 0.f, 60.f, 0.f);
		D3DXMatrixRotationZ(&matRotZ, 0.f);
		D3DXMatrixTranslation(&matTrans, 400.f, 270.f, 0.f);
		m_tInfo.matWorld = matScale * matRotZ * matTrans;

		W_Body.Set_Size(4);
		for (int i = 0; i < L_Body.Size(); ++i)
		{
			D3DXVec3TransformCoord(&W_Body.m_vPoints[i], &L_Body.m_vPoints[i], &m_tInfo.matWorld);
		}
	}
	//D3DXMATRIX matParent;
	{
		D3DXMATRIX matScale, matRotZ, matTrans;

		D3DXMatrixScaling(&matScale, 140.f, 0.f, 1.f);
		D3DXMatrixRotationZ(&matRotZ, 0.f);
		D3DXMatrixTranslation(&matTrans, 400.f, 270.f, 0.f);
		m_tInfo.matWorld = matScale * matRotZ * matTrans;
		//matParent = m_tInfo.matWorld;
		W_Arm.Set_Size(4);
		for (int i = 0; i < L_Arm.Size(); ++i)
		{
			D3DXVec3TransformCoord(&W_Arm.m_vPoints[i], &L_Arm.m_vPoints[i], &m_tInfo.matWorld);
		}
	}

	{
		D3DXMATRIX matScale, matRotZ, matTrans, matTrans2, matTrans3, matRotOrbit;
		D3DXMATRIX matChild;
		D3DXMatrixIdentity(&matChild);
		D3DXMatrixScaling(&matScale, 0.f, 40.f, 1.f);
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
		D3DXMatrixTranslation(&matTrans, 260.f, 230.f, 0.f);

		D3DXMatrixRotationX(&matRotOrbit, D3DXToRadian(-200.f));
		matChild = matScale * matRotZ * matTrans*matRotOrbit ;


		W_LHand.Set_Size(4);
		for (int i = 0; i < L_LHand.Size(); ++i)
		{
			D3DXVec3TransformCoord(&W_LHand.m_vPoints[i], &L_LHand.m_vPoints[i], &matChild);
		}
	}

	/*{
		D3DXMATRIX matScale, matRotZ, matTrans;

		D3DXMatrixScaling(&matScale, 140.f, 0.f, 0.f);
		D3DXMatrixRotationZ(&matRotZ, 0.f);
		D3DXMatrixTranslation(&matTrans, 400.f, 270.f, 0.f);
		m_tInfo.matWorld = matScale * matRotZ * matTrans;

		W_Arm.Set_Size(4);
		for (int i = 0; i < L_Arm.Size(); ++i)
		{
			D3DXVec3TransformCoord(&W_Arm.m_vPoints[i], &L_Arm.m_vPoints[i], &m_tInfo.matWorld);
		}
	}*/
}

void CPlayer4::Render(HDC hDC)
{
	W_Head.DrawPolygon(hDC);
	W_Body.DrawPolygon(hDC);
	W_Arm.DrawPolygon(hDC);
	W_LHand.DrawPolyLine(hDC);
}

void CPlayer4::Release()
{
}
