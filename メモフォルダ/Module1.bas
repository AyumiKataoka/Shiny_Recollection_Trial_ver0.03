Attribute VB_Name = "Module1"
Option Explicit

Const EXT As String = ".csv"

Sub CSV出力_通常()
  Dim Filename As String
  Filename = Mid(ActiveWorkbook.Name, 1, InStrRev(ActiveWorkbook.Name, ".") - 1) & EXT
  
  Dim Filepath As String
  Filepath = ActiveWorkbook.Path & "\" & Filename
  
  Call csv.Output(ActiveSheet, Filepath)
  
  ActiveWorkbook.Save
  MsgBox Filepath & "にCSVファイルを出力しました"
End Sub


Sub CSV出力_詳細指定()
  Dim Filename As String
  Filename = Mid(ActiveWorkbook.Name, 1, InStrRev(ActiveWorkbook.Name, ".") - 1) & EXT
  
  Dim Filepath As String
  Filepath = ActiveWorkbook.Path & "\" & Filename
  
  Call csv.Output(TargetSheet:=ActiveSheet, Filepath:=Filepath, _
                  StartRow:=2, StartCol:=2, _
                  WithFormatCols:="3", WithQuoteCols:="1,2", _
                  Charset:="utf-8")
                 
  MsgBox Filepath & "にCSVファイルを、文字コード「UTF-8」で出力しました。" & Chr(13) _
                  & "2行目から下、2列目から右のみ出力しています。" & Chr(13) _
                  & "また、出力データの3列目は書式付、1列目、2列目は「""」で囲んで出力しています。"
End Sub




