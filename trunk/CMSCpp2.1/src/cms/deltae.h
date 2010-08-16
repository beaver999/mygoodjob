#ifndef DELTAEH
#define DELTAEH

//C�t�Τ��
//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���


namespace cms {
    class DeltaE {
      private:
	const Lab_ptr Lab1, Lab2;
	const bool adaptedToD65;
	double cie2000DeltaE;
	double cieDeltaE;
      public:
	 DeltaE(const Lab_ptr Lab1, const Lab_ptr Lab2);
	 DeltaE(const Lab_ptr Lab1, const Lab_ptr Lab2, bool adaptedToD65);
	static double CIE2000DeltaE(const Lab_ptr Lab1, const Lab_ptr Lab2,
				    double Kl, double Kc, double Kh);
	double getCIE2000Deltaab();
	double getCIE2000DeltaE();
      protected:
	static void calculateCIE2000Parameters(const Lab_ptr Lab1,
					       const Lab_ptr Lab2, double Kl, double Kc, double Kh);
	static double RADIANES(double deg);
	double_array CIE2000DeltaLCh;
	double_array CIE2000Parameters;
      private:
	static double_array _CIE2000Parameters;
	static double_array _CIE2000DeltaLCH;
    };
}
#endif

