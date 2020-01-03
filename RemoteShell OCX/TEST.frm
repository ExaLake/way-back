VERSION 5.00
Object = "{95C9A3B6-DDF5-11D1-B910-00A0C992A443}#17.1#0"; "RSH.ocx"
Begin VB.Form Form1 
   Caption         =   "Remote Shell Demo Form"
   ClientHeight    =   10590
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   13710
   LinkTopic       =   "Form1"
   ScaleHeight     =   10590
   ScaleWidth      =   13710
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton Command2 
      Caption         =   "Clear"
      Height          =   555
      Left            =   7245
      TabIndex        =   14
      Top             =   675
      Width           =   1995
   End
   Begin VB.TextBox Text6 
      Height          =   330
      Left            =   1215
      TabIndex        =   6
      Text            =   "stephbel"
      Top             =   1215
      Width           =   5010
   End
   Begin VB.ComboBox Combo1 
      Height          =   315
      ItemData        =   "TEST.frx":0000
      Left            =   1215
      List            =   "TEST.frx":000A
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   135
      Width           =   5010
   End
   Begin RSH.RemoteShell RemoteShell1 
      Left            =   135
      Top             =   3915
      _ExtentX        =   847
      _ExtentY        =   847
      Async           =   "False"
   End
   Begin VB.TextBox Text5 
      Height          =   330
      IMEMode         =   3  'DISABLE
      Left            =   1215
      PasswordChar    =   "*"
      TabIndex        =   10
      Text            =   "password"
      Top             =   1935
      Width           =   5010
   End
   Begin VB.TextBox Text4 
      Height          =   330
      Left            =   1215
      TabIndex        =   8
      Text            =   "stephbel"
      Top             =   1575
      Width           =   5010
   End
   Begin VB.TextBox Text3 
      Height          =   330
      Left            =   1215
      TabIndex        =   4
      Text            =   "nftc"
      Top             =   855
      Width           =   5010
   End
   Begin VB.TextBox Text2 
      Height          =   330
      Left            =   1200
      TabIndex        =   2
      Text            =   "ls -l"
      Top             =   495
      Width           =   5010
   End
   Begin VB.TextBox Text1 
      BackColor       =   &H00000000&
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FFFF&
      Height          =   7920
      Left            =   1215
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   12
      Top             =   2340
      Width           =   12270
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Execute"
      Height          =   555
      Left            =   7245
      TabIndex        =   13
      Top             =   90
      Width           =   1995
   End
   Begin VB.Label Label6 
      Caption         =   "Local User:"
      Height          =   285
      Left            =   135
      TabIndex        =   5
      Top             =   1260
      Width           =   1140
   End
   Begin VB.Label Label5 
      Caption         =   "Response:"
      Height          =   285
      Left            =   135
      TabIndex        =   11
      Top             =   2385
      Width           =   1140
   End
   Begin VB.Label Label4 
      Caption         =   "Password:"
      Height          =   285
      Left            =   135
      TabIndex        =   9
      Top             =   1980
      Width           =   1140
   End
   Begin VB.Label Label3 
      Caption         =   "Host User:"
      Height          =   285
      Left            =   135
      TabIndex        =   7
      Top             =   1620
      Width           =   1140
   End
   Begin VB.Label Label2 
      Caption         =   "Host:"
      Height          =   285
      Left            =   135
      TabIndex        =   3
      Top             =   900
      Width           =   1140
   End
   Begin VB.Label Label1 
      Caption         =   "Command:"
      Height          =   285
      Left            =   135
      TabIndex        =   1
      Top             =   540
      Width           =   1140
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'********************************************************************************
'* Module: Form1
'* Author: Greg Laycock
'* Description:
'*
'********************************************************************************
'* Revision:
'*
'********************************************************************************
Option Explicit

'********************************************************************************
'* Procedure: Command1_Click
'* Author: Greg Laycock
'* Description:
'*  Execute Command
'********************************************************************************
Private Sub Command1_Click()
    RemoteShell1.Host = Text3.Text
    RemoteShell1.UserName = Text4.Text
    RemoteShell1.Password = Text5.Text
    RemoteShell1.Command = Text2.Text
    RemoteShell1.LocalUserName = Text6.Text
    
    Call RemoteShell1.Process
End Sub

'********************************************************************************
'* Procedure: Combo1_Click
'* Author: Greg Laycock
'* Description:
'*
'********************************************************************************
Private Sub Combo1_Click()
    Select Case Left(Combo1.Text, 1)
    Case "1"
        RemoteShell1.ConnectionType = rsRSH
        Text6.Visible = True
        Text5.Visible = False
        Label4.Visible = False
        Label6.Visible = True
    Case "2"
        RemoteShell1.ConnectionType = rsREXEC
        Text6.Visible = False
        Text5.Visible = True
        Label4.Visible = True
        Label6.Visible = False
    End Select
End Sub

'********************************************************************************
'* Procedure: Command2_Click
'* Author: Greg Laycock
'* Description:
'*
'********************************************************************************
Private Sub Command2_Click()
    Text1.Text = ""
End Sub

'********************************************************************************
'* Procedure: Form_Load
'* Author: Greg Laycock
'* Description:
'*
'********************************************************************************
Private Sub Form_Load()
    Combo1.ListIndex = 0
End Sub

'********************************************************************************
'* Procedure: RemoteShell1_AsyncComplete
'* Author: Greg Laycock
'* Description:
'*  Async Complete Message
'********************************************************************************
Private Sub RemoteShell1_AsyncComplete()
    MsgBox "Complete!"
End Sub

'********************************************************************************
'* Procedure: RemoteShell1_Error
'* Author: Greg Laycock
'* Description:
'*  Connection Error Event
'********************************************************************************
Private Sub RemoteShell1_Error(ByVal ErrorNumber As String, ByVal ErrorText As String)
    Text1.Text = ErrorNumber & "-" & ErrorText
End Sub

'********************************************************************************
'* Procedure: RemoteShell1_ReceiveData
'* Author: Greg Laycock
'* Description:
'*  Receive Data Event
'********************************************************************************
Private Sub RemoteShell1_ReceiveData(ByVal InData As String)
    Dim sTempString As String
    Dim sChar As String
    Dim iLoopcounter As Long
    
    sTempString = ""
    For iLoopcounter = 1 To Len(InData)
        sChar = Mid(InData, iLoopcounter, 1)
        If Asc(sChar) < 32 Then
            If Asc(sChar) = 10 Then
                sChar = vbCrLf
            Else
                sChar = ""
            End If
        End If
        sTempString = sTempString & sChar
    Next iLoopcounter
    
    Text1.Text = Text1.Text & sTempString
End Sub
