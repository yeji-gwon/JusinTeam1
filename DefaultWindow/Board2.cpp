#include "pch.h"
#include "Board2.h"

Board2* Board2::pInstance(nullptr);

Board2::Board2()
{
}

Board2::~Board2()
{
	Release();
}

void Board2::Initialize()
{
	m_fAngleX = 0.f;
	m_fAngleY = 0.f;
	m_fAngleZ = 0.f;

	m_fSpeed = 5.f;

	// TODO : ���� �߰�
	m_tBoard.m_vCenter = { 300.f, 400.f, 0.f };
	m_tBoard.m_vScale = { 90.f, 15.f, 0.f };
	m_tBoard.Set_Size(8);
	m_tBoard.SyncToWorld(m_tBoard);
	
}

int Board2::Update()
{
	if (m_bFlip)
		m_fAngleX += 0.35f;  // 0.2f���� ���� - �� ���� �ø�
	if (m_fAngleX >= 2 * 3.141592f)
	{
		m_bFlip = false;
		m_fAngleX = 0;
	}

	if (m_bShuvit)
		m_fAngleY += 0.4f;   // 0.5f���� ���� - ���� �� �ε巯�� ȸ��
	if (m_fAngleY >= 2 * 3.141592f)
	{
		m_bShuvit = false;
		m_fAngleY = 0;
	}

	if (m_bHardFlip)
		m_fAngleZ += 0.45f;  // 0.5f���� ���� - X��� ��ȭ�ο� �ӵ�
	if (m_fAngleZ >= 2 * 3.141592f)
	{
		m_bHardFlip = false;
		m_fAngleZ = 0;
	}

	Key_Input();

	Update_Matrix();

	return 0;
}

void Board2::Late_Update()
{

}

void Board2::Render(HDC hDC)
{
	struct tagPolygon WorldPoly;
	WorldPoly.Set_Size(8);
	for (int i = 0; i < m_tBoard.Size(); i++)
		D3DXVec3TransformCoord(&WorldPoly.m_vPoints[i], &m_tBoard.m_vPoints[i], &m_matWorld);

	WorldPoly.DrawPolygon(hDC);
}

void Board2::Release()
{

}

void Board2::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))  m_tBoard.m_vCenter.x -= m_fSpeed;
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT)) m_tBoard.m_vCenter.x += m_fSpeed;
	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))    m_tBoard.m_vCenter.y -= m_fSpeed;
	if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))  m_tBoard.m_vCenter.y += m_fSpeed;

	if (CKeyMgr::Get_Instance()->Key_Tap('Q'))
		m_bFlip = true;
	if (CKeyMgr::Get_Instance()->Key_Tap('W'))
		m_bShuvit = true;
	if (CKeyMgr::Get_Instance()->Key_Tap('E'))
		m_bHardFlip = true;
}

void Board2::Update_Matrix()
{
	D3DXMATRIX	m_matScale;
	// ȸ�� ���
	D3DXMATRIX  m_matRotX;
	D3DXMATRIX  m_matRotY;   
	D3DXMATRIX  m_matRotZ;

	D3DXMATRIX  m_matTrans;

	D3DXMatrixScaling(&m_matScale, m_tBoard.m_vScale.x, m_tBoard.m_vScale.y, m_tBoard.m_vScale.z);

	// ȸ�� ��� ������Ʈ
	D3DXMatrixRotationX(&m_matRotX, m_fAngleX);
	D3DXMatrixRotationY(&m_matRotY, m_fAngleY);
	D3DXMatrixRotationZ(&m_matRotZ, m_fAngleZ);


	// �̵� ���
	D3DXMatrixTranslation(&m_matTrans, m_tBoard.m_vCenter.x, m_tBoard.m_vCenter.y, m_tBoard.m_vCenter.z);

	// ���� ��� = (ũ�� * ȸ�� * �̵�) * ���� * �θ�
	m_matWorld = m_matScale * m_matRotY * m_matRotX * m_matRotZ * m_matTrans;
}