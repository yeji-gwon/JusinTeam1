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
	m_vRot.z = _rz;
}

void CJoint::Set_Trans(float _tx, float _ty, float _tz)
{
	if (!m_pParent)
	{
		m_vTrans = D3DXVECTOR3(_tx, _ty, _tz);
	}
	else
	{
		m_vTrans = D3DXVECTOR3((_tx + dynamic_cast<CJoint*>(m_pParent)->Get_Trans().x)/2,
			(_ty + dynamic_cast<CJoint*>(m_pParent)->Get_Trans().y)/2, 0.f);
	}
	if (m_pParent)
	{
		Set_Scale(10.f, sqrt(
			(_ty - dynamic_cast<CJoint*>(m_pParent)->Get_Trans().y) * (_ty - dynamic_cast<CJoint*>(m_pParent)->Get_Trans().y))/2.f, 0.f);
		Set_RotZ( - atan((_tx - dynamic_cast<CJoint*>(m_pParent)->Get_Trans().x )/( _ty - dynamic_cast<CJoint*>(m_pParent)->Get_Trans().y)));
	}
	PolyPoint.m_vCenter = { 0.f, 0.f, 0.f };
	PolyPoint.Set_Size(8);
}

void CJoint::Initialize()
{
	Set_Scale(10.f, 20.f, 10.f);
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

	tmpPolygon.Set_Size(8);
	for (int i = 0; i < PolyPoint.Size(); ++i)
	{
		D3DXVec3TransformCoord(&tmpPolygon.m_vPoints[i], &PolyPoint.m_vPoints[i], &m_tInfo.matWorld);
	}
}

void CJoint::Render(HDC hDC)
{
	if (m_pParent)
	{
		tmpPolygon.DrawPolygon(hDC);
	}
}

void CJoint::Release()
{
}
