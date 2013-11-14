//-----------------------------------------------------------------
// Game Engine Object
// C++ Header - GameEngine.h - version 2012 v2_10
// Copyright Kevin Hoefman, Bart Uyttenhove, Peter Verswyvelen
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------
// Changes since v2_08:
// - Windows GDI paint system replaced by Direct2D.
// - DrawEllipse() and similar functions now take as parameters the centerpoint and radius instead of the bounding rectangle.
// - SetColor() and similar functions now take red, green and blue values as separate parameters. SetColor() now has an optional fourth parameter (alpha).
// - Embedded images need to have the specifier IMAGE instead of BITMAP or TARGA in the .rc file. The Bitmap constructor now only takes the identifier of the image.

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
//#define _WIN32_WINNT 0x0601 // Windows 7
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <Mmsystem.h>	// winmm.lib header, used for playing sound
#undef MessageBox

#include "AbstractGame.h" // needed to use abstract class as basis for all games

#include <vector>			// using std::vector for tab control logic
#include <queue>
#include <algorithm>
using namespace std;

#include <sstream>

#include "../Resource.h"	

#include <dwrite.h>
#include <wincodec.h>
#include <d2d1.h>
#include <d2d1helper.h>

#define _USE_MATH_DEFINES // Define M_PI and other constants
#include "math.h"

using namespace D2D1;

//Unicode defs
#ifdef _UNICODE
#define tstring wstring
#define tstringstream wstringstream
#else
#define tstring string
#define tstringstream stringstream
#endif

#undef LoadImage

//-----------------------------------------------------------------
// Pragma Library includes
//-----------------------------------------------------------------
#pragma comment(lib, "msimg32.lib")		// used for transparency
#pragma comment(lib, "winmm.lib")		// used for sound
// libs used for Direct2D
#pragma comment(lib, "d2d1.lib")			
#pragma comment(lib, "WindowsCodecs.lib")	//WIC
#pragma comment(lib, "dwrite.lib")			//WIC

//-----------------------------------------------------------------
// GameEngine Defines
//-----------------------------------------------------------------
#define KEYBCHECKRATE 60

//-----------------------------------------------------------------
// GameEngine Forward Declarations
//-----------------------------------------------------------------
class Bitmap;
class SoundWave;
class Midi;
class String;
class GraphicsEngine;
class Painter;
class StopWatch;
class Bitmap;
class TextFormat;
class HitRegion;

//-----------------------------------------------------------------
// RECT2 is verplaatst na de DOUBLE2 om deze te kunnen gebruikien. By Emile
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// DOUBLE2 Struct
//-----------------------------------------------------------------
struct DOUBLE2
{
	// -------------------------
	// Constructors 
	// -------------------------
    DOUBLE2();								// Default constructor gives the origin point
	DOUBLE2(double x, double y);			// Usage: DOUBLE2 p(1,2);
    DOUBLE2(const D2D1_POINT_2F& d2dPoint);	// Construct from Direct2D

	// -------------------------
	// Friend declarations 
	// -------------------------
	friend std::ostream&	operator<<(std::ostream& os, DOUBLE2 right);	// Leftshift to a stream
	friend std::wostream&	operator<<(std::wostream& wos, DOUBLE2 right);	// Leftshift to a wide character stream
	friend DOUBLE2			operator*(double factor, DOUBLE2 right);		// Multiplication:										DOUBLE2 w = 2 * v;
	friend DOUBLE2			Lerp(DOUBLE2 from, DOUBLE2 to, double lambda);	// Barycentric interpolation between two points:		DOUBLE2 r = Lerp(p,q,0.5)

	// -------------------------
	// Operators
	// -------------------------
    DOUBLE2&		operator= (DOUBLE2& other);						// Assignment:											DOUBLE2 r = a;
    DOUBLE2&		operator= (D2D1_POINT_2F other);				// Assignment from D2D								
    DOUBLE2			operator+ (DOUBLE2 other);						// Vector addition:										DOUBLE2 r = a + b;
    DOUBLE2			operator- (DOUBLE2 other);						// Vector subtraction:									DOUBLE2 r = a - b;
	DOUBLE2			operator- ();									// Negation:											DOUBLE2 w = -v;
	DOUBLE2			operator+ ();									// Identity:											DOUBLE2 w = +v;
	DOUBLE2			operator* (double factor);						// Right multiplication with a double:					DOUBLE2 w = v * 2;
	DOUBLE2			operator/ (double divisor);						// Division by double:									DOUBLE2 w = v/2;
	void			operator+=(DOUBLE2 other);						// Translate this point inplace:						p += v;
    void			operator-=(DOUBLE2 other);						// Translate this point inplace (opposite direction):	p -= v;
	void			operator*=(double factor);						// Scale vector inplace:								v *= s;
	void			operator/=(double divisor);						// Downscale vector inplace:							v /= s;
    bool			operator==(DOUBLE2 other);						// Are two points exactly equal?						p == q
    bool			operator!=(DOUBLE2 other);						// Are two points exactly unequal?						p != q
	
	// -------------------------
	// Methods
	// -------------------------
    D2D1_POINT_2F	ToPoint2F();									// Convert to Direct2D
    bool			Equals(DOUBLE2 other, double epsilon=0.001);	// Are two points equal within a threshold?				p.Equals(q)
	String			ToString();										// Convert to String 
	double			DotProduct(DOUBLE2 other);						// DotProduct:											double d = u.DotProduct(v);
	double			Determinant(DOUBLE2 other);						// Determinant:											double d = u.Determinant(v);
	double			Norm();											// Norm of a vector:									double l = v.Norm();
	double			Length();										// Length of a vector:									double l = v.Length();
	double			AngleWith(DOUBLE2 other);						// AngleWidth another vector:							double d = u.AngleWith(v);
	DOUBLE2			Normalized(double epsilon = 0.001);				// Normalized form of a vector:							DOUBLE2 u = v.Normalized();
	DOUBLE2			Orthogonal();									// Orthogonal:											DOUBLE2 w = v.Orthogonal();
	
