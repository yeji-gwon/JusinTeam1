#include "pch.h"
#include "Player2.h"

Player2::Player2()
{
}


Player2::~Player2()
{
	Release();
}

void Player2::Initialize()
{
	m_vCenterHead = { 400.f, 300.f , 0.f };
	m_fAngleX = 0.f;
	m_fAngleY = 0.f;
	m_fAngleZ = 0.f;

	m_fSpeed = 5.f;
	m_tHead.m_vCenter = m_vCenterHead;
	m_tHead.m_vScale = { 25.f, 25.f, 0.f };
	m_tHead.Set_Size(36);
	m_tHead.SyncToWorld(m_tHead);

}

int Player2::Update()
{
	Key_Input();
	CKeyMgr::Get_Instance()->Update();

	Update_Matrix();
	return 0;
}

void Player2::Late_Update()
{
}

void Player2::Render(HDC hDC)
{

	struct tagPolygon WorldHead;
	WorldHead.Set_Size(36);
	for (int i = 0; i < m_tHead.Size(); i++)
		D3DXVec3TransformCoord(&WorldHead.m_vPoints[i], &m_tHead.m_vPoints[i], &m_matWorld);
	WorldHead.DrawPolygon(hDC);
	MoveToEx(hDC, WorldHead.m_vCenter.x, WorldHead.m_vCenter.y + 25, NULL);
	LineTo(hDC, WorldHead.m_vCenter.x, WorldHead.m_vCenter.y + 75);

}

void Player2::Release()
{
}

void Player2::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))  m_vCenterHead.x -= m_fSpeed;
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT)) m_vCenterHead.x += m_fSpeed;
	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))    m_vCenterHead.y -= m_fSpeed;
	if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))  m_vCenterHead.y += m_fSpeed;

}


void Player2::Update_Matrix()
{
	D3DXMATRIX	m_matScale;
	D3DXMATRIX  m_matRotX;
	D3DXMATRIX  m_matRotY;   // 회전 행렬
	D3DXMATRIX  m_matRotZ;
	D3DXMATRIX  m_matTrans;

	D3DXMatrixScaling(&m_matScale, m_tHead.m_vScale.x, m_tHead.m_vScale.y, m_tHead.m_vScale.z);
	
	// 회전 행렬 업데이트
	D3DXMatrixRotationX(&m_matRotX, m_fAngleX);
	D3DXMatrixRotationY(&m_matRotY, m_fAngleY);
	D3DXMatrixRotationZ(&m_matRotZ, m_fAngleZ);
	

	// 이동 행렬
	D3DXMatrixTranslation(&m_matTrans, m_vCenterHead.x, m_vCenterHead.y, m_vCenterHead.z);

	// 월드 행렬 = (크기 * 회전 * 이동) * 공전 * 부모
	m_matWorld = m_matScale * m_matRotY * m_matRotX * m_matRotZ * m_matTrans;
}

void Player2::Update_Direction()
{

}
