object Form1: TForm1
  Left = 192
  Top = 107
  Width = 1013
  Height = 562
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
    Left = 88
    Top = 8
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
  object rgdV: TRadioGroup
    Left = 128
    Top = 48
    Width = 57
    Height = 265
    Caption = 'dV'
    ItemIndex = 5
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
    OnClick = rgdVClick
  end
  object Button3: TButton
    Left = 248
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Run PANSYM'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 328
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Get Data'
    TabOrder = 4
  end
  object rgR: TRadioGroup
    Left = 8
    Top = 48
    Width = 49
    Height = 265
    Caption = 'R'
    ItemIndex = 0
    Items.Strings = (
      '01'
      '02'
      '03'
      '04'
      '05'
      '06'
      '07'
      '08')
    TabOrder = 5
    OnClick = rgRClick
  end
  object rgZ: TRadioGroup
    Left = 64
    Top = 48
    Width = 57
    Height = 145
    Caption = 'Z'
    ItemIndex = 0
    Items.Strings = (
      '0.25'
      '0.50'
      '0.75'
      '0.90')
    TabOrder = 6
    OnClick = rgZClick
  end
  object rgWing: TRadioGroup
    Left = 64
    Top = 200
    Width = 57
    Height = 113
    Caption = 'Wing'
    ItemIndex = 0
    Items.Strings = (
      'PK'
      'ZK')
    TabOrder = 7
    OnClick = rgWingClick
  end
  object PageControl1: TPageControl
    Left = 192
    Top = 56
    Width = 801
    Height = 465
    ActivePage = TabSheet2
    MultiLine = True
    Style = tsFlatButtons
    TabOrder = 8
    object TabSheet1: TTabSheet
      Caption = 'Airfoil'
      object Memo1: TMemo
        Left = 0
        Top = 4
        Width = 793
        Height = 429
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 0
        WordWrap = False
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Wing Description'
      ImageIndex = 1
      object Memo4: TMemo
        Left = 0
        Top = 5
        Width = 793
        Height = 429
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'TabSheet3'
      ImageIndex = 2
      object Memo3: TMemo
        Left = 0
        Top = 4
        Width = 793
        Height = 429
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 0
        WordWrap = False
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'TabSheet4'
      ImageIndex = 3
      object Memo2: TMemo
        Left = 0
        Top = 5
        Width = 793
        Height = 429
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 0
        WordWrap = False
      end
    end
  end
  object Button5: TButton
    Left = 168
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Test Wing'
    TabOrder = 9
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 408
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Test Winglet'
    TabOrder = 10
    OnClick = Button6Click
  end
  object OpenDialog1: TOpenDialog
    Left = 960
    Top = 8
  end
end