	// -------------------------
	// Datamembers 
	// -------------------------
    double x, y;
};


//-----------------------------------------------------------------
// RECT2 Struct
//-----------------------------------------------------------------
struct RECT2
{
	// -------------------------
	// Constructors 
	// -------------------------	
	RECT2();
	RECT2(double leftVal, double topVal, double rightVal, double bottomVal);
	

	RECT2 RECT2::operator+(DOUBLE2 other);

	// -------------------------
	// Datamembers 
	// -------------------------	
    double left, top, right, bottom;
};



//-----------------------------------------------------------------
// MATRIX3X2 Struct
//-----------------------------------------------------------------
struct MATRIX3X2
{
	// -------------------------
	// Constructors 
	// -------------------------
	MATRIX3X2(DOUBLE2 dirX = DOUBLE2(1, 0), DOUBLE2 dirY = DOUBLE2(0, 1), DOUBLE2 orig = DOUBLE2(0, 0));	// Default constructor gives a standard matrix
	MATRIX3X2(double e1X, double e1Y, double e2X, double e2Y, double oX, double oY);						// Constructor, using doubles, all required
	MATRIX3X2(const MATRIX3X2& sourceRef);																	// Copy constructor:
	MATRIX3X2(const Matrix3x2F& mat);																		// Construct from Direct2D

	// -------------------------
	// Friend declarations 
	// -------------------------
	friend MATRIX3X2 operator*(MATRIX3X2 f1, MATRIX3X2 f2); 				// Multiply or transform matrix f1 by matrix f2 (operator form)
	friend std::ostream& operator<<(std::ostream& os, MATRIX3X2 right);		// Print to a stream.
	friend std::wostream& operator<<(std::wostream& wos, MATRIX3X2 right);	// Print to a wstream.

	// -------------------------
	// Operators 
	// -------------------------
	bool operator==(MATRIX3X2 other);										// Are two matrices exactly equal?				p == q
	bool operator!=(MATRIX3X2 other);										// Are two matrices exactly unequal?			p != q
		
	// -------------------------
	// General Methods 
	// -------------------------
	DOUBLE2		TransformVector(DOUBLE2 v);									// Transform a vector by this matrix:			DOUBLE2 w = b.Transform(v);
	DOUBLE2		TransformPoint(DOUBLE2 p);									// Transform a point by this matrix:			DOUBLE2 q = f.Transform(p);
	double		Determinant();												// Calculate the determinant
	MATRIX3X2	Inverse();													// Calculate the inverse matrix
	bool		Equals(MATRIX3X2 p, double epsilon=0.001);					// Are two matrices equal within a threshold?	p.Equals(q)
	String		ToString();													// Zet matrix om naar string.
	Matrix3x2F	ToMatrix3x2F();												// Convert to Direct2D

	void SetAsIdentity();													// Converts this matrix into a Identity matrix
	void SetAsRotate(double radians);										// Converts this matrix into a Rotate matrix
	void SetAsTranslate(double tx, double ty);								// Converts this matrix into a Translation matrix
	void SetAsTranslate(DOUBLE2 pt);										// Converts this matrix into a Translation matrix
	void SetAsScale(double sx, double sy); 									// Converts this matrix into a Scale matrix
	void SetAsScale(double s);												// Converts this matrix into a Scale matrix

	// -------------------------
	// Static Methods 
	// -------------------------
	static MATRIX3X2 CreateRotationMatrix(double radians);					// Instantiate a rotation matrix: Matrix r = Matrix::Rotation(M_PI/2);
	static MATRIX3X2 CreateIdentityMatrix();								// Instantiate an identity matrix: MATRIX3X2 m = MATRIX3X2::Identity();
	static MATRIX3X2 CreateScalingMatrix(double scale);						// Instantiate a scale matrix: Matrix s = Matrix::Scaling(2);
	static MATRIX3X2 CreateScalingMatrix(double scaleX, double scaleY);		// Instantiate a scale matrix: Matrix s = Matrix::Scaling(2,-3);
	static MATRIX3X2 CreateScalingMatrix(DOUBLE2 scaleXY);					// Instantiate a scale matrix: Matrix s = Matrix::Scaling( DOUBLE2(2,-3) );
	static MATRIX3X2 CreateTranslationMatrix(DOUBLE2 origin);				// Instantiate a translation matrix: Matrix t = Matrix::Translation( Point2(2,3) );
	static MATRIX3X2 CreateTranslationMatrix(double tx, double ty);			// Instantiate a translation matrix: Matrix t = Matrix::Translation(2,3);

	// -------------------------
	// Datamembers
	// -------------------------
	DOUBLE2 dirX;															// The first matrix vector (the "x-axis")
	DOUBLE2 dirY;															// The second matrix vector (the "y-axis")
	DOUBLE2 orig; 															// The origin of  the coordinate matrix (the "translation")
};

//-----------------------------------------------------------------
// GameEngine Class
//-----------------------------------------------------------------
class GameEngine
{
private:
	// singleton implementation : private constructor + static pointer to game engine
	GameEngine();
	static GameEngine*  m_GameEnginePtr;

public:
	// Destructor
	virtual ~GameEngine();

	// Static methods
	static GameEngine*  GetSingleton();

	// General Methods
	void			SetGame(AbstractGame* gamePtr);
	bool			Run(HINSTANCE hInstance, int iCmdShow);
	bool			ClassRegister(int iCmdShow);
	bool			SetGameValues(const String& titleRef, WORD wIcon, WORD wSmallIcon, int iWidth, int iHeight);
	bool			GoFullscreen();		
	bool			GoWindowedMode();		
	bool			IsFullscreen();		
	void			ShowMousePointer(bool value);	

