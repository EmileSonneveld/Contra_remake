//-----------------------------------------------------------------
// Game Engine Object
// C++ Source - GameEngine.cpp - version 2012 v2_10
// Copyright Kevin Hoefman, Bart Uyttenhove, Peter Verswyvelen
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "GameEngine.h"

#define _USE_MATH_DEFINES	// necessary for including (among other values) PI  - see math.h
#include <math.h>			// used in various draw methods
#include <stdio.h>
#include <tchar.h>			// used for unicode strings

#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory.h>

//-----------------------------------------------------------------
// Static Variable Initialization
//-----------------------------------------------------------------
GameEngine* GameEngine::m_GameEnginePtr = 0;

//-----------------------------------------------------------------
// Windows Functions
//-----------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Route all Windows messages to the game engine
	return GameEngine::GetSingleton()->HandleEvent(hWindow, msg, wParam, lParam);
}

DWORD WINAPI KeybThreadProc(GameEngine* gamePtr)
{
	return gamePtr->KeybThreadProc();
}

DWORD WINAPI MyFirstThreadProc(GameEngine* gamePtr)
{
	return gamePtr->MyFirstThreadProc();
}

//-----------------------------------------------------------------
// GameEngine Constructor(s)/Destructor
//-----------------------------------------------------------------
GameEngine::GameEngine() : m_hInstance(0),
m_hWindow(NULL),
m_TitlePtr(0),
m_PaintTimeTrigger(1.0 / 60),		// 60 FPS default
m_bSleep(true),
m_bRunGameLoop(false),
m_bKeybRunning(true),	// create the keyboard monitoring thread
m_KeyListPtr(0),
m_KeybMonitor(0),		// binary ; 0 = key not pressed, 1 = key pressed
m_IsPainting(false),
m_IsDoublebuffering(false),
m_GamePtr(0),
m_PaintDoublebuffered(false),
m_Fullscreen(false),

m_D2DFactoryPtr(0),
m_WICFactoryPtr(0),
m_RenderTargetPtr(0),
m_DWriteFactoryPtr(0),
m_GraphicsEnginePtr(0),
m_GameTickTimerPtr(0),
m_GamePaintTimerPtr(0),

m_bInitialized(false),

m_ColorBrushPtr(0),
m_AntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED),
m_BitmapInterpolationMode(D2D1_BITMAP_INTERPOLATION_MODE_LINEAR),
m_DefaultFontPtr(0),
m_UserFontPtr(0)
{
	CoInitialize(0);
	CreateDeviceIndependentResources();
	m_hKeybThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) ::KeybThreadProc, this, NULL, &m_dKeybThreadID);

	m_hMyFirstThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) ::MyFirstThreadProc, this, NULL, &m_dMyFirstThreadID);
}

GameEngine::~GameEngine()
{
	// Clean up the keyboard monitoring thread
	m_bKeybRunning = false;
	WaitForSingleObject(m_hKeybThread, INFINITE);
	CloseHandle(m_hKeybThread);

	// clean up keyboard monitor buffer after the thread that uses it is closed
	if (m_KeyListPtr != 0)
	{
		delete m_KeyListPtr;
		m_KeyListPtr = 0;
	}

	// Direct2D paint stuff
	m_ColorBrushPtr->Release();
	delete m_DefaultFontPtr;
	m_DefaultFontPtr = 0;

	// Other stuff
	delete m_GameTickTimerPtr;
	delete m_GamePaintTimerPtr;
	delete m_TitlePtr;
	delete m_GamePtr;

	m_DWriteFactoryPtr->Release();
	m_RenderTargetPtr->Release();
	m_WICFactoryPtr->Release();
	m_D2DFactoryPtr->Release();

	CoUninitialize();
}

//-----------------------------------------------------------------
// Game Engine Static Methods
//-----------------------------------------------------------------
GameEngine* GameEngine::GetSingleton()
{
	if (m_GameEnginePtr == 0) m_GameEnginePtr = new GameEngine();
	return m_GameEnginePtr;
}

void GameEngine::SetGame(AbstractGame* gamePtr)
{
	m_GamePtr = gamePtr;
}

DWORD GameEngine::MyFirstThreadProc()
{
	return 0;
	// MIJN EERSTE THREAD !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!! EUFORIE !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Geen idee hoe het werkt, maa copy pasten uit de game engine lukt goed... :)
	while (true) {
		if (IsKeyDown('K')) {
			MessageBox("stop deze thread");
			return 0;
		}
		//Sleep(2000);
		//MessageBox("2 sec gepaseert!");
	}
	return 0;
}

DWORD GameEngine::KeybThreadProc()
{
	while (m_bKeybRunning)
	{
		if (m_KeyListPtr != 0)
		{
			int count = 0;
			int key = m_KeyListPtr[0];

			while (key != '\0' && count < (8 * sizeof(unsigned int)))
			{
				if (!(GetAsyncKeyState(key) < 0))			// key is not pressed
				{
					if (m_KeybMonitor & (0x1 << count)) {
						m_GamePtr->KeyPressed(key);			// if the bit was 1 then this fires a keypress
					}
					m_KeybMonitor &= ~(0x1 << count);		// the bit is set to 0: key is not pressed
				}
				else m_KeybMonitor |= (0x1 << count);		// the bit is set to 1: key is pressed

				key = m_KeyListPtr[++count];				// increase count and get next key
			}
		}

		Sleep(1000 / KEYBCHECKRATE);
	}
	return 0;
}

//-----------------------------------------------------------------
// Game Engine General Methods
//-----------------------------------------------------------------
void GameEngine::SetTitle(const String& strTitleRef)
{
	delete m_TitlePtr; // delete the title string if it already exists
	m_TitlePtr = new String(strTitleRef);
}

bool GameEngine::Run(HINSTANCE hInstance, int iCmdShow)
{
	// create the game engine object, exit if failure
	if (GameEngine::GetSingleton() == 0) return false;

	// set the instance member variable of the game engine
	GameEngine::GetSingleton()->SetInstance(hInstance);

	// Seed the random number generator
	srand(GetTickCount());

	// Game Initialization
	m_GamePtr->GameInitialize(hInstance);

	// Open the window
	if (!GameEngine::GetSingleton()->ClassRegister(iCmdShow)) return false;

	// Initialize the Graphics Engine
	CreateDeviceResources();

	// User defined functions for start of the game
	m_GamePtr->GameStart();

	// Call GamePaint()
	Repaint();

	// Attach the keyboard thread to the main thread. This gives the keyboard events access to the window state
	// In plain English: this allows a KeyPressed() event to hide the cursor of the window.
	AttachThreadInput(m_dKeybThreadID, GetCurrentThreadId(), true);

	//Initialize the high precision timers
	m_GameTickTimerPtr = new StopWatch();
	m_GameTickTimerPtr->Reset();
	m_GameTickTimerPtr->Start();
	m_GamePaintTimerPtr = new StopWatch();
	m_GamePaintTimerPtr->Reset();
	m_GamePaintTimerPtr->Start();

	// Enter the main message loop
	MSG msg;
	double dTimeTrigger = 0;
	//time in seconds, base tick frequency on paint frequency

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Process the message
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Make sure the game engine isn't sleeping
			if (m_bSleep == false && m_bRunGameLoop == true)
			{
				//Tick timing is independent from Paint timing
				double tickTimeTrigger = m_PaintTimeTrigger / m_TickPaintRatio;
				m_GameTickTimerPtr->Tick();
				double tickTimeNow = m_GameTickTimerPtr->GetGameTime();
				if (tickTimeNow > tickTimeTrigger)
				{
					m_GameTickTimerPtr->Reset();
					m_GameTickTimerPtr->Start();
					m_GamePtr->GameTick(tickTimeNow);
				}
				// Check the time to see if a Draw cycle has elapsed
				//Draw Timing
				m_GamePaintTimerPtr->Tick();
				dTimeTrigger = m_GamePaintTimerPtr->GetGameTime();
				if (dTimeTrigger > m_PaintTimeTrigger)
				{
					m_GamePaintTimerPtr->Reset();
					m_GamePaintTimerPtr->Start();
					// Do user defined keyboard check
					m_GamePtr->CheckKeyboard();
					//	ExecuteDirect2DPaint();
					ExecuteDirect2DPaint();
				}
				else Sleep(1);//Sleep for one ms te bring cpu load from 100% to 1%. if removed this loops like roadrunner
			}
			else WaitMessage(); // if the engine is sleeping or the game loop isn't supposed to run, wait for the next windows message.
		}
	}
	return msg.wParam ? true : false;
}

void GameEngine::ExecuteDirect2DPaint()
{
	D2DBeginPaint();
	RECT usedClientRect = { 0, 0, GetWidth(), GetHeight() };
	m_IsDoublebuffering = true;
	m_GamePtr->GamePaint(usedClientRect);
	m_IsDoublebuffering = false;
	bool result = D2DEndPaint();
	if (!result) PostMessage(GameEngine::GetWindow(), WM_DESTROY, 0, 0);
}

bool GameEngine::SetGameValues(String const& TitleRef, WORD wIcon, WORD wSmallIcon, int iWidth = 640, int iHeight = 480)
{
	SetTitle(TitleRef);
	SetIcon(wIcon);
	SetSmallIcon(wSmallIcon);
	SetWidth(iWidth);
	SetHeight(iHeight);

	return true;
}

void GameEngine::ShowMousePointer(bool value)
{
	ShowCursor(value);
	Repaint();
}

bool GameEngine::GoFullscreen()
{
	// exit if already in fullscreen mode
	if (m_Fullscreen) return false;

	// turn off window region without redraw
	SetWindowRgn(m_hWindow, 0, false);

	DEVMODE newSettings;

	// request current screen settings
	EnumDisplaySettings(0, 0, &newSettings);

	//  set desired screen size/res
	newSettings.dmPelsWidth = GetWidth();
	newSettings.dmPelsHeight = GetHeight();
	newSettings.dmBitsPerPel = 32;

	//specify which aspects of the screen settings we wish to change
	newSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	// attempt to apply the new settings
	long result = ChangeDisplaySettings(&newSettings, CDS_FULLSCREEN);

	// exit if failure, else set datamember to fullscreen and return true
	if (result != DISP_CHANGE_SUCCESSFUL)	return false;
	else
	{
		// store the location of the window
		m_OldLoc = GetLocation();

		// switch off the title bar
		DWORD dwStyle = GetWindowLong(m_hWindow, GWL_STYLE);
		dwStyle &= ~WS_CAPTION;
		SetWindowLong(m_hWindow, GWL_STYLE, dwStyle);

		// move the window to (0,0)
		SetWindowPos(m_hWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		Repaint();

		m_Fullscreen = true;

		return true;
	}
}

bool GameEngine::GoWindowedMode()
{
	// exit if already in windowed mode
	if (!m_Fullscreen) return false;

	// this resets the screen to the registry-stored values
	ChangeDisplaySettings(0, 0);

	// replace the title bar
	DWORD dwStyle = GetWindowLong(m_hWindow, GWL_STYLE);
	dwStyle = dwStyle | WS_CAPTION;
	SetWindowLong(m_hWindow, GWL_STYLE, dwStyle);

	// move the window back to its old position
	SetWindowPos(m_hWindow, 0, m_OldLoc.x, m_OldLoc.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	Repaint();

	m_Fullscreen = false;

	return true;
}

bool GameEngine::IsFullscreen()
{
	return m_Fullscreen;
}

bool GameEngine::ClassRegister(int iCmdShow)
{
	WNDCLASSEX    wndclass;

	// Create the window class for the main window
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = m_hInstance;
	wndclass.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(GetIcon()));
	wndclass.hIconSm = LoadIcon(m_hInstance, MAKEINTRESOURCE(GetSmallIcon()));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = m_PaintDoublebuffered ? NULL : (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = m_TitlePtr->ToTChar();

	// Register the window class
	if (!RegisterClassEx(&wndclass)) return false;

	// Calculate the window size and position based upon the game size
	int iWindowWidth = m_iWidth + GetSystemMetrics(SM_CXFIXEDFRAME) * 2, iWindowHeight = m_iHeight + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);
	if (wndclass.lpszMenuName != NULL) iWindowHeight += GetSystemMetrics(SM_CYMENU);
	int iXWindowPos = (GetSystemMetrics(SM_CXSCREEN) - iWindowWidth) / 2, iYWindowPos = (GetSystemMetrics(SM_CYSCREEN) - iWindowHeight) / 2;

	// Create the window
	m_hWindow = CreateWindow(m_TitlePtr->ToTChar(), m_TitlePtr->ToTChar(),
		WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX | WS_CLIPCHILDREN,
		iXWindowPos, iYWindowPos, iWindowWidth,
		iWindowHeight, NULL, NULL, m_hInstance, NULL);

	if (!m_hWindow) return false;

	// Show and update the window
	ShowWindow(m_hWindow, iCmdShow);
	UpdateWindow(m_hWindow);

	return true;
}

bool GameEngine::IsKeyDown(int vKey)
{
	if (GetAsyncKeyState(vKey) < 0) return true;
	else return false;
}

void GameEngine::SetKeyList(String const& keyListRef)
{
	if (keyListRef.ToTChar() != NULL) delete m_KeyListPtr;				// clear the list if one already exists

	int iLength = 0;

	while (keyListRef.ToTChar()[iLength] != '\0') iLength++;			// count the amount of characters

	m_KeyListPtr = (TCHAR*)malloc((iLength + 1) * sizeof(TCHAR));		// make room for this amount of characters + 1

	for (int count = 0; count < iLength + 1; count++)
	{
		TCHAR key = keyListRef.ToTChar()[count];
		m_KeyListPtr[count] = (key > 96 && key < 123) ? key - 32 : key;	// fill in the character, in uppercase if it's a lowercase one
	}
}

void GameEngine::QuitGame()
{
	PostMessage(GameEngine::GetWindow(), WM_DESTROY, 0, 0);
}

void GameEngine::MessageBox(String const& textRef)
{
	if (sizeof(TCHAR) == 2)	MessageBoxW(GetWindow(), (wchar_t*)textRef.ToTChar(), (wchar_t*)m_TitlePtr->ToTChar(), MB_ICONEXCLAMATION | MB_OK);
	else MessageBoxA(GetWindow(), (char*)textRef.ToTChar(), (char*)m_TitlePtr->ToTChar(), MB_ICONEXCLAMATION | MB_OK);
}

void GameEngine::MessageBox(int value)
{
	MessageBox(String("") + value);
}

void GameEngine::MessageBox(size_t value)
{
	MessageBox(String("") + value);
}

void GameEngine::MessageBox(double value)
{
	MessageBox(String("") + value);
}

static bool CALLBACK EnumInsertChildrenProc(HWND hwnd, LPARAM lParam)
{
	vector<HWND>* row = (vector<HWND>*) lParam;

	row->push_back(hwnd);

	return true;
}

void GameEngine::TabNext(HWND ChildWindow)
{
	vector<HWND> childWindows;

	EnumChildWindows(m_hWindow, (WNDENUMPROC)EnumInsertChildrenProc, (LPARAM)&childWindows);

	int position = 0;
	HWND temp = childWindows[position];
	while (temp != ChildWindow) temp = childWindows[++position]; // find position of childWindow in the vector

	if (position == childWindows.size() - 1) SetFocus(childWindows[0]);
	else SetFocus(childWindows[position + 1]);
}

void GameEngine::TabPrevious(HWND ChildWindow)
{
	vector<HWND> childWindows;

	EnumChildWindows(m_hWindow, (WNDENUMPROC)EnumInsertChildrenProc, (LPARAM)&childWindows);

	int position = (int)childWindows.size() - 1;
	HWND temp = childWindows[position];
	while (temp != ChildWindow) temp = childWindows[--position]; // find position of childWindow in the vector

	if (position == 0) SetFocus(childWindows[childWindows.size() - 1]);
	else SetFocus(childWindows[position - 1]);
}

void GameEngine::SetInstance(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
}

void GameEngine::SetWindow(HWND hWindow)
{
	m_hWindow = hWindow;
}

bool GameEngine::CanIPaint()
{
	return true; // See what happens
	if (m_IsDoublebuffering || m_IsPainting) return true;
	else
	{
		MessageBox("Painting from outside the GamePaint()...\n\nYOU SHALL NOT PASS!!!");	// tempted to use #ifdef _DEBUG here, not doing it because first year code
		return false;
	}
}

void GameEngine::SetColor(int red, int green, int blue, int alpha)
{
	m_ColorBrushPtr->SetColor(D2D1::ColorF((FLOAT)(red / 255.0), (FLOAT)(green / 255.0), (FLOAT)(blue / 255.0), (FLOAT)(alpha / 255.0)));
}

bool GameEngine::DrawSolidBackground(int red, int green, int blue)
{
	if (!CanIPaint()) return false;

	m_RenderTargetPtr->Clear(D2D1::ColorF((FLOAT)(red / 255.0), (FLOAT)(green / 255.0), (FLOAT)(blue / 255.0), (FLOAT)(1.0)));

	return true;
}

bool GameEngine::DrawLine(double x1, double y1, double x2, double y2, double strokeWidth)
{
	if (!CanIPaint()) return false;

	m_RenderTargetPtr->DrawLine(Point2F((FLOAT)x1, (FLOAT)y1), Point2F((FLOAT)x2, (FLOAT)y2), m_ColorBrushPtr, (FLOAT)strokeWidth);

	return true;
}

bool GameEngine::DrawLine(DOUBLE2 p1, DOUBLE2 p2, double strokeWidth)
{
	return DrawLine(p1.x, p1.y, p2.x, p2.y, strokeWidth);
}

bool GameEngine::DrawPolygon(const POINT ptsArr[], int count, bool close, double strokeWidth)
{
	if (!CanIPaint()) return false;

	for (int i = 0; i < count - 1; ++i)
	{
		DrawLine(ptsArr[i].x, ptsArr[i].y, ptsArr[i + 1].x, ptsArr[i + 1].y, strokeWidth);
	}
	if (close)
	{
		DrawLine(ptsArr[0].x, ptsArr[0].y, ptsArr[count - 1].x, ptsArr[count - 1].y, strokeWidth);
	}

	return true;
}

bool GameEngine::DrawPolygon(const POINT ptsArr[], int count, double strokeWidth)
{
	return DrawPolygon(ptsArr, count, false, strokeWidth);
}

bool GameEngine::DrawRect(double left, double top, double width, double height, double strokeWidth)
{
	RECT2 rect2(left, top, left + width, top + height);
	return DrawRect(rect2, strokeWidth);
}

bool GameEngine::DrawRect(DOUBLE2 lefttop, double width, double height, double strokeWidth)
{
	return DrawRect(lefttop.x, lefttop.y, width, height, strokeWidth);
}

bool GameEngine::DrawRect(RECT rect, double strokeWidth)
{
	RECT2 rect2(rect.left, rect.top, rect.right, rect.bottom);
	return DrawRect(rect2, strokeWidth);
}

bool GameEngine::DrawRect(RECT2 rect, double strokeWidth)
{
	if (!CanIPaint()) return false;

	D2D1_RECT_F d2dRect = D2D1::RectF((FLOAT)rect.left, (FLOAT)rect.top, (FLOAT)rect.right, (FLOAT)rect.bottom);
	m_RenderTargetPtr->DrawRectangle(d2dRect, m_ColorBrushPtr, (FLOAT)strokeWidth);

	return true;
}

bool GameEngine::FillRect(double left, double top, double width, double height)
{
	RECT2 rect2(left, top, left + width, top + height);
	return FillRect(rect2);
}

bool GameEngine::FillRect(DOUBLE2 lefttop, double width, double height)
{
	return FillRect(lefttop.x, lefttop.y, width, height);
}

bool GameEngine::FillRect(RECT rect)
{
	RECT2 rect2(rect.left, rect.top, rect.right, rect.bottom);
	return FillRect(rect2);
}

bool GameEngine::FillRect(RECT2 rect)
{
	if (!CanIPaint()) return false;

	D2D1_RECT_F d2dRect = D2D1::RectF((FLOAT)rect.left, (FLOAT)rect.top, (FLOAT)rect.right, (FLOAT)rect.bottom);
	m_RenderTargetPtr->FillRectangle(d2dRect, m_ColorBrushPtr);

	return true;
}

bool GameEngine::DrawRoundedRect(double left, double top, double width, double height, double radiusX, double radiusY, double strokeWidth)
{
	if (!CanIPaint()) return false;
	D2D1_RECT_F d2dRect = D2D1::RectF((FLOAT)left, (FLOAT)top, (FLOAT)(left + width), (FLOAT)(top + height));
	D2D1_ROUNDED_RECT  d2dRoundedRect = D2D1::RoundedRect(d2dRect, (FLOAT)radiusX, (FLOAT)radiusY);
	m_RenderTargetPtr->DrawRoundedRectangle(d2dRoundedRect, m_ColorBrushPtr, (FLOAT)strokeWidth);
	return true;
}

bool GameEngine::DrawRoundedRect(DOUBLE2 lefttop, double width, double height, double radiusX, double radiusY, double strokeWidth)
{
	if (!CanIPaint()) return false;
	D2D1_RECT_F d2dRect = D2D1::RectF((FLOAT)lefttop.x, (FLOAT)lefttop.y, (FLOAT)(lefttop.x + width), (FLOAT)(lefttop.y + height));
	D2D1_ROUNDED_RECT  d2dRoundedRect = D2D1::RoundedRect(d2dRect, (FLOAT)radiusX, (FLOAT)radiusY);
	m_RenderTargetPtr->DrawRoundedRectangle(d2dRoundedRect, m_ColorBrushPtr, (FLOAT)strokeWidth);
	return true;
}

bool GameEngine::DrawRoundedRect(RECT rect, double radiusX, double radiusY, double strokeWidth)
{
	if (!CanIPaint()) return false;
	D2D1_RECT_F d2dRect = D2D1::RectF((FLOAT)rect.left, (FLOAT)rect.top, (FLOAT)rect.right, (FLOAT)rect.bottom);
	D2D1_ROUNDED_RECT  d2dRoundedRect = D2D1::RoundedRect(d2dRect, (FLOAT)radiusX, (FLOAT)radiusY);
	m_RenderTargetPtr->DrawRoundedRectangle(d2dRoundedRect, m_ColorBrushPtr, (FLOAT)strokeWidth);
	return true;
}

bool GameEngine::DrawRoundedRect(RECT2 rect, double radiusX, double radiusY, double strokeWidth)
{
	if (!CanIPaint()) return false;
	D2D1_RECT_F d2dRect = D2D1::RectF((FLOAT)rect.left, (FLOAT)rect.top, (FLOAT)rect.right, (FLOAT)rect.bottom);
	D2D1_ROUNDED_RECT  d2dRoundedRect = D2D1::RoundedRect(d2dRect, (FLOAT)radiusX, (FLOAT)radiusY);
	m_RenderTargetPtr->DrawRoundedRectangle(d2dRoundedRect, m_ColorBrushPtr, (FLOAT)strokeWidth);
	return true;
}

bool GameEngine::FillRoundedRect(double left, double top, double width, double height, double radiusX, double radiusY)
{
	if (!CanIPaint()) return false;
	D2D1_RECT_F d2dRect = D2D1::RectF((FLOAT)left, (FLOAT)top, (FLOAT)(left + width), (FLOAT)(top + height));
	D2D1_ROUNDED_RECT  d2dRoundedRect = D2D1::RoundedRect(d2dRect, (FLOAT)radiusX, (FLOAT)radiusY);
	m_RenderTargetPtr->FillRoundedRectangle(d2dRoundedRect, m_ColorBrushPtr);
	return true;
}

bool GameEngine::FillRoundedRect(DOUBLE2 lefttop, double width, double height, double radiusX, double radiusY)
{
	if (!CanIPaint()) return false;
	D2D1_RECT_F d2dRect = D2D1::RectF((FLOAT)lefttop.x, (FLOAT)lefttop.y, (FLOAT)(lefttop.x + width), (FLOAT)(lefttop.y + height));
	D2D1_ROUNDED_RECT  d2dRoundedRect = D2D1::RoundedRect(d2dRect, (FLOAT)radiusX, (FLOAT)radiusY);
	m_RenderTargetPtr->FillRoundedRectangle(d2dRoundedRect, m_ColorBrushPtr);
	return true;
}

bool GameEngine::FillRoundedRect(RECT rect, double radiusX, double radiusY)
{
	if (!CanIPaint()) return false;
	D2D1_RECT_F d2dRect = D2D1::RectF((FLOAT)rect.left, (FLOAT)rect.top, (FLOAT)rect.right, (FLOAT)rect.bottom);
	D2D1_ROUNDED_RECT  d2dRoundedRect = D2D1::RoundedRect(d2dRect, (FLOAT)radiusX, (FLOAT)radiusY);
	m_RenderTargetPtr->FillRoundedRectangle(d2dRoundedRect, m_ColorBrushPtr);
	return true;
}

bool GameEngine::FillRoundedRect(RECT2 rect, double radiusX, double radiusY)
{
	if (!CanIPaint()) return false;
	D2D1_RECT_F d2dRect = D2D1::RectF((FLOAT)rect.left, (FLOAT)rect.top, (FLOAT)rect.right, (FLOAT)rect.bottom);
	D2D1_ROUNDED_RECT  d2dRoundedRect = D2D1::RoundedRect(d2dRect, (FLOAT)radiusX, (FLOAT)radiusY);
	m_RenderTargetPtr->FillRoundedRectangle(d2dRoundedRect, m_ColorBrushPtr);
	return true;
}

bool GameEngine::DrawEllipse(double centerX, double centerY, double radiusX, double radiusY, double strokeWidth)
{
	if (!CanIPaint()) return false;

	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F((FLOAT)centerX, (FLOAT)centerY), (FLOAT)radiusX, (FLOAT)radiusY);
	m_RenderTargetPtr->DrawEllipse(ellipse, m_ColorBrushPtr, (FLOAT)strokeWidth);

	return true;
}

