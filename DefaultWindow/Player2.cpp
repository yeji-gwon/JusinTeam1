#include "pch.h"
#include "Player2.h"

Player2* Player2::pInstance(nullptr);

Player2::Player2()
{
}


Player2::~Player2()
{
	Release();
}

void Player2::Initialize()
{
	m_vCenterHead = { 375.f, 300.f - 7.5f, 0.f };
	m_fAngleX = 0.f;
	m_fAngleY = 0.f;
	m_fAngleZ = 0.f;
	m_fAngleA = 0.f;
	m_fSpeed = 5.f;

	m_tHead.m_vCenter = m_vCenterHead;
	m_tHead.m_vScale = { 20.f, 20.f, 0.f };
	m_tHead.Set_Size(36);


	// TODO? : 입모양 추가
	m_vBodyPoint[0] = { -6.f / (m_tHead.m_vScale.x / 2), 8.f / (m_tHead.m_vScale.y / 2), 0.f };
	m_vBodyPoint[1] = { m_vBodyPoint[0].x - 1, m_vBodyPoint[0].y + 1, 0.f };
	m_vBodyPoint[2] = { m_vBodyPoint[1].x + 1.25f, m_vBodyPoint[1].y + 1.25f, 0.f };
	m_vBodyPoint[3] = { m_vBodyPoint[1].x + 2.5f, m_vBodyPoint[1].y + 2.5f, 0.f };
	m_vBodyPoint[4] = { m_vBodyPoint[1].x - 1, m_vBodyPoint[1].y - 1, 0.f };
	m_vBodyPoint[5] = { m_vBodyPoint[1].x - 2, m_vBodyPoint[1].y - 2, 0.f };
	m_vBodyPoint[6] = { m_vBodyPoint[1].x - 1.5f, m_vBodyPoint[1].y + 1.5f, 0.f };
	m_vBodyPoint[7] = { m_vBodyPoint[6].x + 1, m_vBodyPoint[6].y, 0.f };
	m_vBodyPoint[8] = { m_vBodyPoint[7].x, m_vBodyPoint[6].y + 2, 0.f };
	m_vBodyPoint[9] = { m_vBodyPoint[6].x - 1, m_vBodyPoint[6].y + 1, 0.f };
	m_vBodyPoint[10] = { m_vBodyPoint[6].x - 2, m_vBodyPoint[6].y + 2, 0.f };

}

int Player2::Update()
{
	if (m_bHardFlip || m_bFlip || m_bShuvit)
		Update_Jump();

	Update_State();
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
	WorldHead.Set_Size(m_tHead.Size());
	for (int i = 0; i < m_tHead.Size(); i++)
		D3DXVec3TransformCoord(&WorldHead.m_vPoints[i], &m_tHead.m_vPoints[i], &m_matWorld);
	WorldHead.DrawPolygon(hDC);

	D3DXVECTOR3 m_vWorldPoint[11];
	for (int i = 0; i < size(m_vWorldPoint); i++)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vBodyPoint[i], &m_matWorld);
	}

	MoveToEx(hDC, m_vWorldPoint[0].x, m_vWorldPoint[0].y, NULL);
	LineTo(hDC, m_vWorldPoint[1].x, m_vWorldPoint[1].y);

	LineTo(hDC, m_vWorldPoint[2].x, m_vWorldPoint[2].y);
	LineTo(hDC, m_vWorldPoint[3].x, m_vWorldPoint[3].y);

	MoveToEx(hDC, m_vWorldPoint[1].x, m_vWorldPoint[1].y, NULL);
	LineTo(hDC, m_vWorldPoint[4].x, m_vWorldPoint[4].y);
	LineTo(hDC, m_vWorldPoint[5].x, m_vWorldPoint[5].y);

	MoveToEx(hDC, m_vWorldPoint[1].x, m_vWorldPoint[1].y, NULL);
	LineTo(hDC, m_vWorldPoint[6].x, m_vWorldPoint[6].y);

	LineTo(hDC, m_vWorldPoint[7].x, m_vWorldPoint[7].y);
	LineTo(hDC, m_vWorldPoint[8].x, m_vWorldPoint[8].y);

	MoveToEx(hDC, m_vWorldPoint[6].x, m_vWorldPoint[6].y, NULL);
	LineTo(hDC, m_vWorldPoint[9].x, m_vWorldPoint[9].y);
	LineTo(hDC, m_vWorldPoint[10].x, m_vWorldPoint[10].y);

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


	if (CKeyMgr::Get_Instance()->Key_Tap('Q'))
		m_bFlip = true;
	if (CKeyMgr::Get_Instance()->Key_Tap('W'))
		m_bShuvit = true;
	if (CKeyMgr::Get_Instance()->Key_Tap('E'))
		m_bHardFlip = true;

}

