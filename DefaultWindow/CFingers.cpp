#include "pch.h"
#include "CFingers.h"
#include "CFinger.h"

CFingers::CFingers()
{
}

CFingers::~CFingers()
{
}

void CFingers::Initialize()
{
	m_mapFingers["thumb"] = new CFinger;
	m_mapFingers["thumb"]->Initialize();
	dynamic_cast<CFinger*>(m_mapFingers["thumb"])->Set_Trans({ 400, 600 }, { 300, 510 }, { 285,450 }, { 285,420 });
	dynamic_cast<CFinger*>(m_mapFingers["thumb"])->Set_RotZ(30, 45, 20);

	m_mapFingers["index"] = new CFinger;
	m_mapFingers["index"]->Initialize();
	dynamic_cast<CFinger*>(m_mapFingers["index"])->Set_Trans({ 400, 600 }, { 340, 495 }, { 340, 405 }, { 340, 330 });
	dynamic_cast<CFinger*>(m_mapFingers["index"])->Set_RotZ(30, 45, 20);

	m_mapFingers["middle"] = new CFinger;
	m_mapFingers["middle"]->Initialize();
	dynamic_cast<CFinger*>(m_mapFingers["middle"])->Set_Trans({ 400, 600 }, { 400, 480 }, { 400, 390 }, { 400, 300 });
	dynamic_cast<CFinger*>(m_mapFingers["middle"])->Set_RotZ(30, 45, 20);

	m_mapFingers["ring"] = new CFinger;
	m_mapFingers["ring"]->Initialize();
	dynamic_cast<CFinger*>(m_mapFingers["ring"])->Set_Trans({ 400, 600 }, { 460, 495 }, { 460, 405 }, { 460, 330 });
	dynamic_cast<CFinger*>(m_mapFingers["ring"])->Set_RotZ(30, 45, 20);

	m_mapFingers["little"] = new CFinger;
	m_mapFingers["little"]->Initialize();
	dynamic_cast<CFinger*>(m_mapFingers["little"])->Set_Trans({ 400, 600 }, { 505, 510 }, { 520, 465 }, { 520, 395 });
	dynamic_cast<CFinger*>(m_mapFingers["little"])->Set_RotZ(30, 45, 20);
}

int CFingers::Update()
{
	for (auto& Finger : m_mapFingers)
	{
		Finger.second->Update();
	}
	return 0;
}

void CFingers::Late_Update()
{
	for (auto& Finger : m_mapFingers)
	{
		Finger.second->Late_Update();

	}
}

void CFingers::Render(HDC hDC)
{
	for (auto& Finger : m_mapFingers)
	{
		Finger.second->Render(hDC);
	}
}

void CFingers::Release()
{
}