	LRESULT			HandleEvent(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);
	bool			IsKeyDown(int vKey);
	void			QuitGame(void);
	void			MessageBox(double value);
	void			MessageBox(int value);
	void			MessageBox(size_t value);
	void			MessageBox(const String& textRef);
	void			RunGameLoop(bool value);
	void			TabNext(HWND ChildWindow);
	void			TabPrevious(HWND ChildWindow);

	// Draw Methods		
	bool			DrawSolidBackground(int red, int green, int blue);
	bool			DrawLine(double x1, double y1, double x2, double y2, double strokeWidth=1);
	bool			DrawLine(DOUBLE2 p1, DOUBLE2 p2, double strokeWidth = 1);
	bool			DrawPolygon(const POINT ptsArr[], int count, double strokeWidth = 1);
	bool			DrawPolygon(const POINT ptsArr[], int count, bool close, double strokeWidth = 1);
	bool			FillPolygon(const POINT ptsArr[], int count);
	bool			FillPolygon(const POINT ptsArr[], int count, bool close);
	bool			DrawEllipse(DOUBLE2 centerPt, double radiusX, double radiusY, double strokeWidth = 1);
	bool			DrawEllipse(double centerX, double centerY, double radiusX, double radiusY, double strokeWidth = 1);
	bool			FillEllipse(DOUBLE2 centerPt, double radiusX, double radiusY);
	bool			FillEllipse(double centerX, double centerY, double radiusX, double radiusY);
	bool			DrawRect(double left, double top, double width, double height, double strokeWidth = 1);
	bool			DrawRect(DOUBLE2 lefttop, double width, double height, double strokeWidth = 1);
	bool			DrawRect(RECT rect, double strokeWidth = 1);
	bool			DrawRect(RECT2 rect, double strokeWidth = 1);
	bool			FillRect(double left, double top, double width, double height);
	bool			FillRect(DOUBLE2 lefttop, double width, double height);
	bool			FillRect(RECT rect);
	bool			FillRect(RECT2 rect);
	bool			DrawRoundedRect(double left, double top, double width, double height, double radiusX, double radiusY, double strokeWidth = 1);
	bool			DrawRoundedRect(DOUBLE2 lefttop, double width, double height, double radiusX, double radiusY, double strokeWidth = 1);
	bool			DrawRoundedRect(RECT rect, double radiusX, double radiusY, double strokeWidth = 1);
	bool			DrawRoundedRect(RECT2 rect, double radiusX, double radiusY, double strokeWidth = 1);
	bool			FillRoundedRect(double left, double top, double width, double height, double radiusX, double radiusY);
	bool			FillRoundedRect(DOUBLE2 lefttop, double width, double height, double radiusX, double radiusY);
	bool			FillRoundedRect(RECT rect, double radiusX, double radiusY);
	bool			FillRoundedRect(RECT2 rect, double radiusX, double radiusY);
	bool			DrawString(TextFormat* textFormatPtr, const String& text,double xPos, double yPos, double width = 0, double height = 0);
	bool			DrawString(const String& text, double xPos, double yPos, double width = 0, double height = 0);
	bool			DrawString(TextFormat* textFormatPtr, const String& text, DOUBLE2 pos, double width = 0, double height = 0);
	bool			DrawString(const String& text, DOUBLE2 pos, double width = 0, double height = 0);
	bool			DrawBitmap(Bitmap* imagePtr, double x, double y);
	bool			DrawBitmap(Bitmap* imagePtr, double x, double y, RECT srcRect);
	bool			DrawBitmap(Bitmap* imagePtr, double x, double y, RECT2 srcRect);
	bool			DrawBitmap(Bitmap* imagePtr, DOUBLE2 lefttop);
	bool			DrawBitmap(Bitmap* imagePtr, DOUBLE2 lefttop, RECT srcRect);
	bool			DrawBitmap(Bitmap* imagePtr, DOUBLE2 lefttop, RECT2 srcRect);
	bool			DrawHitRegion(HitRegion* collisionMeshPtr);
	bool			FillHitRegion(HitRegion* collisionMeshPtr);
	bool			DrawCoordinateSystem(double unitSize);
	void			SetTransformMatrix(MATRIX3X2 mat);
	MATRIX3X2		GetTransformMatrix();
	void			SetBitmapInterpolationModeLinear();
	void			SetBitmapInterpolationModeNearestNeighbor();
	void			SetFont(TextFormat* fontPtr);
	void			SetColor(int red, int green, int blue, int alpha=255);
	void			EnableAntiAlias(bool isAlias);
	void			Repaint();

	// Accessor Methods
	HINSTANCE				GetInstance();
	HWND					GetWindow();
	String&					GetTitle();
	WORD					GetIcon();
	WORD					GetSmallIcon();
	int						GetWidth();
	int						GetHeight();
	double					GetFrameDelay();
	bool					GetSleep();
	ID2D1Factory*			GetD2DFactory();
	IWICImagingFactory*		GetWICImagingFactory();
	ID2D1HwndRenderTarget*	GetHwndRenderTarget();
	IDWriteFactory*			GetDWriteFactory();
	POINT					GetLocation();

	// Mutator Methods	
	void SetTitle(const String& titleRef); // SetTitle automatically sets the window class name to the same name as the title - easier for students 
	void SetIcon(WORD wIcon);
	void SetSmallIcon(WORD wSmallIcon);
	void SetWidth(int iWidth);
	void SetHeight(int iHeight);
	void SetFrameRate(double iFrameRate);
	void SetTickPaintRatio(double ratio);
	void SetSleep(bool bSleep);
	void SetKeyList(const String& keyListRef);
	void SetPaintDoublebuffered();
	void SetLocation(int x, int y);

