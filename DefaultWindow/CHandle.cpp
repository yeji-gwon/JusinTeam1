#include "pch.h"
#include "CHandle.h"
#include "CKeyMgr.h"

CHandle::CHandle()
{
}

CHandle::~CHandle()
{
}

void CHandle::Initialize()
{
	m_vPos = { 400.f,500.f,0 };
	m_vRotate = { 0.f,0.f,0.f };

	m_tInnerLC.m_vScale = { 55.f,55.f,0.f };
	m_tInnerLC.Set_Size(50);
	m_tInnerLC.SyncToWorld(m_tInnerWO);

	m_tOuterLC.m_vScale = { 60.f,60.f,0.f };
	m_tOuterLC.Set_Size(50);
	m_tOuterLC.SyncToWorld(m_tOuterWO);

}

int CHandle::Update()
{
	PolyToWorld(m_tInnerLC, m_tInnerWO);
	PolyToWorld(m_tOuterLC, m_tOuterWO);
	KeyCheck();
	return 0;
}

void CHandle::Late_Update()
{
}
void CHandle::Render(HDC hDC)
{

	//m_tInnerWO.DrawPolygon(hDC);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));

	//m_tOuterWO.DrawPolygon(hDC);
	SelectObject(hDC, hOldBrush);

	m_tOuterWO.DrawPolyLine(hDC, 0, 25);

}



void CHandle::Release()
{
}

D3DXVECTOR3 CHandle::Get_Point_World(int i)
{
	if (m_tOuterWO.m_vPoints[i]) {
		return m_tOuterWO.m_vPoints[i];
	}
	
	return D3DXVECTOR3{};
}

void CHandle::PolyToWorld(tagPolygon circleLC, tagPolygon& circleWO)
{
	D3DXMATRIX matScale, matRotate, matTrans; //월드 포지션 / 크기/자전/이동
	D3DXMatrixIdentity(&worldMat); //초기화
	//크기
	D3DXMatrixScaling(&matScale, circleLC.m_vScale.x, circleLC.m_vScale.y, circleLC.m_vScale.z);

	//자전
	D3DXMatrixRotationZ(&matRotate, D3DXToRadian(m_vRotate.z));

	D3DXMatrixTranslation(&matTrans,
		m_vPos.x,
		m_vPos.y,
		m_vPos.z);

	worldMat = matScale * matRotate * matTrans;

	for (int i = 0; i < circleLC.Size(); ++i) {
		D3DXVec3TransformCoord(&circleWO.m_vPoints[i], &circleLC.m_vPoints[i], &worldMat);
	}
}

void CHandle::KeyCheck()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT)) {
		if(m_vRotate.z < 80)
		m_vRotate.z += 5.f;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT)) {
		if (m_vRotate.z > -80)
		m_vRotate.z -= 5.f;
	}
}
