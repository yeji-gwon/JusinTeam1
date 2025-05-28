#pragma once
class CTimeMgr
{
private:
	CTimeMgr();
	~CTimeMgr();
	CTimeMgr(CTimeMgr& rhs) = delete;
	CTimeMgr operator = (CTimeMgr& rhs) = delete;

public:
	static CTimeMgr* Get_Instance() {
		if (!m_pInstance) {
			m_pInstance = new CTimeMgr;
		}
		return m_pInstance;
	}
	static void Destroy_Instance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();

public:
	float Get_Delta() { return m_fDeltaTime; }

private:
	static CTimeMgr* m_pInstance;

	//������ ǥ��
	TCHAR m_szBuffer[32];
	//���� ī����
	LARGE_INTEGER m_nCurCnt;
	//���� ī����
	LARGE_INTEGER m_nPrevCnt;
	//�ʴ� ���� (ī����)
	LARGE_INTEGER m_nFrequency;
	//��Ÿ Ÿ�� (�����Ӵ� ��)
	float m_fDeltaTime;
	//frame per Second
	int m_iFPS;
private:
	int m_iFrameCount = 0;
	float m_fFPSTimeAcc = 0.f;
};

