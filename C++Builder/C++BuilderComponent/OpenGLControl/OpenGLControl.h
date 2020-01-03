/*
  Author      : Bart van den Broek
  Copyright   : Copyright (c) 1998 by Bart van den Broek
  
  A simple open gl control.

  TODO: - over/under layer planes.
        - runtime changing of pixel format: double buffering, color depth, etc
		- cleaner interface, eliminate TOpenGLSettings

  class TOpenGLControl
  --------------------

  Properties:  (See TWinControl for common properties)
    OpenGLSettings		Contain settings that are used at creation time
						to initialize the window device context for open gl
						commands.
						There not modified to reflect the actual graphics
						hardware capabilities.
						ALSO contains some run time settings.

  Events:					   
    OnOpenGLInit		Called when window handle for the control is created
						and set up for open gl functions.
						Do global open gl initializations here.
    OnOpenGLResize		Called when control is resized.
						Reset the view port and view transformation here.
    OnOpenGLPaint		Do the actual painting here.						

  Methods:
    TOpenGLControl()	Standard constructor
    ~TOpenGLControl		Standard destructor
    SwapBuffers()		Swaps the front and back buffers
	HDC GetDC()			Inline function that returns a cached DC
						Note that the DC stays with the control.

  Remarks:
	Color indexed mode, under/over layer planes are NOT handled
	by this control.

  class TOpenGLSettings
  ---------------------

  Properties:
    FPixelFormatFlags			Set of the following:
	  pfDrawToWindow			  Support drawing to window (default on)
	  pfDrawToBitMap			  Support drawing to a memory bitmap (default off)
	  pfSupportOpenGL			  Support open gl commands (default on)
	  pfDoubleBuffer			  Do double buffered rendering (default off)
	  pfStereo					  Do stereo graphic rendering (default off)
	  pfDoubleBufferDontCare	  Do double buffered rendering when available and appropriate (default off)
	  pfStereoDontCare			  Do stereo graphic rendering when available and appropriate (default off)
	  
	FColorType					Values:
								  pfRGBA for direct colors (default)
	                              pfColorIndex for indexed (paletted) colors
								NOTE: There is no real support for pfColorIndex mode
								(e.g. no palette switching)

    Word FColorBits				Number of bits used for colors (default=24)
    Word FAccumBits				Number of bits for accumulation buffer (default=0)
    Word FAlphaBits				Number of bits in alpha plane (default=0)
    Word FDepthBits;			Number of bits in depth buffer (default=32)
    Word FStencilBits			Number of bits in stencil buffer (default=0)
    Word FAuxilaryBuffers		Number of auxilary buffers (default=0)
								NOTE: This aux buffers not supported by generic implementation
    Boolean FValidate;			Validate the window after each paint (default=true)
    Boolean FBufferSwap;		Swap buffers after each paint when double buffered (default=true)
    Boolean FMultipleOpenGL;	Support multiple TOpenGLControl controls in each thread
								This means multiple controls in one window, or
								multiple windows each with one control.

*/

//---------------------------------------------------------------------------
#ifndef OpenGLControlH
#define OpenGLControlH

//---------------------------------------------------------------------------
#include <vcl\SysUtils.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Forms.hpp>
#include <vcl\DsgnIntf.hpp>
#include <vcl\Messages.hpp>
#include <windows.h>
#include <GL\gl.h>

//---------------------------------------------------------------------------
enum TPixelFormatEnum {pfDrawToWindow, pfDrawToBitMap,
			           pfSupportGdi, pfSupportOpenGL,
                       pfDoubleBuffer, pfStereo,
                       pfDoubleBufferDontCare, pfStereoDontCare
                       };
#define TPixelFormatEnumFirst int(pfDrawToWindow)
#define TPixelFormatEnumLast  int(pfStereoDontCare)
typedef Set<TPixelFormatEnum,pfDrawToWindow,pfStereoDontCare> TPixelFormatFlags;
enum TColorType {pfRGBA, pfColorIndex};
//enum TLayerType {pfMainPlane, pfOverlayPlane, pfUnderlayPlane};