	// Keyboard monitoring thread method
	virtual DWORD KeybThreadProc();

	virtual DWORD MyFirstThreadProc(); // MyFirstThread
	
private:
	// Private Mutator Methods	
	void SetInstance(HINSTANCE hInstance);
	void SetWindow(HWND hWindow);

	// Private Draw Methods
	bool CanIPaint();

	// Direct2D methods
	void Initialize();
	void D2DBeginPaint();
	bool D2DEndPaint();
	void CreateDeviceIndependentResources();
	void CreateD2DFactory();
	void CreateWICFactory();
	void CreateWriteFactory();
    void CreateDeviceResources();
    void DiscardDeviceResources();
	void ExecuteDirect2DPaint();

	// Member Variables
	HINSTANCE           m_hInstance;
	HWND                m_hWindow;
	String*             m_TitlePtr;
	WORD                m_wIcon, m_wSmallIcon;
	int                 m_iWidth, m_iHeight;
	double              m_PaintTimeTrigger;
	double				m_TickPaintRatio;
	bool                m_bSleep;
	bool				m_bRunGameLoop;
	HANDLE				m_hKeybThread;
	DWORD				m_dKeybThreadID;

	HANDLE				m_hMyFirstThread;
	DWORD				m_dMyFirstThreadID;


	bool				m_bKeybRunning;
	TCHAR*				m_KeyListPtr;
	unsigned int		m_KeybMonitor;
	AbstractGame*		m_GamePtr;
	bool				m_PaintDoublebuffered;
	bool				m_Fullscreen;

	// Draw assistance variables
	HDC					m_HdcDraw;
	RECT				m_RectDraw;
	bool				m_IsPainting, m_IsDoublebuffering;

	// Fullscreen assistance variable
	POINT				m_OldLoc;
			
	//AMP2
	bool							m_bInitialized;
	ID2D1Factory*					m_D2DFactoryPtr;
    IWICImagingFactory*				m_WICFactoryPtr;
	ID2D1HwndRenderTarget*			m_RenderTargetPtr;
	IDWriteFactory*					m_DWriteFactoryPtr;
	GraphicsEngine*					m_GraphicsEnginePtr;
	StopWatch*						m_GameTickTimerPtr;
	StopWatch*						m_GamePaintTimerPtr;

	// Direct2D Paint variables
    ID2D1SolidColorBrush*			m_ColorBrushPtr;
	D2D1_ANTIALIAS_MODE				m_AntialiasMode;
	MATRIX3X2						m_MatWorld;
	D2D1_BITMAP_INTERPOLATION_MODE	m_BitmapInterpolationMode;	//used when painting scaled bitmaps:
	TextFormat*						m_DefaultFontPtr;
	TextFormat*						m_UserFontPtr;				// Default Font and the font, the user defined using SetFOnt()

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, the declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	GameEngine(const GameEngine& geRef);
	GameEngine& operator=(const GameEngine& geRef);
};

//-----------------------------------------------------------------
// String Class
//-----------------------------------------------------------------
class String
{
public: 
	// -------------------------
	// Constructors & Destructor
	// -------------------------	
	String(const wchar_t* wideTextPtr = L"");
	String(const char* singleTextPtr);
	String(const String& sRef);
	String(wchar_t character);
	String(char character);

	virtual ~String();

	// -------------------------
	// General String Methods
	// -------------------------	
	TCHAR CharAt(int index) const;
	String Replace(TCHAR oldChar, TCHAR newChar) const;
	String SubString(int index) const;
	String SubString(int index, int length) const;
	String ToLowerCase() const;
	String ToUpperCase() const;
	String Trim() const;
	int IndexOf(TCHAR character) const;
	int LastIndexOf(TCHAR character) const;
	bool StartsWith(const String& sRef) const;
	bool EndsWith(const String& sRef) const;
	int GetLength() const;
	bool Equals(const String& sRef) const;
	String& SetPrecision(int precision);

	// -------------------------
	// Conversion Methods
	// -------------------------	
	TCHAR* ToTChar() const;
	int ToInteger() const;
	double ToDouble() const;

	// ----------------------------------------
	// Overloaded operators: = , +=, +, and ==
	// ----------------------------------------
	String& operator=(const String& sRef);

	String& operator+=(const String& sRef);
	String& operator+=(wchar_t* wideTextPtr);
	String& operator+=(char* singleTextPtr);
	String& operator+=(int number);
	String& operator+=(size_t number);
	String& operator+=(double number);
	String& operator+=(wchar_t character);
	String& operator+=(char character);

	String operator+(const String& sRef);
	String operator+(wchar_t* wideTextPtr);
	String operator+(char* singleTextPtr);
	String operator+(int number);
	String operator+(size_t number);
	String operator+(double number);
	String operator+(wchar_t character);
	String operator+(char character);

	bool operator==(const String& sRef);
	bool operator==(const String& sRef) const;

private:
	// -------------------------
	// Datamembers
	// -------------------------
	TCHAR* m_TextPtr;
	int m_Length;
	int m_Precision;
};

//------------------------------------------------------------------------------------------------
// Callable Interface
//
// Interface implementation for classes that can be called by "caller" objects
//------------------------------------------------------------------------------------------------
class Caller;	// forward declaration

class Callable
{
public:
	virtual ~Callable() {}						// virtual destructor for polymorphism
	virtual void CallAction(Caller* callerPtr) {}
};

//------------------------------------------------------------------------------------------------
// Caller Base Class
//
// Base Clase implementation for up- and downcasting of "caller" objects: TextBox, Button, Timer, Audio and Video
//------------------------------------------------------------------------------------------------
class Caller
{
public:
	virtual ~Caller() {}				// do not delete the targets!

