#include "pch.h"
#include "CHandle.h"

CHandle::CHandle()
{
}

CHandle::~CHandle()
{
}

void CHandle::Initialize()
{
	m_tInnerLC.m_vCenter = { 0,0,0 };
	m_tInnerLC.m_vLT = { -0.5f,-0.5f,0 };
	m_tInnerLC.m_vRB = { 0.5f,0.5f,0 };
	m_tInnerLC.m_vRotate = { 0,0,0 };
	m_tInnerLC.m_vScale = { 2.f,2.f,2.f };
}

int CHandle::Update()
{
	CircleToWorld(m_tInnerLC, m_tInnerWO);
	CircleToWorld(m_tOuterLC, m_tOuterWO);

	return 0;
}

void CHandle::Late_Update()
{
}

void CHandle::Render(HDC hDC)
{
	Ellipse(
		hDC,
		m_tInnerWO.m_vLT.x,
		m_tInnerWO.m_vRB.y,
		m_tInnerWO.m_vRB.x,
		m_tInnerWO.m_vLT.y
	);
}

void CHandle::Release()
{
}

void CHandle::CircleToWorld(tagCirCle circleLC, tagCirCle& circleWO)
{
	D3DXMATRIX matScale, matRotate, matTrans; //월드 포지션 / 크기/자전/이동
	D3DXMatrixIdentity(&worldMat); //초기화
	//크기
	D3DXMatrixScaling(&matScale, circleLC.m_vScale.x, circleLC.m_vScale.y, circleLC.m_vScale.z);

	//자전
	D3DXMatrixRotationZ(&matRotate, D3DXToRadian(circleLC.m_vRotate.z));

	D3DXMatrixTranslation(&matTrans,
		circleLC.m_vCenter.x,
		circleLC.m_vCenter.y,
		circleLC.m_vCenter.z);

	worldMat = matScale * matRotate * matTrans;

	D3DXVec3TransformCoord(&circleWO.m_vLT, &circleLC.m_vLT, &worldMat);
	D3DXVec3TransformCoord(&circleWO.m_vRB, &circleLC.m_vLT, &worldMat);
}