void Player2::Update_State()
{

	switch (m_eState)
	{
	case PLAYER_JUMP1:
		m_vBodyPoint[0] = { 0.f / (m_tHead.m_vScale.x / 2), 10.f / (m_tHead.m_vScale.y / 2), 0.f };
		m_vBodyPoint[1] = { m_vBodyPoint[0].x, m_vBodyPoint[0].y + 1, 0.f };

		m_vBodyPoint[2] = { m_vBodyPoint[1].x + 1.25f, m_vBodyPoint[1].y - 1.25f, 0.f };
		m_vBodyPoint[3] = { m_vBodyPoint[1].x + 2.5f, m_vBodyPoint[1].y - 2.5f, 0.f };

		m_vBodyPoint[4] = { m_vBodyPoint[1].x - 1.25f, m_vBodyPoint[1].y - 1.25f, 0.f };
		m_vBodyPoint[5] = { m_vBodyPoint[1].x - 2.5f, m_vBodyPoint[1].y - 2.5f, 0.f };

		m_vBodyPoint[6] = { m_vBodyPoint[1].x, m_vBodyPoint[1].y + 1.5f, 0.f };

		m_vBodyPoint[7] = { m_vBodyPoint[6].x + 1, m_vBodyPoint[6].y - 1, 0.f };
		m_vBodyPoint[8] = { m_vBodyPoint[6].x + 2, m_vBodyPoint[6].y + 2, 0.f };

		m_vBodyPoint[9] = { m_vBodyPoint[6].x - 1, m_vBodyPoint[6].y - 1, 0.f };
		m_vBodyPoint[10] = { m_vBodyPoint[6].x - 2, m_vBodyPoint[6].y + 2, 0.f };
		break;

	case PLAYER_JUMP2:
		m_vBodyPoint[0] = { 0.f / (m_tHead.m_vScale.x / 2), 10.f / (m_tHead.m_vScale.y / 2), 0.f };
		m_vBodyPoint[1] = { m_vBodyPoint[0].x, m_vBodyPoint[0].y + 1, 0.f };

		m_vBodyPoint[2] = { m_vBodyPoint[1].x + 1.f, m_vBodyPoint[1].y + 0.8f, 0.f };
		m_vBodyPoint[3] = { m_vBodyPoint[1].x + 2.f, m_vBodyPoint[1].y + 1.6f, 0.f };

		m_vBodyPoint[4] = { m_vBodyPoint[1].x - 1.f, m_vBodyPoint[1].y + 1.f, 0.f };
		m_vBodyPoint[5] = { m_vBodyPoint[4].x + 1.25f / 2.f, m_vBodyPoint[4].y + 1.25f / 2.5f, 0.f };

		m_vBodyPoint[6] = { m_vBodyPoint[1].x, m_vBodyPoint[1].y + 1.5f, 0.f };

		m_vBodyPoint[7] = { m_vBodyPoint[6].x, m_vBodyPoint[6].y + 1, 0.f };
		m_vBodyPoint[8] = { m_vBodyPoint[6].x, m_vBodyPoint[6].y + 2, 0.f };

		m_vBodyPoint[9] = { m_vBodyPoint[6].x - 1.f, m_vBodyPoint[6].y + 0.8f, 0.f };
		m_vBodyPoint[10] = { m_vBodyPoint[9].x + 0.5f, m_vBodyPoint[9].y + 0.8f, 0.f };

		m_fAngleY += 0.4f;
		break;

	case PLAYER_JUMP3:
		// 머리 위치 (회전 중심)
		m_vBodyPoint[0] = { 0.f / (m_tHead.m_vScale.x / 2), 10.f / (m_tHead.m_vScale.y / 2), 0.f };

		// 목
		m_vBodyPoint[1] = { m_vBodyPoint[0].x, m_vBodyPoint[0].y + 1, 0.f };

		// 오른팔 (어깨-팔꿈치 짧게, 팔꿈치-손목 길게 오른쪽으로)
		m_vBodyPoint[2] = { m_vBodyPoint[1].x + 1.0f, m_vBodyPoint[1].y + 0.2f, 0.f };   // 팔꿈치 짧게
		m_vBodyPoint[3] = { m_vBodyPoint[2].x + 1.2f, m_vBodyPoint[2].y - 1.5f, 0.f };   // 손목 오른쪽 위로 길게

		// 왼팔 (어깨-팔꿈치 짧게, 팔꿈치-손목 길게 오른쪽으로)
		m_vBodyPoint[4] = { m_vBodyPoint[1].x - 0.8f, m_vBodyPoint[1].y + 0.3f, 0.f };   // 팔꿈치 짧게
		m_vBodyPoint[5] = { m_vBodyPoint[4].x + 1.8f, m_vBodyPoint[4].y - 1.2f, 0.f };   // 손목 오른쪽으로 길게

		// 몸통
		m_vBodyPoint[6] = { m_vBodyPoint[1].x, m_vBodyPoint[1].y + 1.5f, 0.f };

		// 오른다리 (허벅지-무릎 짧게, 무릎-발목 길게 오른쪽으로)
		m_vBodyPoint[7] = { m_vBodyPoint[6].x + 0.8f, m_vBodyPoint[6].y + 0.3f, 0.f };   // 무릎 짧게
		m_vBodyPoint[8] = { m_vBodyPoint[7].x + 1.0f, m_vBodyPoint[7].y - 1.4f, 0.f };   // 발목 오른쪽 위로 길게

		// 왼다리 (허벅지-무릎 짧게, 무릎-발목 길게 오른쪽으로)
		m_vBodyPoint[9] = { m_vBodyPoint[6].x - 0.6f, m_vBodyPoint[6].y + 0.4f, 0.f };   // 무릎 짧게
		m_vBodyPoint[10] = { m_vBodyPoint[9].x + 1.5f, m_vBodyPoint[9].y - 1.1f, 0.f };  // 발목 오른쪽으로 길게

		m_fAngleZ += 0.45f;
		break;
	default:
		m_vBodyPoint[0] = { -6.f / (m_tHead.m_vScale.x / 2), 8.f / (m_tHead.m_vScale.y / 2), 0.f };
		m_vBodyPoint[1] = { m_vBodyPoint[0].x - 0.8f, m_vBodyPoint[0].y + 1, 0.f };

		// 오른팔 (자연스러운 각도)
		m_vBodyPoint[2] = { m_vBodyPoint[1].x + 1.0f, m_vBodyPoint[1].y + 1.0f, 0.f };
		m_vBodyPoint[3] = { m_vBodyPoint[2].x + 1.5f, m_vBodyPoint[2].y + 1.5f, 0.f };

		// 왼팔 (대칭)
		m_vBodyPoint[4] = { m_vBodyPoint[1].x - 1.0f, m_vBodyPoint[1].y + 1.0f, 0.f };
		m_vBodyPoint[5] = { m_vBodyPoint[4].x - 1.5f, m_vBodyPoint[4].y + 1.5f, 0.f };

		// 몸통
		m_vBodyPoint[6] = { m_vBodyPoint[1].x - 0.7f, m_vBodyPoint[1].y + 1.5f, 0.f };

		// 오른다리 (자연스러운 각도)
		m_vBodyPoint[7] = { m_vBodyPoint[6].x + 0.8f, m_vBodyPoint[6].y + 1.0f, 0.f };
		m_vBodyPoint[8] = { m_vBodyPoint[7].x + 0.2f, m_vBodyPoint[7].y + 1.5f, 0.f };

		// 왼다리 (대칭, 같은 지면 높이)
		m_vBodyPoint[9] = { m_vBodyPoint[6].x - 0.8f, m_vBodyPoint[6].y + 1.0f, 0.f };
		m_vBodyPoint[10] = { m_vBodyPoint[9].x - 0.2f, m_vBodyPoint[9].y + 1.5f, 0.f };
		break;
	}
}