	static const int TextBox = 0;
	static const int Button = 1;
	static const int Timer = 2;
	static const int Audio = 3;
	static const int Video = 4;

	virtual int GetType() = 0;

	virtual bool AddActionListener(Callable* targetPtr);		// public interface method, call is passed on to private method
	virtual bool RemoveActionListener(Callable* targetPtr);		// public interface method, call is passed on to private method

protected:
	Caller() {}													// constructor only for derived classes
	vector<Callable*> m_TargetList;

	virtual bool CallListeners();								// placing the event code in a separate method instead of directly in the windows messaging
																// function allows inheriting classes to override the event code. 

private:
	bool AddListenerObject(Callable* targetPtr);
	bool RemoveListenerObject(Callable* targetPtr);

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, the declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Caller(const Caller& cRef);
	Caller& operator=(const Caller& cRef);
};

//--------------------------------------------------------------------------
// Timer Class
//
// This timer is a queue timer, it will only work on Windows 2000 and higher
//--------------------------------------------------------------------------
class Timer : public Caller
{
public:
	// -------------------------
	// Constructor & Destructor
	// -------------------------
	Timer(int msec, Callable* targetPtr); // constructor automatically adds 2nd parameter to the list of listener objects
	virtual ~Timer();
	
	// -------------------------
	// General Methods
	// -------------------------
	int GetType();
	void Start();
	void Stop();
	bool IsRunning();
	void SetDelay(int msec);
	int GetDelay();

private:	
	// -------------------------
	// Datamembers
	// -------------------------
	HANDLE m_TimerHandle;
	bool m_IsRunning;
	int m_Delay;

	// -------------------------
	// Handler functions
	// -------------------------	
	static void CALLBACK TimerProcStatic(void* lpParameter, BOOLEAN TimerOrWaitFired); // proc will call CallListeners()
		
	// -------------------------
	// Disabling default constructor, default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Timer();
	Timer(const Timer& tRef);
	Timer& operator=(const Timer& tRef);
};

//-----------------------------------------------------------------
// TextBox Class
//-----------------------------------------------------------------
class TextBox : public Caller
{
public:
	// -------------------------
	// Constructors & Destructor
	// -------------------------
	TextBox(String const& textRef);
	TextBox();

	virtual ~TextBox();
	
	// -------------------------
	// General Methods
	// -------------------------
	int GetType();
	void SetBounds(int x, int y, int width, int height);
	String GetText();
	void SetText(String const& textRef);
	void SetFont(String const& fontNameRef, bool bold, bool italic, bool underline, int size);
	void SetBackcolor(int red, int green, int blue);
	void SetForecolor(int red, int green, int blue);
	COLORREF GetForecolor();
	COLORREF GetBackcolor();
	HBRUSH GetBackcolorBrush();
	RECT2 GetRect();
	void SetEnabled(bool bEnable);
	void Update(void);
	void Show();
	void Hide();

private:
	// -------------------------
	// Datamembers
	// -------------------------
	int m_X, m_Y;
	HWND m_hWndEdit;
	WNDPROC m_procOldEdit;
	COLORREF m_BgColor, m_ForeColor;
	HBRUSH m_BgColorBrush;
	HFONT m_Font, m_OldFont;

	// -------------------------
	// Handler functions
	// -------------------------	
	static LRESULT CALLBACK EditProcStatic(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT EditProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);
		
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	TextBox(const TextBox& tbRef);
	TextBox& operator=(const TextBox& tbRef);
};

//-----------------------------------------------------------------
// Button Class
//-----------------------------------------------------------------
class Button : public Caller
{
public:
	// -------------------------
	// Constructors & Destructor
	// -------------------------
	Button(String const& textRef);
	Button();

	virtual ~Button();
	
	// -------------------------
	// General Methods
	// -------------------------
	int GetType();
	void SetBounds(int x, int y, int width, int height);
	String GetText();
	void SetText(String const& textRef);
	void SetFont(String const& fontNameRef, bool bold, bool italic, bool underline, int size);
	RECT2 GetRect();
	void SetEnabled(bool bEnable);
	void Update(void);
	void Show();
	void Hide();

private:
	// -------------------------
	// Datamembers
	// -------------------------
	int m_X, m_Y;
	HWND m_hWndButton;
	WNDPROC m_procOldButton;
	bool m_Armed;
	COLORREF m_BgColor, m_ForeColor;
	HFONT m_Font, m_OldFont;

	// -------------------------
	// Handler functions
	// -------------------------	
	static LRESULT CALLBACK ButtonProcStatic(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT ButtonProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);
		
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Button(const Button& bRef);
	Button& operator=(const Button& bRef);
};

//-----------------------------------------------------------------
// Audio Class
//-----------------------------------------------------------------
class Audio : public Caller
{
public:
	// -------------------------
	// Constructors & Destructor
	// -------------------------
	Audio(String const& nameRef);
	Audio(int IDAudio, String const& typeRef);

	virtual ~Audio();
	
	// -------------------------
	// General Methods
	// -------------------------
	String& GetName();
	String& GetAlias();
	int		GetDuration();
	bool	IsPlaying();
	bool	IsPaused();
	void	SwitchPlayingOff();				// internal use only, don't use this unless you know what you're doing
	void	SetRepeat(bool repeat);
	bool	GetRepeat();
	bool	Exists();
	int		GetVolume();
	int		GetType();

	// these methods are called to instruct the object. The methods that perform the actual sendstrings are private.
	void	Play(int msecStart = 0, int msecStop = -1);
	void	Pause();
	void	Stop();
	void	SetVolume(int volume);

	// commands are queued and sent through a Tick() which should be called by the main thread (mcisendstring isn't thread safe) 
	// has the additional benefit of creating a delay between mcisendstring commands
	void	Tick();

private:	
	// -------------------------
	// Member functions
	// -------------------------	
	void Create(String const& nameRef);
	void Extract(WORD id, String sType, String sFilename);

