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
// [GRY, 13/03/97] Created a virtual public method called "GLRepaint" that
//                 contains all the necessary code to paint the OpenGL stuff.
//                 Before, it was done within the "Paint" method, but it wasn't
//                 good enough, because it may happen that the user needs to
//                 refresh his OpenGL stuff (e.g. when doing real time graphism)
// [GRY, 13/03/97] Modified the call to "glClearColor" in the "GLRepaint" method
//                 Indeed, before we divided by "256" which resulted in a long
//                 value of "0" all the time, while we should get a float value
//                 between "0" and "1", we therefore modified "256" to "256.0"
//                 and added a call to "glClear" with "GL_COLOR_BUFFER_BIT" as
//                 a parameter, that way the background color is properly
//                 displayed
// [GRY, 13/03/97] Override the "CreateWnd" that is inherited, and this in order
//                 to add the styles "WS_CLIPCHILDREN" and "WS_CLIPSIBLINGS"
//                 which are compulsory if we want to work with OpenGL
// [GRY, 13/03/97] Use the property "Color" instead of creating a new one (note:
//                 it was "FBackgroundColor"), indeed it's easier to use that
//                 property since it exists...
// [GRY, 14/03/97] Create the property "DC" instead of having it as a variable
//                 within the "GLRepaint" method. This involves the update of
//                 some prototypes
// [GRY, 14/03/97] Added the "CanCreate" variable to avoid strange behaviours
//                 (cf. lines where there is "CanCreate" for more information)
// [GRY, 20/03/97] My BIG mistake was to handle the mouse down/move/up events,
//                 this for future improvements (like zoom, rotation, etc.), BUT
//                 unfortunately I didn't call the inherited handler neither
//                 check if the user handles "OnMouseDown", "OnMouseMove" or
//                 "OnMouseUp", therefore everytime he did so, it simply didn't
//                 work... Anyway, this has been fixed and it works fine now...
// [GRY, 06/04/97] Decided to remove the mouse handling... Indeed, it doesn't 
//                 make sense to have zoom, rotation, etc. within this component
//                 If one wants such facilities, he will have to do it within a
//                 class that inherits from TOpenGL. Moreover, this solved a
//                 problem I didn't know about... Indeed, if one assigned a
//                 handler to one of the three mouse events, it generated it
//                 twice instead of once... Why? I don't know. Actually, if I
//                 remember well, I already had that with TTransBitmap
// [GRY, 06/04/97] Removed the "GLRepaint" method... Actually, it's completely
//                 useless since the "Repaint" method can be called instead...
// [GRY, 06/04/97] Removed the "OnGLPrep" event. Indeed, what could have been
//                 handled by that event can also be handled by "OnGLInit" 
// [GRY, 23/06/97] Finally found the bug there was with 256 colours displays.
//                 Well, I didn't really try to find it. It's just that today,
//                 someone who asked to solve his problem. By trying to do so,
//                 I finally found MY problem!! :) Anyway, what I did is to cast
//                 a word to a byte... This made the whole diff. (cf. the line
//                 "PtrToPalette->palNumEntries = (WORD) Colors;" in the method
//                 "SetControlPixelFormat()"
// [GRY, 25/07/97] Thanks to Paul Doughty (pdoughty@d-and-m.com), the component
//                 can finally be used several times on a same form or on diff.
//                 ones (cf. "Paint", the line commented "Make sure we have the
//                 correct context"). Thanks again Paul!!
// [GRY, 22/08/97] Thanks to Ralph Cady (rcady@erols.com) and its copy of
//                 BoundsChecker 5.0, who found a resource leak with "DC". I
//                 now release the DC in the destructor. Note: to do so, I need
//                 "Handle", but its value is lost when reaching the destructor.
//                 I therefore had to keep a copy of it. I hope that despite the
//                 lost of the value, the handle is till valid... 
////////////////////////////////////////////////////////////////////////////////

#include <vcl\vcl.h>
#pragma hdrstop

#include "OpenGL.h"

////////////////////////////////////////////////////////////////////////////////
//
// CONSTRUCTOR & DESTRUCTOR
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TOpenGL:

