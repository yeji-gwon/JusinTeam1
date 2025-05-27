#include "pch.h"
#include "CFinger.h"
#include "CJoint.h"

CFinger::CFinger()
{
}

CFinger::~CFinger()
{
}

void CFinger::Set_Trans(POINT _ptWrist, POINT _ptMCP, POINT _ptPIP, POINT _ptDIP)
{
	dynamic_cast<CJoint*>(m_pWrist)->Set_Trans(_ptWrist.x, _ptWrist.y, 0.f);
	dynamic_cast<CJoint*>(m_pMCP)->Set_Trans(_ptMCP.x, _ptMCP.y, 0.f);
	dynamic_cast<CJoint*>(m_pPIP)->Set_Trans(_ptPIP.x, _ptPIP.y, 0.f);
	dynamic_cast<CJoint*>(m_pDIP)->Set_Trans(_ptDIP.x, _ptDIP.y, 0.f);
}

void CFinger::Set_RotZ(float _fMCP, float _fPIP, float _fDIP)
{
	dynamic_cast<CJoint*>(m_pMCP)->Set_RotZ(_fMCP);
	dynamic_cast<CJoint*>(m_pPIP)->Set_RotZ(_fPIP);
	dynamic_cast<CJoint*>(m_pDIP)->Set_RotZ(_fDIP);
}

void CFinger::Initialize()
{
	m_pWrist = new CJoint;
	m_pWrist->Initialize();
	dynamic_cast<CJoint*>(m_pWrist)->Set_ParentPtr(nullptr);

	m_pMCP = new CJoint;
	m_pMCP->Initialize();
	dynamic_cast<CJoint*>(m_pMCP)->Set_ParentPtr(dynamic_cast<CJoint*>(m_pWrist));

	m_pPIP= new CJoint;
	m_pPIP->Initialize();
	dynamic_cast<CJoint*>(m_pPIP)->Set_ParentPtr(dynamic_cast<CJoint*>(m_pMCP));
	
	m_pDIP = new CJoint;
	m_pDIP->Initialize();
	dynamic_cast<CJoint*>(m_pDIP)->Set_ParentPtr(dynamic_cast<CJoint*>(m_pPIP));
}

int CFinger::Update()
{
	m_pWrist->Update();
	m_pMCP->Update();
	m_pPIP->Update();
	m_pDIP->Update();
	return 0;
}

void CFinger::Late_Update()
{
	m_pWrist->Late_Update();
	m_pMCP->Late_Update();
	m_pPIP->Late_Update();
	m_pDIP->Late_Update();
}

void CFinger::Render(HDC hDC)
{
	m_pMCP->Render(hDC);
	m_pPIP->Render(hDC);
	m_pDIP->Render(hDC);
}

void CFinger::Release()
{
	Safe_Delete(m_pWrist);
	Safe_Delete(m_pMCP);
}