bool GameEngine::DrawEllipse(DOUBLE2 centerPt, double radiusX, double radiusY, double strokeWidth)
{
	return DrawEllipse(centerPt.x, centerPt.y, radiusX, radiusY, strokeWidth);
}

bool GameEngine::FillEllipse(double centerX, double centerY, double radiusX, double radiusY)
{
	if (!CanIPaint()) return false;

	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F((FLOAT)centerX, (FLOAT)centerY), (FLOAT)radiusX, (FLOAT)radiusY);
	m_RenderTargetPtr->FillEllipse(ellipse, m_ColorBrushPtr);

	return true;
}

bool GameEngine::FillEllipse(DOUBLE2 centerPt, double radiusX, double radiusY)
{
	if (!CanIPaint()) return false;

	FillEllipse(centerPt.x, centerPt.y, radiusX, radiusY);

	return true;
}

bool GameEngine::DrawString(TextFormat* textFormatPtr, const String& text, double xPos, double yPos, double width, double height)
{
	if (!CanIPaint()) return false;

	D2D1_SIZE_F dstSize_f = m_RenderTargetPtr->GetSize();
	if (width == 0) width = dstSize_f.width;
	if (height == 0) height = dstSize_f.height;
	D2D1_RECT_F layoutRect = (RectF)((FLOAT)xPos, (FLOAT)yPos, (FLOAT)(width + xPos), (FLOAT)(height + yPos));

	wstring wText(text.ToTChar(), text.ToTChar() + text.GetLength());
	m_RenderTargetPtr->DrawText(wText.c_str(), text.GetLength(), textFormatPtr->GetTextFormat(), layoutRect, m_ColorBrushPtr);

	return true;
}

bool GameEngine::DrawString(const String &text, double xPos, double yPos, double width, double height)
{
	return DrawString(m_DefaultFontPtr, text, xPos, yPos, width, height);
}

bool GameEngine::DrawString(TextFormat* textFormatPtr, const String &text, DOUBLE2 pos, double width, double height)
{
	return DrawString(textFormatPtr, text, pos.x, pos.y, width, height);
}

bool GameEngine::DrawString(const String &text, DOUBLE2 pos, double width, double height)
{
	return DrawString(m_DefaultFontPtr, text, pos.x, pos.y, width, height);
}

bool GameEngine::DrawBitmap(Bitmap* imagePtr, DOUBLE2 leftTop)
{
	return DrawBitmap(imagePtr, leftTop.x, leftTop.y);
}

bool GameEngine::DrawBitmap(Bitmap* imagePtr, DOUBLE2 leftTop, RECT2 srcRect)
{
	return DrawBitmap(imagePtr, leftTop.x, leftTop.y, srcRect);
}

bool GameEngine::DrawBitmap(Bitmap* imagePtr, double x, double y, RECT srcRect)
{
	RECT2 srcRect2(srcRect.left, srcRect.top, srcRect.right, srcRect.bottom);
	return DrawBitmap(imagePtr, x, y, srcRect2);
}

bool GameEngine::DrawBitmap(Bitmap* imagePtr, double x, double y, RECT2 srcRect)
{
	if (!CanIPaint()) return false;

	//The size and position, in device-independent pixels in the bitmap's coordinate space, of the area within the bitmap to draw.
	D2D1_RECT_F srcRect_f;
	srcRect_f.left = (FLOAT)srcRect.left;
	srcRect_f.right = (FLOAT)srcRect.right;
	srcRect_f.top = (FLOAT)srcRect.top;
	srcRect_f.bottom = (FLOAT)srcRect.bottom;

	//http://msdn.microsoft.com/en-us/library/dd371880(v=VS.85).aspx
	//The size and position, in device-independent pixels in the render target's coordinate space,
	//of the area to which the bitmap is drawn. If the rectangle is not well-ordered, nothing is drawn,
	//but the render target does not enter an error state.
	D2D1_RECT_F dstRect_f;
	dstRect_f.left = (FLOAT)x;
	dstRect_f.right = dstRect_f.left + (FLOAT)(srcRect.right - srcRect.left);
	dstRect_f.top = (FLOAT)y;
	dstRect_f.bottom = dstRect_f.top + (FLOAT)(srcRect.bottom - srcRect.top);

	m_RenderTargetPtr->DrawBitmap(imagePtr->GetBitmapPtr(), dstRect_f, (FLOAT)imagePtr->GetOpacity(), m_BitmapInterpolationMode, srcRect_f);

	return true;
}

bool GameEngine::DrawBitmap(Bitmap* imagePtr, double x, double y)
{
	RECT2 srcRect;
	srcRect.left = 0;
	srcRect.right = imagePtr->GetWidth();
	srcRect.top = 0;
	srcRect.bottom = imagePtr->GetHeight();

	return DrawBitmap(imagePtr, x, y, srcRect);
}

bool GameEngine::DrawHitRegion(HitRegion* collisionMeshPtr)
{
	if (!CanIPaint()) return false;

	m_RenderTargetPtr->DrawGeometry(collisionMeshPtr->GetTransformedGeometry(), m_ColorBrushPtr);

	//restore the transformation matrix
	Matrix3x2F matDirect2D = m_MatWorld.ToMatrix3x2F();
	m_RenderTargetPtr->SetTransform(matDirect2D);

	return true;
}

bool GameEngine::FillHitRegion(HitRegion* collisionMeshPtr)
{
	if (!CanIPaint()) return false;

	m_RenderTargetPtr->FillGeometry(collisionMeshPtr->GetTransformedGeometry(), m_ColorBrushPtr);
	//restore the transformation matrix
	Matrix3x2F matDirect2D = m_MatWorld.ToMatrix3x2F();
	m_RenderTargetPtr->SetTransform(matDirect2D);

	return true;
}
bool GameEngine::DrawCoordinateSystem(double unitSize)
{
	if (!CanIPaint()) return false;

	DrawLine(DOUBLE2(0, 0), DOUBLE2(unitSize * 1.3, 0));
	DrawLine(DOUBLE2(0, 0), DOUBLE2(0, unitSize * 1.3));

	return true;
}

//matrix operations
void GameEngine::SetTransformMatrix(MATRIX3X2 mat)
{
	m_MatWorld = mat;
	Matrix3x2F matDirect2D = m_MatWorld.ToMatrix3x2F();
	m_RenderTargetPtr->SetTransform(matDirect2D);
}

MATRIX3X2 GameEngine::GetTransformMatrix()
{
	return m_MatWorld;
}

void GameEngine::EnableAntiAlias(bool isAlias)
{
	if (isAlias)		m_AntialiasMode = D2D1_ANTIALIAS_MODE_PER_PRIMITIVE;
	else			m_AntialiasMode = D2D1_ANTIALIAS_MODE_ALIASED;
	if (m_RenderTargetPtr)m_RenderTargetPtr->SetAntialiasMode(m_AntialiasMode);
}

void GameEngine::SetBitmapInterpolationModeLinear()
{
	m_BitmapInterpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
}

void GameEngine::SetBitmapInterpolationModeNearestNeighbor()
{
	m_BitmapInterpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
}

void GameEngine::SetFont(TextFormat* fontPtr)
{
	m_UserFontPtr = fontPtr;
}

void GameEngine::Repaint()
{
	InvalidateRect(m_hWindow, NULL, true);
}

HINSTANCE GameEngine::GetInstance()
{
	return m_hInstance;
}

HWND GameEngine::GetWindow()
{
	return m_hWindow;
}

String& GameEngine::GetTitle()
{
	return *m_TitlePtr;
}

WORD GameEngine::GetIcon()
{
	return m_wIcon;
}

WORD GameEngine::GetSmallIcon()
{
	return m_wSmallIcon;
}

int GameEngine::GetWidth()
{
	return m_iWidth;
}

int GameEngine::GetHeight()
{
	return m_iHeight;
}

double GameEngine::GetFrameDelay()
{
	return m_PaintTimeTrigger;
}

bool GameEngine::GetSleep()
{
	return m_bSleep ? true : false;
}

ID2D1Factory* GameEngine::GetD2DFactory()
{
	return m_D2DFactoryPtr;
}

IWICImagingFactory* GameEngine::GetWICImagingFactory()
{
	return m_WICFactoryPtr;
}

ID2D1HwndRenderTarget* GameEngine::GetHwndRenderTarget()
{
	return m_RenderTargetPtr;
}

IDWriteFactory* GameEngine::GetDWriteFactory()
{
	return m_DWriteFactoryPtr;
}

POINT GameEngine::GetLocation()
{
	RECT info;
	POINT pos;

	GetWindowRect(m_hWindow, &info);
	pos.x = info.left;
	pos.y = info.top;

	return pos;
}

void GameEngine::SetIcon(WORD wIcon)
{
	m_wIcon = wIcon;
}

void GameEngine::SetSmallIcon(WORD wSmallIcon)
{
	m_wSmallIcon = wSmallIcon;
}

void GameEngine::SetWidth(int iWidth)
{
	m_iWidth = iWidth;
}

void GameEngine::SetHeight(int iHeight)
{
	m_iHeight = iHeight;
}

void GameEngine::SetFrameRate(double iFrameRate)
{
	m_PaintTimeTrigger = 1.0 / iFrameRate;
}

void GameEngine::SetSleep(bool bSleep)
{
	m_bSleep = bSleep;
}

void GameEngine::SetPaintDoublebuffered()
{
	m_PaintDoublebuffered = true;
}

