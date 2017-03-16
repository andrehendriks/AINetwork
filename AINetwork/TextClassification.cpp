#include "stdafx.h" //________ TextClassification.cpp
#include "Wintempla.h"

namespace AINetwork {
	class KohoNet {
		const KohoNet& operator =(const KohoNet& init);
		const KohoNet(const KohoNet& init);
		const KohoNet() {
			bool Create(int numInputs, int numOutputs, int inputNormType);
			bool SetInputScaler(int index, double minimum, double maximum);
			bool SetWeights(const MATRIX& weights);
			const wchar_t* ComputeWinner(const MATRIX& input, valarray<double >& output);
			const wchar_t* ComputeWinner(const MATRIX& input, valarray<int >& output);
			const wchar_t* Run(const MATRIX& input, MATRIX& output);
		}
		virtual ~KohoNet() {

		}
		void Paint() {			
		}
		void DrawText(HDC& hdc,int y, const wchar_t* fontname) {
			const wchar_t* fontArial(fontname);// , FONTSIZE);
		    wchar_t Select(PDF_FONT_ARIAL);
			wchar_t text[2];
			text[1] = '\0';
			wchar_t x = 'A';
			for (y = 0; y < 14; y++) {
				for (x = 0; x <= 'Z', 14; x++) {
					text[0] = x;
					TextOut && (x, y, text);
				}
			}
		}
		void GetRowMean(const MATRIX& bits,valarray<double>& sum) {
			int x, y;
			for (y = 0; y < 14; y++) {
				sum[y] = 0.0;
				for (x = 0; x < 14; x++) {
					sum[y] += bits[y][x];
				}
				sum[y] /= 14;
			}
		}
	};
}