	// private mcisendstring command methods and command queue datamember
	queue<String> m_CommandQueue;
	void QueuePlayCommand(int msecStart);
	void QueuePlayCommand(int msecStart, int msecStop);
	void QueuePauseCommand();
	void QueueResumeCommand();
	void QueueStopCommand();
	void QueueVolumeCommand(int volume);		
	void QueuePositionCommand(int x, int y);
	void QueueCommand(String const& commandRef);
	void SendMCICommand(String const& commandRef);
			
	// -------------------------
	// Datamembers
	// -------------------------
	static int	m_Nr;
	String		m_FileName;
	String		m_Alias;
	bool		m_Playing, m_Paused;
	bool		m_MustRepeat;
	HWND		m_hWnd;
	int			m_Duration;
	int			m_Volume;
	
	// -------------------------
	// Handler functions
	// -------------------------	
	static LRESULT CALLBACK AudioProcStatic(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

	// -------------------------
	// Disabling default constructor, default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Audio();
	Audio(const Audio& aRef);
	Audio& operator=(const Audio& aRef);
};

//-----------------------------------------------------------------
// Extra OutputDebugString functions
//-----------------------------------------------------------------
void OutputDebugString(String const& textRef);

//-----------------------------------------------------------------
// Windows Procedure Declarations
//-----------------------------------------------------------------
DWORD WINAPI		KeybThreadProc (GameEngine* gamePtr);

DWORD WINAPI		MyFirstThreadProc (GameEngine* gamePtr);

LRESULT CALLBACK	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


//=======================================================================================
// StopWatch.h by Frank Luna (C) 2008 All Rights Reserved.
// Adapted for DAE GP1 by Bart Uyttenhove
//=======================================================================================
class StopWatch
{
public:
	// -------------------------
	// Constructors & Destructor
	// -------------------------
	StopWatch();
	virtual ~StopWatch();
	
	// -------------------------
	// General Methods
	// -------------------------
	double GetGameTime();  // in seconds
	double GetDeltaTime(); // in seconds

	void Reset(); // Call before message loop.
	void Start(); // Call when unpaused.
	void Stop();  // Call when paused.
	void Tick();  // Call every frame.
	bool IsStopped();

private:
	//---------------------------
	// Private methods
	//---------------------------
	double m_SecondsPerCount;
	double m_DeltaTime;
	
	//---------------------------
	// Datamembers
	//---------------------------
	__int64 m_BaseTime;
	__int64 m_PausedTime;
	__int64 m_StopTime;
	__int64 m_PrevTime;
	__int64 m_CurrTime;

	bool m_bStopped;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	StopWatch(const StopWatch& sRef);
	StopWatch& operator=(const StopWatch& sRef);
};


class Bitmap
{
public:
	// -------------------------
	// Constructors & Destructor
	// -------------------------
	Bitmap(const String& fileName);						// Load an Bitmap using a filename
	Bitmap(int resourceID);								// Load an Bitmap using a resourceID

	virtual ~Bitmap();			

	//-------------------------------------------------
	// Methods							
	//-------------------------------------------------
	//getters
	ID2D1Bitmap*	GetBitmapPtr();
	int				GetWidth();
	int				GetHeight();
	double			GetOpacity();

	//The opacity level of an image has a range from 0 to 1
	//The engine uses the opacity level to blend the image with the background
	void			SetOpacity(double opacity);

	void			SetTransparencyColor(int red, int green, int blue); 
	bool			Exists();

private: 
	//---------------------------
	// Private methods
	//---------------------------
	HRESULT LoadResourceBitmap(ID2D1RenderTarget* renderTargetPtr, IWICImagingFactory* wICFactoryPtr, unsigned int resourceNumber, String resourceType, IWICFormatConverter** formatConvertorPtrPtr);
	HRESULT LoadBitmapFromFile(ID2D1RenderTarget* renderTargetPtr, IWICImagingFactory* wICFactoryPtr, String uri, UINT destinationWidth, UINT destinationHeight, IWICFormatConverter** formatConvertorPtrPtr);

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	ID2D1Bitmap*			m_BitmapPtr;
	IWICFormatConverter*	m_ConvertorPtr;
	double					m_Opacity;//range: between 0 and 1
	String					m_FileName;
	int						m_ResourceID;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Bitmap(const Bitmap& yRef);									
	Bitmap& operator=(const Bitmap& yRef);	
};


class TextFormat
{
public:
	// -------------------------
	// Constructors & Destructor
	// -------------------------
	TextFormat(String fontName, float size);
	TextFormat(IDWriteTextFormat *textFormatPtr);

	virtual ~TextFormat();
	
	//-------------------------------------------------
	// Methods							
	//-------------------------------------------------
	IDWriteTextFormat*	GetTextFormat();
	void				SetAlignHLeft();
	void				SetAlignHCenter();
	void				SetAlignHRight();
	void				SetAlignVTop();
	void				SetAlignVCenter();
	void				SetAlignVBottom();

private:
	///---------------------------
	/// Private methods
	///---------------------------
	void LoadTextFormat(const wchar_t* fontName, float size);

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	IDWriteTextFormat* m_TextFormatPtr;
	
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	TextFormat(const TextFormat& yRef);									
	TextFormat& operator=(const TextFormat& yRef);	
};


struct HIT
{
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	HIT():time(0){}
    double	time;
    DOUBLE2 point;
    DOUBLE2 normal;
};


struct CUBIC
{
	// -------------------------
	// Constructors 
	// -------------------------
	CUBIC();
	CUBIC(DOUBLE2 p0Param, DOUBLE2 p1Param, DOUBLE2 p2Param, DOUBLE2 p3Param);
		
