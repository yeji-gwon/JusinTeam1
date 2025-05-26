#include "pch.h"
#include "CScreen.h"

CScreen::CScreen()
{
}

CScreen::~CScreen()
{
}

void CScreen::Initialize()
{
	m_vPos = { 400,300,0.f };
	m_vScale = { 600,300,0.f };
	LT = { -0.5f, -0.5f, 0.f }; // LT 
	RT = { 0.5f, -0.5f, 0.f }; // RT
	RB = { 0.5f,  0.5f, 0.f }; // RB
	LB = { -0.5f,  0.5f, 0.f }; // LB

}

int CScreen::Update()
{
	return 0;
}

void CScreen::Late_Update()
{
}

void CScreen::Render(HDC hDC)
{
	D3DXMATRIX matWorld, matScale, matTrans;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);

	matWorld = matScale * matTrans;

	D3DXVECTOR3 arr[4] = {LT,RT,RB,LB};
	D3DXVECTOR3 arrTmp[4] = {};
	for (int i = 0; i < 4; ++i) {
		D3DXVec3TransformCoord(&arrTmp[i], &arr[i], &matWorld);
	}

	MoveToEx(hDC, arrTmp[0].x, arrTmp[0].y, nullptr);
	LineTo(hDC, arrTmp[1].x, arrTmp[1].y);
	LineTo(hDC, arrTmp[2].x, arrTmp[2].y);
	LineTo(hDC, arrTmp[3].x, arrTmp[3].y);
	LineTo(hDC, arrTmp[0].x, arrTmp[0].y);
}

void CScreen::Release()
{
}
