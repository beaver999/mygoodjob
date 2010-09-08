//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HueSatVal2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "HueSatVal1"
#pragma resource "*.dfm"
THSVForm2 *HSVForm2;
//---------------------------------------------------------------------------
__fastcall THSVForm2::THSVForm2(TComponent * Owner)
:THSVForm1(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall THSVForm2::sb_Hue_gainScroll(TObject * Sender,
					     TScrollCode ScrollCode, int &ScrollPos)
{
    //double sigma = 0;
    if (ScrollCode != scEndScroll) {
	return;
    }
    int tbl_n = 24;
    //copy�L�h���ηN�O??
    for (int i = 0; i < tbl_n; i++) {
	Hue_table_t[i] = Hue_table[i];
	Sat_table_t[i] = Sat_table[i];
	Val_table_t[i] = Val_table[i];
    }

    //�N�ϥΪ̿�J�����״���table����index
    //le_ChAangle: �qRGBCMY���襤����ۨ�
    //tbl_idx: ��ۨ���M��LUT��index
    int tbl_idx = Get_select_idx(StrToFloat(le_ChAangle->Text));

    //�Nscroll bar������ܥX��
    show_gain(sb_Hue_gain->Position, sb_Sat_gain->Position, sb_Val_gain->Position);
    int gain_h = sb_Hue_gain->Position;	// Hue�Ȭ�Gain
    int gain_s = sb_Sat_gain->Position - Sat_table[tbl_idx];	// �վ�ȻPtable�ƭȪ��t����gain
    int gain_v = sb_Val_gain->Position - Val_table[tbl_idx];
    //�̷ӭȰ�(-96~96)�ӻ�, �o��ӧP�_�����ӨS���o�ͪ��i��!?
    if (gain_h > 768 / 2) {
	gain_h -= 768;
    } else if (gain_h < (-1) * 768 / 2) {
	gain_h += 768;
    }
    //set���s�O�Ψӧ�վ�q�u���ǰe��LUT
    btn_set->Enabled = true;
    if (cb_Hue_rotation->Checked == false) {
	//���G�O���Fdiffusion, �ҥH�~�i�}��9�ӭ�
	int tmp_H[9], tmp_S[9], tmp_V[9];
	Get_Adj_tbl(tmp_H, tmp_S, tmp_V, tbl_idx);

	//=====================================================================
	//diffusion
	//=====================================================================
	int low = (4 - sb_dif_n->Position);
	int high = sb_dif_p->Position;

	/*bool dif_ok = CheckDif(high, low, tmp_H, gain_h);
	   if (dif_ok == 0)
	   return; */
	/*sb_dif_p->Position = high;
	   sb_dif_n->Position = 4 - low; */
	tmp_H[4] += gain_h;
	tmp_S[4] += gain_s;
	tmp_V[4] += gain_v;
	//double ratio;

	//=====================================================================
	// high
	//=====================================================================
	//�]�wdiffusion���ܤ�
	/*if (high == 4)
	   sigma = 0.4;
	   else if (high == 3)
	   sigma = 0.5;
	   else if (high == 2)
	   sigma = 0.6;


	   for (int i = 1; i < high; i++) {
	   ratio = pow(double (high - i) / high, 2) + (double) i / high * Gauss(i, sigma);
	   tmp_H[i + 4] = tmp_H[i + 4] + gain_h * ratio;
	   tmp_S[i + 4] = tmp_S[i + 4] + gain_s * ratio;
	   tmp_V[i + 4] = tmp_V[i + 4] + gain_v * ratio;
	   } */
	//=====================================================================

	//=====================================================================
	// low
	//=====================================================================
	/*if (low == 4)
	   sigma = 0.4;
	   else if (low == 3)
	   sigma = 0.5;
	   else if (low == 2)
	   sigma = 0.6;

	   for (int i = 1; i < low; i++) {
	   ratio = pow(double (low - i) / low, 2) + (double) i / low * Gauss(i, sigma);
	   tmp_H[4 - i] = tmp_H[4 - i] + gain_h * ratio;
	   tmp_S[4 - i] = tmp_S[4 - i] + gain_s * ratio;
	   tmp_V[4 - i] = tmp_V[4 - i] + gain_v * ratio;
	   } */
	//=====================================================================
	//=====================================================================


	Set_Adj_tbl(tmp_H, tmp_S, tmp_V, tbl_idx);
	if (!CheckHueIncrease(high, low, tmp_H)) {
	    ShowMessage("Hue value has inverse.");
	    btn_set->Enabled = false;
	    return;
	}
    } else {			//rotation
	//�����@�_�վ�@�˪��q
	for (int i = 0; i < tbl_n; i++) {
	    Hue_table_t[i] = (Hue_table[i] + gain_h + 768) % 768;
	    Sat_table_t[i] = Sat_table[i] + gain_s;
	    Val_table_t[i] = Val_table[i] + gain_v;
	}
    }

    //=========================================================================
    // �N���G���table��
    //=========================================================================
    for (int i = 0; i < tbl_n; i++) {
	sg_HSV->Cells[1][i + 1] = FloatToStr((double) Hue_table_t[i] / 768 * 360);
	sg_HSV->Cells[2][i + 1] = FloatToStr((double) (Sat_table_t[i]) / 32);
	sg_HSV->Cells[3][i + 1] = Val_table_t[i];
    }
    for (int i = 0; i < 3; i++) {
	sg_6HSV->Cells[i][0] = sg_HSV->Cells[i + 1][1];	//Red
	sg_6HSV->Cells[i][1] = sg_HSV->Cells[i + 1][5];	//Yellow
	sg_6HSV->Cells[i][2] = sg_HSV->Cells[i + 1][9];	//Green
	sg_6HSV->Cells[i][3] = sg_HSV->Cells[i + 1][13];	//Cyan
	sg_6HSV->Cells[i][4] = sg_HSV->Cells[i + 1][17];	//Blue
	sg_6HSV->Cells[i][5] = sg_HSV->Cells[i + 1][21];	//Magenta
	sg_6HSV->Cells[i][6] = sg_HSV->Cells[i + 1][tbl_idx + 1];
    }
    //=========================================================================
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2::sb_Hue_gainChange(TObject * Sender)
{
    show_gain(sb_Hue_gain->Position, sb_Sat_gain->Position, sb_Val_gain->Position);
}

//---------------------------------------------------------------------------





