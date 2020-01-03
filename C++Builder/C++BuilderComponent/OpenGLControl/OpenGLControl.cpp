/*
 * Author      : Bart van den Broek
 * Copyright   : Copyright (c) 1998 by Bart van den Broek
 */

//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <windows.h>
#include "pixelformat.h"
#pragma hdrstop

#include <gl\gl.h>
#include "OpenGLControl.h"
//#include "pixelformat.cpp"

//---------------------------------------------------------------------------
// TOpenGLSettings, property type

__fastcall TOpenGLSettings::TOpenGLSettings()
{
  FPixelFormatFlags = TPixelFormatFlags() << pfDrawToWindow << pfSupportOpenGL;
  FColorType = pfRGBA;
  //FLayerType = pfMainPlane;
  FColorBits = 24;
  FAccumBits = 0;
  FAlphaBits = 0;
  FDepthBits = 32;
  FStencilBits = 0;
  FAuxilaryBuffers = 0;
  FValidate = true;
  FBufferSwap = true;
  FMultipleOpenGL = false;
}

void __fastcall TOpenGLSettings::Assign(TPersistent* Value)
{
  TOpenGLSettings *OS = dynamic_cast<TOpenGLSettings*>(Value);
  if (!OS) {
	inherited::Assign(Value);
	return;
  }
  FPixelFormatFlags = OS->FPixelFormatFlags;
  FColorType = OS->FColorType;
  //copy(FLayerType);
  FColorBits = OS->FColorBits;
  FAccumBits = OS->FAccumBits;
  FAlphaBits = OS->FAlphaBits;
  FDepthBits = OS->FDepthBits;
  FStencilBits = OS->FStencilBits;
  FAuxilaryBuffers = OS->FAuxilaryBuffers;
  FValidate = OS->FValidate;
  FBufferSwap = OS->FBufferSwap;
}

void TOpenGLSettings::SetDCPixelFormat(HDC hDC)
{
  static const int Enum2Flag[] = {
	PFD_DRAW_TO_WINDOW,        PFD_DRAW_TO_BITMAP,
	PFD_SUPPORT_GDI,           PFD_SUPPORT_OPENGL,
	PFD_DOUBLEBUFFER,          PFD_STEREO,
	PFD_DOUBLEBUFFER_DONTCARE, PFD_STEREO_DONTCARE };
  static const int CT2Flag[] = {
	PFD_TYPE_RGBA, PFD_TYPE_COLORINDEX };

  PIXELFORMATDESCRIPTOR pfd = {
	sizeof(PIXELFORMATDESCRIPTOR),  // Size of this structure
	1                               // Version of this structure
  };

  int i;
  for (i = TPixelFormatEnumFirst; i <= TPixelFormatEnumLast; i++)
	if (FPixelFormatFlags.Contains(TPixelFormatEnum(i)))
	  pfd.dwFlags |= Enum2Flag[i];
  pfd.iPixelType = CT2Flag[(int)FColorType];
  pfd.cColorBits = FColorBits;
  pfd.cAccumBits = FAccumBits;
  pfd.cAlphaBits = FAlphaBits;
  pfd.cDepthBits = FDepthBits;
  pfd.cStencilBits = FStencilBits;
  pfd.cAuxBuffers = FAuxilaryBuffers;
  pfd.iLayerType = PFD_MAIN_PLANE;

  // Choose a pixel format that best matches that described in pfd
  int nPixelFormat = ChoosePixelFormat(hDC, &pfd);
  // Set the pixel format for the device context
  SetPixelFormat(hDC, nPixelFormat, &pfd);

  // DEBUG
  //	FILE *fout = fopen("pixfmt.txt", "wt");
  //    DumpPixelFormat(fout,hDC, nPixelFormat);
  //    fclose(fout);
  // END
}

//---------------------------------------------------------------------------
// TOpenGLControl component

static inline TOpenGLControl *ValidCtrCheck()
{
  return new TOpenGLControl(NULL);
}

