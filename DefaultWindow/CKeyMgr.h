#pragma once
class CKeyMgr
{
public:
	enum class KeyState {
		NONE,
		TAP,
		HOLD,
		AWAY
	};

private:
	CKeyMgr();
	~CKeyMgr();

public:
	int			Update();
	void		Late_Update();
	void		Release();

public:
	static CKeyMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CKeyMgr;
		}

		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	bool Key_Down(int _vk);
	bool Key_Tap(int _vk);
	bool Key_Hold(int _vk);
	bool Key_Away(int _vk);

private:
	static CKeyMgr* m_pInstance;
	vector<KeyState> m_KeyContainer;

};

