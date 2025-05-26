// DefaultWindow.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "DefaultWindow.h"
#include "CMainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND       g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));

    MSG msg;
    msg.message = WM_NULL;

    CMainGame       MainGame;
    MainGame.Initialize();

    DWORD   dwTime = GetTickCount();

    // 기본 메시지 루프입니다:
    while (true)
    {
        // PM_REMOVE : 메세지 큐에 있는 메세지를 확인 후 제거
        // PM_NOREMOVE : 메세지 큐에 메세지 여부만 확인, 만약 메세지를 가져와야 할 경우, 개별적으로 getmessage 함수를 호출해야 함

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        
        else
        {
            if (dwTime + 10 < GetTickCount())
            {
                MainGame.Update();
                MainGame.Late_Update();
                MainGame.Render();

                dwTime = GetTickCount();
            }        
        }
        
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;   // 윈도우 창 생성을 위해 값을 채워야할 구조체

    wcex.cbSize = sizeof(WNDCLASSEX);       // 자기 자신의 사이즈를 저장

    wcex.style          = CS_HREDRAW | CS_VREDRAW;

    // 가로 다시 그리기 | 세로 다시 그리기
    // 윈도우 창의 스타일 정의, 초기화 되는 값이 창의 수평, 수직 크기가 변할 경우 다시 그리기를 말하는 옵션

    wcex.lpfnWndProc    = WndProc;
    // 메세지 처리기 함수의 이름을 전달

    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    // 윈도우가 특수한 목적으로 사용하는 여분의 공간(일종의 예약 영역)

    wcex.hInstance      = hInstance;
    // 윈도우 클래스를 사용하는 프로그램의 번호를 설정, main함수 매개 변수 전달 값이 자동 사용

    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));
    // 윈도우 차이 사용할 아이콘 지정

    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    // 창에서 사용할 마우스 커서

    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    // 창 배경 색상

    wcex.lpszMenuName = NULL; //MAKEINTRESOURCEW(IDC_DEFAULTWINDOW);
    // 창 메뉴

    wcex.lpszClassName  = szWindowClass;
    // 실행 파일 이름 지정

    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    // 창 상단의 아이콘

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    RECT rc{ 0, 0, WINCX, WINCY };

   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // rc = rc + 기본 창 옵션 + 메뉴 바 사이즈 고려 여부

   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass,     // 클래스 이름(실행 파일 이름)
                            szTitle,            // 창 위에 띄울 문자열
                            WS_OVERLAPPEDWINDOW, // 윈도우 창 스타일 옵션(기본 창 모양)
                            CW_USEDEFAULT, 0,   // 창 생성 위치(X, Y 좌표)
                            rc.right - rc.left,
                            rc.bottom - rc.top,           // 창의 가로, 세로 사이즈
                            nullptr,            // 부모 윈도우 핸들
                            nullptr,            // 윈도우에서 사용할 메뉴 핸들
                            hInstance,          // 윈도우를 만드는 주체
                            nullptr);           // 운영체제가 특수한 목적으로 사용

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

// kernel : 메모리를 관리하고 프로그램을 실행시키는 명령어 집합
// user : 유저 인터페이스와 윈도우 창 관리 명령어 집합
// gdi : 화면 처리와 그래픽 담당 명령어 집합

RECT rc{ 100, 100, 200, 200 };
list<RECT>      BulletList;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    //case WM_CREATE:

    //    SetTimer(hWnd, 0, 0, 0);
    //    
    //    // 타이머 설치 함수
    //    // 1. 윈도우 핸들
    //    // 2. 타이머 id
    //    // 3. 타이머 주기(default 1 / 1000)
    //    // 4. NULL인 경우 3 매개 변수 주기로 WM_TIMER 메세지를 발생시킴
    //    break;

    //case WM_TIMER:

    //    InvalidateRect(hWnd, 0, TRUE);

    //    // 윈도우 갱신 함수
    //    // 1. 갱신할 윈도우 핸들
    //    // 2. 윈도우 갱신 범위(NULL 인 경우 화면 전체 영역)
    //    // 3. TRUE : 그려져 있지 않는 부분도 갱신
    //    //   FALSE : 새로 그리는 부분만 갱신
    //    break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;

            // dc : 출력에 관한 정보를 갖고 있는 구조체

            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

           // MoveToEx(hdc, 100, 100, nullptr);       // 4인자 : 이전 커서의 위치 반환 값
           //
           // LineTo(hdc, 200, 100);
           // LineTo(hdc, 200, 200);
           // LineTo(hdc, 100, 200);
           // LineTo(hdc, 100, 100);
           // LineTo(hdc, 200, 200);
           //
           // MoveToEx(hdc, 200, 100, nullptr);
           // LineTo(hdc, 100, 200);

           //  Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
           // 
           // 
           //  for (auto& Bullet : BulletList)
           //  {
           //      Ellipse(hdc, Bullet.left, Bullet.top, Bullet.right, Bullet.bottom);
           // 
           //      Bullet.top -= 10;
           //      Bullet.bottom -= 10;
           //  }


            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN:

        switch (wParam)
        {
     

   /*     case VK_SPACE:

            BulletList.push_back(rc);

            break;*/

        case VK_ESCAPE:
            DestroyWindow(g_hWnd);
            break;
        }

        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
