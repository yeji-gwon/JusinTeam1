#include "pch.h"
#include "CStage3.h"
#include "CKeyMgr.h"
#include "CObj.h"
#include "CHandle.h"

CStage3::CStage3()
	:m_pHandle(nullptr)
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
}

int CStage3::Update()
{
	CKeyMgr::Get_Instance()->Update();
	m_pHandle->Update();
	return 0;
}

void CStage3::Late_Update()
{
	m_pHandle->Late_Update();
}

void CStage3::Render(HDC hDC)
{
	m_pHandle->Render(hDC);
}

void CStage3::Release()
{
}
