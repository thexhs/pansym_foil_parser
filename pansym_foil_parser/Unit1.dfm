object Form1: TForm1
  Left = 192
  Top = 107
  BorderStyle = bsSingle
  Caption = 'Form1'
  ClientHeight = 453
  ClientWidth = 920
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 8
    Top = 320
    Width = 521
    Height = 129
  end
  object Button1: TButton
    Left = 8
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Open File'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Memo1: TMemo
    Left = 8
    Top = 48
    Width = 393
    Height = 265
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 1
    WordWrap = False
  end
  object Memo2: TMemo
    Left = 536
    Top = 64
    Width = 377
    Height = 193
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 2
    WordWrap = False
  end
  object Button3: TButton
    Left = 408
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Extract Airfoil'
    TabOrder = 3
    OnClick = Button3Click
  end
  object lbePointCount: TLabeledEdit
    Left = 408
    Top = 64
    Width = 121
    Height = 21
    EditLabel.Width = 66
    EditLabel.Height = 13
    EditLabel.Caption = 'lbePointCount'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 4
  end
  object lbeNumber: TLabeledEdit
    Left = 408
    Top = 104
    Width = 121
    Height = 21
    EditLabel.Width = 51
    EditLabel.Height = 13
    EditLabel.Caption = 'lbeNumber'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 5
  end
  object lbeType: TLabeledEdit
    Left = 408
    Top = 144
    Width = 121
    Height = 21
    EditLabel.Width = 38
    EditLabel.Height = 13
    EditLabel.Caption = 'lbeType'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 6
  end
  object lstAirfoils: TListBox
    Left = 408
    Top = 176
    Width = 121
    Height = 137
    ItemHeight = 13
    TabOrder = 7
    OnClick = lstAirfoilsClick
  end
  object stgAcoords: TStringGrid
    Left = 536
    Top = 264
    Width = 377
    Height = 129
    ColCount = 2
    FixedCols = 0
    ScrollBars = ssVertical
    TabOrder = 8
  end
  object Save: TButton
    Left = 808
    Top = 416
    Width = 99
    Height = 25
    Caption = 'Save to VISTRAN'
    TabOrder = 9
    OnClick = SaveClick
  end
  object Button2: TButton
    Left = 120
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 10
    OnClick = Button2Click
  end
  object Button4: TButton
    Left = 696
    Top = 416
    Width = 107
    Height = 25
    Caption = 'Save to XFLR *.dat'
    TabOrder = 11
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 592
    Top = 416
    Width = 99
    Height = 25
    Caption = 'Save as PANSYM'
    TabOrder = 12
    OnClick = SaveClick
  end
  object cbeNormalize: TCheckBox
    Left = 696
    Top = 395
    Width = 217
    Height = 17
    Caption = 'Normalize to unit chord'
    TabOrder = 13
  end
  object OpenDialog1: TOpenDialog
    Left = 88
    Top = 8
  end
  object SaveDialog1: TSaveDialog
    Left = 536
    Top = 416
  end
end
