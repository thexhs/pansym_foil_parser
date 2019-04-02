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
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object btnFoil: TButton
    Left = 8
    Top = 312
    Width = 75
    Height = 25
    Caption = 'FOIL'
    TabOrder = 0
    OnClick = btnFoilClick
  end
  object rgdV: TRadioGroup
    Left = 128
    Top = 8
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
    TabOrder = 1
    OnClick = rgdVClick
  end
  object Button4: TButton
    Left = 8
    Top = 440
    Width = 75
    Height = 25
    Caption = 'Get Data'
    TabOrder = 2
    OnClick = Button4Click
  end
  object rgR: TRadioGroup
    Left = 8
    Top = 8
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
    TabOrder = 3
    OnClick = rgRClick
  end
  object rgZ: TRadioGroup
    Left = 64
    Top = 8
    Width = 57
    Height = 145
    Caption = 'Z'
    ItemIndex = 0
    Items.Strings = (
      '0.25'
      '0.50'
      '0.75'
      '0.90')
    TabOrder = 4
    OnClick = rgZClick
  end
  object rgWing: TRadioGroup
    Left = 64
    Top = 160
    Width = 57
    Height = 113
    Caption = 'Wing'
    ItemIndex = 0
    Items.Strings = (
      'PK'
      'ZK')
    TabOrder = 5
    OnClick = rgWingClick
  end
  object PageControl1: TPageControl
    Left = 192
    Top = 16
    Width = 801
    Height = 505
    ActivePage = TabSheet5
    MultiLine = True
    Style = tsFlatButtons
    TabIndex = 0
    TabOrder = 6
    object TabSheet5: TTabSheet
      Caption = 'HEAD'
      ImageIndex = 4
      object mHead: TMemo
        Left = 0
        Top = 0
        Width = 793
        Height = 433
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheet1: TTabSheet
      Caption = 'Airfoil'
      object mAirfoil: TMemo
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
      Caption = 'WING'
      ImageIndex = 1
      object mWing: TMemo
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
      Caption = 'WINGLET'
      ImageIndex = 2
      object mWinglet: TMemo
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
      Caption = 'IN FILE'
      ImageIndex = 3
      object mInFile: TMemo
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
  object btnWing: TButton
    Left = 8
    Top = 344
    Width = 75
    Height = 25
    Caption = 'WING'
    TabOrder = 7
    OnClick = btnWingClick
  end
  object btnWinglet: TButton
    Left = 8
    Top = 376
    Width = 75
    Height = 25
    Caption = 'WINGLET'
    TabOrder = 8
    OnClick = btnWingletClick
  end
  object btnAuto: TButton
    Left = 88
    Top = 280
    Width = 75
    Height = 25
    Caption = 'AUTO'
    TabOrder = 9
    OnClick = btnAutoClick
  end
  object btnMakeIn: TButton
    Left = 88
    Top = 312
    Width = 75
    Height = 25
    Caption = 'MAKE FILE'
    TabOrder = 10
    OnClick = btnMakeInClick
  end
  object btnPANSYM: TButton
    Left = 88
    Top = 344
    Width = 75
    Height = 25
    Caption = 'Run PANSYM'
    TabOrder = 11
    OnClick = btnPANSYMClick
  end
  object btnVisual: TButton
    Left = 8
    Top = 408
    Width = 75
    Height = 25
    Caption = 'VISUAL'
    TabOrder = 12
    OnClick = btnVisualClick
  end
  object btnOU2GEO: TButton
    Left = 88
    Top = 376
    Width = 75
    Height = 25
    Caption = 'MAKE GEO'
    TabOrder = 13
    OnClick = btnOU2GEOClick
  end
  object btnGetOu: TButton
    Left = 88
    Top = 408
    Width = 75
    Height = 25
    Caption = 'GET OU'
    TabOrder = 14
    OnClick = btnGetOuClick
  end
  object btnHead: TButton
    Left = 8
    Top = 280
    Width = 75
    Height = 25
    Caption = 'HEAD'
    TabOrder = 15
    OnClick = btnHeadClick
  end
  object OpenDialog1: TOpenDialog
    Left = 96
    Top = 480
  end
end
