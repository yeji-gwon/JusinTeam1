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
	m_vCenterHead = { 375.f, 300.f , 0.f };
	m_fAngleX = 0.f;
	m_fAngleY = 0.f;
	m_fAngleZ = 0.f;
	m_fAngleA = 0.f;
	m_fSpeed = 5.f;

	m_tHead.m_vCenter = m_vCenterHead;
	m_tHead.m_vScale = { 20.f, 20.f, 0.f };
	m_tHead.Set_Size(36);
	m_tHead.SyncToWorld(m_tHead);


	// TODO? : �Ը�� �߰�
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
	// TODO : Flip ���� ���� �� ���� (JUMP2, 3)
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
		m_vBodyPoint[5] = { m_vBodyPoint[4].x + 1.25f/2.f, m_vBodyPoint[4].y + 1.25f/2.5f, 0.f };

		m_vBodyPoint[6] = { m_vBodyPoint[1].x, m_vBodyPoint[1].y + 1.5f, 0.f };

		m_vBodyPoint[7] = { m_vBodyPoint[6].x, m_vBodyPoint[6].y + 1, 0.f };
		m_vBodyPoint[8] = { m_vBodyPoint[6].x, m_vBodyPoint[6].y + 2, 0.f };

		m_vBodyPoint[9] = { m_vBodyPoint[6].x - 1.f, m_vBodyPoint[6].y + 0.8f, 0.f };
		m_vBodyPoint[10] = { m_vBodyPoint[9].x + 0.5f, m_vBodyPoint[9].y + 0.8f, 0.f };

		m_fAngleY += 0.4f;
		break;

	case PLAYER_JUMP3:
		m_vBodyPoint[0] = { 0.f / (m_tHead.m_vScale.x / 2), 10.f / (m_tHead.m_vScale.y / 2), 0.f };

		// ��
		m_vBodyPoint[1] = { m_vBodyPoint[0].x, m_vBodyPoint[0].y + 1, 0.f };

		// ������ (ȸ���� ���� �� ��������)
		m_vBodyPoint[2] = { m_vBodyPoint[1].x + 0.8f, m_vBodyPoint[1].y + 0.5f, 0.f };
		m_vBodyPoint[3] = { m_vBodyPoint[2].x + 1.2f, m_vBodyPoint[2].y + 0.3f, 0.f };

		// ���� (ȸ�� �ݴ�������)
		m_vBodyPoint[4] = { m_vBodyPoint[1].x - 0.8f, m_vBodyPoint[1].y + 0.8f, 0.f };
		m_vBodyPoint[5] = { m_vBodyPoint[4].x - 1.0f, m_vBodyPoint[4].y + 0.5f, 0.f };

		// ����
		m_vBodyPoint[6] = { m_vBodyPoint[1].x, m_vBodyPoint[1].y + 1.8f, 0.f };

		// �����ٸ� (���� ���θ�)
		m_vBodyPoint[7] = { m_vBodyPoint[6].x + 0.5f, m_vBodyPoint[6].y + 1.2f, 0.f };
		m_vBodyPoint[8] = { m_vBodyPoint[7].x + 0.3f, m_vBodyPoint[7].y + 1.5f, 0.f };

		// �޴ٸ� (�ణ �ڷ�)
		m_vBodyPoint[9] = { m_vBodyPoint[6].x - 0.3f, m_vBodyPoint[6].y + 1.0f, 0.f };
		m_vBodyPoint[10] = { m_vBodyPoint[9].x - 0.2f, m_vBodyPoint[9].y + 1.8f, 0.f };
		m_fAngleA += 0.45f;
		break;
	default:
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
		break;
	}
}

void Player2::Update_Jump()
{
	//wchar_t szDebug[256];
//swprintf_s(szDebug, L"�߳� Y��ǥ: %.2f, ����: %.2f, �����ӵ�: %.2f, �±׶���: %s",
//	m_vBodyPoint[10].y, m_vCenterHead.y + m_vBodyPoint[10].y, m_fJumpVelocity, m_bOnGround ? L"��" : L"����");
//OutputDebugString(szDebug);
//OutputDebugString(L"\n");

	// Ʈ�� ���� �� ���� �ʱ�ȭ
	if (m_bOnGround)
	{
		if (m_bFlip)
		{
			m_fJumpVelocity = -12.0f;      // ű�ø�: ���� ����
			m_eState = PLAYER_JUMP1;
		}
		else if (m_bShuvit)
		{
			m_fJumpVelocity = -8.0f;       // ����: ���� ����
			m_eState = PLAYER_JUMP2;
		}
		else if (m_bHardFlip)
		{
			m_fJumpVelocity = -14.0f;      // �ϵ��ø�: ���� ���� ����
			m_eState = PLAYER_JUMP3;
			m_vRotAxis = { 1.0f, 0.2f, 0.8f };
		}

		m_bOnGround = false;
	}
	else
	{
		m_fJumpVelocity += m_fGravity;
		m_vCenterHead.y += m_fJumpVelocity;
		
		// ���� ó��
		// TODO : ������ �߽�x��ǥ ���� ��� ����
		if (m_vCenterHead.y + m_vBodyPoint[10].y >= m_fGroundY - 20.f)
		{
			m_vCenterHead.y = 300.f;
			m_fJumpVelocity = 0.0f;
			m_bOnGround = true;
			
			m_bFlip = false;
			m_bShuvit = false;
			m_fAngleY = 0.f;
			m_bHardFlip = false;
			m_fAngleA = 0.f;
			m_eState = PLAYER_IDLE;
		}
	}
}


void Player2::Update_Matrix()
{
	D3DXMATRIX matScale, matRotX, matRotY, matRotZ, matTrans, matRotAxis;
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matRotX);
	D3DXMatrixIdentity(&matRotY);
	D3DXMatrixIdentity(&matRotZ);
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matRotAxis);
	// ũ��
	D3DXMatrixScaling(&matScale, m_tHead.m_vScale.x, m_tHead.m_vScale.y, m_tHead.m_vScale.z);
	// ����
	D3DXMatrixRotationX(&matRotX, m_fAngleX);
	D3DXMatrixRotationY(&matRotY, m_fAngleY);
	D3DXMatrixRotationZ(&matRotZ, m_fAngleZ);
	// �̵�
	D3DXMatrixTranslation(&matTrans, m_vCenterHead.x, m_vCenterHead.y, m_vCenterHead.z);
	// ����
	D3DXMatrixRotationAxis(&matRotAxis, &m_vRotAxis, m_fAngleA);
	// �θ� : X
	m_matWorld = matScale * matRotY * matRotX * matRotZ * matTrans * matRotAxis;

	D3DXMatrixIdentity(&matScale);
	// ũ���̰���
	m_matBodyWorld = matScale * matRotY * matRotX * matRotZ * matTrans * matRotAxis;
}