__fastcall TOpenGLControl::TOpenGLControl(TComponent* Owner)
  : inherited(Owner)
{
  FOpenGLSettings = new TOpenGLSettings();
  FOnOpenGLInit = NULL;
  FOnOpenGLResize = NULL;
  FOnOpenGLPaint = NULL;
  OpenGLRC = 0;
  Width = 100;
  Height = 100;
  CachedHandle = 0;
}

__fastcall TOpenGLControl::~TOpenGLControl()
{
  SetOpenGLSettings(NULL);
}

void TOpenGLControl::SwapBuffers()
{
  ::SwapBuffers(CachedDC);
}

void __fastcall TOpenGLControl::DestroyWindowHandle()
{
  if (OpenGLRC != NULL)
  	{
	  wglMakeCurrent(CachedDC,NULL);
	  wglDeleteContext(OpenGLRC);
    }
  inherited::DestroyWindowHandle();
}

void __fastcall TOpenGLControl::CreateParams(TCreateParams &Params)
{
  inherited::CreateParams(Params);
  // Necessary for OpenGL
  Params.Style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
}

void __fastcall TOpenGLControl::SetOpenGLSettings (TOpenGLSettings *OGLS)
{
  delete FOpenGLSettings;
  FOpenGLSettings = OGLS;
}

TOpenGLSettings* __fastcall TOpenGLControl::GetOpenGLSettings()
{
  return FOpenGLSettings;
}

void __fastcall TOpenGLControl::WMPaint(TWMPaint& Message)
{
  if (FOpenGLSettings->MultipleOpenGL)
	wglMakeCurrent(CachedDC, OpenGLRC);

  if (ComponentState.Contains(csDesigning))
	{
	  inherited::PaintHandler(Message);
	  glDrawBuffer(GL_FRONT);
	  glClearColor(0.5f, 0.5f, 0.5f, 1.0f );
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  glFlush();
	}
  else if (FOnOpenGLPaint)
	{
	  FOnOpenGLPaint(this);
	  if (FOpenGLSettings->BufferSwap)
		if (FOpenGLSettings->PixelFormatFlags.Contains(pfDoubleBuffer))
		  ::SwapBuffers(CachedDC);
		else
		  glFlush();
	  if (FOpenGLSettings->Validate)
		::ValidateRect(Handle, NULL);
	}
}

void __fastcall TOpenGLControl::WMSize(TWMSize& Message)
{
  if (FOnOpenGLResize)
	FOnOpenGLResize(this, Message.Width, Message.Height);
}

void __fastcall TOpenGLControl::WMCreate(TWMCreate& Message)
{
  if (!FOpenGLSettings) return;
  if (OpenGLRC == NULL)
    {
	  CachedHandle = Handle;
	  HDC hDC = CachedDC = ::GetDC(CachedHandle);
	  FOpenGLSettings->SetDCPixelFormat(hDC);
	  OpenGLRC = wglCreateContext(hDC);
	  wglMakeCurrent(hDC, OpenGLRC);
    }
  if (FOnOpenGLInit)
   	FOnOpenGLInit(this);
}

void __fastcall TOpenGLControl::WMEraseBkgnd(TWMEraseBkgnd& Message)
{
  //   if (ComponentState.Contains(csDesigning))
  // 	{
  // 	  RECT cr;
  // 	  cr.left = cr.top = 0;
  // 	  cr.right = ClientWidth;
  // 	  cr.bottom = ClientHeight;
  // 	  FillRect(Message.DC, &cr, Brush->Handle);
  // 	}
  Message.Result = 1;
}

//---------------------------------------------------------------------------
// Registration
namespace Openglcontrol
{
  void __fastcall Register()
	{
	  TComponentClass classes[1] = {__classid(TOpenGLControl)};
	  RegisterComponents("Custom", classes, 0);
/* 	  RegisterPropertyEditor(__typeinfo(TOpenGLSettings),
							 NULL,
							 "",
							 __classid(TClassProperty));
	  /*	  	RegisterPropertyEditor(__typeinfo(TPixelBufferSet),
				NULL,
				"",
				__classid(TSetProperty));
				*/
	}
}
//---------------------------------------------------------------------------
