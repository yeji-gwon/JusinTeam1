#include "pch.h"
#include "CDriver.h"

CDriver::CDriver()
{
}

CDriver::~CDriver()
{
}

void CDriver::Initialize()
{
    m_tLeftHand.m_vScale = { 15.f,15.f,0.f };
    m_tLeftHand.Set_Size(10);


    m_tRightHand.m_vScale = { 15.f,15.f,0.f };
	m_tRightHand.Set_Size(10);

}

int CDriver::Update()
{
	m_tRightArm[1] = m_tLeftHand.m_vPoints[5];
	m_tRightArm[2] = m_tLeftHand.m_vPoints[9];
    return 0;
}

void CDriver::Late_Update()
{
}

void CDriver::Render(HDC hDC)
{

	RenderHand(hDC, m_tLeftHand);
	RenderHand(hDC, m_tRightHand);
}

void CDriver::Release()
{
}

void CDriver::RenderHand(HDC hDC, tagPolygon poly)
{
	D3DXMATRIX matWorld,matScale, matRotate, matTrans; //월드 포지션 / 크기/자전/이동
	D3DXMatrixIdentity(&matWorld); //초기화
	//크기
	D3DXMatrixScaling(&matScale, poly.m_vScale.x, poly.m_vScale.y, poly.m_vScale.z);

	//자전
	//D3DXMatrixRotationZ(&matRotate, D3DXToRadian(.z));

	D3DXMatrixTranslation(&matTrans,
		poly.m_vCenter.x,
		poly.m_vCenter.y,
		poly.m_vCenter.z);

	matWorld = matScale * matTrans;

	tagPolygon tmpPoly;
	poly.SyncToWorld(tmpPoly);

	for (int i = 0; i < poly.Size(); ++i) {
		D3DXVec3TransformCoord(&tmpPoly.m_vPoints[i], &poly.m_vPoints[i], &matWorld);
	}

	tmpPoly.DrawPolygon(hDC);
}

void CDriver::RenderArm(HDC hDC, tagPolygon poly)
{
	D3DXMATRIX matWorld, matScale, matRotate, matTrans; //월드 포지션 / 크기/자전/이동
	D3DXMatrixIdentity(&matWorld); //초기화
	//크기
	D3DXMatrixScaling(&matScale, poly.m_vScale.x, poly.m_vScale.y, poly.m_vScale.z);

	//자전
	D3DXMatrixRotationZ(&matRotate, D3DXToRadian(90));

	D3DXMatrixTranslation(&matTrans,
		poly.m_vCenter.x,
		poly.m_vCenter.y,
		poly.m_vCenter.z);

	matWorld = matScale *matRotate* matTrans;

	tagPolygon tmpPoly;
	poly.SyncToWorld(tmpPoly);

	for (int i = 0; i < poly.Size(); ++i) {
		D3DXVec3TransformCoord(&tmpPoly.m_vPoints[i], &poly.m_vPoints[i], &matWorld);
	}

	tmpPoly.DrawPolygon(hDC);
}

void CDriver::Set_CenterLeft(D3DXVECTOR3 left)
{
    m_tLeftHand.m_vCenter = left;
}

void CDriver::Set_CenterRight(D3DXVECTOR3 right)
{
    m_tRightHand.m_vCenter = right;
}