	// -------------------------
	// Friend declarations 
	// -------------------------
	friend bool IntersectLines(DOUBLE2 p1, DOUBLE2 p2, DOUBLE2 q1, DOUBLE2 q2, double& outLambda1, double& outLambda2, double epsilon = 1e-6);

	//-------------------------------------------------
	// Methods							
	//-------------------------------------------------
	bool IntersectLineSegments(DOUBLE2 p1, DOUBLE2 p2, DOUBLE2 q1, DOUBLE2 q2, double& outLambda1, double& outLambda2, double epsilon = 1e-6);
	void Split(CUBIC& c0, CUBIC& c1);
	void FitQuads(double squareTolerance, std::vector<DOUBLE2>& qs, int recurse=3, bool split=true);

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	DOUBLE2 p0, p1, p2, p3;
};


class SimplifiedGeometrySink : public ID2D1SimplifiedGeometrySink
{
public:
	// -------------------------
	// Constructor and Destructor
	// -------------------------
	SimplifiedGeometrySink(ID2D1GeometrySink* baseSink, double flatteningTolerance, std::vector<DOUBLE2>& lines, std::vector<DOUBLE2>& quads);
	virtual ~SimplifiedGeometrySink();
	
	//-------------------------------------------------
	// Methods							
	//-------------------------------------------------
    HRESULT STDMETHODCALLTYPE		QueryInterface(REFIID riid, void** ppvObject);
    virtual	ULONG STDMETHODCALLTYPE AddRef();
    virtual ULONG STDMETHODCALLTYPE Release();
    void STDMETHODCALLTYPE			SetFillMode(D2D1_FILL_MODE fillMode);
    void STDMETHODCALLTYPE			SetSegmentFlags(D2D1_PATH_SEGMENT vertexFlags);
    void STDMETHODCALLTYPE			BeginFigure(D2D1_POINT_2F startPoint, D2D1_FIGURE_BEGIN figureBegin);
    void STDMETHODCALLTYPE			AddLines(CONST D2D1_POINT_2F *points, UINT pointsCount);
    void STDMETHODCALLTYPE			AddBeziers(CONST D2D1_BEZIER_SEGMENT *beziers, UINT beziersCount);
    void STDMETHODCALLTYPE			EndFigure(D2D1_FIGURE_END figureEnd);
    HRESULT STDMETHODCALLTYPE		Close();
	
private:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
    ID2D1GeometrySink*		m_BaseSink;
    std::vector<DOUBLE2>&	m_Lines;
    std::vector<DOUBLE2>&	m_Quads;
    double					m_FlatteningTolerance;
    DOUBLE2					m_Cursor;
	DOUBLE2					m_StartPoint; //Bart: used to close the figure

    // -------------------------
    // Disabling default copy constructor and default assignment operator.
    // If you get a linker error from one of these functions, your class is internally trying to use them. This is
    // an error in your class, these declarations are deliberately made without implementation because they should never be used.
    // -------------------------
    SimplifiedGeometrySink(const SimplifiedGeometrySink& sRef);				
    SimplifiedGeometrySink& operator=(const SimplifiedGeometrySink& sRef);	
};


class HitOutline
{
public:
    // Converts geometry to an outline suitable for ray casting.
    // maxDegree=1 => outline only contains line segments
    // maxDegree=2 => outline contains line segments and quadratic curve segments
    HitOutline(ID2D1Geometry* geometryPtr, ID2D1GeometrySink* targetSink, int maxDegree = 2, double flatteningTolerance = 1);
    virtual ~HitOutline();

    // Intersects this outline with a ray.
    // All points on the ray are p + time*v, where time >= 0
    // Returns all hits with time >= 0 && time < maxTime.
    // Return number of hits.
    // Ignores hits facing in the same direction as v,
    // i.e. with dot(normal, v) * sense > 0
    int Raycast(DOUBLE2 p, DOUBLE2 v, double maxTime, HIT* hitArr, int hitArrSize, double sense=-1);
	int SolveQuadratic(double a, double b, double c, double* xArr);
	double SolveLinear(double a, double b);

	static double DBL_NAN;
	static const int MAX_HITS = 100;

private:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
    std::vector<DOUBLE2> m_Lines;
    std::vector<DOUBLE2> m_Quads;

    // -------------------------
    // Disabling default copy constructor and default assignment operator.
    // If you get a linker error from one of these functions, your class is internally trying to use them. This is
    // an error in your class, these declarations are deliberately made without implementation because they should never be used.
    // -------------------------
    HitOutline(const HitOutline& hrRef);				
    HitOutline& operator=(const HitOutline& hrRef);	

};


//-----------------------------------------------------
// HitRegion Class									
//-----------------------------------------------------
class HitRegion
{
public: 
	//---------------------------
	// Constructor(s)
	//---------------------------
	HitRegion();						
	HitRegion(ID2D1Factory* d2DFactoryPtr);						

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~HitRegion();			

	//---------------------------
	// General Methods
	//---------------------------
	bool CreateFromRect(double x, double y, double width, double height);						// Creates a rectangular HitRegion in object space
	bool CreateFromEllipse(double centerX, double centerY, double radiusX, double radiusY);		// Creates an elliptical HitRegion in object space
	bool CreateFromPolygon(DOUBLE2* pntArr, int nrPoints, bool close);							// Creates a polygon using the DOUBLE2 array
	bool CreateFromFile(String filePath);														// Load geometry from a file: Currently only a tiny subset of SVG is supported, namely groups and paths (but no arcs)