void GameEngine::SetLocation(int x, int y)
{
	SetWindowPos(m_hWindow, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	Repaint();
}

void GameEngine::RunGameLoop(bool value)
{
	m_bRunGameLoop = value;
}

LRESULT GameEngine::HandleEvent(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC         hDC;
	PAINTSTRUCT ps;

	// Get window rectangle and HDC
	RECT windowClientRect;
	GetClientRect(hWindow, &windowClientRect);

	RECT usedClientRect;
	usedClientRect.left = 0;
	usedClientRect.top = 0;
	usedClientRect.right = GetWidth();
	usedClientRect.bottom = GetHeight();

	double scaleX = 1, scaleY = 1;
	if (windowClientRect.right != 0 && windowClientRect.bottom != 0)
	{
		scaleX = (usedClientRect.right - usedClientRect.left) / (double)(windowClientRect.right - windowClientRect.left);
		scaleY = (usedClientRect.bottom - usedClientRect.top) / (double)(windowClientRect.bottom - windowClientRect.top);
	}
	// Double buffering code
	//HDC hBufferDC;
	//HBITMAP hBufferBmp;
	//HBITMAP hOldBmp;


	// Route Windows messages to game engine member functions
	switch (msg)
	{
	case WM_CREATE:
		// Set the game window
		SetWindow(hWindow);

		return 0;

	case WM_ACTIVATE:
		// Activate/deactivate the game and update the Sleep status
		if (wParam != WA_INACTIVE)
		{
			//Lock hDC
			hDC = GetDC(hWindow);

			// Do user defined drawing functions
			//m_GamePtr->GameActivate(hDC, usedClientRect);
			m_GamePtr->GameActivate();

			// Release HDC
			ReleaseDC(hWindow, hDC);

			SetSleep(false);
		}
		else
		{
			//Lock hDC
			hDC = GetDC(hWindow);

			// Do user defined drawing functions
			//m_GamePtr->GameDeactivate(hDC, usedClientRect);
			m_GamePtr->GameDeactivate();

			// Release HDC
			ReleaseDC(hWindow, hDC);
		}
		return 0;

	case WM_PAINT:
		//WM_PAINT needs BeginPaint and EndPaint
		hDC = BeginPaint(hWindow, &ps);
		if (m_bRunGameLoop == false && m_bInitialized == true) ExecuteDirect2DPaint();
		EndPaint(hWindow, &ps);

		//if (m_PaintDoublebuffered)
		//{
			//// Get window, rectangle and HDC
			//hDC = BeginPaint(hWindow, &ps);

			//// Double buffering code
			//hBufferDC = CreateCompatibleDC(hDC);
			//// Create the buffer, size is area used by client
			//hBufferBmp = CreateCompatibleBitmap(hDC, GetWidth(), GetHeight());
			//hOldBmp = (HBITMAP) SelectObject(hBufferDC, hBufferBmp);

			//// Do user defined drawing functions on the buffer, parameters added
			//// for ease of drawing
			//m_HdcDraw = hBufferDC;
			//m_RectDraw = usedClientRect;

			//m_IsPainting = true;
			//m_GamePtr->GamePaint(usedClientRect);
			//m_IsPainting = false;

			//// As a last step copy the memdc to the hdc
			////BitBlt(hDC, 0, 0, iWidth, iHeight, hBufferDC, 0, 0, SRCCOPY);
			//StretchBlt(
			//		hDC, 0,0,windowClientRect.right-windowClientRect.left,windowClientRect.bottom-windowClientRect.top,
			//		hBufferDC, 0, 0, GetWidth(),GetHeight(),SRCCOPY
			//);

			//// Reset the old bmp of the buffer, mainly for show since we kill it anyway
			//SelectObject(hBufferDC, hOldBmp);
			//// Kill the buffer
			//DeleteObject(hBufferBmp);
			//DeleteDC(hBufferDC);

			//// end paint
			//EndPaint(hWindow, &ps);

		//}
		//else
		//{

			//m_HdcDraw = BeginPaint(hWindow, &ps);
			//GetClientRect(hWindow, &m_RectDraw);

			//m_IsPainting = true;
			//m_GamePtr->GamePaint(m_RectDraw);
			//m_IsPainting = false;

			//EndPaint(hWindow, &ps);
		//}

		return 0;

	case WM_CTLCOLOREDIT:
		return SendMessage((HWND)lParam, WM_CTLCOLOREDIT, wParam, lParam);	// delegate this message to the child window

	case WM_CTLCOLORBTN:
		return SendMessage((HWND)lParam, WM_CTLCOLOREDIT, wParam, lParam);	// delegate this message to the child window

	case WM_LBUTTONDOWN:
		m_GamePtr->MouseButtonAction(true, true, (int)(LOWORD(lParam) * scaleX), (int)(HIWORD(lParam) * scaleY), wParam);
		return 0;

	case WM_LBUTTONUP:
		m_GamePtr->MouseButtonAction(true, false, (int)(LOWORD(lParam) * scaleX), (int)(HIWORD(lParam) * scaleY), wParam);
		return 0;

	case WM_RBUTTONDOWN:
		m_GamePtr->MouseButtonAction(false, true, (int)(LOWORD(lParam) * scaleX), (int)(HIWORD(lParam) * scaleY), wParam);
		return 0;

	case WM_RBUTTONUP:
		m_GamePtr->MouseButtonAction(false, false, (int)(LOWORD(lParam) * scaleX), (int)(HIWORD(lParam) * scaleY), wParam);
		return 0;

	case WM_MOUSEMOVE:
		m_GamePtr->MouseMove((int)(LOWORD(lParam) * scaleX), (int)(HIWORD(lParam) * scaleY), wParam);
		return 0;

	case WM_SYSCOMMAND:	// trapping this message prevents a freeze after the ALT key is released
		if (wParam == SC_KEYMENU) return 0;			// see win32 API : WM_KEYDOWN
		else break;

	case WM_DESTROY:
		// User defined code for exiting the game
		m_GamePtr->GameEnd();
		// Delete the game engine
		delete GameEngine::GetSingleton();

		// End the game and exit the application
		PostQuitMessage(0);
		return 0;

	case WM_SIZE:
		if (wParam == SIZE_MAXIMIZED)
		{
			// switch off the title bar
			DWORD dwStyle = GetWindowLong(m_hWindow, GWL_STYLE);
			dwStyle &= ~WS_CAPTION;
			SetWindowLong(m_hWindow, GWL_STYLE, dwStyle);
			//If you have changed certain window data using SetWindowLong, you must call SetWindowPos for the changes to take effect.
			SetWindowPos(m_hWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
			return 0;
		}
		return 0;
		//use ESC key to go from fullscreen window to smaller window
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			// only if in fullscreen
			RECT WindowRect;
			GetWindowRect(hWindow, &WindowRect);
			if ((WindowRect.right - WindowRect.left) >= GetSystemMetrics(SM_CXSCREEN))
			{
				// turns title bar on/off
				DWORD dwStyle = GetWindowLong(m_hWindow, GWL_STYLE);
				if (dwStyle & WS_CAPTION) dwStyle &= ~WS_CAPTION;
				else dwStyle = dwStyle | WS_CAPTION;
				SetWindowLong(m_hWindow, GWL_STYLE, dwStyle);
				// this should be called but it messes up GetClientRect().
				//SetWindowPos(m_hWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
			}
			return 0;
		}
		return 0;

	}
	return DefWindowProc(hWindow, msg, wParam, lParam);
}

void GameEngine::SetTickPaintRatio(double ratio)
{
	if (ratio > 0.2 && ratio < 10) m_TickPaintRatio = ratio;
}

//-----------------------------------------------------------------
// Caller methods
//-----------------------------------------------------------------
bool Caller::AddActionListener(Callable* targetPtr)
{
	return AddListenerObject(targetPtr);
}

bool Caller::RemoveActionListener(Callable* targetPtr)
{
	return RemoveListenerObject(targetPtr);
}

bool Caller::CallListeners()
{
	for (vector<Callable*>::iterator it = m_TargetList.begin(); it != m_TargetList.end(); ++it)
	{
		(*it)->CallAction(this);
	}

	return (m_TargetList.size() > 0);
}

bool Caller::AddListenerObject(Callable* targetPtr)
{
	for (vector<Callable*>::iterator it = m_TargetList.begin(); it != m_TargetList.end(); ++it)
	{
		if ((*it) == targetPtr) return false;
	}

	m_TargetList.push_back(targetPtr);
	return true;
}

bool Caller::RemoveListenerObject(Callable* targetPtr)
{
	vector<Callable*>::iterator pos = find(m_TargetList.begin(), m_TargetList.end(), targetPtr); // find algorithm from STL

	if (pos == m_TargetList.end()) return false;
	else
	{
		m_TargetList.erase(pos);
		return true;
	}
}

//-----------------------------------------------------------------
// Audio methods
//-----------------------------------------------------------------
// set static datamember to zero
int Audio::m_Nr = 0;

#pragma warning(disable:4311)
#pragma warning(disable:4312)
Audio::Audio(String const& nameRef) : m_Playing(false), m_Paused(false), m_MustRepeat(false), m_hWnd(0), m_Volume(100)
{
	if (nameRef.EndsWith(".mp3") || nameRef.EndsWith(".wav") || nameRef.EndsWith(".mid"))
	{
		m_Alias = String("audio") + m_Nr++;
		m_FileName = nameRef;

		Create(nameRef);
	}
}

Audio::Audio(int IDAudio, String const& typeRef) : m_Playing(false), m_Paused(false), m_MustRepeat(false), m_hWnd(0), m_Volume(100)
{
	if (typeRef == "MP3" || typeRef == "WAV" || typeRef == "MID")
	{
		m_Alias = String("audio") + m_Nr++;
		m_FileName = String("temp\\") + m_Alias;

		if (typeRef == "MP3") m_FileName += ".mp3";
		else if (typeRef == "WAV") m_FileName += ".wav";
		else m_FileName += ".mid";

		Extract(IDAudio, typeRef, m_FileName);

		Create(m_FileName);
	}
}

void Audio::Create(const String& nameRef)
{
	TCHAR buffer[100];

	String sendString;

	if (nameRef.EndsWith(".mp3")) sendString = String("open \"") + m_FileName + "\" type mpegvideo alias " + m_Alias;
	else if (nameRef.EndsWith(".wav")) sendString = String("open \"") + m_FileName + "\" type waveaudio alias " + m_Alias;
	else if (nameRef.EndsWith(".mid")) sendString = String("open \"") + m_FileName + "\" type sequencer alias " + m_Alias;

	int result = mciSendString(sendString.ToTChar(), 0, 0, 0);
	if (result != 0) return;

	sendString = String("set ") + m_Alias + " time format milliseconds";
	mciSendString(sendString.ToTChar(), 0, 0, 0);

	sendString = String("status ") + m_Alias + " length";
	mciSendString(sendString.ToTChar(), buffer, 100, 0);

	m_Duration = String(buffer).ToInteger();

	// Create a window to catch the MM_MCINOTIFY message with
	m_hWnd = CreateWindow(TEXT("STATIC"), TEXT(""), 0, 0, 0, 0, 0, 0, 0, GameEngine::GetSingleton()->GetInstance(), 0);
	SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)AudioProcStatic);	// set the custom message loop (subclassing)
	SetWindowLong(m_hWnd, GWL_USERDATA, (LONG) this);			// set this object as the parameter for the Proc
}

void Audio::Extract(WORD id, String sType, String sFilename)
{
	CreateDirectory(TEXT("temp\\"), NULL);

	HRSRC hrsrc = FindResource(NULL, MAKEINTRESOURCE(id), sType.ToTChar());
	HGLOBAL hLoaded = LoadResource(NULL, hrsrc);
	LPVOID lpLock = LockResource(hLoaded);
	DWORD dwSize = SizeofResource(NULL, hrsrc);
	HANDLE hFile = CreateFile(sFilename.ToTChar(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwByteWritten;
	WriteFile(hFile, lpLock, dwSize, &dwByteWritten, NULL);
	CloseHandle(hFile);
	FreeResource(hLoaded);
}

#pragma warning(default:4311)
#pragma warning(default:4312)

Audio::~Audio()
{
	Stop();

	String sendString = String("close ") + m_Alias;
	mciSendString(sendString.ToTChar(), 0, 0, 0);

	// release the window resources if necessary
	if (m_hWnd)
	{
		DestroyWindow(m_hWnd);
		m_hWnd = 0;
	}
}

void Audio::Play(int msecStart, int msecStop)
{
	if (!m_Playing)
	{
		m_Playing = true;
		m_Paused = false;

		if (msecStop == -1) QueuePlayCommand(msecStart);
		else QueuePlayCommand(msecStart, msecStop);
	}
	else if (m_Paused)
	{
		m_Paused = false;

		QueueResumeCommand();
	}
}

void Audio::Pause()
{
	if (m_Playing && !m_Paused)
	{
		m_Paused = true;

		QueuePauseCommand();
	}
}

void Audio::Stop()
{
	if (m_Playing)
	{
		m_Playing = false;
		m_Paused = false;

		QueueStopCommand();
	}
}

void Audio::QueuePlayCommand(int msecStart)
{
	QueueCommand(String("play ") + m_Alias + " from " + msecStart + " notify");
}

void Audio::QueuePlayCommand(int msecStart, int msecStop)
{
	QueueCommand(String("play ") + m_Alias + " from " + msecStart + " to " + msecStop + " notify");
}

void Audio::QueuePauseCommand()
{
	QueueCommand(String("pause ") + m_Alias);
}

void Audio::QueueResumeCommand()
{
	QueueCommand(String("resume ") + m_Alias);
}

void Audio::QueueStopCommand()
{
	QueueCommand(String("stop ") + m_Alias);
}

void Audio::QueueVolumeCommand(int volume)
{
	QueueCommand(String("setaudio ") + m_Alias + " volume to " + volume * 10);
}

void Audio::QueueCommand(String const& commandRef)
{
	m_CommandQueue.push(commandRef);
}

void Audio::Tick()
{
	if (!m_CommandQueue.empty())
	{
		SendMCICommand(m_CommandQueue.front());
		m_CommandQueue.pop();
	}
}

void Audio::SendMCICommand(String const& commandRef)
{
	int result = mciSendString(commandRef.ToTChar(), 0, 0, m_hWnd);
}

String& Audio::GetName()
{
	return m_FileName;
}

String& Audio::GetAlias()
{
	return m_Alias;
}

bool Audio::IsPlaying()
{
	return m_Playing;
}

bool Audio::IsPaused()
{
	return m_Paused;
}

void Audio::SwitchPlayingOff()
{
	m_Playing = false;
	m_Paused = false;
}

void Audio::SetRepeat(bool repeat)
{
	m_MustRepeat = repeat;
}

bool Audio::GetRepeat()
{
	return m_MustRepeat;
}

int Audio::GetDuration()
{
	return m_Duration;
}

void Audio::SetVolume(int volume)
{
	m_Volume = min(100, max(0, volume));	// values below 0 and above 100 are trimmed to 0 and 100, respectively

	QueueVolumeCommand(volume);
}

int Audio::GetVolume()
{
	return m_Volume;
}

bool Audio::Exists()
{
	return m_hWnd ? true : false;
}

int Audio::GetType()
{
	return Caller::Audio;
}

LRESULT Audio::AudioProcStatic(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#pragma warning(disable: 4312)
	Audio* audio = reinterpret_cast<Audio*>(GetWindowLong(hWnd, GWL_USERDATA));
#pragma warning(default: 4312)

	switch (msg)
	{
	case MM_MCINOTIFY: // message received when an audio file has finished playing - used for repeat function

		if (wParam == MCI_NOTIFY_SUCCESSFUL && audio->IsPlaying())
		{
			audio->SwitchPlayingOff();

			if (audio->GetRepeat()) audio->Play();	// repeat the audio
			else audio->CallListeners();			// notify listeners that the audio file has come to an end
		}
	}
	return 0;
}

//-----------------------------------------------------------------
// TextBox methods
//-----------------------------------------------------------------
#pragma warning(disable:4311)
#pragma warning(disable:4312)
TextBox::TextBox(String const& textRef) : m_X(0), m_Y(0), m_BgColor(RGB(255, 255, 255)), m_ForeColor(RGB(0, 0, 0)), m_BgColorBrush(0), m_Font(0), m_OldFont(0)
{
	// Create the edit box
	m_hWndEdit = CreateWindow(TEXT("EDIT"), textRef.ToTChar(), WS_BORDER | WS_CHILD | WS_CLIPSIBLINGS | WS_TABSTOP | ES_LEFT | ES_AUTOHSCROLL, 0, 0, 0, 0, GameEngine::GetSingleton()->GetWindow(), NULL, GameEngine::GetSingleton()->GetInstance(), NULL);

	// Set the new WNDPROC for the edit box, store the old value
	m_procOldEdit = (WNDPROC)SetWindowLong(m_hWndEdit, GWL_WNDPROC, (LONG)EditProcStatic);

	// Set this object as userdata vor the static wndproc function of the edit box so that it can call members
	SetWindowLong(m_hWndEdit, GWL_USERDATA, (LONG) this);
}

TextBox::TextBox() : m_X(0), m_Y(0), m_BgColor(RGB(255, 255, 255)), m_ForeColor(RGB(0, 0, 0)), m_BgColorBrush(0), m_Font(0), m_OldFont(0)
{
	// Create the edit box
	m_hWndEdit = CreateWindow(TEXT("EDIT"), TEXT(""), WS_BORDER | WS_CHILD | WS_CLIPSIBLINGS | WS_TABSTOP | ES_LEFT | ES_AUTOHSCROLL, 0, 0, 0, 0, GameEngine::GetSingleton()->GetWindow(), NULL, GameEngine::GetSingleton()->GetInstance(), NULL);

	// Set the new WNDPROC for the edit box, store the old value
	m_procOldEdit = (WNDPROC)SetWindowLong(m_hWndEdit, GWL_WNDPROC, (LONG)EditProcStatic);

	// Set this object as userdata vor the static wndproc function of the edit box so that it can call members
	SetWindowLong(m_hWndEdit, GWL_USERDATA, (LONG) this);
}
#pragma warning(default:4311)
#pragma warning(default:4312)

TextBox::~TextBox()
{
	// release the background brush if necessary
	if (m_BgColorBrush != 0)
	{
		DeleteObject(m_BgColorBrush);
		m_BgColorBrush = 0;
	}

	// release the font if necessary
	if (m_Font != 0)
	{
		SelectObject(GetDC(m_hWndEdit), m_OldFont);
		DeleteObject(m_Font);
		m_Font = m_OldFont = 0;
	}

	// release the window resources
	DestroyWindow(m_hWndEdit);
	m_hWndEdit = NULL;
}

int TextBox::GetType()
{
	return Caller::TextBox;
}

void TextBox::SetBounds(int x, int y, int width, int height)
{
	m_X = x;
	m_Y = y;

	MoveWindow(m_hWndEdit, x, y, width, height, true);
}

RECT2 TextBox::GetRect()
{
	RECT rc;
	RECT2 result;

	GetClientRect(m_hWndEdit, &rc);

	result.left = rc.left + m_X;
	result.right = rc.right + m_X;
	result.top = rc.top + m_Y;
	result.bottom = rc.bottom += m_Y;

	return result;
}

void TextBox::SetEnabled(bool bEnable)
{
	EnableWindow(m_hWndEdit, bEnable);
}

void TextBox::Update()
{
	UpdateWindow(m_hWndEdit);
}

void TextBox::Show()
{
	// Show and update the edit box
	ShowWindow(m_hWndEdit, SW_SHOW);
	UpdateWindow(m_hWndEdit);
}

void TextBox::Hide()
{
	// Show and update the edit box
	ShowWindow(m_hWndEdit, SW_HIDE);
	UpdateWindow(m_hWndEdit);
}

String TextBox::GetText()
{
	int textLength = (int)SendMessage(m_hWndEdit, (UINT)WM_GETTEXTLENGTH, 0, 0);

	TCHAR* bufferPtr = new TCHAR[textLength + 1];

	SendMessage(m_hWndEdit, (UINT)WM_GETTEXT, (WPARAM)textLength + 1, (LPARAM)bufferPtr);

	String newString(bufferPtr);

	delete[] bufferPtr;

	return newString;
}

void TextBox::SetText(String const& textRef)
{
	SendMessage(m_hWndEdit, WM_SETTEXT, 0, (LPARAM)textRef.ToTChar());
}

void TextBox::SetFont(String const& fontNameRef, bool bold, bool italic, bool underline, int size)
{
	LOGFONT ft;

	_tcscpy_s(ft.lfFaceName, sizeof(ft.lfFaceName) / sizeof(TCHAR), fontNameRef.ToTChar());
	ft.lfStrikeOut = 0;
	ft.lfUnderline = underline ? 1 : 0;
	ft.lfHeight = size;
	ft.lfEscapement = 0;
	ft.lfWeight = bold ? FW_BOLD : 0;
	ft.lfItalic = italic ? 1 : 0;

	// clean up if another custom font was already in place
	if (m_Font != 0) { DeleteObject(m_Font); }

	// create the new font. The WM_CTLCOLOREDIT message will set the font when the textbox is about to redraw
	m_Font = CreateFontIndirect(&ft);

	// redraw the textbox
	InvalidateRect(m_hWndEdit, NULL, true);
}

void TextBox::SetForecolor(int red, int green, int blue)
{
	m_ForeColor = RGB(red, green, blue);

	// redraw the textbox
	InvalidateRect(m_hWndEdit, NULL, true);
}

void TextBox::SetBackcolor(int red, int green, int blue)
{
	m_BgColor = RGB(red, green, blue);

	if (m_BgColorBrush != 0) DeleteObject(m_BgColorBrush);
	m_BgColorBrush = CreateSolidBrush(m_BgColor);

	// redraw the textbox
	InvalidateRect(m_hWndEdit, NULL, true);
}

COLORREF TextBox::GetForecolor()
{
	return m_ForeColor;
}

COLORREF TextBox::GetBackcolor()
{
	return m_BgColor;
}

HBRUSH TextBox::GetBackcolorBrush()
{
	return m_BgColorBrush;
}

LRESULT TextBox::EditProcStatic(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#pragma warning(disable: 4312)
	return reinterpret_cast<TextBox*>(GetWindowLong(hWnd, GWL_USERDATA))->EditProc(hWnd, msg, wParam, lParam);
#pragma warning(default: 4312)
}

LRESULT TextBox::EditProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CTLCOLOREDIT:
		SetBkColor((HDC)wParam, GetBackcolor());
		SetTextColor((HDC)wParam, GetForecolor());
		if (m_Font != 0)
		{
			if (m_OldFont == 0) m_OldFont = (HFONT)SelectObject((HDC)wParam, m_Font);
			else SelectObject((HDC)wParam, m_Font);
		}
		return (LRESULT)GetBackcolorBrush();

	case WM_CHAR:
		if (wParam == VK_TAB) return 0;
		if (wParam == VK_RETURN) return 0;
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_TAB:
			if (GameEngine::GetSingleton()->IsKeyDown(VK_SHIFT)) GameEngine::GetSingleton()->TabPrevious(hWnd);
			else GameEngine::GetSingleton()->TabNext(hWnd);
			return 0;
		case VK_ESCAPE:
			SetFocus(GetParent(hWnd));
			return 0;
		case VK_RETURN:
			//if (m_Target) result = m_Target->CallAction(this);
			CallListeners();
			break;
		}
	}
	return CallWindowProc(m_procOldEdit, hWnd, msg, wParam, lParam);
}


