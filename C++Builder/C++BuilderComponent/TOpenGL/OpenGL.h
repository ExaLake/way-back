////////////////////////////////////////////////////////////////////////////////
// TOpenGL component - Heart 5.0
//
// Component which allows to deal with the OpenGL library
//
// by Alan GARNY
//    gry@physiol.ox.ac.uk
//    http://www.physiol.ox.ac.uk/~gry
//
// © Copyright 1996-97
////////////////////////////////////////////////////////////////////////////////
// Date of Creation: 07/02/97
//
// Modifications: (model: [<initials>, dd/mm/yy] <what has been done>)
//
////////////////////////////////////////////////////////////////////////////////

#ifndef OpenGLH
#define OpenGLH

////////////////////////////////////////////////////////////////////////////////

#include <vcl\sysutils.hpp>
#include <vcl\controls.hpp>
#include <vcl\classes.hpp>
#include <vcl\forms.hpp>

#include <gl\gl.h>
//#include <gl\glu.h>

////////////////////////////////////////////////////////////////////////////////

enum TGLFlag {f_DOUBLEBUFFER, f_DRAW_TO_BITMAP, f_DRAW_TO_WINDOW,
              f_GENERIC_ACCELERATED, f_GENERIC_FORMAT, f_NEED_PALETTE,
              f_NEED_SYSTEM_PALETTE, f_SUPPORT_GDI, f_SUPPORT_OPENGL, f_STEREO,
              f_SWAP_COPY, f_SWAP_EXCHANGE, f_SWAP_LAYER_BUFFERS};

typedef Set<TGLFlag, f_DOUBLEBUFFER, f_SWAP_LAYER_BUFFERS> TGLFlags;

enum TGLLayerType {lt_MAIN_PLANE, lt_OVERLAY_PLANE, lt_UNDERLAY_PLANE};

enum TGLPixelType {pt_TYPE_RGBA, pt_TYPE_COLORINDEX};

class TOpenGL: public TCustomPanel
{
   private:
      // Private representation of published properties

      HDC DC;
      HGLRC GLContext;

      HWND CopyOfHandle;   // Useful to release the DC, indeed since we have to
                           // do that in the destructor and that there, the
                           // Handle's value is lost...

      // Properties used for the format of the pixel (cf. the structure
      // PIXELFORMATDESCRIPTION in "WinGDI.h")

      short FGLColorBits;
      short FGLDepthBits;
      TGLFlags FGLFlags;
      TGLLayerType FGLLayerType;
      TGLPixelType FGLPixelType;

      // Properties used for internal purpose

      bool NeedToInitialise;
      bool NeedToSetControlPixelFormat;

      DWORD ConvertedFlags;
      BYTE ConvertedLayerType;
      BYTE ConvertedPixelType;

      HPALETTE Palette;

      // Methods to modify the different published properties

      void __fastcall SetGLColorBits(const short aValue);
      void __fastcall SetGLDepthBits(const short aValue);
      void __fastcall SetGLFlags(const TGLFlags aValue);
      void __fastcall SetGLLayerType(const TGLLayerType aValue);
      void __fastcall SetGLPixelType(const TGLPixelType aValue);

      // Methods used for internal purpose

      void __fastcall SetControlPixelFormat();
      void __fastcall CreateGLContext();

      void __fastcall ConvertFlags();
      void __fastcall ConvertLayerType();
      void __fastcall ConvertPixelType();

   protected:
      // Inheritable methods

      virtual void __fastcall Paint();
      virtual void __fastcall Resize();

      virtual void __fastcall CreateWnd();

      // Special internal events

      TNotifyEvent FOnGLPaint;   // User's routine for GL paint
      TNotifyEvent FOnGLInit;   // User's routine for GL initialisation

   public:
      // Constructor & Destructor

      virtual __fastcall TOpenGL(TComponent *aOwner);
      virtual __fastcall ~TOpenGL();

   __published:
      // Published properties

      __property Align;
      __property Color;
      __property Ctl3D;
      __property DragCursor;
      __property DragMode;
      __property Enabled;
      __property short GLColorBits = {read=FGLColorBits, write=SetGLColorBits, default=32};
      __property short GLDepthBits = {read=FGLDepthBits, write=SetGLDepthBits, default=32};
      __property TGLFlags GLFlags = {read=FGLFlags, write=SetGLFlags, nodefault};//default=__GL_DRAW_TO_WINDOW, __GL_SUPPORT_OPENGL, __GL_DOUBLEBUFFER};
      __property TGLLayerType GLLayerType = {read=FGLLayerType, write=SetGLLayerType, default=lt_MAIN_PLANE};
      __property TGLPixelType GLPixelType = {read=FGLPixelType, write=SetGLPixelType, default=pt_TYPE_RGBA};
      __property ParentColor;
      __property ParentCtl3D;
      __property ParentFont;
      __property ParentShowHint;
      __property PopupMenu;
      __property ShowHint;
      __property TabOrder;
      __property TabStop;
      __property Visible;

      // Available events

      __property OnClick;
      __property OnDblClick;
      __property OnDragDrop;
      __property OnDragOver;
      __property OnEndDrag;
      __property OnEnter;
      __property OnExit;
      __property OnMouseDown;
      __property OnMouseMove;
      __property OnMouseUp;
      __property OnResize;
      __property OnStartDrag;

      // OpenGL events

      __property TNotifyEvent OnGLPaint = {read=FOnGLPaint, write=FOnGLPaint};
      __property TNotifyEvent OnGLInit = {read=FOnGLInit, write=FOnGLInit};
};

////////////////////////////////////////////////////////////////////////////////

#endif

// End of file
////////////////////////////////////////////////////////////////////////////////