	bool HitTest(HitRegion* regPtr);															// Returns true if the Geometries overlap in World space
	bool HitTest(double x, double y);															// Returns true if geometry includes x,y in World Space
	bool HitTest(DOUBLE2 pt);																	// Returns true if geometry includes pt in World Space
	bool Exists();																				// Returns true if HitRegion is created
	RECT2 CollisionTest(HitRegion* regPtr);														// Returns rectangular intersection of this HitRegion and regPtr in World Space
	RECT2 GetBounds();																			// Returns the bounding rectangle of the geometry.
	int Raycast(DOUBLE2 startPoint, DOUBLE2 vector, HIT* hitArr, int hitArrSize, int sense=0);	// Intersects this HitRegion with a ray. All points on the ray are p + v. Return number of hits. sense=1 only hits facing in the same direction as v, sense=-1 only hits facing in the opposite direction as v, sense=0 all hits
    // i.e. with dot(normal, v) * sense > 0
	void SetPos(double x, double y);															// Positions the HitRegion from object space to world space at position x,y		
	void SetPos(DOUBLE2 pt);																	// Positions the HitRegion at position pt
	void Move(double dx, double dy);
    
	// Internal usage only.
    ID2D1TransformedGeometry* GetTransformedGeometry();
    ID2D1Geometry* GetGeometry();

	// the matrix is used to set the position, rotation and scale of the geometry*/
    // The matrix that will transform vertices of this geometry 
    // from object space to world space.
	void SetTransformMatrix(MATRIX3X2 matTrans);
	
	MATRIX3X2 GetTransformMatrix();

	HitRegion* ExcludeMesh(HitRegion* excludingMeshPtr);										// Exclude this HitRegion with the excludingMesh
	HitRegion* UnionMesh(HitRegion* includingMeshPtr);											// Include the includingMesh with this HitRegion
	HitRegion* InterSectMesh(HitRegion* interSectingMeshPtr);									// InterSect the interSectingMesh with this HitRegion this can take some msecs if the HitRegion is complex
	HitRegion* XORMesh(HitRegion* meshPtr);														// XOR the mesh with this HitRegion

private:
	//---------------------------
	// Private methods
	//---------------------------
	void CreateTransformedGeometry(double posX, double posY);
	enum CombineMode{Union, Exclude, Intersect, XOr};
	HitRegion* Combine(HitRegion* meshPtr, CombineMode mode);
	void CheckIfCreated(ID2D1Geometry* collisionMeshPtr);
	void Simplify(int maxDegree=2, double flatteningTolerance=5);
	//---------------------------
	// Datamembers
	//---------------------------
	ID2D1Factory* m_D2DFactoryPtr;
	ID2D1Geometry* m_GeometryPtr;																//object spaced and simplified geometry
	ID2D1TransformedGeometry* m_TransformedGeometryPtr;											//world spaced, NOT view spaced
	MATRIX3X2 m_MatTransform;																	//used to create TransformedGeometry
	HRESULT m_HResult;
	HitOutline *m_HitOutlinePtr;																//used to perform Raycast
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	HitRegion(const HitRegion& hrRef);				
	HitRegion& operator=(const HitRegion& hrRef);	
};


//-----------------------------------------------------------------
// SVGLoader Class
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------
class SVGLoader
{
public:
	//---------------------------
	// Constructor(s) and Destructor
	//---------------------------
	SVGLoader();
	virtual ~SVGLoader();
	
	//---------------------------
	// General Methods
	//---------------------------
	bool LoadGeometryFromSvgFile(String svgFilePath, ID2D1Geometry*& geometryPtrRef);

private:
	//---------------------------
	// Private methods
	//---------------------------
	bool ExtractTransformInformation(tstring& svgTextRef, tstring& sTransformInfoRef); 
	bool ExtractPathInformation(tstring& svgTextRef, tstring& sPathInfoRef); 
	bool ReadSvgFromData(ID2D1Factory* factoryPtr, tstring& sTransformInfoRef, tstring& sPathInfoRef, ID2D1Geometry*& geometryPtrRef);
	bool GetGeometryOrGroup(ID2D1Factory* factoryPtr, std::vector<ID2D1Geometry*>& childrenRef, ID2D1Geometry*& geometryPtrRef);
	MATRIX3X2 ReadTransform(tstring& sTransformInfoRef);
	bool ReadSvgPath(ID2D1Factory* factoryPtr, tstring& sPathInfoRef, ID2D1PathGeometry*& pathGeometryPtrRef);

	TCHAR WhiteSpaceMapper(TCHAR c);														// Replace all whitespace by space.

	// Skips any optional commas in the stream
	// SVG has a really funky format,
	// not sure this code works for all cases.
	// TODO: Test cases!
	void SkipSvgComma(tstringstream& ssRef, bool isRequired);
	double ReadSvgValue(tstringstream& ssRef, double defaultValue);
	double ReadSvgValue(tstringstream& ssRef, bool separatorRequired);

	DOUBLE2 ReadSvgPoint(tstringstream& ssRef);												// Reads a single point

	// Read the first point, 
	// taking into account relative and absolute positioning.
	// Stores this point, needed when path is closed
	// Advances the cursor if requested.
	DOUBLE2 FirstSvgPoint(tstringstream& ssRef, DOUBLE2& cursor, TCHAR cmd, bool isOpen, bool advance);
	// Read the next point, 
	// taking into account relative and absolute positioning.
	// Advances the cursor if requested.
	// Throws an exception if the figure is not open
	DOUBLE2 NextSvgPoint(tstringstream& ssRef, DOUBLE2& cursor, TCHAR cmd, bool isOpen, bool advance);

	DOUBLE2 NextSvgCoordX(tstringstream& ssRef, DOUBLE2& cursor, TCHAR cmd, bool isOpen);	// Reads next point, given only the new x coordinate
	DOUBLE2 NextSvgCoordY(tstringstream& ssRef, DOUBLE2& cursor, TCHAR cmd, bool isOpen);	// Reads next point, given only the new y coordinate 
	

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	SVGLoader(const SVGLoader& svgRef);				
	SVGLoader& operator=(const SVGLoader& svgRef);	
};