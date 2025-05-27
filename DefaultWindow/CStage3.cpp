#include "pch.h"
#include "CStage3.h"
#include "CKeyMgr.h"
#include "CObj.h"
#include "CHandle.h"
#include "CDriver.h"
#include "CRoad.h"

CStage3::CStage3()
	:m_pHandle(nullptr),m_pDriver(nullptr), m_pRoad(nullptr)
{
}

CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize()
{
	m_pHandle = new CHandle;
	m_pHandle->Initialize();
	m_pDriver = new CDriver;
	m_pDriver->Initialize();
	m_pRoad = new CRoad;
	m_pRoad->Initialize();
}

int CStage3::Update()
{
	CKeyMgr::Get_Instance()->Update();
	m_pHandle->Update();
	static_cast<CDriver*>(m_pDriver)->Set_CenterLeft(static_cast<CHandle*>(m_pHandle)->Get_Point_World(20));
	static_cast<CDriver*>(m_pDriver)->Set_CenterRight(static_cast<CHandle*>(m_pHandle)->Get_Point_World(49));
	static_cast<CDriver*>(m_pDriver)->Get_Rotate(static_cast<CHandle*>(m_pHandle)->Get_Rotate());
	m_pDriver->Update();
	m_pRoad->Update();
	return 0;
}

void CStage3::Late_Update()
{
	m_pHandle->Late_Update();
	m_pDriver->Late_Update();
	m_pRoad->Late_Update();
}

void CStage3::Render(HDC hDC)
{
	m_pRoad->Render(hDC);
	m_pHandle->Render(hDC);
	m_pDriver->Render(hDC);
}

void CStage3::Release()
{
	Safe_Delete<CObj*>(m_pHandle);
	Safe_Delete<CObj*>(m_pDriver);
	Safe_Delete<CObj*>(m_pRoad);
}
