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

	// IP TODO : 시간되면 바퀴안에 사각형 만들기(회전 시각화)

	// 바퀴 설정 (보드 중심 기준으로 앞뒤 배치)
	// 앞바퀴 (보드 중심에서 앞쪽으로 30.f)
	m_tWheel[0].m_vCenter = { 40.f, 20.f, 0.f };
	m_tWheel[0].m_vScale = { 8.f, 8.f, 0.f };
	m_tWheel[0].Set_Size(36);

	// 뒷바퀴 (보드 중심에서 뒤쪽으로 30.f)
	m_tWheel[1].m_vCenter = { -40.f, 20.f, 0.f };
	m_tWheel[1].m_vScale = { 8.f, 8.f, 0.f };
	m_tWheel[1].Set_Size(36);

}

int Board2::Update()
{
	if (m_bFlip)
		m_fAngleX += 0.35f;  // 0.2f에서 증가 - 더 빠른 플립
	if (m_fAngleX >= 4 * 3.141592f)
	{
		m_bFlip = false;
		m_fAngleX = 0;
	}

	if (m_bShuvit)
		m_fAngleY += 0.4f;   // 0.5f에서 감소 - 조금 더 부드러운 회전
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

	Key_Input();

	Update_Matrix();

	return 0;
}

void Board2::Late_Update()
{

}

void Board2::Render(HDC hDC)
{
	// 보드 렌더링
	tagPolygon WorldBoard;
	WorldBoard.Set_Size(m_tBoard.Size());
	for (int i = 0; i < m_tBoard.Size(); i++)
		D3DXVec3TransformCoord(&WorldBoard.m_vPoints[i], &m_tBoard.m_vPoints[i], &m_matWorld);
	WorldBoard.DrawPolygon(hDC);

	// 바퀴 렌더링
	for (int wheelIdx = 0; wheelIdx < 2; wheelIdx++)
	{
		tagPolygon WorldWheel;
		WorldWheel.Set_Size(m_tWheel[0].Size());
		for (int i = 0; i < m_tWheel[0].Size(); i++)
		{
			D3DXVec3TransformCoord(&WorldWheel.m_vPoints[i], &m_tWheel[0].m_vPoints[i], &m_matWorldWheel[0]);
		}
		WorldWheel.DrawPolygon(hDC);

		for (int i = 0; i < m_tWheel[1].Size(); i++)
		{
			D3DXVec3TransformCoord(&WorldWheel.m_vPoints[i], &m_tWheel[1].m_vPoints[i], &m_matWorldWheel[1]);
		}
		WorldWheel.DrawPolygon(hDC);
			
	}

	
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
	D3DXMATRIX	m_matScaleB;
	D3DXMATRIX	m_matScaleW;
	// 회전 행렬
	D3DXMATRIX  m_matRotX;
	D3DXMATRIX  m_matRotY;
	D3DXMATRIX  m_matRotZ;

	D3DXMATRIX  m_matRotXW;
	D3DXMATRIX  m_matRotYW;
	D3DXMATRIX  m_matRotZW;

	D3DXMATRIX  m_matTransB;
	D3DXMATRIX  m_matTransW[2];

	D3DXMatrixScaling(&m_matScaleB, m_tBoard.m_vScale.x, m_tBoard.m_vScale.y, m_tBoard.m_vScale.z);
	D3DXMatrixScaling(&m_matScaleW, m_tWheel[0].m_vScale.x, m_tWheel[0].m_vScale.y, m_tWheel[0].m_vScale.z);
	//D3DXMatrixScaling(&m_matScaleW[1], m_tWheel[1].m_vScale.x, m_tWheel[1].m_vScale.y, m_tWheel[1].m_vScale.z);

<<<<<<< Updated upstream

	// TODO : 바퀴의 회전 구현
	// 회전 행렬 업데이트
=======
	// 회전 행렬 업데이트 : 보드
>>>>>>> Stashed changes
	D3DXMatrixRotationX(&m_matRotX, m_fAngleX);
	D3DXMatrixRotationY(&m_matRotY, m_fAngleY);
	D3DXMatrixRotationZ(&m_matRotZ, m_fAngleZ);

	// 회전 : 바퀴(보드에 대한 공전)
	D3DXMatrixRotationX(&m_matRotXW, m_fAngleX);
	D3DXMatrixRotationY(&m_matRotYW, m_fAngleY);
	D3DXMatrixRotationZ(&m_matRotZW, m_fAngleZ);



	// 이동 행렬
	D3DXMatrixTranslation(&m_matTransB, m_tBoard.m_vCenter.x, m_tBoard.m_vCenter.y, m_tBoard.m_vCenter.z);
	D3DXMatrixTranslation(&m_matTransW[0], m_tWheel[0].m_vCenter.x, m_tWheel[0].m_vCenter.y, m_tWheel[0].m_vCenter.z);
	D3DXMatrixTranslation(&m_matTransW[1], m_tWheel[1].m_vCenter.x, m_tWheel[1].m_vCenter.y, m_tWheel[1].m_vCenter.z);


	// 월드 행렬 = (크기 * 회전 * 이동) * 공전 * 부모
	m_matWorld = m_matScaleB * m_matRotY * m_matRotX * m_matRotZ * m_matTransB;

	// 바퀴 행렬 계산 (보드와 동일한 회전과 이동 적용)
	//m_matWorldWheel[0] = m_matScaleW * m_matRotY * m_matRotX * m_matRotZ * m_matTransW[0] * m_matTransB;
	//m_matWorldWheel[1] = m_matScaleW * m_matRotY * m_matRotX * m_matRotZ * m_matTransW[1] * m_matTransB;
	m_matWorldWheel[0] = m_matScaleW * m_matTransW[0] * m_matRotYW * m_matRotXW * m_matRotZW * m_matTransB ;
	m_matWorldWheel[1] = m_matScaleW * m_matTransW[1] * m_matRotYW * m_matRotXW * m_matRotZW * m_matTransB;
}