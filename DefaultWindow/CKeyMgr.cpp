#include "pch.h"
#include "CKeyMgr.h"

CKeyMgr::CKeyMgr()
	:m_KeyContainer(256, KeyState::NONE)
{
}

CKeyMgr::~CKeyMgr()
{
	Release();
}

int CKeyMgr::Update()
{
	for (int i = 0; i < 256; ++i) {
		if (GetAsyncKeyState(i) & 0x8000) {
			if (m_KeyContainer[i] == KeyState::NONE || m_KeyContainer[i] == KeyState::AWAY) {
				m_KeyContainer[i] = KeyState::TAP;
			}
			else {
				m_KeyContainer[i] = KeyState::HOLD;
			}
		}
		else {
			if (m_KeyContainer[i] == KeyState::NONE || m_KeyContainer[i] == KeyState::AWAY) {
				m_KeyContainer[i] = KeyState::NONE;
			}
			else {
				m_KeyContainer[i] = KeyState::AWAY;
			}
		}
	}
}

void CKeyMgr::Late_Update()
{
}

void CKeyMgr::Release()
{
	m_KeyContainer.clear();
}

bool CKeyMgr::Key_Down(int _vk)
{
	return m_KeyContainer[_vk] == KeyState::HOLD || m_KeyContainer[_vk] == KeyState::TAP;
}

bool CKeyMgr::Key_Tap(int _vk)
{
	return m_KeyContainer[_vk] == KeyState::TAP;
}

bool CKeyMgr::Key_Hold(int _vk)
{
	return m_KeyContainer[_vk] == KeyState::HOLD;
}

bool CKeyMgr::Key_Away(int _vk)
{
	return m_KeyContainer[_vk] == KeyState::AWAY;
}