class TOpenGLSettings : public TPersistent
{
  typedef TPersistent inherited;
protected:
//  	enum MySetElems { msOne, msTwo, msThree, msFour, msFive};
//  	typedef Set<int,0,10> IntSet;
    TPixelFormatFlags FPixelFormatFlags;
    TColorType FColorType;
    //TLayerType FLayerType;
    Word FColorBits; // 16..24(?)
    Word FAccumBits; // >= 0
    Word FAlphaBits;  // >= 0
    Word FDepthBits;  // >= 0
    Word FStencilBits; // >= 0
    Word FAuxilaryBuffers; // >= 0
    Boolean FValidate;
    Boolean FBufferSwap;
    Boolean FMultipleOpenGL;
public:
	__fastcall TOpenGLSettings ();
	void __fastcall Assign(TPersistent* Value);
    // Sets pixel format for hDC
    // YOU CAN ONLY SET THE PIXEL FORMAT FOR hDC BELONGING TO SOME WINDOW
    // hWnd O N L Y  O N C E ! ! !
    // Returns a rendering context
	void SetDCPixelFormat(HDC hDC);
__published:
    __property TPixelFormatFlags PixelFormatFlags =
      { read = FPixelFormatFlags, write = FPixelFormatFlags,
        nodefault };//= (TPixelFormatFlags() << pfDrawToWindow << pfSupportOpenGL) };
    __property TColorType ColorType =
      { read = FColorType, write = FColorType, default = pfRGBA };
    //__property TLayerType LayerType =
    //  { read = FLayerType, write = FLayerType, default = pfMainPlane };
  	__property Word ColorBits =
      { read = FColorBits, write = FColorBits, default = 24 };
  	__property Word AccumBits =
      { read = FAccumBits, write = FAccumBits, default = 0 };
  	__property Word AlphaBits =
      { read = FAlphaBits, write = FAlphaBits, default = 0 };
  	__property Word DepthBits =
      { read = FDepthBits, write = FDepthBits, default = 32 };
    __property Word StencilBits =
      { read = FStencilBits, write = FStencilBits, default = 0 };
    __property Word AuxilaryBuffers =
      { read = FAuxilaryBuffers, write = FAuxilaryBuffers, default = 0 };
    __property Boolean Validate =
      { read = FValidate, write = FValidate, default = true };
    __property Boolean BufferSwap =
      { read = FBufferSwap, write = FBufferSwap, default = true };
    __property Boolean MultipleOpenGL =
      { read = FMultipleOpenGL, write = FMultipleOpenGL, default = false };
	
};

//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TSizeEvent)
  (System::TObject* Sender, int Width, int Height);

class TOpenGLControl : public TWinControl
{
private:
	typedef TWinControl inherited;
protected:
    HGLRC OpenGLRC;
    HWND CachedHandle;
    HDC  CachedDC;

    TNotifyEvent FOnOpenGLInit;
    TSizeEvent FOnOpenGLResize;
    TNotifyEvent FOnOpenGLPaint;
  	TOpenGLSettings *FOpenGLSettings;
    void __fastcall SetOpenGLSettings (TOpenGLSettings *OGLS);
    TOpenGLSettings* __fastcall GetOpenGLSettings();

	virtual void __fastcall CreateParams(TCreateParams &Params);
//     virtual void __fastcall CreateWindowHandle(const TCreateParams &Params);
    virtual void __fastcall DestroyWindowHandle(void);

	void __fastcall WMPaint(TWMPaint &Message);
    void __fastcall WMSize(TWMSize &Message);
    void __fastcall WMCreate(TWMCreate &Message);
    void __fastcall WMEraseBkgnd(TWMEraseBkgnd &Message);
//    virtual void __fastcall WMCreate(TWMCreate &Message);
	BEGIN_MESSAGE_MAP
    	MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint)
    	MESSAGE_HANDLER(WM_SIZE, TWMSize, WMSize)
        MESSAGE_HANDLER(WM_CREATE, TWMCreate, WMCreate)
        MESSAGE_HANDLER(WM_ERASEBKGND, TWMEraseBkgnd, WMEraseBkgnd)
	END_MESSAGE_MAP(inherited)
public:
	__fastcall TOpenGLControl(TComponent* Owner);
	virtual __fastcall ~TOpenGLControl();
    void SwapBuffers();
    HDC GetDC() { return CachedDC; }
__published:
  	__property TOpenGLSettings *OpenGLSettings =
  	  {read = FOpenGLSettings, write = SetOpenGLSettings};
    __property Classes::TNotifyEvent OnOpenGLInit =
      {read = FOnOpenGLInit, write = FOnOpenGLInit};
    __property TSizeEvent OnOpenGLResize =
      {read = FOnOpenGLResize, write = FOnOpenGLResize};
    __property Classes::TNotifyEvent OnOpenGLPaint =
      {read = FOnOpenGLPaint, write = FOnOpenGLPaint};

  // Publish all inherited events
  	__property OnClick;
  	__property OnDblClick;
  	__property OnDragDrop;
  	__property OnDragOver;
  	__property OnEndDrag;
  	__property OnMouseDown;
  	__property OnMouseMove;
  	__property OnMouseUp;
  	__property OnStartDrag;
  	__property OnEnter;
  	__property OnExit;
  	__property OnKeyDown;
  	__property OnKeyPress;
  	__property OnKeyUp;
 // Publish specific properties
    __property Align;
    //__property BorderStyle;
    __property Cursor;
    __property DragCursor;
	__property DragMode;
    __property Enabled;
    __property Height;
    __property Hint;
    __property Left;
    __property Name;
    __property Top;
    __property Visible;
    __property Width;
    //__property Ctl3D;
    __property HelpContext;
    __property TabOrder;
    __property TabStop;
};
//---------------------------------------------------------------------------
#endif

