object Form1: TForm1
  Left = 192
  Top = 107
  Width = 1232
  Height = 399
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 72
    Top = 328
    Width = 75
    Height = 25
    Caption = 'Replace foil'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 8
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Open IN'
    TabOrder = 1
    OnClick = Button2Click
  end
  object RadioGroup1: TRadioGroup
    Left = 8
    Top = 48
    Width = 57
    Height = 265
    Caption = 'dV'
    Items.Strings = (
      '-10'
      '-8'
      '-6'
      '-4'
      '-2'
      '0'
      '2'
      '4'
      '6'
      '8'
      '10')
    TabOrder = 2
    OnClick = RadioGroup1Click
  end
  object Memo1: TMemo
    Left = 72
    Top = 56
    Width = 249
    Height = 257
    Lines.Strings = (
      'Memo1')
    TabOrder = 3
    WordWrap = False
  end
  object Memo2: TMemo
    Left = 328
    Top = 56
    Width = 289
    Height = 257
    Lines.Strings = (
      'Memo2')
    TabOrder = 4
    WordWrap = False
  end
  object Memo3: TMemo
    Left = 624
    Top = 56
    Width = 281
    Height = 257
    Lines.Strings = (
      'Memo3')
    TabOrder = 5
    WordWrap = False
  end
  object Button3: TButton
    Left = 328
    Top = 328
    Width = 75
    Height = 25
    Caption = 'Run PANSYM'
    TabOrder = 6
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 624
    Top = 328
    Width = 75
    Height = 25
    Caption = 'Get Data'
    TabOrder = 7
  end
  object Memo4: TMemo
    Left = 912
    Top = 56
    Width = 297
    Height = 257
    Lines.Strings = (
      'Memo4')
    TabOrder = 8
  end
  object OpenDialog1: TOpenDialog
    Left = 88
    Top = 8
  end
end