//-----------------------------------------------------------------
// Button methods
//-----------------------------------------------------------------
#pragma warning(disable:4311)
#pragma warning(disable:4312)
Button::Button(String const& textRef) : m_X(0), m_Y(0), m_Armed(false), m_Font(0), m_OldFont(0)
{
	// Create the button object
	m_hWndButton = CreateWindow(TEXT("BUTTON"), textRef.ToTChar(), WS_BORDER | WS_CHILD | WS_CLIPSIBLINGS | WS_TABSTOP | BS_PUSHBUTTON, 0, 0, 0, 0, GameEngine::GetSingleton()->GetWindow(), NULL, GameEngine::GetSingleton()->GetInstance(), NULL);

	// Set de new WNDPROC for the button, and store the old one
	m_procOldButton = (WNDPROC)SetWindowLong(m_hWndButton, GWL_WNDPROC, (LONG)ButtonProcStatic);

	// Store 'this' as data for the Button object so that the static PROC can call the member proc
	SetWindowLong(m_hWndButton, GWL_USERDATA, (LONG) this);
}

Button::Button() : m_X(0), m_Y(0), m_Armed(false), m_Font(0), m_OldFont(0)
{
	// Create the button object
	m_hWndButton = CreateWindow(TEXT("BUTTON"), TEXT(""), WS_BORDER | WS_CHILD | WS_CLIPSIBLINGS | WS_TABSTOP | BS_PUSHBUTTON, 0, 0, 0, 0, GameEngine::GetSingleton()->GetWindow(), NULL, GameEngine::GetSingleton()->GetInstance(), NULL);

	// Set de new WNDPROC for the button, and store the old one
	m_procOldButton = (WNDPROC)SetWindowLong(m_hWndButton, GWL_WNDPROC, (LONG)ButtonProcStatic);

	// Store 'this' as data for the Button object so that the static PROC can call the member proc
	SetWindowLong(m_hWndButton, GWL_USERDATA, (LONG) this);
}
#pragma warning(default:4311)
#pragma warning(default:4312)

Button::~Button()
{
	// release the font if necessary
	if (m_Font != 0)
	{
		SelectObject(GetDC(m_hWndButton), m_OldFont);
		DeleteObject(m_Font);
		m_Font = m_OldFont = 0;
	}

	// release the window resource
	DestroyWindow(m_hWndButton);
	m_hWndButton = NULL;
}

int Button::GetType()
{
	return Caller::Button;
}

void Button::SetBounds(int x, int y, int width, int height)
{
	m_X = x;
	m_Y = y;

	MoveWindow(m_hWndButton, x, y, width, height, true);
}

RECT2 Button::GetRect()
{
	RECT rc;
	RECT2 result;

	GetClientRect(m_hWndButton, &rc);

	result.left = rc.left + m_X;
	result.right = rc.right + m_X;
	result.top = rc.top + m_Y;
	result.bottom = rc.bottom + m_Y;

	return result;
}

void Button::SetEnabled(bool bEnable)
{
	EnableWindow(m_hWndButton, bEnable);
}

void Button::Update()
{
	UpdateWindow(m_hWndButton);
}

void Button::Show()
{
	// Show and update the button
	ShowWindow(m_hWndButton, SW_SHOW);
	UpdateWindow(m_hWndButton);
}

void Button::Hide()
{
	// Show and update the button
	ShowWindow(m_hWndButton, SW_HIDE);
	UpdateWindow(m_hWndButton);
}

String Button::GetText()
{
	int textLength = (int)SendMessage(m_hWndButton, (UINT)WM_GETTEXTLENGTH, 0, 0);

	TCHAR* bufferPtr = new TCHAR[textLength + 1];

	SendMessage(m_hWndButton, (UINT)WM_GETTEXT, (WPARAM)textLength + 1, (LPARAM)bufferPtr);

	String newString(bufferPtr);

	delete[] bufferPtr;

	return newString;
}

void Button::SetText(String const& textRef)
{
	SendMessage(m_hWndButton, WM_SETTEXT, 0, (LPARAM)textRef.ToTChar());
}

void Button::SetFont(String const& fontNameRef, bool bold, bool italic, bool underline, int size)
{
	LOGFONT ft;

	_tcscpy_s(ft.lfFaceName, sizeof(ft.lfFaceName) / sizeof(TCHAR), fontNameRef.ToTChar());
	ft.lfStrikeOut = 0;
	ft.lfUnderline = underline ? 1 : 0;
	ft.lfHeight = size;
	ft.lfEscapement = 0;
	ft.lfWeight = bold ? FW_BOLD : 0;
	ft.lfItalic = italic ? 1 : 0;

	// clean up if another custom font was already in place
	if (m_Font != 0) { DeleteObject(m_Font); }

	// create the new font. The WM_CTLCOLOREDIT message will set the font when the button is about to redraw
	m_Font = CreateFontIndirect(&ft);

	// redraw the button
	InvalidateRect(m_hWndButton, NULL, true);
}

LRESULT Button::ButtonProcStatic(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#pragma warning(disable: 4312)
	return reinterpret_cast<Button*>(GetWindowLong(hWnd, GWL_USERDATA))->ButtonProc(hWnd, msg, wParam, lParam);
#pragma warning(default: 4312)
}

LRESULT Button::ButtonProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CTLCOLOREDIT:
		if (m_Font != 0)
		{
			if (m_OldFont == 0) m_OldFont = (HFONT)SelectObject((HDC)wParam, m_Font);
			else SelectObject((HDC)wParam, m_Font);
		}
		return 0;

	case WM_CHAR:
		if (wParam == VK_TAB) return 0;
		if (wParam == VK_RETURN) return 0;
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_TAB:
			if (GameEngine::GetSingleton()->IsKeyDown(VK_SHIFT)) GameEngine::GetSingleton()->TabPrevious(hWnd);
			else GameEngine::GetSingleton()->TabNext(hWnd);
			return 0;
		case VK_ESCAPE:
			SetFocus(GetParent(hWnd));
			return 0;
		case VK_SPACE:
			//if (m_Target) result = m_Target->CallAction(this);
			CallListeners();
		}
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:					// clicking fast will throw LBUTTONDBLCLK's as well as LBUTTONDOWN's, you need to capture both to catch all button clicks
		m_Armed = true;
		break;
	case WM_LBUTTONUP:
		if (m_Armed)
		{
			RECT rc;
			POINT pt;
			GetWindowRect(hWnd, &rc);
			GetCursorPos(&pt);

			//if (PtInRect(&rc, pt) && m_Target) result = m_Target->CallAction(this);
			if (PtInRect(&rc, pt)) CallListeners();

			m_Armed = false;
		}
	}
	return CallWindowProc(m_procOldButton, hWnd, msg, wParam, lParam);
}

//-----------------------------------------------------------------
// Timer methods
//-----------------------------------------------------------------
Timer::Timer(int msec, Callable* targetPtr) : m_IsRunning(false)
{
	m_Delay = msec;

	AddActionListener(targetPtr);
}

Timer::~Timer()
{
	if (m_IsRunning) Stop(); // stop closes the handle

	// no objects to delete
}

int Timer::GetType()
{
	return Caller::Timer;
}

void Timer::Start()
{
	if (m_IsRunning == false)
	{
		CreateTimerQueueTimer(&m_TimerHandle, NULL, TimerProcStatic, (void*) this, m_Delay, m_Delay, WT_EXECUTEINTIMERTHREAD);
		m_IsRunning = true;
	}
}

void Timer::Stop()
{
	if (m_IsRunning == true)
	{
		DeleteTimerQueueTimer(NULL, m_TimerHandle, NULL);
		//CloseHandle (m_TimerHandle);		DeleteTimerQueueTimer automatically closes the handle? MSDN Documentation seems to suggest this

		m_IsRunning = false;
	}
}

bool Timer::IsRunning()
{
	return m_IsRunning;
}

void Timer::SetDelay(int msec)
{
	m_Delay = max(msec, 1); // timer will not accept values less than 1 msec

	if (m_IsRunning)
	{
		Stop();
		Start();
	}
}

int Timer::GetDelay()
{
	return m_Delay;
}

void CALLBACK Timer::TimerProcStatic(void* lpParameter, BOOLEAN TimerOrWaitFired)
{
	Timer* timer = reinterpret_cast<Timer*>(lpParameter);

	//if (timer->m_IsRunning) timer->m_Target->CallAction(timer);
	if (timer->m_IsRunning) timer->CallListeners();
}

//-----------------------------------------------------------------
// String methods
//-----------------------------------------------------------------

String::String(wchar_t const* wideTextPtr) : m_Precision(-1)
{
	m_Length = (int)wcslen(wideTextPtr) + 1; // include room for null terminator
	m_TextPtr = new TCHAR[m_Length];

	if (sizeof(TCHAR) == 2) _tcscpy_s(m_TextPtr, m_Length, (TCHAR*)wideTextPtr);
	else WideCharToMultiByte(CP_ACP, 0, wideTextPtr, -1, (char*)m_TextPtr, m_Length, NULL, NULL);
}

String::String(char const* singleTextPtr) : m_Precision(-1)
{
	m_Length = (int)strlen(singleTextPtr) + 1; // inlude room for null terminator

	m_TextPtr = new TCHAR[m_Length];

	if (sizeof(TCHAR) == 1) strcpy_s((char*)m_TextPtr, m_Length, singleTextPtr);
	else MultiByteToWideChar(CP_ACP, 0, singleTextPtr, -1, (wchar_t*)m_TextPtr, m_Length * 2);
}

String::String(wchar_t character) : m_Precision(-1)
{
	m_Length = 2; // include room for null terminator
	m_TextPtr = new TCHAR[m_Length];

	m_TextPtr[0] = (TCHAR)character;
	m_TextPtr[1] = '\0';
}

String::String(char character) : m_Precision(-1)
{
	m_Length = 2; // include room for null terminator
	m_TextPtr = new TCHAR[m_Length];

	m_TextPtr[0] = character;
	m_TextPtr[1] = '\0';
}

String::String(String const& sRef) : m_Precision(sRef.m_Precision)
{
	m_Length = sRef.GetLength() + 1; // include room for null terminator
	m_TextPtr = new TCHAR[m_Length];

	_tcscpy_s(m_TextPtr, m_Length, sRef.ToTChar());
}

String::~String()
{
	delete m_TextPtr;
	m_TextPtr = 0;
}

String& String::operator=(String const& sRef)
{
	if (this != &sRef) // beware of self assignment: s = s
	{
		delete m_TextPtr;
		m_Length = sRef.GetLength() + 1;
		m_TextPtr = new TCHAR[m_Length];
		_tcscpy_s(m_TextPtr, m_Length, sRef.ToTChar());
	}
	return *this;
}

String& String::operator+=(String const& sRef)
{
	m_Length = this->GetLength() + sRef.GetLength() + 1;

	TCHAR* buffer = new TCHAR[m_Length];

	_tcscpy_s(buffer, m_Length, m_TextPtr);
	_tcscat_s(buffer, m_Length, sRef.m_TextPtr);

	delete m_TextPtr;
	m_TextPtr = buffer;

	return *this;
}

String& String::operator+=(wchar_t* wideTextPtr)
{
	return *this += String(wideTextPtr);
}

String& String::operator+=(char* singleTextPtr)
{
	return *this += String(singleTextPtr);
}

String& String::operator+=(int number)
{
	char buffer[65]; // an int will never take more than 65 characters (int64 is max 20 characters)

	_itoa_s(number, buffer, sizeof(buffer), 10);

	return *this += String(buffer);
}

String& String::operator+=(size_t number)
{
	char buffer[65]; // an int will never take more than 65 characters (int64 is max 20 characters)

	_ultoa_s((unsigned long)number, buffer, sizeof(buffer), 10);

	return *this += String(buffer);
}

String& String::operator+=(double number)
{
	tstringstream buffer;
	if (m_Precision != -1)
		buffer << std::fixed << std::setprecision(m_Precision);
	buffer << number;
	tstring result;
	buffer >> result;
	return *this += String(result.c_str());
}

String& String::operator+=(wchar_t character)
{
	return *this += String(character);
}

String& String::operator+=(char character)
{
	return *this += String(character);
}

String String::operator+(String const& sRef)
{
	String newString = *this;

	newString += sRef;

	return newString;
}

String String::operator+(wchar_t* wideTextPtr)
{
	String newString = *this;

	newString += wideTextPtr;

	return newString;
}

String String::operator+(char* singleTextPtr)
{
	String newString = *this;

	newString += singleTextPtr;

	return newString;
}

String String::operator+(int number)
{
	String newString = *this;

	newString += number;

	return newString;
}

String String::operator+(size_t number)
{
	String newString = *this;

	newString += number;

	return newString;
}

String String::operator+(double number)
{
	String newString = *this;

	newString += number;

	return newString;
}

String String::operator+(wchar_t character)
{
	String newString = *this;

	newString += character;

	return newString;
}

String String::operator+(char character)
{
	String newString = *this;

	newString += character;

	return newString;
}

bool String::operator==(String const& sRef)
{
	return this->Equals(sRef);
}

bool String::operator==(String const& sRef) const
{
	return this->Equals(sRef);
}

TCHAR String::CharAt(int index) const
{
	if (index > this->GetLength() - 1) return 0;

	return m_TextPtr[index];
}

String String::Replace(TCHAR oldChar, TCHAR newChar) const
{
	String newString = *this;

	for (int count = 0; count < newString.GetLength(); count++)
	{
		if (newString.m_TextPtr[count] == oldChar) newString.m_TextPtr[count] = newChar;
	}

	return newString;
}

String String::SubString(int index) const
{
	if (index > this->GetLength() - 1) return String("");

	return String(m_TextPtr + index);
}

String String::SubString(int index, int length) const
{
	if (index + length - 1 > this->GetLength() - 1) return String("");

	String newString = *this;
	newString.m_TextPtr[index + length] = TEXT('\0');

	return String(newString.m_TextPtr + index);
}

String String::ToLowerCase() const
{
	String newString = *this;

	for (int count = 0; count < newString.GetLength(); count++)
	{
		TCHAR character = newString.m_TextPtr[count];

		if (character < 91 && character > 64) newString.m_TextPtr[count] += 32;
	}

	return newString;
}

String String::ToUpperCase() const
{
	String newString = *this;

	for (int count = 0; count < newString.GetLength(); count++)
	{
		TCHAR character = newString.m_TextPtr[count];

		if (character < 123 && character > 96) newString.m_TextPtr[count] -= 32;
	}

	return newString;
}

String String::Trim() const
{
	int beginIndex = 0;
	int endIndex = this->GetLength() - 1;

	while (m_TextPtr[beginIndex] == TEXT(' ') && m_TextPtr[beginIndex] != TEXT('\0')) ++beginIndex;
	while (m_TextPtr[endIndex] == TEXT(' ') && endIndex > 0) --endIndex;

	return this->SubString(beginIndex, endIndex - beginIndex + 1);
}

int String::IndexOf(TCHAR character) const
{
	int index = 0;

	while (m_TextPtr[index] != character && m_TextPtr[index] != TEXT('\0')) ++index;

	if (m_TextPtr[index] == character) return index;
	else return -1;
}

int String::LastIndexOf(TCHAR character) const
{
	int index = this->GetLength() - 1;

	while (m_TextPtr[index] != character && index > 0) --index;

	if (m_TextPtr[index] == character) return index;
	else return -1;
}

bool String::StartsWith(String const& sRef) const
{
	// return false if 2nd string is longer than 1st string
	if (this->GetLength() < sRef.GetLength()) return false;

	// check individual characters
	bool result = true;
	int index = 0;
	int max = sRef.GetLength();

	while (index < max && result)
	{
		if (m_TextPtr[index] != sRef.m_TextPtr[index]) result = false;
		else ++index;
	}

	return result;
}

bool String::EndsWith(String const& sRef) const
{
	// return false if 2nd string is longer than 1st string
	if (this->GetLength() < sRef.GetLength()) return false;

	String temp = this->SubString(this->GetLength() - sRef.GetLength());

	return sRef.Equals(temp);
}

int String::GetLength() const
{
	return m_Length - 1; // don't include the null terminator when asked how many characters are in the string
}

bool String::Equals(String const& sRef) const
{
	if (sRef.GetLength() != this->GetLength()) return false;

	return _tcscmp(this->ToTChar(), sRef.ToTChar()) ? false : true; // return true if cmp returns 0, false if not
}

String& String::SetPrecision(int precision)
{
	m_Precision = precision;
	return *this;
}

int String::ToInteger() const
{
	return _tstoi(this->ToTChar());
}

double String::ToDouble() const
{
	return _tcstod(this->ToTChar(), 0);
}

TCHAR* String::ToTChar() const
{
	return m_TextPtr;
}

//-----------------------------------------------------------------
// OutputDebugString functions
//-----------------------------------------------------------------
void OutputDebugString(String const& textRef)
{
	OutputDebugString(textRef.ToTChar());
}

// Create resources which are not bound
// to any device. Their lifetime effectively extends for the
// duration of the app. These resources include the Direct2D and
// DirectWrite factories,  and a DirectWrite Text Format object
// (used for identifying particular font characteristics).
//
void GameEngine::CreateDeviceIndependentResources()
{
	CreateD2DFactory();
	CreateWICFactory();
	CreateWriteFactory();
}

void GameEngine::CreateD2DFactory()
{
	HRESULT hr;
	// Create a Direct2D factory.
	ID2D1Factory* localD2DFactoryPtr;
	if (!m_D2DFactoryPtr)
	{
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &localD2DFactoryPtr);
		if (FAILED(hr))
		{
			MessageBox("Create D2D Factory Failed");
			exit(-1);
		}
		m_D2DFactoryPtr = localD2DFactoryPtr;
	}
}

