#include <vcl.h>
#include <vcl\printers.hpp>
#include <vcl\graphics.hpp>
#include <float.h>
#include <stdlib.h>
#pragma hdrstop

#include "TOpenGLPanel.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TOpenGLPanel *)
{
        new TOpenGLPanel(NULL);
}
//---------------------------------------------------------------------------
__fastcall TOpenGLPanel::TOpenGLPanel(TComponent* Owner)
        : TCustomPanel(Owner)
{
 _control87(MCW_EM, MCW_EM);
 FdwFlags.Clear();
 FdwFlags << f_PFD_DRAW_TO_WINDOW << f_PFD_SUPPORT_OPENGL <<f_PFD_DOUBLEBUFFER;
 FiPixelType=f_PFD_TYPE_RGBA;
 SavedPixelType=PFD_TYPE_RGBA;
 FcColorBits=32;
 FcDepthBits=32;
 FOpenGLPrintScale=pglProportional;
 FOpenGLPixelsPerInch=96;
}
//---------------------------------------------------------------------------
__fastcall TOpenGLPanel::~TOpenGLPanel()
{

 return;
}
//---------------------------------------------------------------------------
namespace Topenglpanel
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TOpenGLPanel)};
                 RegisterComponents("OpenGL Toolkit", classes, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TOpenGLPanel::WMCreate(TWMCreate &Message)
{
 if (!CreateGLContext())
     {
      ShowMessage("Open GL Context Create Failed");
      return;
     }
 if (FOnInit)
  {
   if (wglMakeCurrent(DisplayDeviceContext,GLRenderingContext)==false)
        ShowMessage("wglMakeCurrent:" + IntToStr(GetLastError()));
   FOnInit(this);
   wglMakeCurrent(NULL, NULL);
  }
 return;
}
//---------------------------------------------------------------------------
void __fastcall TOpenGLPanel::WMPaletteChanged(TWMPaletteChanged &Message)
{
 TWMQueryNewPalette Dummy;
 if (Message.PalChg==Handle) return;
 WMQueryNewPalette(Dummy);
 return;
}
//---------------------------------------------------------------------------
void __fastcall TOpenGLPanel::WMQueryNewPalette(TWMQueryNewPalette &Message)
{
  UINT     num;
  HPALETTE OldPalette=SelectPalette(DisplayDeviceContext,Palette,FALSE);
  if ((num=RealizePalette(DisplayDeviceContext))==GDI_ERROR)
        {
         ShowMessage("RealizePallette:"+IntToStr(GetLastError()));
         return;
        }
  if (wglMakeCurrent(DisplayDeviceContext,GLRenderingContext)==false)
        {
         Message.Result=0;
         return;
        }
  wglMakeCurrent(NULL, NULL);
  SelectPalette(GLRenderingContext,OldPalette,TRUE);
  if (num) InvalidateRect(Handle,NULL,TRUE); // Force Repaint
  Message.Result=num;
  return;
}
//---------------------------------------------------------------------------
void __fastcall TOpenGLPanel::WMDestroy(TWMDestroy &Message)
{
  DestroyGLContext();
  return;
}
//---------------------------------------------------------------------------
void __fastcall TOpenGLPanel::WMEraseBkgnd(TWMEraseBkgnd &Message)
{
 if (ComponentState.Contains(csDesigning))
    {
      TRect Rect;
      TColor OldColor=Canvas->Brush->Color;
      Rect =GetClientRect();
      Canvas->Brush->Color=clBtnFace;
      Canvas->FillRect(Rect);
      Canvas->Brush->Color=OldColor;
    }
 Message.Result=TRUE;
 return;
}
//---------------------------------------------------------------------------
void __fastcall TOpenGLPanel::CreateParams(TCreateParams &Params)
{
 TCustomPanel::CreateParams(Params);
 Params.Style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
 Params.ExStyle|= 0;                // Place Holder
 Params.WindowClass.style|=0;       // Place Holder
 return;
}
//---------------------------------------------------------------------------
void __fastcall TOpenGLPanel::Paint(void)
{
  //TCustomPanel::Paint();
   if (FOnPaint)
      {
        HPALETTE OldPalette=SelectPalette(DisplayDeviceContext,Palette,FALSE);
        if (RealizePalette(DisplayDeviceContext)==GDI_ERROR)
            {
             ShowMessage("RealizePallette:"+IntToStr(GetLastError()));
             return;
            }
        if (wglMakeCurrent(DisplayDeviceContext,GLRenderingContext)==false)
            {
             ShowMessage("wglMakeCurrent:" + IntToStr(GetLastError()));
             return;
            }
        FOnPaint(this);
        if (DoubleBuffer) ::SwapBuffers(DisplayDeviceContext);
        SelectPalette(DisplayDeviceContext,OldPalette,TRUE);
        wglMakeCurrent(NULL, NULL) ;
      }
 return;
}
//---------------------------------------------------------------------------
void __fastcall TOpenGLPanel::PrintOpenGLPanel(void)
{
 Graphics::TBitmap *BitMap = new Graphics::TBitmap();
 int                BitMapInfoSize,BitMapImageSize,
                    XPixelsPerInch,YPixelsPerInch,
                    XSizeInPixels,YSizeInPixels;
 void              *BitMapImage;
 BITMAPINFO        *BitMapInfo;
 RECT               Rect;

 BitMap->Height= Height;
 BitMap->Width = Width;
 BringToFront();
 Paint();
 BitMap->Canvas->CopyRect(ClientRect ,Canvas,ClientRect);
 XPixelsPerInch=GetDeviceCaps(Printer()->Handle,LOGPIXELSX);
 YPixelsPerInch=GetDeviceCaps(Printer()->Handle,LOGPIXELSY);

 Rect.left  =0.18*XPixelsPerInch;
 Rect.top   =0.18*YPixelsPerInch;

 if (FOpenGLPrintScale==pglPrintToFit)
    {
     XSizeInPixels=GetDeviceCaps(Printer()->Handle,HORZRES)-2*Rect.left;
     YSizeInPixels=GetDeviceCaps(Printer()->Handle,VERTRES)-2*Rect.top;
     if (XSizeInPixels > YSizeInPixels)
        {
         Rect.right=BitMap->Width*(YSizeInPixels/BitMap->Height);
         Rect.bottom=YSizeInPixels;
        }
     else
        {
         Rect.right= XSizeInPixels;
         Rect.bottom = BitMap->Height* (XSizeInPixels / BitMap->Width);
        }
    }
 else if (FOpenGLPrintScale==pglProportional)
    {
     if (FOpenGLPixelsPerInch<=0)  FOpenGLPixelsPerInch=96;

     Rect.right =(int)(((float)BitMap->Width/(float)FOpenGLPixelsPerInch)*
                 (float)XPixelsPerInch)+Rect.left;
     Rect.bottom=(int)(((float)BitMap->Height/(float)FOpenGLPixelsPerInch)*
                 (float)YPixelsPerInch)+Rect.top;
    }
  else // pglNone
    {
     Rect.right =BitMap->Width+Rect.left;
     Rect.bottom=BitMap->Height+Rect.right;
    }

 GetDIBSizes(BitMap->Handle,BitMapInfoSize,BitMapImageSize);
 BitMapInfo=(BITMAPINFO *)malloc(BitMapInfoSize);
 BitMapImage=malloc(BitMapImageSize);
 if ((BitMapInfo==NULL) || (BitMapImage==NULL))
  {
   ShowMessage("Print: Malloc Error");
   if (BitMapInfo) free(BitMapInfo);
   if (BitMapImage) free(BitMapImage);
   return;
  }
 Printer()->BeginDoc();
 GetDIB(BitMap->Handle,BitMap->Palette,BitMapInfo,BitMapImage);
 StretchDIBits(Printer()->Canvas->Handle,
              Rect.left,Rect.top,
              Rect.right-Rect.left,
              Rect.bottom-Rect.top,
              0,0,
              BitMap->Width,BitMap->Height,
              BitMapImage,
              BitMapInfo,
              DIB_RGB_COLORS,
              SRCCOPY);
 free(BitMapInfo);
 free(BitMapImage);
 Printer()->EndDoc();
 delete BitMap;
 return;
}
//---------------------------------------------------------------------------
void __fastcall TOpenGLPanel::SaveOpenGLPanelToFile(const String &FileName)
{
 Graphics::TBitmap *BitMap = new Graphics::TBitmap();
 BitMap->Height= Height;
 BitMap->Width = Width;
 BringToFront();
 Paint();
 BitMap->Canvas->CopyRect(ClientRect ,Canvas,ClientRect);
 BitMap->SaveToFile(FileName);
 delete BitMap;
 return;
}
//---------------------------------------------------------------------------
void __fastcall TOpenGLPanel::Resize(void)
{
  TCustomPanel::Resize();
  if (FOnResize)
     {
      if (wglMakeCurrent(DisplayDeviceContext,GLRenderingContext)==false)
          {
            ShowMessage("wglMakeCurrent:" + IntToStr(GetLastError()));
            return;
          }
      FOnResize(this);
      wglMakeCurrent(NULL, NULL) ;
     }
  return;
}
//---------------------------------------------------------------------------
 bool __fastcall TOpenGLPanel::CreateGLContext(void)
 {
  int PixelFormatIndex;
  PIXELFORMATDESCRIPTOR pfd=
    {
     sizeof(PIXELFORMATDESCRIPTOR), // size
     1,                             // version 1
     0,                             // Flags
     SavedPixelType,                // Color Mode
     FcColorBits,                   // Number of color bits
     0,0,0,0,0,0,                   // RGB color bits with shift (not used)
     0,0,                           // Alpha bits with shift     (not used)
     0,                             // Number of accumulator bits
     0,0,0,0,                       // RGBA accumulator bits
     FcDepthBits,                   // Number of bits for Z-Buffer Depth
     0,                             // Stencil buffer depth
     0,                             // Auxiliary buffer depth
     PFD_MAIN_PLANE,                // Layer type
     0,                             // Reserved
     0,                             // Layer mask
     0,                             // Visible mask
     0                              // Damage mask
    };

  if (FdwFlags.Contains(f_PFD_DRAW_TO_WINDOW))
                 pfd.dwFlags|=PFD_DRAW_TO_WINDOW;
  if (FdwFlags.Contains(f_PFD_DRAW_TO_BITMAP))
                 pfd.dwFlags|= PFD_DRAW_TO_BITMAP;
  if (FdwFlags.Contains(f_PFD_SUPPORT_GDI))
                 pfd.dwFlags|= PFD_SUPPORT_GDI;
  else           pfd.dwFlags|= PFD_DOUBLEBUFFER;
  if (FdwFlags.Contains(f_PFD_SUPPORT_OPENGL))
                 pfd.dwFlags|= PFD_SUPPORT_OPENGL;
  if (FdwFlags.Contains(f_PFD_GENERIC_ACCELERATED))
                 pfd.dwFlags|= PFD_GENERIC_ACCELERATED;
  if (FdwFlags.Contains(f_PFD_GENERIC_FORMAT))
                 pfd.dwFlags|= PFD_GENERIC_FORMAT;
  if (FdwFlags.Contains(f_PFD_NEED_PALETTE))
                 pfd.dwFlags|=PFD_NEED_PALETTE ;
  if (FdwFlags.Contains(f_PFD_NEED_SYSTEM_PALETTE))
                 pfd.dwFlags|= PFD_NEED_SYSTEM_PALETTE;
  if (FdwFlags.Contains(f_PFD_STEREO))
                 pfd.dwFlags|= PFD_STEREO;
  if (FdwFlags.Contains(f_PFD_SWAP_LAYER_BUFFERS))
                 pfd.dwFlags|=PFD_SWAP_LAYER_BUFFERS;

  DisplayDeviceContext=GetDC(this->Handle);
  if ((PixelFormatIndex = ChoosePixelFormat(DisplayDeviceContext,&pfd))==0)
        {
         ShowMessage("ChoosePixelFormat:" + IntToStr(glGetError()));
         ReleaseDC(this->Handle,DisplayDeviceContext);
         return false;
        }

  if (SetPixelFormat(DisplayDeviceContext,PixelFormatIndex,&pfd)!=true)
        {
         ShowMessage("SetPixelFormat:" + IntToStr(glGetError()));
         ReleaseDC(this->Handle,DisplayDeviceContext);
         return false;
        }
 if (pfd.dwFlags & PFD_DOUBLEBUFFER) DoubleBuffer=true;
 else DoubleBuffer=false;

 DescribePixelFormat(DisplayDeviceContext,PixelFormatIndex,
                       sizeof(PIXELFORMATDESCRIPTOR),&pfd);
  if (pfd.dwFlags & PFD_NEED_PALETTE)
        {
         if (ConstructPalette(pfd)==false)
             {
              ReleaseDC(this->Handle,DisplayDeviceContext);
              return false;
             }
        }
  else Palette=NULL;
   if ((GLRenderingContext=wglCreateContext(DisplayDeviceContext))==NULL)
        {
         ShowMessage("wglRenderingContext:" + IntToStr(glGetError()));
         if (Palette)
            {
             SelectPalette(DisplayDeviceContext,
                           GetStockObject(DEFAULT_PALETTE),false);
             if (DeleteObject(Palette)==false)
                 ShowMessage("DeleteObject: Failed");
            }
         ReleaseDC(this->Handle,DisplayDeviceContext);
         return false;
        }
   return true;
 }
 //---------------------------------------------------------------------------
 void __fastcall TOpenGLPanel::DestroyGLContext(void)
 {
  wglMakeCurrent(NULL,NULL);
  if (GLRenderingContext!=NULL)
        {
         if (wglDeleteContext(GLRenderingContext)==false)
         	ShowMessage("wglDeleteContext:"+IntToStr(GetLastError()));
         if ((Palette) && (DeleteObject(Palette)==false))
                     ShowMessage("DeleteObject: Failed");
         if (ReleaseDC(this->Handle,GLRenderingContext)!=0)
           ShowMessage("ReleaseDC: Failed");
        }
  return;
 }
 //---------------------------------------------------------------------------
 bool __fastcall TOpenGLPanel::ConstructPalette(PIXELFORMATDESCRIPTOR &pfd)
 {
  LOGPALETTE *LPalettep;
  int NumColors= 1 << pfd.cColorBits;

  if (( LPalettep=(LOGPALETTE * )
             malloc(sizeof(LOGPALETTE)+(sizeof(PALETTEENTRY)*NumColors)))==NULL)
       {
        ShowMessage("ConstructPalette: Malloc failure");
        return false;
       }
  LPalettep->palVersion=0x300;
  LPalettep->palNumEntries=NumColors;

  int RedMask   =( 1 << pfd.cRedBits  ) -1;
  int GreenMask =( 1 << pfd.cGreenBits) -1;
  int BlueMask  =( 1 << pfd.cBlueBits ) -1;

  for (int i=0;i<NumColors;i++)
        {
         LPalettep->palPalEntry[i].peRed=
         	(((i >> pfd.cRedShift) & RedMask)     *255)/RedMask;

         LPalettep->palPalEntry[i].peGreen=
         	(((i >> pfd.cGreenShift) & GreenMask) *255)/GreenMask;

         LPalettep->palPalEntry[i].peBlue=
         	(((i >> pfd.cBlueShift) &  BlueMask)  *255)/BlueMask;
        }
  if ((Palette=CreatePalette(LPalettep))==NULL)
        {
         ShowMessage("CreatePalette:"+IntToStr(GetLastError()));
         return false;
        }
  free(LPalettep);
  return true;
 }
//---------------------------------------------------------------------------
void __fastcall TOpenGLPanel::SetPFDPixelType(const TPFDPixelTypes Value)
  {
   if (Value==f_PFD_TYPE_RGBA) SavedPixelType=PFD_TYPE_RGBA;
   else SavedPixelType=PFD_TYPE_COLORINDEX;
   FiPixelType=Value;
   return;
  }
//---------------------------------------------------------------------------
void __fastcall TOpenGLPanel::SetPFDFlags(const TPFDFlagsSet Value)
  {
   TPFDFlagsSet Temp=Value;

   if ((Value.Contains(f_PFD_SUPPORT_GDI)) &&
       (Value.Contains(f_PFD_DOUBLEBUFFER)))
       {
        if (FdwFlags.Contains(f_PFD_SUPPORT_GDI)) Temp >> f_PFD_SUPPORT_GDI;
        else Temp >> f_PFD_DOUBLEBUFFER;
       }
   else if ((!Value.Contains(f_PFD_SUPPORT_GDI)) &&
       (!Value.Contains(f_PFD_DOUBLEBUFFER)))
       {
        if (FdwFlags.Contains(f_PFD_SUPPORT_GDI)) Temp  << f_PFD_DOUBLEBUFFER;
        else Temp << f_PFD_SUPPORT_GDI;
       }
   FdwFlags=Temp;
   return;
  }
//--------------------------------------------------------------------------

void __fastcall TOpenGLPanel::SetPFDNumColorBits(const BYTE Value)
  {
   FcColorBits=Value;
   return;
  }
//---------------------------------------------------------------------------
void __fastcall TOpenGLPanel::SetPFDNumDepthBits(const BYTE Value)
  {
   FcDepthBits=Value;
   return;
  }
//---------------------------------------------------------------------------
void __fastcall TOpenGLPanel::SetOpenGLPrintScale(const TOpenGLPrintScale Value)
  {
   FOpenGLPrintScale=Value;
   return;
  }
//---------------------------------------------------------------------------
void __fastcall TOpenGLPanel::SetOpenGLPixelsPerInch(const int Value)
  {
   FOpenGLPixelsPerInch=Value;
   return;
  }
//---------------------------------------------------------------------------