void Player2::Update_Jump()
{
	//wchar_t szDebug[256];
//swprintf_s(szDebug, L"발끝 Y좌표: %.2f, 지면: %.2f, 점프속도: %.2f, 온그라운드: %s",
//	m_vBodyPoint[10].y, m_vCenterHead.y + m_vBodyPoint[10].y, m_fJumpVelocity, m_bOnGround ? L"참" : L"거짓");
//OutputDebugString(szDebug);
//OutputDebugString(L"\n");

	// 트릭 시작 시 점프 초기화
	if (m_bOnGround)
	{
		if (m_bFlip)
		{
			m_fJumpVelocity = -12.0f;      // 킥플립: 높은 점프
			m_eState = PLAYER_JUMP1;
		}
		else if (m_bShuvit)
		{
			m_fJumpVelocity = -10.0f;       // 슈빗: 낮은 점프
			m_eState = PLAYER_JUMP2;
		}
		else if (m_bHardFlip)
		{
			m_fJumpVelocity = -14.0f;      // 하드플립: 가장 높은 점프
			m_eState = PLAYER_JUMP3;
		}

		m_bOnGround = false;
	}
	else
	{
		m_fJumpVelocity += m_fGravity;
		m_vCenterHead.y += m_fJumpVelocity;
		float fBottomY = m_vBodyPoint[0].y;
		for (int i = 0; i < size(m_vBodyPoint); i++)
		{
			if (m_vBodyPoint[i].y > fBottomY)
				fBottomY = m_vBodyPoint[i].y;
		}
		float fHeight = 5.f * m_tHead.m_vScale.y;
		float fBoardLineY = Board2::Get_Instance()->Get_Center().second - (Board2::Get_Instance()->Get_Scale().second / 2.f);
		// 착지 처리 : -10.f 마진
		if (m_vCenterHead.y + fHeight >= fBoardLineY - 5.f)
		{
			// 머리 좌표 = 발 좌표(주로 오른발이 바닥에 먼저 닫는다) - 머리 중심 좌표(=0) + 보드 중심 y 좌표  (relative)
			m_vCenterHead.y = fBoardLineY - fHeight;
			m_fJumpVelocity = 0.0f;
			m_bOnGround = true;

			m_bFlip = false;
			m_bShuvit = false;
			m_fAngleY = 0.f;
			m_bHardFlip = false;
			m_fAngleZ = 0.f;
			m_eState = PLAYER_IDLE;
		}
	}
}


