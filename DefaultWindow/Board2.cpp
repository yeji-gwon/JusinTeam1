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

	m_tBoard.m_vCenter = { 300.f, 400.f, 0.f };
	m_tBoard.m_vScale = { 90.f, 15.f, 0.f };
	m_tBoard.Set_Size(8);

	// ���� ���� (���� �߽� �������� �յ� ��ġ)
	// �չ��� (���� �߽ɿ��� �������� 30.f)
	m_tWheel[0].m_vCenter = { 40.f, 20.f, 0.f };
	// �޹��� (���� �߽ɿ��� �������� 30.f)
	m_tWheel[1].m_vCenter = { -40.f, 20.f, 0.f };
	for (int i = 0; i < 2; i++)
	{
		m_tWheel[i].Set_Size(64);
		m_tWheel[i].m_vScale = { 8.f, 8.f, 0.f };
	}
	// ���� �߽�(��� : �簢��)

	for (int i = 0; i < 2; i++)
	{
		m_tWheelHub[i].Set_Size(4);
		m_tWheelHub[i].m_vCenter = m_tWheel[i].m_vCenter;
		m_tWheelHub[i].m_vScale = { 6.f, 6.f, 0.f };

	}

}

int Board2::Update()
{
	if (m_bFlip)
		m_fAngleX += 0.35f;  // 0.2f���� ���� - �� ���� �ø�
	if (m_fAngleX >= 4 * 3.141592f)
	{
		m_bFlip = false;
		m_fAngleX = 0;
	}

	if (m_bShuvit)
		m_fAngleY += 0.4f;   // 0.5f���� ���� - ���� �� �ε巯�� ȸ��
	if (m_fAngleY >= 4 * 3.141592f)
	{
		m_bShuvit = false;
		m_fAngleY = 0;
	}

	if (m_bHardFlip)
		m_fAngleZ += 0.45f;
	if (m_fAngleZ >= 6 * 3.141592f)
	{
		m_bHardFlip = false;
		m_fAngleZ = 0;
	}
	// ���� ��긦 ���� �ӵ��� Z�� ȸ��
	m_fDelta += 5.f;
	// PI * k �� ������ ��������� k�� ���� ���� ���� ��
	// m_fDelta�� ������ �������� �� k = 113 => PI * 113 = 355
	if (m_fDelta >= 113 * 3.1412592f)	
	{
		m_fDelta = 0;
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
	// ���� ������
	tagPolygon WorldBoard;
	WorldBoard.Set_Size(m_tBoard.Size());
	for (int i = 0; i < m_tBoard.Size(); i++)
		D3DXVec3TransformCoord(&WorldBoard.m_vPoints[i], &m_tBoard.m_vPoints[i], &m_matWorld);
	WorldBoard.DrawPolygon(hDC);

	tagPolygon WorldWheel;
	tagPolygon WorldHub;
	for (int wheelIdx = 0; wheelIdx < 2; wheelIdx++)
	{
		// ���� ������
		WorldWheel.Set_Size(m_tWheel[wheelIdx].Size());
		for (int i = 0; i < m_tWheel[wheelIdx].Size(); i++)
		{
			D3DXVec3TransformCoord(&WorldWheel.m_vPoints[i], &m_tWheel[wheelIdx].m_vPoints[i], &m_matWorldWheel[wheelIdx]);
		}
		WorldWheel.DrawPolygon(hDC);

		// ��� ������
		WorldHub.Set_Size(m_tWheelHub[wheelIdx].Size());
		for (int i = 0; i < m_tWheelHub[wheelIdx].Size(); i++)
		{
			D3DXVec3TransformCoord(&WorldHub.m_vPoints[i], &m_tWheelHub[wheelIdx].m_vPoints[i], &m_matWorldHub[wheelIdx]);
		}
		WorldHub.DrawPolygon(hDC);
	}
}

void Board2::Release()
{

}

void Board2::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))  m_tBoard.m_vCenter.x -= m_fSpeed;
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT)) m_tBoard.m_vCenter.x += m_fSpeed;
	if(!m_bFlip && !m_bShuvit && !m_bHardFlip)
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))    m_tBoard.m_vCenter.y -= m_fSpeed;
		if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))  m_tBoard.m_vCenter.y += m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Tap('Q'))
		m_bFlip = true;
	if (CKeyMgr::Get_Instance()->Key_Tap('W'))
		m_bShuvit = true;
	if (CKeyMgr::Get_Instance()->Key_Tap('E'))
		m_bHardFlip = true;
}

void Board2::Update_Matrix()
{
	D3DXMATRIX	m_matScaleB, m_matScaleW, m_matScaleH;

	D3DXMATRIX  m_matRotX, m_matRotY, m_matRotZ;
	D3DXMATRIX  m_matRotXW, m_matRotYW, m_matRotZW;
	D3DXMATRIX  m_matRotZH;

	D3DXMATRIX  m_matTransB, m_matTransW[2], m_matTransH[2];

	D3DXMatrixScaling(&m_matScaleB, m_tBoard.m_vScale.x, m_tBoard.m_vScale.y, m_tBoard.m_vScale.z);
	D3DXMatrixScaling(&m_matScaleW, m_tWheel[0].m_vScale.x, m_tWheel[0].m_vScale.y, m_tWheel[0].m_vScale.z);
	D3DXMatrixScaling(&m_matScaleH, m_tWheelHub[0].m_vScale.x, m_tWheelHub[0].m_vScale.y, m_tWheelHub[0].m_vScale.z);

	// ȸ�� ��� ������Ʈ : ����
	D3DXMatrixRotationX(&m_matRotX, m_fAngleX);
	D3DXMatrixRotationY(&m_matRotY, m_fAngleY);
	D3DXMatrixRotationZ(&m_matRotZ, m_fAngleZ);

	// ȸ�� : ����(���忡 ���� ����)
	D3DXMatrixRotationX(&m_matRotXW, m_fAngleX);
	D3DXMatrixRotationY(&m_matRotYW, m_fAngleY);
	D3DXMatrixRotationZ(&m_matRotZW, m_fAngleZ);

	D3DXMatrixRotationZ(&m_matRotZH, m_fDelta);

	// �̵� ���
	D3DXMatrixTranslation(&m_matTransB, m_tBoard.m_vCenter.x, m_tBoard.m_vCenter.y, m_tBoard.m_vCenter.z);
	D3DXMatrixTranslation(&m_matTransW[0], m_tWheel[0].m_vCenter.x, m_tWheel[0].m_vCenter.y, m_tWheel[0].m_vCenter.z);
	D3DXMatrixTranslation(&m_matTransW[1], m_tWheel[1].m_vCenter.x, m_tWheel[1].m_vCenter.y, m_tWheel[1].m_vCenter.z);
	
	// ���� ���� ��� = (ũ�� * ȸ�� * �̵�) * ���� * �θ�
	m_matWorld = m_matScaleB * m_matRotY * m_matRotX * m_matRotZ * m_matTransB;
	for (int i = 0; i < 2; i++)
	{
		// ���� ���� ���
		m_matWorldWheel[i] = m_matScaleW * m_matTransW[i] * m_matRotYW * m_matRotXW * m_matRotZW * m_matTransB;
		// ���� ���� ���
		m_matWorldHub[i] = m_matScaleH * m_matRotZH * m_matTransW[i] * m_matRotYW * m_matRotXW * m_matRotZW * m_matTransB;
	}
}