void GameEngine::CreateWICFactory()
{
	HRESULT hr;
	// Create a WIC factory if it does not exists
	IWICImagingFactory* localWICFactoryPtr;
	if (!m_WICFactoryPtr)
	{
		hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&localWICFactoryPtr));
		if (FAILED(hr))
		{
			MessageBox("Create WIC Factory Failed");
			exit(-1);
		}
		m_WICFactoryPtr = localWICFactoryPtr;
	}
}

void GameEngine::CreateWriteFactory()
{
	HRESULT hr;
	// Create a DirectWrite factory.
	IDWriteFactory *localDWriteFactoryPtr;
	if (!m_DWriteFactoryPtr)
	{
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(localDWriteFactoryPtr), reinterpret_cast<IUnknown **>(&localDWriteFactoryPtr));
		if (FAILED(hr))
		{
			MessageBox("Create WRITE Factory Failed");
			exit(-1);
		}
		m_DWriteFactoryPtr = localDWriteFactoryPtr;
	}
}

//
//  This method creates resources which are bound to a particular
//  Direct3D device. It's all centralized here, in case the resources
//  need to be recreated in case of Direct3D device loss (eg. display
//  change, remoting, removal of video card, etc).
//
void GameEngine::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!m_RenderTargetPtr)
	{
		D2D1_SIZE_U size = D2D1::SizeU((UINT)GetWidth(), (UINT)GetHeight());

		// Create a Direct2D render target.
		// EndPaint waits till VBLank !!! when OPTIONS_NONE
		//use D2D1_PRESENT_OPTIONS::D2D1_PRESENT_OPTIONS_NONE for vblank sync
		//and D2D1_PRESENT_OPTIONS::D2D1_PRESENT_OPTIONS_IMMEDIATELY for no waiting
		//D2D1_PRESENT_OPTIONS_RETAIN_CONTENTS
		D2D1_PRESENT_OPTIONS pres_opt;
		//if(m_GameConfiguratorPtr->GetWaitForDisplayRefresh())pres_opt = D2D1_PRESENT_OPTIONS_NONE;
		//else
		pres_opt = D2D1_PRESENT_OPTIONS_IMMEDIATELY;

		//Peter: DPI setting van Display kan verschillen, waardoor client area niet correct afmetingen heeft
		D2D1_RENDER_TARGET_PROPERTIES rtp = D2D1::RenderTargetProperties();
		rtp.dpiX = 96;
		rtp.dpiY = 96;
		ID2D1HwndRenderTarget *localRenderTargetPtr;
		hr = m_D2DFactoryPtr->CreateHwndRenderTarget(rtp, D2D1::HwndRenderTargetProperties(m_hWindow, size, pres_opt), &localRenderTargetPtr);

		if (FAILED(hr))
		{
			MessageBox("Create CreateDeviceResources Failed");
			exit(-1);
		}
		m_RenderTargetPtr = localRenderTargetPtr;

		//set alias mode
		m_RenderTargetPtr->SetAntialiasMode(m_AntialiasMode);

		// Create a brush.
		m_RenderTargetPtr->CreateSolidColorBrush((D2D1::ColorF) D2D1::ColorF::Black, &m_ColorBrushPtr);
		//Create a Font
		m_DefaultFontPtr = new TextFormat(_T("Consolas"), 12);

		m_bInitialized = true;
	}
}

//
//  Discard device-specific resources which need to be recreated
//  when a Direct3D device is lost
//
void GameEngine::DiscardDeviceResources()
{
	m_bInitialized = false;
}

void GameEngine::D2DBeginPaint()
{
	ID2D1HwndRenderTarget *renderTargetPtr = m_RenderTargetPtr;

	if (renderTargetPtr)
	{
		renderTargetPtr->BeginDraw();
		renderTargetPtr->SetTransform(D2D1::Matrix3x2F::Identity());
		renderTargetPtr->Clear((D2D1::ColorF) D2D1::ColorF::White);
	}
}

bool GameEngine::D2DEndPaint()
{
	HRESULT hr = S_OK;
	ID2D1HwndRenderTarget *renderTargetPtr = m_RenderTargetPtr;
	hr = renderTargetPtr->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
		m_bInitialized = false;
		return false; //app should close or re-initialize
	}
	return true;
}
//=======================================================================================
// StopWatch.cpp by Frank Luna (C) 2008 All Rights Reserved.
// Adapted for DAE GP1 by Bart Uyttenhove
//=======================================================================================
StopWatch::StopWatch() : m_SecondsPerCount(0.0), m_DeltaTime(-1.0), m_BaseTime(0), m_PausedTime(0), m_PrevTime(0), m_CurrTime(0), m_bStopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_SecondsPerCount = 1.0 / (double)countsPerSec;
}

StopWatch::~StopWatch()
{}

// Returns the total time elapsed since reset() was called, NOT counting any
// time when the clock is stopped.
double StopWatch::GetGameTime()
{
	// If we are stopped, do not count the time that has passed since we stopped.
	//
	// ----*---------------*------------------------------*------> time
	//  mBaseTime       mStopTime                      mCurrTime

	if (m_bStopped)
	{
		return (double)((m_StopTime - m_BaseTime) * m_SecondsPerCount);
	}

	// The distance mCurrTime - mBaseTime includes paused time,
	// which we do not want to count.  To correct this, we can subtract
	// the paused time from mCurrTime:
	//
	//  (mCurrTime - mPausedTime) - mBaseTime
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mCurrTime

	else
	{
		return (double)(((m_CurrTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);
	}
}

double StopWatch::GetDeltaTime()
{
	return (double)m_DeltaTime;
}

void StopWatch::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_BaseTime = currTime;
	m_PrevTime = currTime;
	m_StopTime = 0;
	m_bStopped = false;
}

void StopWatch::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);


	// Accumulate the time elapsed between stop and start pairs.
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------> time
	//  mBaseTime       mStopTime        startTime

	if (m_bStopped)
	{
		m_PausedTime += (startTime - m_StopTime);

		m_PrevTime = startTime;
		m_StopTime = 0;
		m_bStopped = false;
	}
}

void StopWatch::Stop()
{
	if (!m_bStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_StopTime = currTime;
		m_bStopped = true;
	}
}

void StopWatch::Tick()
{
	if (m_bStopped)
	{
		m_DeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_CurrTime = currTime;

	// Time difference between this frame and the previous.
	m_DeltaTime = (m_CurrTime - m_PrevTime) * m_SecondsPerCount;

	// Prepare for next frame.
	m_PrevTime = m_CurrTime;

	// Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the
	// processor goes into a power save mode or we get shuffled to another
	// processor, then mDeltaTime can be negative.
	if (m_DeltaTime < 0.0)
	{
		m_DeltaTime = 0.0;
	}
}

bool StopWatch::IsStopped()
{
	return m_bStopped;
}

//---------------------------
// Bitmap methods
//---------------------------
// Load an Bitmap using a filename
Bitmap::Bitmap(const String& fileName) : m_BitmapPtr(0), m_ConvertorPtr(0), m_Opacity(1.0), m_ResourceID(0)
{
	m_FileName = fileName.ToTChar();
	//IWICFormatConverter *convertorPtr=0;
	ID2D1RenderTarget *renderTargetPtr = GameEngine::GetSingleton()->GetHwndRenderTarget();
	IWICImagingFactory *iWICFactoryPtr = GameEngine::GetSingleton()->GetWICImagingFactory();

	HRESULT hr = LoadBitmapFromFile(renderTargetPtr, iWICFactoryPtr, m_FileName, 0, 0, &m_ConvertorPtr);
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = renderTargetPtr->CreateBitmapFromWicBitmap(m_ConvertorPtr, &m_BitmapPtr);
	}

	if (FAILED(hr))
	{
		//show messagebox and leave the program
		GameEngine::GetSingleton()->MessageBox(String("IMAGE LOADING ERROR File ") + fileName);
		exit(-1);
	}
}

// Load an Bitmap using a resourceID
Bitmap::Bitmap(int resourceID) : m_BitmapPtr(0), m_ConvertorPtr(0), m_Opacity(1), m_ResourceID(resourceID)
{
	IWICFormatConverter* convertorPtr = 0;
	ID2D1RenderTarget* renderTargetPtr = GameEngine::GetSingleton()->GetHwndRenderTarget();
	IWICImagingFactory* iWICFactoryPtr = GameEngine::GetSingleton()->GetWICImagingFactory();

	HRESULT hr = LoadResourceBitmap(renderTargetPtr, iWICFactoryPtr, (unsigned int)resourceID, _T("IMAGE"), &m_ConvertorPtr);
	if (SUCCEEDED(hr))
	{
		//Create a Direct2D bitmap from the WIC bitmap.
		hr = renderTargetPtr->CreateBitmapFromWicBitmap(m_ConvertorPtr, &m_BitmapPtr);
	}

	if (FAILED(hr))
	{
		//show messagebox
		GameEngine::GetSingleton()->MessageBox(String("RESOURCE IMAGE LOADING ERROR File. ID: ") + resourceID);
	}
}

Bitmap::~Bitmap()
{
	m_BitmapPtr->Release();
	m_ConvertorPtr->Release();
}

HRESULT Bitmap::LoadResourceBitmap(ID2D1RenderTarget* renderTargetPtr, IWICImagingFactory* wICFactoryPtr, unsigned int resourceNumber, String resourceType, IWICFormatConverter** formatConverterPtr)
{
	HRESULT hr = S_OK;
	IWICBitmapDecoder* decoderPtr = 0;
	IWICBitmapFrameDecode* sourcePtr = 0;
	IWICStream* streamPtr = 0;

	HRSRC imageResHandle = 0;
	HGLOBAL imageResDataHandle = 0;
	void* bitmapFilePtr = 0;
	DWORD imageFileSize = 0;

	// Locate the resource. http://msdn.microsoft.com/en-us/library/ms648042(VS.85).aspx
	imageResHandle = FindResource(GetModuleHandle(0), MAKEINTRESOURCE(resourceNumber), resourceType.ToTChar());

	hr = imageResHandle ? S_OK : E_FAIL;
	if (SUCCEEDED(hr))
	{
		// Load the resource.
		imageResDataHandle = LoadResource(GetModuleHandle(0), imageResHandle);

		hr = imageResDataHandle ? S_OK : E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		// Lock it to get a system memory pointer.
		bitmapFilePtr = LockResource(imageResDataHandle);

		hr = bitmapFilePtr ? S_OK : E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		// Calculate the size.
		imageFileSize = SizeofResource(GetModuleHandle(0), imageResHandle);

		hr = imageFileSize ? S_OK : E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		// Create a WIC stream to map onto the memory.
		hr = wICFactoryPtr->CreateStream(&streamPtr);
	}

	if (SUCCEEDED(hr))
	{
		// Initialize the stream with the memory pointer and size.
		hr = streamPtr->InitializeFromMemory(reinterpret_cast<BYTE*>(bitmapFilePtr), imageFileSize);
	}

	if (SUCCEEDED(hr))
	{
		// Create a decoder for the stream.
		hr = wICFactoryPtr->CreateDecoderFromStream(streamPtr, NULL, WICDecodeMetadataCacheOnLoad, &decoderPtr);
	}

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = decoderPtr->GetFrame(0, &sourcePtr);
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = wICFactoryPtr->CreateFormatConverter(formatConverterPtr);
	}

	if (SUCCEEDED(hr))
	{
		hr = (*formatConverterPtr)->Initialize(sourcePtr, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
	}

	if (decoderPtr != 0) decoderPtr->Release();
	if (sourcePtr != 0)  sourcePtr->Release();
	if (streamPtr != 0)  streamPtr->Release();

	return hr;
}

HRESULT Bitmap::LoadBitmapFromFile(ID2D1RenderTarget *renderTargetPtr, IWICImagingFactory *wICFactoryPtr, String uri, UINT destinationWidth, UINT destinationHeight, IWICFormatConverter **FormatConverterPtr)
{
	IWICBitmapDecoder*		decoderPtr = 0;
	IWICBitmapFrameDecode*	sourcePtr = 0;
	IWICBitmapScaler*		scalerPtr = 0;
	//CreateDecoderFromFilename->first param HAS TO BE LPCWSTR
	tstring tUri(uri.ToTChar());
	wstring wUri(tUri.begin(), tUri.end());
	HRESULT hr = wICFactoryPtr->CreateDecoderFromFilename(wUri.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoderPtr);

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = decoderPtr->GetFrame(0, &sourcePtr);
	}
	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = wICFactoryPtr->CreateFormatConverter(FormatConverterPtr);
	}

	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = sourcePtr->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = (FLOAT)destinationHeight / (FLOAT)originalHeight;
					destinationWidth = (UINT)(scalar * (FLOAT)originalWidth);
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = (FLOAT)destinationWidth / (FLOAT)originalWidth;
					destinationHeight = (UINT)(scalar * (FLOAT)originalHeight);
				}

				hr = wICFactoryPtr->CreateBitmapScaler(&scalerPtr);
				if (SUCCEEDED(hr))
				{
					hr = scalerPtr->Initialize(sourcePtr, destinationWidth, destinationHeight, WICBitmapInterpolationModeCubic);
				}
				if (SUCCEEDED(hr))
				{
					hr = (*FormatConverterPtr)->Initialize(scalerPtr, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = (*FormatConverterPtr)->Initialize(sourcePtr, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
		}
	}

	if (decoderPtr != 0) decoderPtr->Release();
	if (sourcePtr != 0)  sourcePtr->Release();
	if (scalerPtr != 0)  scalerPtr->Release();

	return hr;
}

ID2D1Bitmap* Bitmap::GetBitmapPtr()
{
	return m_BitmapPtr;
}

int Bitmap::GetWidth()
{
	return m_BitmapPtr->GetPixelSize().width;
}

int	Bitmap::GetHeight()
{
	return m_BitmapPtr->GetPixelSize().height;
}

double Bitmap::GetOpacity()
{
	return m_Opacity;
}

void Bitmap::SetOpacity(double opacity)
{
	m_Opacity = opacity;
}

void Bitmap::SetTransparencyColor(int red, int green, int blue)
{
	COLORREF color = RGB(red, green, blue);

	UINT width = 0, height = 0;
	WICPixelFormatGUID* pPixelFormat = 0;
	m_ConvertorPtr->GetPixelFormat(pPixelFormat);
	m_ConvertorPtr->GetSize(&width, &height);
	UINT bitmapStride = 4 * width;
	UINT size = width * height * 4;
	unsigned char* pixelsPtr = new unsigned char[size]; // create 32 bit buffer
	m_ConvertorPtr->CopyPixels(NULL, bitmapStride, size, pixelsPtr);

	for (unsigned int count = 0; count < width * height; ++count)
	{
		if (RGB(pixelsPtr[count * 4 + 2], pixelsPtr[count * 4 + 1], pixelsPtr[count * 4]) == color) // if the color of this pixel == transparency color
		{
			((int*)pixelsPtr)[count] = 0; // set all four values to zero, this assumes sizeof(int) == 4 on this system
											// setting values to zero means premultiplying the RGB values to an alpha of 0
		}
	}

	//assign modified pixels to bitmap
	IWICImagingFactory* iWICFactoryPtr = GameEngine::GetSingleton()->GetWICImagingFactory();
	IWICBitmap* iWICBitmapPtr = 0;
	HRESULT hr = iWICFactoryPtr->CreateBitmapFromMemory(width, height, GUID_WICPixelFormat32bppPBGRA, bitmapStride, size, pixelsPtr, &iWICBitmapPtr);
	delete[] pixelsPtr; //destroy buffer
	if (hr == S_OK)
	{
		ID2D1RenderTarget *renderTargetPtr = GameEngine::GetSingleton()->GetHwndRenderTarget();
		if (m_BitmapPtr != 0) m_BitmapPtr->Release();
		renderTargetPtr->CreateBitmapFromWicBitmap(iWICBitmapPtr, &m_BitmapPtr);
		iWICBitmapPtr->Release();
	}
}

bool Bitmap::Exists()
{
	return m_BitmapPtr ? true : false;
}


//---------------------------
// TextFormat methods
//---------------------------
TextFormat::TextFormat(IDWriteTextFormat *textFormatPtr) : m_TextFormatPtr(textFormatPtr)
{}

TextFormat::TextFormat(String fontName, float size)
{
	tstring temp(fontName.ToTChar());
	wstring str(temp.begin(), temp.end());
	LoadTextFormat(str.c_str(), size);
}


TextFormat::~TextFormat(void)
{
	m_TextFormatPtr->Release();
}

void TextFormat::LoadTextFormat(const wchar_t* fontName, float size)
{
	HRESULT hr;
	// Create a DirectWrite text format object.
	hr = GameEngine::GetSingleton()->GetDWriteFactory()->CreateTextFormat(fontName, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"", &m_TextFormatPtr);

	if (SUCCEEDED(hr))
	{
		// align left and top the text horizontally and vertically.
		m_TextFormatPtr->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_TextFormatPtr->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}
	else
	{
		MessageBoxW(NULL, fontName, L"TEXTFORMAT BUILDING ERROR", MB_ICONERROR);
		exit(-1);
	}
}

IDWriteTextFormat* TextFormat::GetTextFormat()
{
	return m_TextFormatPtr;
}

void TextFormat::SetAlignHLeft()
{
	m_TextFormatPtr->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
}

void TextFormat::SetAlignHCenter()
{
	m_TextFormatPtr->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
}

void TextFormat::SetAlignHRight()
{
	m_TextFormatPtr->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
}

void TextFormat::SetAlignVTop()
{
	m_TextFormatPtr->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
}

