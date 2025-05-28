#pragma once
#include "CObj.h"

class CFinger : public CObj
{
public:
	CFinger();
	virtual ~CFinger();

public:
	void		Set_Trans(POINT _ptWrist, POINT _ptMCP, POINT _ptPIP, POINT _ptDIP);
	void		Set_RotZ(float _fMCP, float _fPIP, float _fDIP);
public:
	void		Initialize() override;
	int			Update() override;
	void		Late_Update() override;
	void		Render(HDC hDC) override;
	void		Release() override;

private:
	CObj*			m_pWrist;	//손목
	CObj*			m_pMCP;		//손가락 관절1
	CObj*			m_pPIP;		//손가락 관절2
	CObj*			m_pDIP;		//손가락 관절3
};