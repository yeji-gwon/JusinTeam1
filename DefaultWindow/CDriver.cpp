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

	m_tLeftArm.m_vScale = { 1.5f,10.f,0.f };
	m_tLeftArm.m_vPos = { 0.f,5.f,0.f };
	m_tLeftArm.m_vRotate = { 0.f,0.f,0.f };

	// 팔의 로컬 꼭짓점 (기본 정사각형 기준)
	m_tLeftArm.m_vCorner[0] = { -0.5f, -0.5f, 0.f }; // LT
	m_tLeftArm.m_vCorner[1] = { 0.5f, -0.5f, 0.f }; // RT
	m_tLeftArm.m_vCorner[2] = { 0.5f,  0.5f, 0.f }; // RB
	m_tLeftArm.m_vCorner[3] = { -0.5f,  0.5f, 0.f }; // LB

	m_tRightArm.m_vScale = { 1.5f,10.f,0.f };
	m_tRightArm.m_vPos = { 0.f,5.f,0.f };
	m_tRightArm.m_vRotate = { 0.f,0.f,0.f };

	// 팔의 로컬 꼭짓점 (기본 정사각형 기준)
	m_tRightArm.m_vCorner[0] = { -0.5f, -0.5f, 0.f }; // LT
	m_tRightArm.m_vCorner[1] = { 0.5f, -0.5f, 0.f }; // RT
	m_tRightArm.m_vCorner[2] = { 0.5f,  0.5f, 0.f }; // RB
	m_tRightArm.m_vCorner[3] = { -0.5f,  0.5f, 0.f }; // LB
}

int CDriver::Update()
{
	return 0;
}

void CDriver::Late_Update()
{
}

void CDriver::Render(HDC hDC)
{
	RenderHand(hDC, m_tLeftHand, true);
	RenderHand(hDC, m_tRightHand, false);
}

void CDriver::Release()
{
}

void CDriver::RenderHand(HDC hDC, tagPolygon poly, bool left)
{
	// 1. 손 월드 변환
	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, poly.m_vScale.x, poly.m_vScale.y, poly.m_vScale.z);
	D3DXMatrixTranslation(&matTrans, poly.m_vCenter.x, poly.m_vCenter.y, poly.m_vCenter.z);
	matWorld = matScale * matTrans;

	// 2. 손 좌표 변환
	tagPolygon tmpPoly;
	poly.SyncToWorld(tmpPoly);
	for (int i = 0; i < poly.Size(); ++i)
		D3DXVec3TransformCoord(&tmpPoly.m_vPoints[i], &poly.m_vPoints[i], &matWorld);

	// 3. 팔 사각형 설정
	tagArm* pArm = left ? &m_tLeftArm : &m_tRightArm;
	RenderArm(hDC,*pArm,matWorld);
	// 5. 손 그리기
	tmpPoly.DrawPolygon(hDC);
}
void CDriver::RenderArm(HDC hDC, tagArm& arm, const D3DXMATRIX& matParent)
{
	// 1. 팔 월드 변환 행렬 구성
	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, arm.m_vScale.x, arm.m_vScale.y, arm.m_vScale.z);
	D3DXMatrixTranslation(&matTrans, arm.m_vPos.x, arm.m_vPos.y, arm.m_vPos.z);
	matWorld = matScale * matTrans;

	//공전
	D3DXMATRIX matOrbit, matRotate, matReOrbit, matRotateOrb;
	D3DXMatrixTranslation(&matOrbit,0.f,-5.f,0.f);
	D3DXMatrixRotationZ(&matRotate, D3DXToRadian(arm.m_vRotate.z)); // 회전 포함 가능
	D3DXMatrixTranslation(&matReOrbit, 0.f, 5.f, 0.f);
	matRotateOrb = matReOrbit * matRotate * matOrbit;

	matWorld *= matRotate * matParent;
	// 꼭짓점 변환
	tagArm tmpArm;
	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&tmpArm.m_vCorner[i], &arm.m_vCorner[i], &matWorld);

	vector<POINT> pts;
	for (int i = 0; i < 4; ++i)
	{
		pts.push_back({
			LONG(tmpArm.m_vCorner[i].x),
			LONG(tmpArm.m_vCorner[i].y)
			});
	}

	Polygon(hDC, pts.data(), static_cast<int>(pts.size()));

}



void CDriver::Set_CenterLeft(D3DXVECTOR3 left)
{
	m_tLeftHand.m_vCenter = left;
}

void CDriver::Set_CenterRight(D3DXVECTOR3 right)
{
	m_tRightHand.m_vCenter = right;
}

void CDriver::Get_Rotate(D3DXVECTOR3 Rot)
{
	m_tLeftArm.m_vRotate = Rot*0.3;
	m_tRightArm.m_vRotate = Rot * 0.3;
}