void TextFormat::SetAlignVCenter()
{
	m_TextFormatPtr->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

void TextFormat::SetAlignVBottom()
{
	m_TextFormatPtr->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
}


//-----------------------------------------------------------------
// SVGLoader Class
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------
// This ifdef block is here because in the 1st year students still need to learn what it means/put it in themselves. In the 2nd year engine it is defined in GameDefines.h
#ifdef _UNICODE
#define tifstream wifstream
#else
#define tifstream ifstream
#endif

SVGLoader::SVGLoader()
{}

SVGLoader::~SVGLoader()
{}

bool SVGLoader::LoadGeometryFromSvgFile(String svgFilePath, ID2D1Geometry*& geometryPtrRef)
{
	// open the file, close if not found
	tifstream svgFile(svgFilePath.ToTChar());

	if (!svgFile)
	{
		GameEngine::GetSingleton()->MessageBox(String("Failed to load geometry from file ") + svgFilePath);
		return false;
	}
	else
	{
		// read the file
		tstring sLine;
		tstring svgText;
		while (!svgFile.eof())
		{
			getline(svgFile, sLine);
			svgText += sLine;
		}

		// close the file
		svgFile.close();

		// extract the transform information, if present
		tstring sTransformInfo;
		bool result = ExtractTransformInformation(svgText, sTransformInfo);

		// extract the geometry information, exit if not found
		tstring sGeometryInfo;
		result = ExtractPathInformation(svgText, sGeometryInfo);
		if (result == false)
		{
			GameEngine::GetSingleton()->MessageBox(String("Malformed geometry information in file ") + svgFilePath);
			return false;
		}

		// process the geometry information
		return ReadSvgFromData(GameEngine::GetSingleton()->GetD2DFactory(), sTransformInfo, sGeometryInfo, geometryPtrRef);
	}
}

bool SVGLoader::ExtractTransformInformation(tstring& svgTextRef, tstring& sTransformInfoRef)
{
	tstring pattern = _T("transform=");
	tstring::iterator posTransform = search(svgTextRef.begin(), svgTextRef.end(), pattern.begin(), pattern.end());
	if (posTransform == svgTextRef.end()) // d attribute not found, maybe with a space?
	{
		pattern = _T("transform =");
		posTransform = search(svgTextRef.begin(), svgTextRef.end(), pattern.begin(), pattern.end());
	}
	if (posTransform == svgTextRef.end()) // try in caps?
	{
		pattern = _T("TRANSFORM=");
		posTransform = search(svgTextRef.begin(), svgTextRef.end(), pattern.begin(), pattern.end());
	}
	if (posTransform == svgTextRef.end()) // last try
	{
		pattern = _T("TRANSFORM =");
		posTransform = search(svgTextRef.begin(), svgTextRef.end(), pattern.begin(), pattern.end());
	}
	if (posTransform == svgTextRef.end()) // give up
	{
		return false;
	}

	tstring::iterator posOpeningDoubleQuote = find(posTransform, svgTextRef.end(), _T('\"'));
	tstring::iterator posClosingDoubleQuote = find(posOpeningDoubleQuote + 1, svgTextRef.end(), _T('\"'));

	sTransformInfoRef = tstring(posOpeningDoubleQuote + 1, posClosingDoubleQuote);

	return true;
}

bool SVGLoader::ExtractPathInformation(tstring& svgTextRef, tstring& sGeometryInfoRef)
{
	// extract the path information part
	tstring pattern(_T("<path"));
	tstring::iterator posPath = search(svgTextRef.begin(), svgTextRef.end(), pattern.begin(), pattern.end());
	pattern = _T(" d=");
	tstring::iterator posD = search(posPath, svgTextRef.end(), pattern.begin(), pattern.end());
	if (posD == svgTextRef.end()) // d attribute not found, maybe with a space?
	{
		pattern = _T(" d =");
		posD = search(posPath, svgTextRef.end(), pattern.begin(), pattern.end());
	}
	if (posD == svgTextRef.end()) // try in caps?
	{
		pattern = _T(" D=");
		posD = search(posPath, svgTextRef.end(), pattern.begin(), pattern.end());
	}
	if (posD == svgTextRef.end()) // last try
	{
		pattern = _T(" D =");
		posD = search(posPath, svgTextRef.end(), pattern.begin(), pattern.end());
	}
	if (posD == svgTextRef.end()) // give up
	{
		return false;
	}

	tstring::iterator posOpeningDoubleQuote = find(posD, svgTextRef.end(), _T('\"'));
	tstring::iterator posClosingDoubleQuote = find(posOpeningDoubleQuote + 1, svgTextRef.end(), _T('\"'));

	sGeometryInfoRef = tstring(posOpeningDoubleQuote + 1, posClosingDoubleQuote);

	return true;
}

// Reads geometry from a tiny XML node.
// Points are transformed by groups into the same space.
bool SVGLoader::ReadSvgFromData(ID2D1Factory* factoryPtr, tstring& sTransformInfoRef, tstring& sPathInfoRef, ID2D1Geometry*& geometryPtrRef)
{
	std::vector<ID2D1Geometry*> outGeometryArr;

	HRESULT hr;

	// parse the transform information
	MATRIX3X2 pathTransform = ReadTransform(sTransformInfoRef);

	// parse the geometry information
	ID2D1PathGeometry* pathGeometryPtr;
	bool result = ReadSvgPath(factoryPtr, sPathInfoRef, pathGeometryPtr);


	ID2D1TransformedGeometry* transformedGeometryPtr;
	hr = factoryPtr->CreateTransformedGeometry(pathGeometryPtr, pathTransform.ToMatrix3x2F(), &transformedGeometryPtr);
	if (FAILED(hr))
	{
		GameEngine::GetSingleton()->MessageBox("CreateTransformedGeometry failed");
		return false;
	}

	outGeometryArr.push_back(transformedGeometryPtr);

	return GetGeometryOrGroup(factoryPtr, outGeometryArr, geometryPtrRef);
}

bool SVGLoader::GetGeometryOrGroup(ID2D1Factory* factoryPtr, std::vector<ID2D1Geometry*>& childrenRef, ID2D1Geometry*& geometryPtrRef)
{
	if (!childrenRef.empty())
	{
		if (childrenRef.size() == 1)
		{
			geometryPtrRef = childrenRef[0];
		}
		else
		{
			ID2D1GeometryGroup* geometryGroupPtr;
			HRESULT hr = factoryPtr->CreateGeometryGroup(D2D1_FILL_MODE_WINDING, &childrenRef[0], childrenRef.size(), &geometryGroupPtr);
			if (FAILED(hr))
			{
				GameEngine::GetSingleton()->MessageBox("CreateTransformedGeometry failed");
				return false;
			}

			geometryPtrRef = geometryGroupPtr;
		}
	}

	return true;
}

MATRIX3X2 SVGLoader::ReadTransform(tstring& sTransformInfoRef)
{
	int argCount;
	MATRIX3X2 matrix;

	if (sTransformInfoRef != _T(""))
	{
		switch (sTransformInfoRef.c_str()[0])
		{
		case _T('m'):
			_stscanf_s(sTransformInfoRef.c_str(), _T("matrix(%lf,%lf,%lf,%lf,%lf,%lf)"), &matrix.dirX.x, &matrix.dirX.y, &matrix.dirY.x, &matrix.dirY.y, &matrix.orig.x, &matrix.orig.y);
			break;

		case _T('t'):
			argCount = _stscanf_s(sTransformInfoRef.c_str(), _T("translate(%lf,%lf)"), &matrix.orig.x, &matrix.orig.y);
			break;

		case _T('s'):
			argCount = _stscanf_s(sTransformInfoRef.c_str(), _T("scale(%lf,%lf)"), &matrix.dirX.x, &matrix.dirY.y);

			if (argCount == 1)
			{
				matrix.dirY.y = matrix.dirX.x;
			}
			break;

		case _T('r'):
		{
			double angle;
			DOUBLE2 center;
			argCount = _stscanf_s(sTransformInfoRef.c_str(), _T("rotate(%lf,%lf,%lf)"), &angle, &center.x, &center.y);

			switch (argCount)
			{
			case 1:
				matrix = MATRIX3X2::CreateRotationMatrix(angle * M_PI / 180);
				break;
			case 3:
				matrix = MATRIX3X2::CreateTranslationMatrix(-center) * MATRIX3X2::CreateRotationMatrix(angle * M_PI / 180) * MATRIX3X2::CreateTranslationMatrix(center);
				break;
			}
		}
		break;

		default:
			GameEngine::GetSingleton()->MessageBox("unsupported transform attribute");
			break;
		}
	}

	return matrix;
}

bool SVGLoader::ReadSvgPath(ID2D1Factory* factoryPtr, tstring& sPathInfoRef, ID2D1PathGeometry*& pathGeometryPtrRef)
{
	HRESULT hr;

	// Create path geometry
	hr = factoryPtr->CreatePathGeometry(&pathGeometryPtrRef);
	if (FAILED(hr))
	{
		pathGeometryPtrRef->Release();
		GameEngine::GetSingleton()->MessageBox("Failed to create path geometry");
		return false;
	}

	// Write to the path geometry using the geometry sink.
	ID2D1GeometrySink* geometrySinkPtr = 0;
	hr = pathGeometryPtrRef->Open(&geometrySinkPtr);
	if (FAILED(hr))
	{
		geometrySinkPtr->Release();
		pathGeometryPtrRef->Release();
		GameEngine::GetSingleton()->MessageBox("Failed to open path geometry");
		return false;
	}

	// Use streamstream for parsing
	tstringstream ss(sPathInfoRef);

	TCHAR cmd;
	tstring svgCmds(_T("mMZzLlHhVvCcSsQqTtAa"));
	DOUBLE2 cursor;
	DOUBLE2 abscur;
	DOUBLE2 startPoint;//At the end of the z command, the new current point is set to the initial point of the current subpath.

	union
	{
		D2D1_BEZIER_SEGMENT cbs;
		D2D1_QUADRATIC_BEZIER_SEGMENT qbs;
	};

	bool isOpen = true;

	while (true)
	{
		TCHAR c;
		ss >> c;

		if (ss.eof())
			break;

		if (_tcschr(svgCmds.c_str(), c) != 0)
		{
			cmd = c;
		}
		else
		{
			ss.putback(c);
		}

		switch (cmd)
		{
		case _T('Z'):
		case _T('z'):
			geometrySinkPtr->EndFigure(D2D1_FIGURE_END_CLOSED);
			cursor = startPoint;//relative path: new point is set to the initial statpoint of the current path
			isOpen = true;
			break;

		case _T('M'):
		case _T('m'):
			if (isOpen)
			{
				cursor = FirstSvgPoint(ss, cursor, cmd, isOpen, true);
				startPoint = cursor;//record startpoint, cursor is set back to startPoint when path closes
				cbs.point2 = cursor.ToPoint2F();
				geometrySinkPtr->BeginFigure(cbs.point2, D2D1_FIGURE_BEGIN_FILLED);
				isOpen = false;
				break;
			}
			// Fallthrough when isOpen
		case _T('L'):
		case _T('l'):
			cbs.point2 = NextSvgPoint(ss, cursor, cmd, isOpen, true).ToPoint2F();
			geometrySinkPtr->AddLine(cbs.point2);
			break;

		case _T('h'):
		case _T('H'):
			cbs.point2 = NextSvgCoordX(ss, cursor, cmd, isOpen).ToPoint2F();
			geometrySinkPtr->AddLine(cbs.point2);
			break;

		case _T('v'):
		case _T('V'):
			cbs.point2 = NextSvgCoordY(ss, cursor, cmd, isOpen).ToPoint2F();
			geometrySinkPtr->AddLine(cbs.point2);
			break;

		case _T('C'):
		case _T('c'):
			cbs.point1 = NextSvgPoint(ss, cursor, cmd, isOpen, false).ToPoint2F();
			cbs.point2 = NextSvgPoint(ss, cursor, cmd, isOpen, false).ToPoint2F();
			cbs.point3 = NextSvgPoint(ss, cursor, cmd, isOpen, true).ToPoint2F();
			geometrySinkPtr->AddBezier(cbs);
			break;

		case _T('S'):
		case _T('s'):
			abscur = cursor;
			cbs.point1.x = (FLOAT)(abscur.x + (abscur.x - cbs.point2.x));
			cbs.point1.y = (FLOAT)(abscur.y + (abscur.y - cbs.point2.y));
			cbs.point2 = NextSvgPoint(ss, cursor, cmd, isOpen, false).ToPoint2F();
			cbs.point3 = NextSvgPoint(ss, cursor, cmd, isOpen, true).ToPoint2F();
			geometrySinkPtr->AddBezier(cbs);
			break;

		case _T('Q'):
		case _T('q'):
			qbs.point1 = NextSvgPoint(ss, cursor, cmd, isOpen, false).ToPoint2F();
			qbs.point2 = NextSvgPoint(ss, cursor, cmd, isOpen, true).ToPoint2F();
			geometrySinkPtr->AddQuadraticBezier(qbs);
			break;

		case _T('T'):
		case _T('t'):
			abscur = cursor;
			qbs.point1.x = (FLOAT)((abscur.x + (abscur.x - qbs.point2.x)));
			qbs.point1.y = (FLOAT)((abscur.y + (abscur.y - qbs.point2.y)));
			qbs.point2 = NextSvgPoint(ss, cursor, cmd, isOpen, true).ToPoint2F();
			geometrySinkPtr->AddQuadraticBezier(qbs);
			break;

		case _T('A'):
		case _T('a'):
			// (rx ry x-axis-rotation large-arc-flag sweep-flag x y)+
			// Draws an elliptical arc from the current point to (x, y).
			// The size and orientation of the ellipse are defined by two radii (rx, ry) and an x-axis-rotation,
			// which indicates how the ellipse as a whole is rotated relative to the current coordinate system.
			// The center (cx, cy) of the ellipse is calculated automatically to satisfy the constraints imposed by the other parameters.
			// large-arc-flag and sweep-flag contribute to the automatic calculations and help determine how the arc is drawn.
		{
			OutputDebugString("WARNING: SVG Arcs not supported yet\n");
			D2D1_ARC_SEGMENT arc;
			arc.size.width = (float)ReadSvgValue(ss, true);
			arc.size.height = (float)ReadSvgValue(ss, true);
			arc.rotationAngle = (float)ReadSvgValue(ss, true);
			arc.arcSize = (D2D1_ARC_SIZE)(int)ReadSvgValue(ss, true);
			arc.sweepDirection = (D2D1_SWEEP_DIRECTION)(int)ReadSvgValue(ss, true);
			cbs.point2 = arc.point = NextSvgPoint(ss, cursor, cmd, isOpen, true).ToPoint2F();
			geometrySinkPtr->AddArc(arc);
		}
		break;

		default:
			GameEngine::GetSingleton()->MessageBox("%c is not a supported SVG command");
			return false;
		}
	}

	if (!isOpen)
	{
		geometrySinkPtr->EndFigure(D2D1_FIGURE_END_CLOSED);
	}

	geometrySinkPtr->Close();
	geometrySinkPtr->Release();

	return true;
}

// Replace all whitespace by space.
TCHAR SVGLoader::WhiteSpaceMapper(TCHAR c)
{
	switch (c)
	{
	case _T('\n'):
	case _T('\r'):
	case _T('\t'):
		return _T(' ');

	default:
		return c;
	}
}

// Skips any optional commas in the stream
// SVG has a really funky format,
// not sure this code works for all cases.
// TODO: Test cases!
void SVGLoader::SkipSvgComma(tstringstream& ssRef, bool isRequired)
{
	while (true)
	{
		TCHAR c = ssRef.get();

		if (ssRef.eof())
		{
			if (isRequired) GameEngine::GetSingleton()->MessageBox("expected comma or whitespace");
			break;
		}

		if (c == _T(','))
			return;

		if (!isspace(c))
		{
			ssRef.unget();
			return;
		}
	}
}

double SVGLoader::ReadSvgValue(tstringstream& ssRef, double defaultValue)
{
	double s;
	ssRef >> s;

	if (ssRef.eof())
	{
		s = defaultValue;
	}
	else
	{
		SkipSvgComma(ssRef, false);
	}

	return s;
}

double SVGLoader::ReadSvgValue(tstringstream& ssRef, bool separatorRequired)
{
	double s;
	ssRef >> s;
	SkipSvgComma(ssRef, separatorRequired);
	return s;
}

// Reads a single point
DOUBLE2 SVGLoader::ReadSvgPoint(tstringstream& ssRef)
{
	DOUBLE2 p;
	p.x = ReadSvgValue(ssRef, true);
	p.y = ReadSvgValue(ssRef, false);
	return p;
}

DOUBLE2 SVGLoader::FirstSvgPoint(tstringstream& ssRef, DOUBLE2& cursor, TCHAR cmd, bool isOpen, bool advance)
{
	if (!isOpen) GameEngine::GetSingleton()->MessageBox("expected 'Z' or 'z' command");

	DOUBLE2 p = ReadSvgPoint(ssRef);

	if (islower(cmd))
	{
		// Relative point
		p = cursor + p;
	}

	if (advance)
	{
		cursor = p;
	}

	return p;
}
// Read the next point,
// taking into account relative and absolute positioning.
// Advances the cursor if requested.
// Throws an exception if the figure is not open
DOUBLE2 SVGLoader::NextSvgPoint(tstringstream& ssRef, DOUBLE2& cursor, TCHAR cmd, bool isOpen, bool advance)
{
	if (isOpen) GameEngine::GetSingleton()->MessageBox("expected 'M' or 'm' command");

	DOUBLE2 p = ReadSvgPoint(ssRef);

	if (islower(cmd))
	{
		// Relative point
		p = cursor + (p - DOUBLE2());
	}

	if (advance)
	{
		cursor = p;
	}

	return p;
}

// Reads next point, given only the new x coordinate
DOUBLE2 SVGLoader::NextSvgCoordX(tstringstream& ssRef, DOUBLE2& cursor, TCHAR cmd, bool isOpen)
{
	if (isOpen)
		GameEngine::GetSingleton()->MessageBox("expected 'M' or 'm' command");

	double c;
	ssRef >> c;

	if (islower(cmd))
	{
		// Relative point
		cursor += DOUBLE2(c, 0);
	}
	else
	{
		cursor.x = c;
	}

	return cursor;
}

// Reads next point, given only the new y coordinate
DOUBLE2 SVGLoader::NextSvgCoordY(tstringstream& ssRef, DOUBLE2& cursor, TCHAR cmd, bool isOpen)
{
	if (isOpen)
		GameEngine::GetSingleton()->MessageBox("expected 'M' or 'm' command");

	double c;
	ssRef >> c;

	if (islower(cmd))
	{
		// Relative point
		cursor += DOUBLE2(0, c);
	}
	else
	{
		cursor.y = c;
	}

	return cursor;
}

bool sortHitOnTime(HIT hit1, HIT hit2)
{
	return hit1.time < hit2.time;
}


//-----------------------------------------------------------------
// CUBIC methods
//-----------------------------------------------------------------
CUBIC::CUBIC()
{}

CUBIC::CUBIC(DOUBLE2 p0Param, DOUBLE2 p1Param, DOUBLE2 p2Param, DOUBLE2 p3Param) : p0(p0Param), p1(p1Param), p2(p2Param), p3(p3Param)
{}

bool IntersectLines(DOUBLE2 p1, DOUBLE2 p2, DOUBLE2 q1, DOUBLE2 q2, double& outLambda1, double& outLambda2, double epsilon)
{
	bool hit = false;

	DOUBLE2 p1p2 = p2 - p1;
	DOUBLE2 q1q2 = q2 - q1;

	double denom = p1p2.Determinant(q1q2);

	// Don't divide by zero
	if (denom < -epsilon ||
		denom > +epsilon)
	{
		hit = true;

		DOUBLE2 p1q1 = q1 - p1;

		double nomin1 = p1q1.Determinant(q1q2);
		double nomin2 = p1q1.Determinant(p1p2);
		outLambda1 = nomin1 / denom;
		outLambda2 = nomin2 / denom;
	}

	return hit;
}

bool CUBIC::IntersectLineSegments(DOUBLE2 p1, DOUBLE2 p2, DOUBLE2 q1, DOUBLE2 q2, double& outLambda1, double& outLambda2, double epsilon)
{
	bool hit = IntersectLines(p1, p2, q1, q2, outLambda1, outLambda2, epsilon);

	if (hit)
	{
		hit = outLambda1 >= 0 && outLambda1 <= 1 && outLambda2 >= 0 && outLambda2 <= 1;
	}

	return hit;
}

void CUBIC::Split(CUBIC& c0, CUBIC& c1)
{
	DOUBLE2 p01 = Lerp(p0, p1, 0.5);
	DOUBLE2 p12 = Lerp(p1, p2, 0.5);
	DOUBLE2 p23 = Lerp(p2, p3, 0.5);
	DOUBLE2 p02 = Lerp(p01, p12, 0.5);
	DOUBLE2 p13 = Lerp(p12, p23, 0.5);
	DOUBLE2 p03 = Lerp(p02, p13, 0.5);

	c0.p0 = p0;
	c0.p1 = p01;
	c0.p2 = p02;
	c0.p3 = p03;

	c1.p0 = p03;
	c1.p1 = p13;
	c1.p2 = p23;
	c1.p3 = p3;
}

void CUBIC::FitQuads(double squareTolerance, std::vector<DOUBLE2>& qs, int recurse, bool split)
{
	double time1;
	double time2;

	if (!split)
	{
		// If the lines are parallel, we must split
		split = !IntersectLines(p0, p1, p2, p3, time1, time2);;
	}

	if (!split)
	{
		// Compute intersection point of p0..p1 and p2..p3
		// This is the control point of the quadratic curve.
		DOUBLE2 q = p0 + time1*(p1 - p0);

		// Measure distance between midpoint on cubic curve [p0,p1,p2,p3] and quadratic curve [p0,q,p3]
		double dx = (4 * q.x + p3.x - 3 * p2.x - 3 * p1.x + p0.x) / 8;
		double dy = (4 * q.y + p3.y - 3 * p2.y - 3 * p1.y + p0.y) / 8;
		double dd = dx*dx + dy*dy;

		// split curve if the quadratic isn't close enough
		split = dd > squareTolerance;

		if (!split)
		{
			// no need to split, stop recursion
			qs.push_back(p0);
			qs.push_back(q);
			qs.push_back(p3);
		}
	}

	if (split)
	{
		if (recurse == 0)
		{
			qs.push_back(p0);
			qs.push_back(Lerp(p1, p2, 0.5));
			qs.push_back(p3);
		}
		else
		{
			CUBIC c0, c1;
			Split(c0, c1);
			c0.FitQuads(squareTolerance, qs, recurse - 1, false);
			c1.FitQuads(squareTolerance, qs, recurse - 1, false);
		}
	}
}


//-----------------------------------------------------------------
// SimplifiedGeometrySink methods
//-----------------------------------------------------------------
SimplifiedGeometrySink::SimplifiedGeometrySink(ID2D1GeometrySink* baseSink, double flatteningTolerance, std::vector<DOUBLE2>& lines, std::vector<DOUBLE2>& quads) :
	m_FlatteningTolerance(flatteningTolerance), m_BaseSink(baseSink), m_Lines(lines), m_Quads(quads)
{}

SimplifiedGeometrySink::~SimplifiedGeometrySink()
{}

HRESULT SimplifiedGeometrySink::QueryInterface(REFIID riid, void** ppvObject)
{
	return E_NOTIMPL;
}

ULONG SimplifiedGeometrySink::AddRef()
{
	return 0;
}

ULONG SimplifiedGeometrySink::Release()
{
	return 0;
}

void SimplifiedGeometrySink::SetFillMode(D2D1_FILL_MODE fillMode)
{
	if (m_BaseSink)
		m_BaseSink->SetFillMode(fillMode);
}

void SimplifiedGeometrySink::SetSegmentFlags(D2D1_PATH_SEGMENT vertexFlags)
{
	if (m_BaseSink)
		m_BaseSink->SetSegmentFlags(vertexFlags);
}

void SimplifiedGeometrySink::BeginFigure(D2D1_POINT_2F startPoint, D2D1_FIGURE_BEGIN figureBegin)
{
	m_StartPoint = startPoint;	//Bart: remember, may be needed when endfigure is drawn
	m_Cursor = startPoint;

	if (m_BaseSink)
		m_BaseSink->BeginFigure(startPoint, figureBegin);
}

void SimplifiedGeometrySink::AddLines(CONST D2D1_POINT_2F *points, UINT pointsCount)
{
	if (m_BaseSink)
		m_BaseSink->AddLines(points, pointsCount);

	for (UINT count = 0; count < pointsCount; ++count)
	{
		m_Lines.push_back(m_Cursor);
		m_Lines.push_back(points[count]);
		m_Cursor = points[count];
	}
}

void SimplifiedGeometrySink::AddBeziers(CONST D2D1_BEZIER_SEGMENT *beziers, UINT beziersCount)
{
	size_t quadIndex0 = m_Quads.size();

	for (UINT count = 0; count < beziersCount; ++count)
	{
		CUBIC c;
		c.p0 = m_Cursor;
		c.p1 = beziers[count].point1;
		c.p2 = beziers[count].point2;
		c.p3 = beziers[count].point3;
		m_Cursor = beziers[count].point3;
		c.FitQuads(m_FlatteningTolerance*m_FlatteningTolerance, m_Quads);
	}

	size_t quadIndex1 = m_Quads.size();

	if (m_BaseSink)
	{
		for (UINT count = quadIndex0; count < quadIndex1; count += 3)
		{
			D2D1_QUADRATIC_BEZIER_SEGMENT s;
			s.point1 = m_Quads[count + 1].ToPoint2F();
			s.point2 = m_Quads[count + 2].ToPoint2F();
			m_BaseSink->AddQuadraticBezier(&s);
		}
	}
}

void SimplifiedGeometrySink::EndFigure(D2D1_FIGURE_END figureEnd)
{
	if (m_BaseSink)
		m_BaseSink->EndFigure(figureEnd);

	if (figureEnd == D2D1_FIGURE_END_CLOSED)
	{
		m_Lines.push_back(m_Cursor);
		m_Lines.push_back(m_StartPoint);
	}
}

HRESULT SimplifiedGeometrySink::Close()
{
	HRESULT hr = S_OK;

	if (m_BaseSink)
	{
		hr = m_BaseSink->Close();
	}

	return hr;
}


//-----------------------------------------------------------------
// HitOutline methods
//-----------------------------------------------------------------
double HitOutline::DBL_NAN = sqrt(-1.0);

HitOutline::HitOutline(ID2D1Geometry* geometryPtr, ID2D1GeometrySink* targetSink, int maxDegree, double flatteningTolerance)
{
	SimplifiedGeometrySink sink(targetSink, flatteningTolerance, m_Lines, m_Quads);

	// TODO: Call Outline first?
	geometryPtr->Simplify(maxDegree >= 2 ? D2D1_GEOMETRY_SIMPLIFICATION_OPTION_CUBICS_AND_LINES : D2D1_GEOMETRY_SIMPLIFICATION_OPTION_LINES, MATRIX3X2().ToMatrix3x2F(), (float)flatteningTolerance, &sink);
}

HitOutline::~HitOutline()
{}

int HitOutline::Raycast(DOUBLE2 p, DOUBLE2 v, double maxTime, HIT* hitArr, int hitArrSize, double sense)
{
	//local data: Bart
	HIT localHitArr[MAX_HITS];

	int hitCount = 0;

	// TODO: Currently very slow, brute force!
	int lineVertexCount = m_Lines.size();
	int quadVertexCount = m_Quads.size();

	double epsilon = 1e-6;

	DOUBLE2 p1 = p;
	DOUBLE2 p2 = p + v;
	DOUBLE2 orig(0, 0);
	double vDv = v.DotProduct(v);
	DOUBLE2 n = v.Orthogonal();

	// Line-line intersections.
	if (lineVertexCount > 0)
	{
		DOUBLE2* lines = &m_Lines[0];

		for (int count = 0; count < lineVertexCount && hitCount < MAX_HITS; count += 2)
		{
			DOUBLE2 q1 = lines[count + 0];
			DOUBLE2 q2 = lines[count + 1];

			DOUBLE2 ortho = (q2 - q1).Orthogonal();
			if ((ortho.DotProduct(v) * sense < 0) || sense == 0)
			{
				double time1, time2;
				if (IntersectLines(p1, p2, q1, q2, time1, time2))
				{
					if (time1 >= 0 && time1 < maxTime && time2 >= 0 && time2 <= 1)
					{
						HIT hit;
						hit.time = time1;
						hit.point = p + time1 * v;
						hit.normal = ortho.Normalized();
						localHitArr[hitCount++] = hit;
					}
				}
			}
		}
	}

	// Line-quadratic intersections.
	if (quadVertexCount > 0)
	{
		DOUBLE2* quads = &m_Quads[0];
		for (int count = 0; count < quadVertexCount && hitCount < MAX_HITS; count += 3)
		{
			DOUBLE2 q0 = quads[count + 0] - p;
			DOUBLE2 q1 = quads[count + 1] - p;
			DOUBLE2 q2 = quads[count + 2] - p;

			// Hit only possible if:
			// (1) not all points are on same side of ray,
			//
			// (2) and some points are in front of ray (currently not checked, handled by abc formula)

			double dot_n_q0 = n.DotProduct(q0);
			double dot_n_q1 = n.DotProduct(q1);
			double dot_n_q2 = n.DotProduct(q2);

			if (dot_n_q0 <= 0 && dot_n_q1 <= 0 && dot_n_q2 <= 0)
				continue;

			if (dot_n_q0 >= 0 && dot_n_q1 >= 0 && dot_n_q2 >= 0)
				continue;

			double ts[2];
			double a = 2 * dot_n_q1 - dot_n_q0 - dot_n_q2;
			double b = 2 * dot_n_q0 - 2 * dot_n_q1;
			double c = -dot_n_q0;
			int n = SolveQuadratic(a, b, c, ts);

			for (int count2 = 0; count2 < n && hitCount < MAX_HITS; ++count2)
			{
				double t = ts[count2];
				if (t >= 0 && t <= 1)
				{
					DOUBLE2 diff = (2 * (q2 - q1) + 2 * (q0 - q1)) * t + 2 * (q1 - q0);
					DOUBLE2 ortho = diff.Orthogonal();
					if ((ortho.DotProduct(v) * sense < 0) || sense == 0)
					{
						DOUBLE2 h = Lerp(Lerp(q0, q1, t), Lerp(q1, q2, t), t);
						double time = h.DotProduct(v) / vDv;
						//time >= -maxTime
						if (time >= 0 && time < maxTime)
						{
							HIT hit;
							hit.point = p + h;
							hit.time = time;
							hit.normal = ortho.Normalized();
							localHitArr[hitCount++] = hit;
						}
					}
				}
			}
		}
	}

	std::sort(localHitArr, localHitArr + hitCount, sortHitOnTime);
	//Bart
	for (int count = 0; count < hitCount && count < hitArrSize; ++count)
	{
		hitArr[count] = localHitArr[count];
	}
	return hitCount;
}

int HitOutline::SolveQuadratic(double a, double b, double c, double* xArr)
{
	int numberOfXs = 0;

	double epsilon = 1e-6;

	if (fabs(a) < epsilon)
	{
		xArr[0] = xArr[1] = SolveLinear(b, c);
		numberOfXs = 1;
	}
	else
	{
		// Compute the discriminant d
		double d = b * b - 4 * a * c;

		if (d < 0)
		{
			// No real solutions
			xArr[0] = xArr[1] = DBL_NAN;
			numberOfXs = 0;
		}
		else if (fabs(d) < epsilon)
		{
			// One real solution
			xArr[0] = xArr[1] = -b / (2 * a);
			numberOfXs = 1;
		}
		else
		{
			// Two real solutions
			xArr[0] = (-b + sqrt(d)) / (2 * a);
			xArr[1] = (-b - sqrt(d)) / (2 * a);
			numberOfXs = 2;
		}
	}

	return numberOfXs;
}

double HitOutline::SolveLinear(double a, double b)
{
	return -b / a;
}

//-----------------------------------------------------------------
// HitRegion Object
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------
HitRegion::HitRegion() : m_D2DFactoryPtr(GameEngine::GetSingleton()->GetD2DFactory()), m_GeometryPtr(0), m_TransformedGeometryPtr(0), m_HitOutlinePtr(0)
{}

HitRegion::HitRegion(ID2D1Factory* d2DFactoryPtr) : m_D2DFactoryPtr(d2DFactoryPtr), m_GeometryPtr(0), m_TransformedGeometryPtr(0)
{}

HitRegion::~HitRegion()
{
	if (m_GeometryPtr != 0) m_GeometryPtr->Release();
	if (m_TransformedGeometryPtr != 0) m_TransformedGeometryPtr->Release();
	if (m_HitOutlinePtr != 0) delete m_HitOutlinePtr;
}

bool HitRegion::CreateFromRect(double x, double y, double width, double height)
{
	ID2D1RectangleGeometry* rg = 0;
	m_HResult = m_D2DFactoryPtr->CreateRectangleGeometry(D2D1::RectF((FLOAT)x, (FLOAT)y, (FLOAT)(x + width), (FLOAT)(y + height)), &rg);

	if (SUCCEEDED(m_HResult))
	{
		//ID2D1EllipseGeometry inherits from interface ID2D1Geometry
		if (m_GeometryPtr != 0) m_GeometryPtr->Release();
		m_GeometryPtr = rg;
		CreateTransformedGeometry(0, 0);
		return true;
	}
	else
	{
		GameEngine::GetSingleton()->MessageBox("HitRegion CreateRect Failed");
		exit(-1);
	}
	return false;
}

bool HitRegion::CreateFromEllipse(double centerX, double centerY, double radiusX, double radiusY)
{
	ID2D1EllipseGeometry* eg = 0;
	m_HResult = m_D2DFactoryPtr->CreateEllipseGeometry(D2D1::Ellipse(D2D1::Point2F((FLOAT)centerX, (FLOAT)centerY), (FLOAT)radiusX, (FLOAT)radiusY), &eg);
	if (SUCCEEDED(m_HResult))
	{
		//ID2D1EllipseGeometry inherits from interface ID2D1Geometry
		if (m_GeometryPtr != 0) m_GeometryPtr->Release();
		m_GeometryPtr = eg;
		CreateTransformedGeometry(0, 0);
		return true;
	}
	else
	{
		GameEngine::GetSingleton()->MessageBox("HitRegion CreateEllipse Failed");
		exit(-1);
	}
	return false;
}

bool HitRegion::CreateFromPolygon(DOUBLE2* pntArr, int nrPoints, bool close)
{
	ID2D1GeometrySink* sinkPtr = 0;
	ID2D1PathGeometry* pathGeometryPtr = 0;

	HRESULT hr = m_D2DFactoryPtr->CreatePathGeometry(&pathGeometryPtr);
	if (SUCCEEDED(hr))
	{
		// Write to the path geometry using the geometry sink.
		hr = pathGeometryPtr->Open(&sinkPtr);

		if (SUCCEEDED(hr))
		{
			sinkPtr->BeginFigure(D2D1::Point2F((FLOAT)pntArr[0].x, (FLOAT)pntArr[0].y), D2D1_FIGURE_BEGIN_FILLED);
			for (int count = 1; count < nrPoints; ++count)
			{
				sinkPtr->AddLine(D2D1::Point2F((FLOAT)pntArr[count].x, (FLOAT)pntArr[count].y));
			}

			if (close) sinkPtr->EndFigure(D2D1_FIGURE_END_CLOSED);
			else sinkPtr->EndFigure(D2D1_FIGURE_END_OPEN);

			hr = sinkPtr->Close();
		}
		if (sinkPtr != 0) sinkPtr->Release();
	}
	if (SUCCEEDED(hr))
	{
		if (m_GeometryPtr != 0) m_GeometryPtr->Release();
		m_GeometryPtr = pathGeometryPtr;
		CreateTransformedGeometry(0, 0);
		return true;
	}
	else
	{
		GameEngine::GetSingleton()->MessageBox("HitRegion CreatePolygon Failed");
		exit(-1);
		return(0);
	}
}

bool HitRegion::CreateFromFile(String filePath)
{
	SVGLoader sVGLoader;
	ID2D1Geometry* geometryPtr;
	bool result = sVGLoader.LoadGeometryFromSvgFile(filePath, geometryPtr);

	if (m_GeometryPtr != 0) m_GeometryPtr->Release();
	m_GeometryPtr = geometryPtr;
	CreateTransformedGeometry(0, 0);
	Simplify();//prepare for raycast
	return result;
}

bool HitRegion::HitTest(HitRegion* regPtr)
{
	HRESULT hr;
	CheckIfCreated(regPtr->GetTransformedGeometry());
	CheckIfCreated(m_TransformedGeometryPtr);

	D2D1_GEOMETRY_RELATION result = D2D1_GEOMETRY_RELATION_UNKNOWN;
	hr = m_TransformedGeometryPtr->CompareWithGeometry(regPtr->GetTransformedGeometry(), D2D1::IdentityMatrix(), &result);
	if (SUCCEEDED(hr))
	{
		if (result != D2D1_GEOMETRY_RELATION_DISJOINT) return true;
	}
	return false;
}

bool HitRegion::HitTest(double x, double y)
{
	CheckIfCreated(m_TransformedGeometryPtr);

	BOOL bHit;
	m_TransformedGeometryPtr->FillContainsPoint(D2D1::Point2F((FLOAT)x, (FLOAT)y), D2D1::Matrix3x2F::Identity(), &bHit);
	if (bHit) return true;
	else return false;
}

bool HitRegion::HitTest(DOUBLE2 pt)
{
	return HitTest(pt.x, pt.y);
}

bool HitRegion::Exists()
{
	return m_GeometryPtr == 0 ? false : true;
}

RECT2 HitRegion::CollisionTest(HitRegion* regPtr)
{
	HRESULT hr = 0;
	CheckIfCreated(regPtr->GetTransformedGeometry());
	CheckIfCreated(m_TransformedGeometryPtr);

	D2D1_RECT_F bounds = D2D1::RectF();

	//if there is no intersection, there is no need to calculate the intersection HitRegion -> So return an empty rect

	//this "optimisation" doubles the CollisionTest execution time
	//RECT nulrect={};
	//if(!HitTest(regPtr))return nulrect;

	ID2D1PathGeometry* pPathGeometryIntersect = NULL;
	ID2D1GeometrySink* pGeometrySink = NULL;
	hr = m_D2DFactoryPtr->CreatePathGeometry(&pPathGeometryIntersect);
	hr = pPathGeometryIntersect->Open(&pGeometrySink);
	if (SUCCEEDED(hr))
	{
		hr = m_TransformedGeometryPtr->CombineWithGeometry(regPtr->GetTransformedGeometry(), D2D1_COMBINE_MODE_INTERSECT, NULL, NULL, pGeometrySink);
	}
	else
	{
		DebugBreak();
	}

	if (SUCCEEDED(hr))
	{
		hr = pGeometrySink->Close();
	}
	else
	{
		DebugBreak();
	}

	pGeometrySink->Release();

	if (SUCCEEDED(hr))
	{
		hr = pPathGeometryIntersect->GetBounds(D2D1::IdentityMatrix(), &bounds);
		// If the bounds are empty, this will be a rect where bounds.left > bounds.right.
		if (bounds.left > bounds.right) bounds = D2D1::RectF();
	}
	else
	{
		DebugBreak();
	}
	pPathGeometryIntersect->Release();

	//return boundingbox;
	RECT2 rect;
	rect.left = bounds.left;
	rect.top = bounds.top;
	rect.right = bounds.right;
	rect.bottom = bounds.bottom;

	return rect;
}

RECT2 HitRegion::GetBounds()
{
	HRESULT hr;
	CheckIfCreated(m_TransformedGeometryPtr);
	D2D1_RECT_F bounds = D2D1::RectF();

	hr = m_TransformedGeometryPtr->GetBounds(D2D1::IdentityMatrix(), &bounds);
	// If the bounds are empty, this will be a rect where bounds.left > bounds.right.
	if (bounds.left > bounds.right) bounds = D2D1::RectF();

	RECT2 rect;
	rect.left = bounds.left;
	rect.top = bounds.top;
	rect.right = bounds.right;
	rect.bottom = bounds.bottom;

	return rect;
}
int HitRegion::Raycast(DOUBLE2 startPoint, DOUBLE2 vector, HIT* hitArr, int hitArrSize, int sense)
{
	if (m_HitOutlinePtr == nullptr)
	{
		GameEngine::GetSingleton()->MessageBox("You must call Simplify before Raycast");
	}
	//Transform point and vector to object space
	DOUBLE2 localStartPoint = m_MatTransform.Inverse().TransformPoint(startPoint);
	DOUBLE2 localVector = m_MatTransform.Inverse().TransformVector(vector);
	//pass the Raycast to the HitOutline
	int numHits = m_HitOutlinePtr->Raycast(localStartPoint, localVector, 1, hitArr, hitArrSize, sense);
	//transform the results to world space
	for (int i = 0; i < numHits; ++i)
	{
		hitArr[i].point = m_MatTransform.TransformPoint(hitArr[i].point);
		hitArr[i].normal = m_MatTransform.TransformVector(hitArr[i].normal);
	}
	return numHits;
}
void HitRegion::SetPos(double x, double y)
{
	CheckIfCreated(m_GeometryPtr);

	D2D_MATRIX_3X2_F matTransform = D2D1::Matrix3x2F::Translation((FLOAT)x, (FLOAT)y);
	if (m_TransformedGeometryPtr != 0) m_TransformedGeometryPtr->Release();
	m_D2DFactoryPtr->CreateTransformedGeometry(m_GeometryPtr, &matTransform, &m_TransformedGeometryPtr);
}

void HitRegion::SetPos(DOUBLE2 pt)
{
	SetPos(pt.x, pt.y);
}

void HitRegion::Move(double dx, double dy)
{
	MATRIX3X2 matTranslate = MATRIX3X2::CreateTranslationMatrix((FLOAT)dx, (FLOAT)dy);
	SetTransformMatrix(m_MatTransform * matTranslate);
}

ID2D1TransformedGeometry* HitRegion::GetTransformedGeometry()
{
	return m_TransformedGeometryPtr;
}

ID2D1Geometry* HitRegion::GetGeometry()
{
	return m_GeometryPtr;
}

void HitRegion::CheckIfCreated(ID2D1Geometry* collisionMeshPtr)
{
	if (collisionMeshPtr == 0)
		GameEngine::GetSingleton()->MessageBox("HitRegion object is being used but no Create() function has been called!");
}

void HitRegion::SetTransformMatrix(MATRIX3X2 matTrans)
{
	CheckIfCreated(m_GeometryPtr);

	m_MatTransform = matTrans;

	m_TransformedGeometryPtr->Release();
	D2D1_MATRIX_3X2_F d2dTransform = m_MatTransform.ToMatrix3x2F();
	m_D2DFactoryPtr->CreateTransformedGeometry(m_GeometryPtr, &d2dTransform, &m_TransformedGeometryPtr);
}

MATRIX3X2 HitRegion::GetTransformMatrix()
{
	return m_MatTransform;
}

HitRegion* HitRegion::ExcludeMesh(HitRegion* excludingMeshPtr)
{
	return Combine(excludingMeshPtr, Exclude);
}

HitRegion* HitRegion::UnionMesh(HitRegion* includingMeshPtr)
{
	return Combine(includingMeshPtr, Union);
}

HitRegion* HitRegion::InterSectMesh(HitRegion* interSectingMeshPtr)
{
	return Combine(interSectingMeshPtr, Intersect);
}

HitRegion* HitRegion::XORMesh(HitRegion* meshPtr)
{
	return Combine(meshPtr, XOr);
}

HitRegion* HitRegion::Combine(HitRegion* meshPtr, CombineMode mode)
{
	//todo: do not use the transformed geometries
	HRESULT hr = 0;

	CheckIfCreated(meshPtr->GetTransformedGeometry());
	CheckIfCreated(m_GeometryPtr);

	D2D1_COMBINE_MODE combineMode = D2D1_COMBINE_MODE_EXCLUDE;
	if (mode == Union) combineMode = D2D1_COMBINE_MODE_UNION;
	if (mode == Intersect) combineMode = D2D1_COMBINE_MODE_INTERSECT;
	if (mode == XOr) combineMode = D2D1_COMBINE_MODE_XOR;

	ID2D1PathGeometry* pPathGeometryIntersect = 0;
	ID2D1GeometrySink* pGeometrySink = 0;
	hr = m_D2DFactoryPtr->CreatePathGeometry(&pPathGeometryIntersect);
	hr = pPathGeometryIntersect->Open(&pGeometrySink);
	if (SUCCEEDED(hr))
	{
		hr = m_GeometryPtr->CombineWithGeometry(meshPtr->GetTransformedGeometry(), combineMode, NULL, NULL, pGeometrySink);
	}
	else
	{
		DebugBreak();
	}

	if (SUCCEEDED(hr))
	{
		hr = pGeometrySink->Close();
	}
	else
	{
		DebugBreak();
	}

	pGeometrySink->Release();

	if (SUCCEEDED(hr))
	{
		HitRegion* hitRegionPtr = new HitRegion();
		hitRegionPtr->m_GeometryPtr = pPathGeometryIntersect;
		hitRegionPtr->CreateTransformedGeometry(0, 0);
		return hitRegionPtr;
	}
	else
	{
		GameEngine::GetSingleton()->MessageBox("Excluding Failed");
	}

	return 0;
}

void HitRegion::CreateTransformedGeometry(double posX, double posY)
{
	SetPos(posX, posY);
}

void HitRegion::Simplify(int maxDegree, double flatteningTolerance)
{
	HitOutline* newHitOutlinePtr;
	ID2D1GeometrySink *pSink = NULL;
	ID2D1PathGeometry * pathGeometryPtr;
	HRESULT hr = GameEngine::GetSingleton()->GetD2DFactory()->CreatePathGeometry(&pathGeometryPtr);

	if (SUCCEEDED(hr))
	{
		// Write to the path geometry using the geometry sink.
		hr = pathGeometryPtr->Open(&pSink);

		if (SUCCEEDED(hr))
		{
			newHitOutlinePtr = new HitOutline(m_GeometryPtr, pSink, maxDegree, flatteningTolerance);
			hr = pSink->Close();
		}
		pSink->Release();
	}
	if (FAILED(hr))
	{
		GameEngine::GetSingleton()->MessageBox("Geometry::Simplify failed");
	}
	m_GeometryPtr->Release();
	m_GeometryPtr = pathGeometryPtr;

	SetTransformMatrix(m_MatTransform);
	delete m_HitOutlinePtr;
	m_HitOutlinePtr = newHitOutlinePtr;
}

//-----------------------------------------------------------------
// RECT2 Constructors
//-----------------------------------------------------------------
RECT2::RECT2() : left(0), top(0), right(0), bottom(0)
{}

RECT2::RECT2(double leftVal, double topVal, double rightVal, double bottomVal) : left(leftVal), top(topVal), right(rightVal), bottom(bottomVal)
{}

RECT2 RECT2::operator+(DOUBLE2 other) {
	RECT2 tmpRect;
	tmpRect.left = left + other.x;
	tmpRect.top = top + other.y;
	tmpRect.right = right + other.x;
	tmpRect.bottom = bottom + other.y;
	return tmpRect;
}



//-----------------------------------------------------------------
// DOUBLE2 Constructors, friend operators, operators, general methods
//-----------------------------------------------------------------
DOUBLE2::DOUBLE2() : x(0), y(0)
{}

DOUBLE2::DOUBLE2(double x, double y) : x(x), y(y)
{}

DOUBLE2::DOUBLE2(const D2D1_POINT_2F& d2dPoint) : x(d2dPoint.x), y(d2dPoint.y)
{}

DOUBLE2 operator*(double factor, DOUBLE2 right)
{
	return DOUBLE2(right.x * factor, right.y * factor);
}

std::ostream& operator<<(std::ostream& os, DOUBLE2 right)
{
	os << "DOUBLE2( " << right.x << ", " << right.y << " )";
	return os;
}

std::wostream& operator<<(std::wostream& wos, DOUBLE2 right)
{
	wos << L"DOUBLE2( " << right.x << L", " << right.y << L" )";
	return wos;
}

DOUBLE2 Lerp(DOUBLE2 from, DOUBLE2 to, double lambda)
{
	return from + (to - from) * lambda;
}

DOUBLE2& DOUBLE2::operator=(DOUBLE2& other)
{
	if (&other != this)			// check for self assignment
	{
		x = other.x;
		y = other.y;
	}

	return *this;
}

DOUBLE2& DOUBLE2::operator=(D2D1_POINT_2F other)
{
	x = other.x;
	y = other.y;

	return *this;
}

DOUBLE2 DOUBLE2::operator+(DOUBLE2 other)
{
	return DOUBLE2(x + other.x, y + other.y);
}

DOUBLE2 DOUBLE2::operator-(DOUBLE2 other)
{
	return DOUBLE2(x - other.x, y - other.y);
}

DOUBLE2 DOUBLE2::operator-()
{
	return DOUBLE2(-x, -y);
}

DOUBLE2 DOUBLE2::operator+()
{
	return *this;
}

DOUBLE2 DOUBLE2::operator*(double factor)
{
	return DOUBLE2(x * factor, y * factor);
}

DOUBLE2 DOUBLE2::operator/(double divisor)
{
	return DOUBLE2(x / divisor, y / divisor);
}

void DOUBLE2::operator+=(DOUBLE2 other)
{
	x += other.x;
	y += other.y;
}

void DOUBLE2::operator-=(DOUBLE2 other)
{
	x -= other.x;
	y -= other.y;
}

void DOUBLE2::operator*=(double factor)
{
	x *= factor;
	y *= factor;
}

void DOUBLE2::operator/=(double divisor)
{
	x /= divisor;
	y /= divisor;
}

bool DOUBLE2::operator==(DOUBLE2 other)
{
	return x == other.x && y == other.y;
}

bool DOUBLE2::operator!=(DOUBLE2 other)
{
	return !(*this == other);
}

bool DOUBLE2::Equals(DOUBLE2 other, double epsilon)
{
	return abs(x - other.x) < epsilon && abs(y - other.y) < epsilon;
}

D2D1_POINT_2F DOUBLE2::ToPoint2F()
{
	D2D1_POINT_2F p;
	p.x = (FLOAT)x;
	p.y = FLOAT(y);
	return p;
}

double DOUBLE2::DotProduct(DOUBLE2 other)
{
	return x * other.x + y * other.y;
}

double DOUBLE2::Determinant(DOUBLE2 other)
{
	return x * other.y - y * other.x;
}

String DOUBLE2::ToString()
{
	return String("[").SetPrecision(2) + x + ", " + y + "]";
}

double DOUBLE2::Norm()
{
	return Length();
}

double DOUBLE2::Length()
{
	return sqrt(x * x + y * y);
}

double DOUBLE2::AngleWith(DOUBLE2 other)
{
	double angleA = atan2(y, x);
	double angleB = atan2(other.y, other.x);
	return angleB - angleA;
}

DOUBLE2 DOUBLE2::Normalized(double epsilon)
{
	double length = Length();
	if (length < epsilon) return DOUBLE2(0, 0);
	else return DOUBLE2(x / length, y / length);
}

DOUBLE2 DOUBLE2::Orthogonal()
{
	return DOUBLE2(-y, x);
}


//------------------------------------------------------------------------------
// MATRIX3X2 Constructors, friend operators, operators, methods, static methods
//------------------------------------------------------------------------------
MATRIX3X2::MATRIX3X2(DOUBLE2 dirX, DOUBLE2 dirY, DOUBLE2 orig) : dirX(dirX), dirY(dirY), orig(orig)
{}

MATRIX3X2::MATRIX3X2(double e1X, double e1Y, double e2X, double e2Y, double oX, double oY) : dirX(e1X, e1Y), dirY(e2X, e2Y), orig(oX, oY)
{}

MATRIX3X2::MATRIX3X2(const MATRIX3X2& sourceRef) : dirX(sourceRef.dirX), dirY(sourceRef.dirY), orig(sourceRef.orig)
{}

MATRIX3X2::MATRIX3X2(const Matrix3x2F& mat) : dirX(mat._11, mat._12), dirY(mat._21, mat._22), orig(mat._31, mat._32)
{}

MATRIX3X2 operator*(MATRIX3X2 matrix1, MATRIX3X2 matrix2)
{
	return MATRIX3X2(DOUBLE2(matrix1.dirX.x * matrix2.dirX.x + matrix1.dirX.y * matrix2.dirY.x, matrix1.dirX.x * matrix2.dirX.y + matrix1.dirX.y * matrix2.dirY.y),
		DOUBLE2(matrix1.dirY.x * matrix2.dirX.x + matrix1.dirY.y * matrix2.dirY.x, matrix1.dirY.x * matrix2.dirX.y + matrix1.dirY.y * matrix2.dirY.y),
		DOUBLE2(matrix1.orig.x * matrix2.dirX.x + matrix1.orig.y * matrix2.dirY.x + matrix2.orig.x, matrix1.orig.x * matrix2.dirX.y + matrix1.orig.y * matrix2.dirY.y + matrix2.orig.y));
}

std::ostream& operator<<(std::ostream& os, MATRIX3X2 matrix)
{
	os << "MATRIX3X2( " << matrix.dirX.x << ", " << matrix.dirX.y << ", " << matrix.dirY.x << ", " << matrix.dirY.y << ", " << matrix.orig.x << ", " << matrix.orig.y << " )";

	return os;
}

std::wostream& operator<<(std::wostream& wos, MATRIX3X2 matrix)
{
	wos << L"MATRIX3X2( " << matrix.dirX.x << L", " << matrix.dirX.y << L", " << matrix.dirY.x << L", " << matrix.dirY.y << L", " << matrix.orig.x << L", " << matrix.orig.y << L" )";

	return wos;
}

DOUBLE2 MATRIX3X2::TransformVector(DOUBLE2 vector)
{
	return vector.x * dirX + vector.y * dirY;
}

DOUBLE2 MATRIX3X2::TransformPoint(DOUBLE2 point)
{
	return orig + TransformVector(point - DOUBLE2(0, 0));
}

double MATRIX3X2::Determinant()
{
	return dirX.x * dirY.y - dirX.y * dirY.x;
}

MATRIX3X2 MATRIX3X2::Inverse()
{
	//calculate derminant
	double det = Determinant();
	//1)calculate matrix of minors
	//2)Use the alternating law of signs to produce the matrix of cofactors
	//3)Transpose
	//4)the inverse matrix is 1/Determinant * the resulting matrix
	return MATRIX3X2(DOUBLE2(+dirY.y, -dirX.y) / det,
		DOUBLE2(-dirY.x, +dirX.x) / det,
		DOUBLE2(dirY.x * orig.y - dirY.y * orig.x, -(dirX.x * orig.y - dirX.y * orig.x)) / det);
}

bool MATRIX3X2::Equals(MATRIX3X2 p, double epsilon)
{
	return dirX.Equals(p.dirX) && dirY.Equals(p.dirY) && orig.Equals(p.orig);
}

bool MATRIX3X2::operator==(MATRIX3X2 other)
{
	return dirX == other.dirX && dirY == other.dirY && orig == other.orig;
}

bool MATRIX3X2::operator!=(MATRIX3X2 other)
{
	return !(*this == other);
}

Matrix3x2F MATRIX3X2::ToMatrix3x2F()
{
	Matrix3x2F mat;

	mat._11 = (FLOAT)dirX.x;
	mat._12 = (FLOAT)dirX.y;
	mat._21 = (FLOAT)dirY.x;
	mat._22 = (FLOAT)dirY.y;
	mat._31 = (FLOAT)orig.x;
	mat._32 = (FLOAT)orig.y;

	return mat;
}

String MATRIX3X2::ToString()
{
	return String("x=[").SetPrecision(2) + dirX.x + ", " + dirX.y + "]\ny=[" + dirY.x + ", " + dirY.y + "]\no=[" + orig.x + ", " + orig.y + "]";
}

void MATRIX3X2::SetAsIdentity()
{
	dirX = DOUBLE2(1, 0);
	dirY = DOUBLE2(0, 1);
	orig = DOUBLE2(0, 0);
}

void MATRIX3X2::SetAsRotate(double radians)
{
	dirX = DOUBLE2(cos(radians), sin(radians));
	dirY = DOUBLE2(-sin(radians), cos(radians));
	orig = DOUBLE2(0, 0);
}
void MATRIX3X2::SetAsTranslate(double tx, double ty)
{
	dirX = DOUBLE2(1, 0);
	dirY = DOUBLE2(0, 1);
	orig = DOUBLE2(tx, ty);
}

void MATRIX3X2::SetAsTranslate(DOUBLE2 pt)
{
	dirX = DOUBLE2(1, 0);
	dirY = DOUBLE2(0, 1);
	orig = DOUBLE2(pt.x, pt.y);
}

void MATRIX3X2::SetAsScale(double scaleX, double scaleY)
{
	dirX = DOUBLE2(scaleX, 0);
	dirY = DOUBLE2(0, scaleY);
	orig = DOUBLE2(0, 0);
}

void MATRIX3X2::SetAsScale(double scale)
{
	SetAsScale(scale, scale);
}

MATRIX3X2 MATRIX3X2::CreateRotationMatrix(double angle)
{
	return MATRIX3X2(DOUBLE2(cos(angle), sin(angle)), DOUBLE2(-sin(angle), cos(angle)), DOUBLE2());
}

MATRIX3X2 MATRIX3X2::CreateIdentityMatrix()
{
	return MATRIX3X2(DOUBLE2(1, 0), DOUBLE2(0, 1), DOUBLE2());
}

MATRIX3X2 MATRIX3X2::CreateScalingMatrix(double scale)
{
	return CreateScalingMatrix(scale, scale);
}

MATRIX3X2 MATRIX3X2::CreateScalingMatrix(DOUBLE2 scaleXY)
{
	return CreateScalingMatrix(scaleXY.x, scaleXY.y);
}

MATRIX3X2 MATRIX3X2::CreateScalingMatrix(double scaleX, double scaleY)
{
	return MATRIX3X2(DOUBLE2(scaleX, 0), DOUBLE2(0, scaleY), DOUBLE2());
}

MATRIX3X2 MATRIX3X2::CreateTranslationMatrix(DOUBLE2 origin)
{
	return MATRIX3X2(DOUBLE2(1, 0), DOUBLE2(0, 1), origin);
}

MATRIX3X2 MATRIX3X2::CreateTranslationMatrix(double tx, double ty)
{
	return CreateTranslationMatrix(DOUBLE2(tx, ty));
}