__fastcall TOpenGL::TOpenGL(TComponent *aOwner)
   : TCustomPanel(aOwner),
     NeedToInitialise(true),
     NeedToSetControlPixelFormat(false),
     DC(NULL),
     GLContext(NULL),
     FGLPixelType(pt_TYPE_RGBA),
     FGLColorBits(32),
     FGLDepthBits(32),
     FGLLayerType(lt_MAIN_PLANE)
{
   FGLFlags.Clear();

   FGLFlags << f_DRAW_TO_WINDOW << f_SUPPORT_OPENGL << f_DOUBLEBUFFER;

   ConvertFlags();
   ConvertLayerType();
   ConvertPixelType();
}

////////////////////////////////////////////////////////////////////////////////
// ~TOpenGL:

__fastcall TOpenGL::~TOpenGL()
{
   if (wglGetCurrentContext())
      // Make the rendering context not current

      wglMakeCurrent(NULL, NULL);

   if (GLContext)
      wglDeleteContext(GLContext);

   if (Palette)
      DeleteObject(Palette);

   if (DC)
      ReleaseDC(CopyOfHandle, DC);
}

////////////////////////////////////////////////////////////////////////////////
//
// INHERITABLE METHODS
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Paint:

void __fastcall TOpenGL::Paint()
{
   if (NeedToInitialise)
   {
      NeedToInitialise = false;

      DC = GetDC(Handle);   // We have to get it only once!!

      CopyOfHandle = Handle;

      SetControlPixelFormat();

      CreateGLContext();

      if (OnGLInit)
         OnGLInit(this);

      if (OnResize)
         OnResize(this);
   }
   else if (NeedToSetControlPixelFormat)
   {
      NeedToSetControlPixelFormat = false;

      SetControlPixelFormat();
   }

   // Make sure we have the correct context
   
   if (GLContext != wglGetCurrentContext())
      wglMakeCurrent(DC, GLContext);

   // Background color

  // glClearColor((ColorToRGB(Color) % 256) / 256.0,
  //              ((ColorToRGB(Color) / 256) % 256) / 256.0,
  //              (ColorToRGB(Color) / 65536) / 256.0,
  //              0.0);

   //glClear(GL_COLOR_BUFFER_BIT);

   if (OnGLPaint)
      OnGLPaint(this);

   if (FGLFlags.Contains(f_DOUBLEBUFFER))
      SwapBuffers(DC);
}

////////////////////////////////////////////////////////////////////////////////
// Resize:

void __fastcall TOpenGL::Resize()
{
   TCustomPanel::Resize();

   if (OnResize)
      OnResize(this);
}

////////////////////////////////////////////////////////////////////////////////
// CreateWnd:

void __fastcall TOpenGL::CreateWnd()
{
   TCustomPanel::CreateWnd();
   
   SetWindowLong(Handle, GWL_STYLE, GetWindowLong(Handle, GWL_STYLE)|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
}

////////////////////////////////////////////////////////////////////////////////
//
// METHODS USED FOR EXTERNAL PURPOSE
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// METHODS TO MODIFY THE DIFFERENT PUBLISHED PROPERTIES
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SetGLColorBits:

void __fastcall TOpenGL::SetGLColorBits(const short aValue)
{
   if ((aValue != FGLColorBits) && (aValue >= 0) &&  (aValue < 256))
   {
      FGLColorBits = aValue;

      NeedToSetControlPixelFormat = true;

      Repaint();
   }
}

////////////////////////////////////////////////////////////////////////////////
// SetGLDepthBits:

void __fastcall TOpenGL::SetGLDepthBits(const short aValue)
{
   if ((aValue != FGLDepthBits) && (aValue >= 0) && (aValue < 256))
   {
      FGLDepthBits = aValue;

      NeedToSetControlPixelFormat = true;

      Repaint();
   }
}

////////////////////////////////////////////////////////////////////////////////
// SetGLFlags:

void __fastcall TOpenGL::SetGLFlags(const TGLFlags aValue)
{
   // Note: the flags f_SUPPORT_GDI and f_DOUBLEBUFFER cannot be used together

   if ((aValue != FGLFlags) &&
       !(aValue.Contains(f_SUPPORT_GDI) && aValue.Contains(f_DOUBLEBUFFER)))
   {
      FGLFlags = aValue;

      ConvertFlags();

      NeedToSetControlPixelFormat = true;

      Repaint();
   }
}

////////////////////////////////////////////////////////////////////////////////
// SetGLLayerType:

void __fastcall TOpenGL::SetGLLayerType(const TGLLayerType aValue)
{
   if (aValue != FGLLayerType)
   {
      FGLLayerType = aValue;

      ConvertLayerType();

      NeedToSetControlPixelFormat = true;

      Repaint();
   }
}

////////////////////////////////////////////////////////////////////////////////
// SetGLPixelType:

void __fastcall TOpenGL::SetGLPixelType(const TGLPixelType aValue)
{
   if (aValue != FGLPixelType)
   {
      FGLPixelType = aValue;

      ConvertPixelType();

      NeedToSetControlPixelFormat = true;

      Repaint();
   }
}

////////////////////////////////////////////////////////////////////////////////
//
// METHODS USED FOR INTERNAL PURPOSE
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SetControlPixelFormat:

void __fastcall TOpenGL::SetControlPixelFormat()
{
   PIXELFORMATDESCRIPTOR PixelDesc =
   {
      sizeof(PIXELFORMATDESCRIPTOR),   // nSize
      1,                               // nVersion
      ConvertedFlags,                  // dwFlags
      ConvertedPixelType,              // iPixelType
      FGLColorBits,                    // cColorBits
      8,                               // cRedBits
      16,                              // cRedShift
      8,                               // cGreenBits
      8,                               // cGreenShift
      8,                               // cBlueBits
      0,                               // cBlueShift
      0,                               // cAlphaBits
      0,                               // cAlphaShift
      64,                              // cAccumBits
      16,                              // cAccumRedBits
      16,                              // cAccumGreenBits
      16,                              // cAccumBlueBits
      0,                               // cAccumAlphaBits
      FGLDepthBits,                    // cDepthBits
      8,                               // cStencilBits
      0,                               // cAuxBuffers
      ConvertedLayerType,              // iLayerType
      0,                               // bReserved
      0,                               // dwLayerMask
      0,                               // dwVisibleMask
      0                                // dwDamageMask
   };

   // Get the best available match pixel format for the device context

   int GLPixelFormat = ChoosePixelFormat(DC, &PixelDesc);

   if (!GLPixelFormat)
      // We didn't get any, so let's choose a default one

      GLPixelFormat = 1;

   // Set up the pixel format

   SetPixelFormat(DC, GLPixelFormat, &PixelDesc);

   DescribePixelFormat(DC, GLPixelFormat, sizeof(PIXELFORMATDESCRIPTOR),&PixelDesc);

   if (PixelDesc.dwFlags & PFD_NEED_PALETTE)
   {
      int Colors = 1 << PixelDesc.cColorBits;
      HANDLE Heap = GetProcessHeap();
      TLogPalette *PtrToPalette = (TLogPalette *) HeapAlloc(Heap, 0, sizeof(TLogPalette) + (Colors * sizeof(TPaletteEntry)));
      int ByRedMask   = (1 << PixelDesc.cRedBits) - 1;
      int ByGreenMask = (1 << PixelDesc.cGreenBits) - 1;
      int ByBlueMask  = (1 << PixelDesc.cBlueBits) - 1;

      PtrToPalette->palVersion    = 0x300;
      PtrToPalette->palNumEntries = (WORD) Colors;

      for (int I = 0; I < Colors; I++)
      {
         PtrToPalette->palPalEntry[I].peRed   = (BYTE) ((((I >> PixelDesc.cRedShift)   & ByRedMask)   * 255) / ByRedMask);
         PtrToPalette->palPalEntry[I].peGreen = (BYTE) ((((I >> PixelDesc.cGreenShift) & ByGreenMask) * 255) / ByGreenMask);
         PtrToPalette->palPalEntry[I].peBlue  = (BYTE) ((((I >> PixelDesc.cBlueShift)  & ByBlueMask)  * 255) / ByBlueMask);
         PtrToPalette->palPalEntry[I].peFlags = 0;                                                     
      }

      Palette = CreatePalette(PtrToPalette);
      HeapFree(Heap, 0, PtrToPalette);

      if (Palette)
      {
         SelectPalette(DC, Palette, false);

         RealizePalette(DC);
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
// CreateGLContext:

void __fastcall TOpenGL::CreateGLContext()
{
   GLContext = wglCreateContext(DC);

   if (GLContext)
      wglMakeCurrent(DC, GLContext);
}

////////////////////////////////////////////////////////////////////////////////
// ConvertFlags:

void __fastcall TOpenGL::ConvertFlags()
{
   ConvertedFlags = 0;

   if (FGLFlags.Contains(f_DOUBLEBUFFER))        ConvertedFlags |= PFD_DOUBLEBUFFER;
   if (FGLFlags.Contains(f_DRAW_TO_BITMAP))      ConvertedFlags |= PFD_DRAW_TO_BITMAP;
   if (FGLFlags.Contains(f_DRAW_TO_WINDOW))      ConvertedFlags |= PFD_DRAW_TO_WINDOW;
   if (FGLFlags.Contains(f_GENERIC_ACCELERATED)) ConvertedFlags |= PFD_GENERIC_ACCELERATED;
   if (FGLFlags.Contains(f_GENERIC_FORMAT))      ConvertedFlags |= PFD_GENERIC_FORMAT;
   if (FGLFlags.Contains(f_NEED_PALETTE))        ConvertedFlags |= PFD_NEED_PALETTE;
   if (FGLFlags.Contains(f_NEED_SYSTEM_PALETTE)) ConvertedFlags |= PFD_NEED_SYSTEM_PALETTE;
   if (FGLFlags.Contains(f_SUPPORT_GDI))         ConvertedFlags |= PFD_SUPPORT_GDI;
   if (FGLFlags.Contains(f_SUPPORT_OPENGL))      ConvertedFlags |= PFD_SUPPORT_OPENGL;
   if (FGLFlags.Contains(f_STEREO))              ConvertedFlags |= PFD_STEREO;
   if (FGLFlags.Contains(f_SWAP_COPY))           ConvertedFlags |= PFD_SWAP_COPY;
   if (FGLFlags.Contains(f_SWAP_EXCHANGE))       ConvertedFlags |= PFD_SWAP_EXCHANGE;
   if (FGLFlags.Contains(f_SWAP_LAYER_BUFFERS))  ConvertedFlags |= PFD_SWAP_LAYER_BUFFERS;
}

////////////////////////////////////////////////////////////////////////////////
// ConvertLayerType:

void __fastcall TOpenGL::ConvertLayerType()
{
        if (FGLLayerType == lt_MAIN_PLANE)     ConvertedLayerType = PFD_MAIN_PLANE;
   else if (FGLLayerType == lt_OVERLAY_PLANE)  ConvertedLayerType = PFD_OVERLAY_PLANE;
   else if (FGLLayerType == lt_UNDERLAY_PLANE) ConvertedLayerType = PFD_UNDERLAY_PLANE;
}

////////////////////////////////////////////////////////////////////////////////
// ConvertPixelType:

void __fastcall TOpenGL::ConvertPixelType()
{
        if (FGLPixelType == pt_TYPE_RGBA)       ConvertedPixelType = PFD_TYPE_RGBA;
   else if (FGLPixelType == pt_TYPE_COLORINDEX) ConvertedPixelType = PFD_TYPE_COLORINDEX;
}

////////////////////////////////////////////////////////////////////////////////
//
// MISCELLANEOUS
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Registration

namespace Opengl
{
   void __fastcall Register()
   {
      TComponentClass classes[1] = {__classid(TOpenGL)};

      RegisterComponents("Silicon Graphics", classes, 0);
   }
}

// End of file
////////////////////////////////////////////////////////////////////////////////

