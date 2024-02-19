Attribute VB_Name = "csv"
Option Explicit

'���̕W�����W���[���͕ύX���Ȃ�

Enum CSVCols
  Default = 0  '�����ݒ�ɏ]��
  force = 1    '�����I�ɏ������s��
  Ignore = 2   '�������s��Ȃ�
End Enum


'CSV�o�̓��C�����W�b�N
'����I����TRUE��Ԃ��@������́A�G���[�������s���Ă��Ȃ��̂ŏ��TRUE���Ԃ�
'��charset �� utf-8n �Ǝw�肷��ƁuBOM�Ȃ�UTF-8�v��CSV�f�[�^���쐬����
Function Output(TargetSheet As Worksheet, ByVal Filepath As String, _
    Optional ByVal StartRow As Long = 1, Optional ByVal EndRow As Long = 0, _
    Optional ByVal StartCol As Long = 1, Optional ByVal EndCol As Long = 0, _
    Optional ByVal WithFormatCols As String = "", Optional ByVal WithoutFormatCols As String = "", _
    Optional ByVal WithQuoteCols As String = "", Optional ByVal WithoutQuoteCols As String = "", _
    Optional ByVal Delimitar As String = ",", Optional ByVal LineEndingCode As String = vbCr & vbLf, _
    Optional ByVal QuoteChar As String = """", Optional ByVal CharReplaceQuote As String = """""", _
    Optional ByVal Charset As String = "shift_jis") As Boolean
   
  '�o�͔͈́i�s�j�̎w��
  If EndRow = 0 Then
    EndRow = getLastRow(TargetSheet)
  End If
  
  '�o�͔͈́i��j�̐ݒ�
  If EndCol = 0 Then
    EndCol = getLastColumn(TargetSheet)
  End If
       
  '�e��o�͎��̏����t�����ǂ����̏������@��z��Ɋi�[
  Dim FormatOptionOfColumns() As Long
  FormatOptionOfColumns = setOption(WithFormatCols, WithoutFormatCols, StartCol, EndCol)
  
  '�e��o�͎��Ɂh�ň͂ނ��ǂ����̏������@��z��Ɋi�[
  Dim QuoteOptionOfColumns() As Long
  QuoteOptionOfColumns = setOption(WithQuoteCols, WithoutQuoteCols, StartCol, EndCol)
                   
  'CSV�o�̓f�[�^����
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
    
  '1�s�̃f�[�^���f���~�^�łȂ��ŁA���s��t��
    csvData = csvData & Join(rowData, Delimitar) & LineEndingCode
  Next
  
  
'csv�o��
  Output = writeCSVFile(csvData, Filepath, Charset)
    
End Function


Private Function getLastRow(TargetSheet As Worksheet) As Long
 
  Dim Row As Long
  Dim Column As Long
  
'UsedRange�Ŏ擾�����ŉ��s�̉E�����A�ŉ��s��1�i��̉E�����Ƒ������Ă���
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
  
'UsedRange�Ŏ擾�����ŉE�s�̉�����A�ŉE�s��1�񍶂̉�����Ƒ������Ă���
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


'CSV�o�͎��̃I�v�V����
'�i�P�D�����t�ŏo�͂��邩�A�Q�D�u�h�v�ň͂ނ��ɂ��Ă̐ݒ�j
'���g���₷���`�i�z��j�Ɋi�[����
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


'�e�Z���̒l��CSV�o�͗p�ɉ��H����
Private Function convertFormatTowriteCSVFile(R As Range, BaseCol As Long, _
         Delimitar As String, QuoteChar As String, CharReplaceQuote As String, _
         FormatOptionOfColumns() As Long, QuoteOptionOfColumns() As Long)
  Dim Val As Variant
  Val = R.Value
               
  '������K�p
  If FormatOptionOfColumns(R.Column - BaseCol) = CSVCols.force Or _
    FormatOptionOfColumns(R.Column - BaseCol) = CSVCols.Default And addFormat(Val) Then
    Val = R.Text
  End If
    
  '�u�h�v�ň͂ށ@���f�[�^���Ɂu�h�v������΁A�w��̒l�ɒu��������
  If QuoteOptionOfColumns(R.Column - BaseCol) = CSVCols.force Or _
    QuoteOptionOfColumns(R.Column - BaseCol) = CSVCols.Default And AddQuote(Val, Delimitar, QuoteChar) Then
    Val = QuoteChar & Replace(Val, QuoteChar, CharReplaceQuote) & QuoteChar
  End If

  convertFormatTowriteCSVFile = Val
End Function


'CSVCols.Default�̏ꍇ�ɁA������K�p���邩�ǂ����̔���
Private Function addFormat(Val As Variant) As Boolean
    addFormat = False
End Function

'CSVCols.Default�̏ꍇ�ɁA�u�h�v�ň͂ނ��̔���B
Private Function AddQuote(Val As Variant, Delimitar As String, QuoteChar As String) As Boolean
  If InStr(Val, Delimitar) Or InStr(Val, QuoteChar) Or _
     InStr(Val, vbLf) Or InStr(Val, vbCr) Then
    AddQuote = True
  Else
    AddQuote = False
  End If
End Function


'CSV�f�[�^�o��
'����I����TRUE��Ԃ�
Private Function writeCSVFile(csvData As String, Filepath As String, Charset As String) As Boolean
  Dim removeBom As Boolean
  
  If Charset = "utf-8n" Then
    Charset = "utf-8"
    removeBom = True
  Else
    removeBom = False
  End If
  
   
'�{���́A���L�ŕϐ��錾���������A�Q�Ɛݒ肵�Ȃ��ꍇ�̂��߂ɁA�ϐ��錾��Object�ɂ���
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
'�ȉ��ABom��������
'BOM������ǂݔ�΂��āA���̐悩��ǂݍ���
    ST.Position = 0
    ST.Type = 1  'adTypeBinary
    ST.Position = 3

'�ʂ̃X�g���[���Ƀo�C�i���Ƃ��ăR�s�[
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



