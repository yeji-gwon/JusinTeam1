#pragma once

#define WINCX		800
#define WINCY		600

#define PI			3.141592f

#define PURE		= 0

extern HWND g_hWnd;

enum SCENEID { SC_MENU, SC_STAGE1, SC_STAGE2, SC_STAGE3, SC_STAGE4, SC_END };

template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

typedef struct tagInfo
{
	D3DXVECTOR3			vPos;	
	
	D3DXVECTOR3			vDir;		
	D3DXVECTOR3			vLook;

	D3DXVECTOR3			vNormal;	
	D3DXMATRIX			matWorld;
}INFO;

static D3DXVECTOR3		Get_Mouse()
{
	POINT pt{ };
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return D3DXVECTOR3((float)pt.x, (float)pt.y, 0.f);
}


struct tagPolygon {
    vector<D3DXVECTOR3>m_vPoints;
    D3DXVECTOR3 m_vScale;
    D3DXVECTOR3 m_vCenter;

    float m_PointSize;

    tagPolygon()
        :m_PointSize(3), m_vPoints(3, { 0,0,0 })
    {
        m_vCenter = { 0,0,0 };
        Set_Points();
    }

private:
    void Set_Points() {
        for (int i = 0; i < m_PointSize; ++i) {
            float theta = (2 * 3.141592f * i) / m_PointSize;
            m_vPoints[i].x = cosf(theta);
            m_vPoints[i].y = sinf(theta);
            m_vPoints[i].z = 0.f;
        }
    }

public:
    void SyncToWorld(tagPolygon& rhs) {
        rhs.Set_Size(m_PointSize);
    }
    void Set_OnePoint(int index, D3DXVECTOR3 vector) {
        m_vPoints[index] = vector;
    }

    int Size() { return m_PointSize; }

    void Set_Size(int size) {
        if (size > m_PointSize) {
            m_vPoints.resize(size, { 0.f, 0.f, 0.f });
        }
        m_PointSize = size;
        Set_Points();
    }

    void DrawPolygon(HDC hDC) {
        MoveToEx(hDC, m_vPoints[0].x, m_vPoints[0].y, nullptr);
        for (int i = 1; i < Size(); ++i) {
            LineTo(hDC, m_vPoints[i].x, m_vPoints[i].y);
        }
        LineTo(hDC, m_vPoints[0].x, m_vPoints[0].y);
    }
};