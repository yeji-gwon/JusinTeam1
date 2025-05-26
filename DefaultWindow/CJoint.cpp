#include "pch.h"
#include "CJoint.h"

CJoint::CJoint()
{
}

CJoint::~CJoint()
{
}

void CJoint::Set_ParentPtr(CJoint* pParent)
{
	m_pParent = pParent;
}

void CJoint::Set_Scale(float _sx, float _sy, float _sz)
{
	m_vScale = D3DXVECTOR3(_sx, _sy, _sz);
}

void CJoint::Set_RotZ(float _rz)
{
	m_vRot.z = D3DXToRadian(_rz);
}

void CJoint::Set_Trans(float _tx, float _ty, float _tz)
{
	m_vTrans = D3DXVECTOR3(_tx, _ty, _tz);
	m_tInfo.vPos = m_vTrans;

	if (m_pParent)
	{
		m_vPoint[0] = { m_tInfo.vPos.x - 8.f, m_tInfo.vPos.y, 0.f };
		m_vPoint[1] = { m_pParent->Get_Info().vPos.x - 9.f, m_pParent->Get_Info().vPos.y , 0.f };
		m_vPoint[2] = { m_pParent->Get_Info().vPos.x + 9.f, m_pParent->Get_Info().vPos.y, 0.f };
		m_vPoint[3] = { m_tInfo.vPos.x + 8.f, m_tInfo.vPos.y, 0.f };
	
		//for (int i = 0; i < 4; ++i)
		//{
		//	m_vOriginPoint[i] = m_vPoint[i];
		//}
	}
}

void CJoint::Initialize()
{
	m_vOriginPoint[0] = { -8.f, 0.f, 0.f };
	m_vOriginPoint[1] = { -8.f, -20.f, 0.f };
	m_vOriginPoint[2] = { 8.f, -20.f, 0.f };
	m_vOriginPoint[3] = { 8.f, 0.f, 0.f };
}

int CJoint::Update()
{
	return 0;
}

void CJoint::Late_Update()
{
	D3DXMATRIX matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationZ(&matRotZ, m_vRot.z);
	D3DXMatrixTranslation(&matTrans, m_vTrans.x, m_vTrans.y, m_vTrans.z);
	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}
}

void CJoint::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, NULL);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);
	}

	LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);
}

void CJoint::Release()
{
}
