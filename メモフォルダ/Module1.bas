Attribute VB_Name = "Module1"
Option Explicit

Const EXT As String = ".csv"

Sub CSV�o��_�ʏ�()
  Dim Filename As String
  Filename = Mid(ActiveWorkbook.Name, 1, InStrRev(ActiveWorkbook.Name, ".") - 1) & EXT
  
  Dim Filepath As String
  Filepath = ActiveWorkbook.Path & "\" & Filename
  
  Call csv.Output(ActiveSheet, Filepath)
  
  ActiveWorkbook.Save
  MsgBox Filepath & "��CSV�t�@�C�����o�͂��܂���"
End Sub


Sub CSV�o��_�ڍ׎w��()
  Dim Filename As String
  Filename = Mid(ActiveWorkbook.Name, 1, InStrRev(ActiveWorkbook.Name, ".") - 1) & EXT
  
  Dim Filepath As String
  Filepath = ActiveWorkbook.Path & "\" & Filename
  
  Call csv.Output(TargetSheet:=ActiveSheet, Filepath:=Filepath, _
                  StartRow:=2, StartCol:=2, _
                  WithFormatCols:="3", WithQuoteCols:="1,2", _
                  Charset:="utf-8")
                 
  MsgBox Filepath & "��CSV�t�@�C�����A�����R�[�h�uUTF-8�v�ŏo�͂��܂����B" & Chr(13) _
                  & "2�s�ڂ��牺�A2��ڂ���E�̂ݏo�͂��Ă��܂��B" & Chr(13) _
                  & "�܂��A�o�̓f�[�^��3��ڂ͏����t�A1��ځA2��ڂ́u""�v�ň͂�ŏo�͂��Ă��܂��B"
End Sub




