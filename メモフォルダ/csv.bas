Attribute VB_Name = "csv"
Option Explicit

'この標準モジュールは変更しない

Enum CSVCols
  Default = 0  '当初設定に従う
  force = 1    '強制的に処理を行う
  Ignore = 2   '処理を行わない
End Enum


'CSV出力メインロジック
'正常終了時TRUEを返す　※現状は、エラー処理を行っていないので常にTRUEが返る
'※charset に utf-8n と指定すると「BOMなしUTF-8」でCSVデータを作成する
Function Output(TargetSheet As Worksheet, ByVal Filepath As String, _
    Optional ByVal StartRow As Long = 1, Optional ByVal EndRow As Long = 0, _
    Optional ByVal StartCol As Long = 1, Optional ByVal EndCol As Long = 0, _
    Optional ByVal WithFormatCols As String = "", Optional ByVal WithoutFormatCols As String = "", _
    Optional ByVal WithQuoteCols As String = "", Optional ByVal WithoutQuoteCols As String = "", _
    Optional ByVal Delimitar As String = ",", Optional ByVal LineEndingCode As String = vbCr & vbLf, _
    Optional ByVal QuoteChar As String = """", Optional ByVal CharReplaceQuote As String = """""", _
    Optional ByVal Charset As String = "shift_jis") As Boolean
   
  '出力範囲（行）の指定
  If EndRow = 0 Then
    EndRow = getLastRow(TargetSheet)
  End If
  
  '出力範囲（列）の設定
  If EndCol = 0 Then
    EndCol = getLastColumn(TargetSheet)
  End If
       
  '各列出力時の書式付きかどうかの処理方法を配列に格納
  Dim FormatOptionOfColumns() As Long
  FormatOptionOfColumns = setOption(WithFormatCols, WithoutFormatCols, StartCol, EndCol)
  
  '各列出力時に”で囲むかどうかの処理方法を配列に格納
  Dim QuoteOptionOfColumns() As Long
  QuoteOptionOfColumns = setOption(WithQuoteCols, WithoutQuoteCols, StartCol, EndCol)
                   
  'CSV出力データ準備
  Dim csvData As String
  
  Dim rowData() As String
  ReDim rowData(0 To EndCol - StartCol) As String
  
  Dim R As Long
  Dim C As Long
  For R = StartRow To EndRow
    For C = StartCol To EndCol
      rowData(C - StartCol) = convertFormatTowriteCSVFile(TargetSheet.Cells(R, C), StartCol, _
                                            Delimitar, QuoteChar, CharReplaceQuote, _
                                            FormatOptionOfColumns, QuoteOptionOfColumns)
    Next
    
  '1行のデータをデリミタでつないで、改行を付加
    csvData = csvData & Join(rowData, Delimitar) & LineEndingCode
  Next
  
  
'csv出力
  Output = writeCSVFile(csvData, Filepath, Charset)
    
End Function


Private Function getLastRow(TargetSheet As Worksheet) As Long
 
  Dim Row As Long
  Dim Column As Long
  
'UsedRangeで取得した最下行の右→左、最下行の1段上の右→左と走査していく
  For Row = TargetSheet.UsedRange.Row + TargetSheet.UsedRange.Rows.Count - 1 To 1 Step -1
    For Column = TargetSheet.UsedRange.Column + TargetSheet.UsedRange.Columns.Count - 1 To 1 Step -1
      If TargetSheet.Cells(Row, Column).Value <> "" Then
        GoTo Finally
      End If
    Next
  Next

Finally:
  getLastRow = Row
End Function

Private Function getLastColumn(TargetSheet As Worksheet) As Long
  Dim Row As Long
  Dim Column As Long
  
'UsedRangeで取得した最右行の下→上、最右行の1列左の下→上と走査していく
  For Column = TargetSheet.UsedRange.Column + TargetSheet.UsedRange.Columns.Count - 1 To 1 Step -1
    For Row = TargetSheet.UsedRange.Row + TargetSheet.UsedRange.Rows.Count - 1 To 1 Step -1
      If TargetSheet.Cells(Row, Column).Value <> "" Then
        GoTo Finally
      End If
    Next
  Next

Finally:
  getLastColumn = Column
End Function


'CSV出力時のオプション
'（１．書式付で出力するか、２．「”」で囲むかについての設定）
'を使いやすい形（配列）に格納する
Private Function setOption(WithCols As String, WithoutCols As String, minCol As Long, maxCol As Long)
  WithCols = "," & WithCols & ","
  WithoutCols = "," & WithoutCols & ","
  
  Dim ret() As Long
  ReDim ret(0 To maxCol - minCol)

  Dim C As Long
  For C = LBound(ret) To UBound(ret)
    If InStr(WithCols, "," & C + 1 & ",") Then
      ret(C) = CSVCols.force
    ElseIf InStr(WithoutCols, "," & C + 1 & ",") Then
      ret(C) = CSVCols.Ignore
    Else
      ret(C) = CSVCols.Default
    End If
  Next
  
  setOption = ret
End Function


'各セルの値をCSV出力用に加工する
Private Function convertFormatTowriteCSVFile(R As Range, BaseCol As Long, _
         Delimitar As String, QuoteChar As String, CharReplaceQuote As String, _
         FormatOptionOfColumns() As Long, QuoteOptionOfColumns() As Long)
  Dim Val As Variant
  Val = R.Value
               
  '書式を適用
  If FormatOptionOfColumns(R.Column - BaseCol) = CSVCols.force Or _
    FormatOptionOfColumns(R.Column - BaseCol) = CSVCols.Default And addFormat(Val) Then
    Val = R.Text
  End If
    
  '「”」で囲む　※データ中に「”」があれば、指定の値に置き換える
  If QuoteOptionOfColumns(R.Column - BaseCol) = CSVCols.force Or _
    QuoteOptionOfColumns(R.Column - BaseCol) = CSVCols.Default And AddQuote(Val, Delimitar, QuoteChar) Then
    Val = QuoteChar & Replace(Val, QuoteChar, CharReplaceQuote) & QuoteChar
  End If

  convertFormatTowriteCSVFile = Val
End Function


'CSVCols.Defaultの場合に、書式を適用するかどうかの判定
Private Function addFormat(Val As Variant) As Boolean
    addFormat = False
End Function

'CSVCols.Defaultの場合に、「”」で囲むかの判定。
Private Function AddQuote(Val As Variant, Delimitar As String, QuoteChar As String) As Boolean
  If InStr(Val, Delimitar) Or InStr(Val, QuoteChar) Or _
     InStr(Val, vbLf) Or InStr(Val, vbCr) Then
    AddQuote = True
  Else
    AddQuote = False
  End If
End Function


'CSVデータ出力
'正常終了時TRUEを返す
Private Function writeCSVFile(csvData As String, Filepath As String, Charset As String) As Boolean
  Dim removeBom As Boolean
  
  If Charset = "utf-8n" Then
    Charset = "utf-8"
    removeBom = True
  Else
    removeBom = False
  End If
  
   
'本来は、下記で変数宣言したいが、参照設定しない場合のために、変数宣言をObjectにする
'  Dim ST As ADODB.Stream
  Dim ST As Object
  Set ST = CreateObject("ADODB.stream")
  
  With ST
    .Mode = 3  'adModeReadWrite
    .Type = 2  'adTypeText
    .Charset = Charset
  
    .Open
    .WriteText csvData, 0  'adWriteChar
  End With
  
  If removeBom Then
'以下、Bom抜き処理
'BOM部分を読み飛ばして、その先から読み込む
    ST.Position = 0
    ST.Type = 1  'adTypeBinary
    ST.Position = 3

'別のストリームにバイナリとしてコピー
'    Dim ST2 As ADODB.Stream
    Dim ST2 As Object
    Set ST2 = CreateObject("ADODB.stream")
    
    With ST2
      .Mode = 3  'adModeReadWrite
      .Type = 1  'adTypeBinary
      .Open
  
      .Write ST.Read
    
      .SaveToFile Filepath, 2  'adSaveCreateOverWrite
      .Close
    End With
  Else
    ST.SaveToFile Filepath, 2  'adSaveCreateOverWrite
  End If
  
  ST.Close
  writeCSVFile = True
End Function