void Player2::Update_Matrix()
{
	D3DXMATRIX matScale, matRotX, matRotY, matRotZ, matTrans, matRotAxis, matOrbitTrans, matOrbitBack;
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matRotX);
	D3DXMatrixIdentity(&matRotY);
	D3DXMatrixIdentity(&matRotZ);
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matRotAxis);
	D3DXMatrixIdentity(&matOrbitTrans);
	D3DXMatrixIdentity(&matOrbitBack);
	// 크기
	D3DXMatrixScaling(&matScale, m_tHead.m_vScale.x, m_tHead.m_vScale.y, m_tHead.m_vScale.z);
	// 자전
	D3DXMatrixRotationX(&matRotX, m_fAngleX);
	D3DXMatrixRotationY(&matRotY, m_fAngleY);
	D3DXMatrixRotationZ(&matRotZ, m_fAngleZ);

	// 플레이어 위치
	D3DXMatrixTranslation(&matTrans, m_vCenterHead.x, m_vCenterHead.y, m_vCenterHead.z);
	
	// 일반적인 변환
	D3DXMatrixTranslation(&matTrans, m_vCenterHead.x, m_vCenterHead.y, m_vCenterHead.z);
	m_matWorld = matScale * matRotY * matRotX * matRotZ * matTrans;
	
}
