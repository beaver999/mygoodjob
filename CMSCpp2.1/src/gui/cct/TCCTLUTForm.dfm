object CCTLUTForm: TCCTLUTForm
  Left = 339
  Top = 312
  Width = 842
  Height = 482
  Caption = 'CCT LUT'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object Label9: TLabel
    Left = 473
    Top = 425
    Width = 349
    Height = 16
    Caption = 'Copyright (C) 2010, AU Optronics Corp., All Right Reserved.'
  end
  object GroupBox1: TGroupBox
    Left = 9
    Top = 9
    Width = 192
    Height = 312
    Caption = 'Gray Level Option'
    TabOrder = 0
    object Label1: TLabel
      Left = 9
      Top = 48
      Width = 63
      Height = 16
      Caption = 'Start Level'
    end
    object Label2: TLabel
      Left = 9
      Top = 80
      Width = 60
      Height = 16
      Caption = 'End Level'
    end
    object Label3: TLabel
      Left = 9
      Top = 112
      Width = 64
      Height = 16
      Caption = 'Level Step'
    end
    object Edit_StartLevel: TEdit
      Left = 80
      Top = 48
      Width = 105
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 0
      Text = '255'
    end
    object ComboBox_LevelStep: TComboBox
      Left = 80
      Top = 112
      Width = 105
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      ItemHeight = 16
      TabOrder = 1
      Text = '1'
      Items.Strings = (
        '1'
        '2'
        '4'
        '8'
        '16'
        '17'
        '32'
        '34')
    end
    object Edit_EndLevel: TEdit
      Left = 80
      Top = 80
      Width = 105
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 2
      Text = '0'
    end
    object CheckBox_Expand: TCheckBox
      Left = 9
      Top = 16
      Width = 120
      Height = 25
      Caption = 'Expand Mode'
      TabOrder = 3
      OnClick = CheckBox_ExpandClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 209
    Top = 9
    Width = 208
    Height = 96
    Caption = 'Gamma'
    TabOrder = 1
    object RadioButton_GammaCurve: TRadioButton
      Left = 9
      Top = 41
      Width = 112
      Height = 24
      Caption = 'Gamma Curve'
      TabOrder = 0
      OnClick = RadioButton_GammaCurveClick
    end
    object CheckBox_GByPass: TCheckBox
      Left = 33
      Top = 64
      Width = 96
      Height = 25
      Caption = 'G ByPass'
      TabOrder = 1
      Visible = False
    end
    object RadioButton_Gamma: TRadioButton
      Left = 9
      Top = 16
      Width = 80
      Height = 25
      Caption = 'Gamma'
      Checked = True
      TabOrder = 2
      TabStop = True
      OnClick = RadioButton_GammaClick
    end
    object ComboBox_Gamma: TComboBox
      Left = 89
      Top = 16
      Width = 96
      Height = 24
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ItemHeight = 16
      TabOrder = 3
      Text = '2.2'
      OnChange = ComboBox_GammaChange
      Items.Strings = (
        '1.8'
        '1.9'
        '2.0'
        '2.1'
        '2.2'
        '2.3'
        '2.4'
        '2.5')
    end
  end
  object GroupBox3: TGroupBox
    Left = 425
    Top = 9
    Width = 192
    Height = 312
    Caption = 'Low Level Correction'
    TabOrder = 2
    object Label4: TLabel
      Left = 32
      Top = 89
      Width = 37
      Height = 16
      Caption = 'Under'
    end
    object Label7: TLabel
      Left = 32
      Top = 41
      Width = 16
      Height = 16
      Caption = 'P1'
    end
    object Label8: TLabel
      Left = 121
      Top = 41
      Width = 16
      Height = 16
      Caption = 'P2'
    end
    object Label17: TLabel
      Left = 32
      Top = 153
      Width = 37
      Height = 16
      Caption = 'Under'
      Visible = False
    end
    object Label14: TLabel
      Left = 32
      Top = 185
      Width = 49
      Height = 16
      Caption = 'Strength'
      Visible = False
    end
    object RadioButton_P1P2: TRadioButton
      Left = 9
      Top = 17
      Width = 96
      Height = 24
      Caption = 'P1 P2'
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = RadioButton_P1P2Click
    end
    object RadioButton_RBInterp: TRadioButton
      Left = 9
      Top = 65
      Width = 128
      Height = 24
      Caption = 'RB Interpolation'
      TabOrder = 1
    end
    object Edit_RBInterpUnder: TEdit
      Left = 89
      Top = 89
      Width = 72
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 2
      Text = '50'
    end
    object Edit_P1: TEdit
      Left = 57
      Top = 41
      Width = 40
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 3
      Text = '20'
    end
    object Edit_P2: TEdit
      Left = 144
      Top = 41
      Width = 41
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 4
      Text = '50'
    end
    object RadioButton_None: TRadioButton
      Left = 9
      Top = 108
      Width = 72
      Height = 25
      Caption = 'None'
      TabOrder = 5
      Visible = False
    end
    object RadioButton_DefinedDim: TRadioButton
      Left = 9
      Top = 129
      Width = 120
      Height = 24
      Caption = 'Defined Dim'
      Enabled = False
      TabOrder = 6
      Visible = False
    end
    object Edit_DefinedDimUnder: TEdit
      Left = 89
      Top = 153
      Width = 72
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 7
      Text = '50'
      Visible = False
    end
    object CheckBox_AverageDimDG: TCheckBox
      Left = 32
      Top = 208
      Width = 137
      Height = 25
      Caption = 'Average Dim DG'
      TabOrder = 8
      Visible = False
    end
    object Edit_DimGamma: TEdit
      Left = 89
      Top = 185
      Width = 72
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 9
      Text = '2.2'
      Visible = False
    end
  end
  object GroupBox4: TGroupBox
    Left = 625
    Top = 9
    Width = 192
    Height = 152
    Caption = 'Blue Correction'
    TabOrder = 3
    object Label18: TLabel
      Left = 32
      Top = 89
      Width = 35
      Height = 16
      Caption = 'Begin'
      Visible = False
    end
    object Label19: TLabel
      Left = 32
      Top = 121
      Width = 49
      Height = 16
      Caption = 'Strength'
      Visible = False
    end
    object CheckBox_BGain: TCheckBox
      Left = 9
      Top = 17
      Width = 120
      Height = 24
      Caption = 'B Intensity Gain'
      TabOrder = 0
    end
    object Edit_BGain: TEdit
      Left = 129
      Top = 17
      Width = 56
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 1
      Text = '1.05'
    end
    object CheckBox_BMax: TCheckBox
      Left = 9
      Top = 41
      Width = 96
      Height = 24
      Caption = 'B Max'
      TabOrder = 2
    end
    object CheckBox_BMax2: TCheckBox
      Left = 9
      Top = 65
      Width = 160
      Height = 24
      Caption = 'B Max (Smooth)'
      TabOrder = 3
      Visible = False
      OnClick = CheckBox_BMax2Click
    end
    object Edit_BMax2Begin: TEdit
      Left = 89
      Top = 89
      Width = 72
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 4
      Text = '235'
      Visible = False
    end
    object Edit_BMax2Gamma: TEdit
      Left = 89
      Top = 121
      Width = 72
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 5
      Text = '2.2'
      Visible = False
    end
  end
  object GroupBox5: TGroupBox
    Left = 625
    Top = 161
    Width = 192
    Height = 160
    Caption = 'Options'
    TabOrder = 4
    object CheckBox_AvoidNoise: TCheckBox
      Left = 9
      Top = 17
      Width = 136
      Height = 24
      Caption = 'Avoid FRC Noise'
      TabOrder = 0
    end
    object CheckBox_NewMethod: TCheckBox
      Left = 9
      Top = 41
      Width = 120
      Height = 24
      Caption = 'New Method'
      TabOrder = 1
      Visible = False
      OnClick = CheckBox_NewMethodClick
    end
  end
  object Button_MeaRun: TButton
    Left = 625
    Top = 369
    Width = 104
    Height = 24
    Hint = 'Measure panel characteristic and produce CCT DG LUT.'
    Caption = 'Measue&&Run'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 5
    OnClick = Button_MeaRunClick
  end
  object Button_Debug: TButton
    Left = 625
    Top = 353
    Width = 56
    Height = 16
    Caption = 'debug'
    TabOrder = 6
    OnClick = Button_DebugClick
  end
  inline TOutputFileFrame1: TOutputFileFrame
    Left = 9
    Top = 329
    Width = 616
    Height = 96
    TabOrder = 7
    inherited GroupBox_OutputFile: TGroupBox
      Width = 610
      Height = 90
      inherited Label5: TLabel
        Left = 9
        Top = 25
      end
      inherited Label6: TLabel
        Left = 9
        Top = 57
      end
      inherited Edit_Prefix: TEdit
        Top = 25
        Text = 'Cal_Table'
      end
      inherited Edit_Directory: TEdit
        Top = 57
        Width = 425
      end
      inherited Button_BrowseDir: TButton
        Left = 545
        Top = 57
        Width = 56
        Height = 24
        OnClick = TOutputFileFrame1Button_BrowseDirClick
      end
    end
  end
  object Panel_Expand: TPanel
    Left = 17
    Top = 57
    Width = 176
    Height = 256
    Caption = 'Panel_Expand'
    TabOrder = 8
    Visible = False
    object GroupBox6: TGroupBox
      Left = 9
      Top = 9
      Width = 160
      Height = 120
      Caption = 'Low Gray Level'
      TabOrder = 0
      object Label5: TLabel
        Left = 9
        Top = 89
        Width = 64
        Height = 16
        Caption = 'Level Step'
      end
      object Label6: TLabel
        Left = 9
        Top = 57
        Width = 60
        Height = 16
        Caption = 'End Level'
      end
      object Label10: TLabel
        Left = 9
        Top = 25
        Width = 63
        Height = 16
        Caption = 'Start Level'
      end
      object ComboBox_LowStep: TComboBox
        Left = 80
        Top = 89
        Width = 73
        Height = 24
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        ItemHeight = 16
        TabOrder = 0
        Text = '8'
        Items.Strings = (
          '1'
          '2'
          '4'
          '8'
          '16'
          '32')
      end
      object Edit_LowEndLevel: TEdit
        Left = 80
        Top = 57
        Width = 73
        Height = 24
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        TabOrder = 1
        Text = '0'
      end
      object Edit_LowStartLevel: TEdit
        Left = 80
        Top = 25
        Width = 73
        Height = 24
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        TabOrder = 2
        Text = '64'
      end
    end
    object GroupBox7: TGroupBox
      Left = 9
      Top = 128
      Width = 160
      Height = 121
      Caption = 'High Gray Level'
      TabOrder = 1
      object Label11: TLabel
        Left = 9
        Top = 25
        Width = 63
        Height = 16
        Caption = 'Start Level'
      end
      object Label12: TLabel
        Left = 9
        Top = 89
        Width = 64
        Height = 16
        Caption = 'Level Step'
      end
      object Label13: TLabel
        Left = 9
        Top = 57
        Width = 60
        Height = 16
        Caption = 'End Level'
      end
      object Edit_HighStartLevel: TEdit
        Left = 80
        Top = 25
        Width = 73
        Height = 24
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        TabOrder = 0
        Text = '255'
      end
      object Edit_HighEndLevel: TEdit
        Left = 80
        Top = 57
        Width = 73
        Height = 24
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        TabOrder = 1
        Text = '64'
      end
      object ComboBox_HighStep: TComboBox
        Left = 80
        Top = 89
        Width = 73
        Height = 24
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        ItemHeight = 16
        TabOrder = 2
        Text = '16'
        Items.Strings = (
          '1'
          '2'
          '4'
          '8'
          '16'
          '32')
      end
    end
  end
  object Button_Reset: TButton
    Left = 625
    Top = 336
    Width = 56
    Height = 17
    Caption = 'reset'
    TabOrder = 9
    Visible = False
    OnClick = Button_ResetClick
  end
  object Button_Run: TButton
    Left = 625
    Top = 393
    Width = 104
    Height = 24
    Caption = 'Run'
    Enabled = False
    TabOrder = 10
    Visible = False
    OnClick = Button_RunClick
  end
  object GroupBox_KeepMaxLuminance: TGroupBox
    Left = 208
    Top = 105
    Width = 209
    Height = 216
    Caption = 'Keep Max Luminance'
    TabOrder = 11
    Visible = False
    object Label20: TLabel
      Left = 32
      Top = 113
      Width = 29
      Height = 16
      Caption = 'Over'
    end
    object Label21: TLabel
      Left = 32
      Top = 145
      Width = 49
      Height = 16
      Caption = 'Strength'
    end
    object RadioButton_MaxYTarget: TRadioButton
      Left = 9
      Top = 41
      Width = 168
      Height = 24
      Caption = 'Target White'
      TabOrder = 0
    end
    object RadioButton_MaxYNative: TRadioButton
      Left = 9
      Top = 64
      Width = 160
      Height = 25
      Caption = 'Native White'
      TabOrder = 1
    end
    object RadioButton_MaxYNone: TRadioButton
      Left = 9
      Top = 16
      Width = 144
      Height = 25
      Caption = 'None'
      Checked = True
      TabOrder = 2
      TabStop = True
    end
    object RadioButton_MaxYNativeAdv: TRadioButton
      Left = 9
      Top = 89
      Width = 168
      Height = 24
      Caption = 'Native White (Smooth)'
      Enabled = False
      TabOrder = 3
      OnClick = RadioButton_MaxYNativeAdvClick
    end
    object Edit_MaxYAdvOver: TEdit
      Left = 89
      Top = 113
      Width = 72
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 4
      Text = '235'
    end
    object Edit_MaxYAdvGamma: TEdit
      Left = 89
      Top = 145
      Width = 72
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 5
      Text = '2.2'
    end
    object CheckBox_BTargetIntensity: TCheckBox
      Left = 8
      Top = 176
      Width = 137
      Height = 25
      Caption = 'B Target intensity'
      TabOrder = 6
      OnClick = CheckBox_BTargetIntensityClick
    end
    object Edit_BTargetIntensity: TEdit
      Left = 152
      Top = 176
      Width = 49
      Height = 24
      Enabled = False
      TabOrder = 7
      Text = '100'
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'DGCode Files(*.xls)|*.xls'
    Options = [ofEnableSizing]
  end
end
