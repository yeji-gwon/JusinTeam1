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

	// 몸통 (머리 기준 상대 위치)
	m_vRelativeBody = { 0.f, 50.f, 0.f };  // 머리 아래 50픽셀
	m_fAngleBody = 0.f;
	m_tBody.m_vScale = { 20.f, 40.f, 0.f };
	m_tBody.Set_Size(4);  // 사각형

	// 왼팔 (머리 기준 상대 위치)
	m_vRelativeLeftArm = { -30.f, 40.f, 0.f };  // 머리 왼쪽 아래
	m_fAngleLeftArm = 0.f;
	m_tLeftArm.m_vScale = { 8.f, 25.f, 0.f };
	m_tLeftArm.Set_Size(4);

	// 오른팔 (머리 기준 상대 위치)
	m_vRelativeRightArm = { 30.f, 40.f, 0.f };  // 머리 오른쪽 아래
	m_fAngleRightArm = 0.f;
	m_tRightArm.m_vScale = { 8.f, 25.f, 0.f };
	m_tRightArm.Set_Size(4);

	// 왼다리 (머리 기준 상대 위치)
	m_vRelativeLeftLeg = { -15.f, 90.f, 0.f };  // 몸통 아래 왼쪽
	m_fAngleLeftLeg = 0.f;
	m_tLeftLeg.m_vScale = { 8.f, 30.f, 0.f };
	m_tLeftLeg.Set_Size(4);

	// 오른다리 (머리 기준 상대 위치)
	m_vRelativeRightLeg = { 15.f, 90.f, 0.f };  // 몸통 아래 오른쪽
	m_fAngleRightLeg = 0.f;
	m_tRightLeg.m_vScale = { 8.f, 30.f, 0.f };
	m_tRightLeg.Set_Size(4);

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

	// 몸통 렌더링
	struct tagPolygon WorldBody;
	WorldBody.Set_Size(4);
	for (int i = 0; i < m_tBody.Size(); i++)
		D3DXVec3TransformCoord(&WorldBody.m_vPoints[i], &m_tBody.m_vPoints[i], &m_matWorldBody);
	WorldBody.DrawPolygon(hDC);

	// 왼팔 렌더링
	struct tagPolygon WorldLeftArm;
	WorldLeftArm.Set_Size(4);
	for (int i = 0; i < m_tLeftArm.Size(); i++)
		D3DXVec3TransformCoord(&WorldLeftArm.m_vPoints[i], &m_tLeftArm.m_vPoints[i], &m_matWorldLeftArm);
	WorldLeftArm.DrawPolygon(hDC);

	// 오른팔 렌더링
	struct tagPolygon WorldRightArm;
	WorldRightArm.Set_Size(4);
	for (int i = 0; i < m_tRightArm.Size(); i++)
		D3DXVec3TransformCoord(&WorldRightArm.m_vPoints[i], &m_tRightArm.m_vPoints[i], &m_matWorldRightArm);
	WorldRightArm.DrawPolygon(hDC);

	// 왼다리 렌더링
	struct tagPolygon WorldLeftLeg;
	WorldLeftLeg.Set_Size(4);
	for (int i = 0; i < m_tLeftLeg.Size(); i++)
		D3DXVec3TransformCoord(&WorldLeftLeg.m_vPoints[i], &m_tLeftLeg.m_vPoints[i], &m_matWorldLeftLeg);
	WorldLeftLeg.DrawPolygon(hDC);

	// 오른다리 렌더링
	struct tagPolygon WorldRightLeg;
	WorldRightLeg.Set_Size(4);
	for (int i = 0; i < m_tRightLeg.Size(); i++)
		D3DXVec3TransformCoord(&WorldRightLeg.m_vPoints[i], &m_tRightLeg.m_vPoints[i], &m_matWorldRightLeg);
	WorldRightLeg.DrawPolygon(hDC);

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
	D3DXMATRIX matScale, matRot, matTrans;

	// 1. 머리 월드 행렬 (부모)
	D3DXMatrixScaling(&matScale, m_tHead.m_vScale.x, m_tHead.m_vScale.y, m_tHead.m_vScale.z);
	D3DXMatrixRotationZ(&matRot, m_fAngleZ);
	D3DXMatrixTranslation(&matTrans, m_vCenterHead.x, m_vCenterHead.y, m_vCenterHead.z);
	m_matWorldHead = matScale * matRot * matTrans;

	// 2. 몸통 월드 행렬 (머리의 자식)
	D3DXMatrixScaling(&matScale, m_tBody.m_vScale.x, m_tBody.m_vScale.y, m_tBody.m_vScale.z);
	D3DXMatrixRotationZ(&matRot, m_fAngleBody);
	D3DXMatrixTranslation(&matTrans, m_vRelativeBody.x, m_vRelativeBody.y, m_vRelativeBody.z);
	m_matWorldBody = matScale * matRot * matTrans * m_matWorldHead;

	// 3. 왼팔 월드 행렬 (머리의 자식)
	D3DXMatrixScaling(&matScale, m_tLeftArm.m_vScale.x, m_tLeftArm.m_vScale.y, m_tLeftArm.m_vScale.z);
	D3DXMatrixRotationZ(&matRot, m_fAngleLeftArm);
	D3DXMatrixTranslation(&matTrans, m_vRelativeLeftArm.x, m_vRelativeLeftArm.y, m_vRelativeLeftArm.z);
	m_matWorldLeftArm = matScale * matRot * matTrans * m_matWorldHead;

	// 4. 오른팔 월드 행렬 (머리의 자식)
	D3DXMatrixScaling(&matScale, m_tRightArm.m_vScale.x, m_tRightArm.m_vScale.y, m_tRightArm.m_vScale.z);
	D3DXMatrixRotationZ(&matRot, m_fAngleRightArm);
	D3DXMatrixTranslation(&matTrans, m_vRelativeRightArm.x, m_vRelativeRightArm.y, m_vRelativeRightArm.z);
	m_matWorldRightArm = matScale * matRot * matTrans * m_matWorldHead;

	// 5. 왼다리 월드 행렬 (머리의 자식)
	D3DXMatrixScaling(&matScale, m_tLeftLeg.m_vScale.x, m_tLeftLeg.m_vScale.y, m_tLeftLeg.m_vScale.z);
	D3DXMatrixRotationZ(&matRot, m_fAngleLeftLeg);
	D3DXMatrixTranslation(&matTrans, m_vRelativeLeftLeg.x, m_vRelativeLeftLeg.y, m_vRelativeLeftLeg.z);
	m_matWorldLeftLeg = matScale * matRot * matTrans * m_matWorldHead;

	// 6. 오른다리 월드 행렬 (머리의 자식)
	D3DXMatrixScaling(&matScale, m_tRightLeg.m_vScale.x, m_tRightLeg.m_vScale.y, m_tRightLeg.m_vScale.z);
	D3DXMatrixRotationZ(&matRot, m_fAngleRightLeg);
	D3DXMatrixTranslation(&matTrans, m_vRelativeRightLeg.x, m_vRelativeRightLeg.y, m_vRelativeRightLeg.z);
	m_matWorldRightLeg = matScale * matRot * matTrans * m_matWorldHead;
}

void Player2::Update_Direction()
{

}
