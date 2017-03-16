#include "stdafx.h"  //________________________________________ AINetwork.cpp
#include "AINetwork.h"
#include "Wintempla.h"
Service1 AINetwork1;
Service2 AINetwork2;

void WINAPI Service1Main(DWORD dwArgc, PTSTR* pszArgv)
{
	AINetwork1.ServiceMain(dwArgc, pszArgv);
}

void WINAPI Service2Main(DWORD dwArgc, PTSTR* pszArgv)
{
	AINetwork2.ServiceMain(dwArgc, pszArgv);
}

int APIENTRY wWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	AINetwork1.Run(NULL, NULL, lpCmdLine, Service1Main);
	AINetwork2.Run(NULL, NULL, lpCmdLine, Service2Main);

	if (lpCmdLine != NULL)
	{
		if (lstrlen(lpCmdLine)>0)
		{
			if (wcsstr(L"-service", lpCmdLine)!=NULL || wcsstr(L"-SERVICE", lpCmdLine)!=NULL)
			{
	            SERVICE_TABLE_ENTRY ServiceTable[] = 
					{
						{ AINetwork1.GetName(), Service1Main},
						{ AINetwork2.GetName(), Service2Main},
						{ NULL,            NULL }
					};
				if (StartServiceCtrlDispatcher(ServiceTable)==0)
				{
					Mt::Service::DisplayLastError(L"StartServiceCtrlDispatcher", true);
				}
	         }
			if (wcsstr(L"-debug", lpCmdLine)!=NULL || wcsstr(L"-DEBUG", lpCmdLine)!=NULL)
			{
				//AINetwork1.ServiceMain(0, NULL);
				AINetwork2.ServiceMain(0, NULL);
			}
		}
	}
 	return 0;
}

//_____________________________________________ Service1 (Returns current time to the client)
Service1::Service1()
{
}

Service1::~Service1()
{
}

wchar_t* Service1::GetName()
{
	return L"AINetwork1";
}

wchar_t* Service1::GetDisplayName()
{
	return L"AINetwork1";
}

wchar_t* Service1::GetDescription()
{
	return L"AINetwork1 description";
}

void Service1::OnStart(DWORD dwArgc, PTSTR* pszArgv)
{
	pipe.CreateServer(L"\\\\.\\pipe\\MatixXService", sizeof(Sys::MatrixX), 1000); 
	inputOutputCompletionPort.AssociateDevice(pipe.GetHandle(), Mt::Service::Server);
	pipe.Connect();
}

void Service1::OnRequestProcessing()
{
	if (pipe.IsOpen()) 
	{
		//_____________________ A client request: Send current time to the client
		Sys::MatrixX AINetwork2;


		pipe.Flush();
		pipe.Disconnect();

		//___________________ Allow another client to connect 
		pipe.Connect();
	} 
}

void Service1::OnStop()
{
	pipe.Close();
}

//_____________________________________________ Service2 (Creates a file with the current time)
Service2::Service2()
{
	class Adc {
		const Adc(void) {
			bool IsEvent(int notification); {
				bool IsRecording();
				bool Stop();
				double GetBufferDuration();
				bool isSignDifferent(int x, int y);
				void GetFrequency(LPARAM lParam, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2);
				void GetFrequency(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2);
				void GetMaxLevel(LPARAM lParam, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2);
				void GetMaxLevel(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2);
				void GetPhaseDifference(LPARAM lParam, int channels, int& out_differenceCount);
				void GetPhaseDifference(LPSTR buffer, unsigned int bufferSize, int channels, int& out_differenceCount);
				void GetRmsLevel(LPARAM lParam, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2);
				void GetRmsLevel(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2);
				void GetZeroCrossings(LPARAM lParam, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2);
				void GetZeroCrossings(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2);
			}
		}
		virtual ~Adc(void) {
			void SetIDataTransfer(IDataTransferManagerInterop* idataTransfer);
			void DeleteBuffers(void);
			wchar_t* Start(unsigned int sampleRate, int channels, int bitsPerSample, unsigned int bufferSize);
		}
	};
	class IDataTransfer {
		virtual void OnData(LPARAM lParam) = 0;
		virtual void OnDataStarted() = 0;
		virtual void OnDataStopped() = 0;
	};
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
		void DrawText(HDC& hdc, int y, const wchar_t* fontname) {
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
		void GetRowMean(const MATRIX& bits, valarray<double>& sum) {
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
	class LayerNetC {
		const LayerNetC& operator =(const LayerNetC& init);
		const LayerNetC(const LayerNetC& init);
		const LayerNetC(void) {
			int netand = (2, 0, 0, 1);
		}
		virtual	~LayerNetC(void) {
			NN_LAYERNETC_ON;
			int w[1][3];
			int i1 = 0;
			int j1 = 0;
			for (i1 = 0; i1 < 1; i1++) {
				for (j1 = 0; j1 < 3; j1++) {
					LEX_FUNC_LAYERNETC_SET_OUTPUT_SCALER & (20, 20, 10);
					LEX_FUNC_LAYERNETC_SET_WEIGHTS && (3, w);
				}
			}
			int x1[1][4];
			int i2 = 0;
			int j2 = 0;
			for (i2 = 0; i2 < 1; i2++) {
				for (j2 = 0; j2 < 4; j2++) {
					LEX_FUNC_LAYERNETC_SET_INPUT_SCALER & (0, 0, 1, 1);
				}
			}
			int x2[1][4];
			int i3 = 0;
			int j3 = 0;
			for (i3 = 0; i3 < 1; i3++) {
				for (j3 = 0; j3 < 4; j3++) {
					LEX_FUNC_LAYERNETC_SET_INPUT_SCALER & (0, 1, 0, 1);
				}
			}
		}
	};
	class LayerNetC1 {
		const LayerNetC1& operator =(const LayerNetC1& init);
		const LayerNetC1(const LayerNetC1& init);
		const LayerNetC1() {
		}
		~LayerNetC1() {
			NN_LAYERNETC_ON;
			int netxor = (2, 0, 0, 1);
			int x1[1][4];
			int i29 = 0;
			int j29 = 0;
			for (i29 = 0; i29 < 1; i29++);
			{
				for (j29 = 0; j29 < 4; j29++);
				{
					LEX_FUNC_LAYERNETC_SET_INPUT_SCALER & (0, 0, 1, 1);
				}
			}
			int x2[1][4];
			int i30 = 0;
			int j30 = 0;
			for (i30 = 0; i30 < 1; i30++);
			{
				for (j30 = 0; j30 < 4; j30++);
				{
					LEX_FUNC_LAYERNETC_SET_INPUT_SCALER & (0, 1, 1, 1);
				}
			}
			int z[1][4];
			int i31 = 0;
			int j31 = 0;
			for (i31 = 0; i31 < 1; i31++);
			{
				for (j31 = 0; j31 < 4; j31++);
				{
					LEX_FUNC_LAYERNETC_SET_OUTPUT_SCALER & (0, 1, 1, 0);
				}
			}
			LEX_FUNC_LAYERNETC_RUN &&& (x1, x2, z);
		}
	};
	class LayerNetC2 {
		const LayerNetC2& operator =(const LayerNetC2& init);
		const LayerNetC2(const LayerNetC2& init);
		const LayerNetC2(void) {
			int netor = (2, 0, 0, 1);
		}
		virtual	~LayerNetC2(void) {
			NN_LAYERNETC_ON;
			int w[1][3];
			int i1 = 0;
			int j1 = 0;
			for (i1 = 0; i1 < 1; i1++) {
				for (j1 = 0; j1 < 3; j1++) {
					LEX_FUNC_LAYERNETC_SET_OUTPUT_SCALER & (20, 20, 10);
					LEX_FUNC_LAYERNETC_SET_WEIGHTS && (3, w);
				}
			}
			int x1[1][4];
			int i2 = 0;
			int j2 = 0;
			for (i2 = 0; i2 < 1; i2++) {
				for (j2 = 0; j2 < 4; j2++) {
					LEX_FUNC_LAYERNETC_SET_INPUT_SCALER & (0, 0, 1, 1);
				}
			}
			int x2[1][4];
			int i3 = 0;
			int j3 = 0;
			for (i3 = 0; i3 < 1; i3++) {
				for (j3 = 0; j3 < 4; j3++) {
					LEX_FUNC_LAYERNET_SET_INPUT_SCALER & (0, 1, 0, 1);
				}
			}
		}
	};
	class preprocessing {

		void pre_proccessing() {
			int x1[200];
			int i21 = 0;
			for (i21 = 0; i21 < 200; i21++);
			{
				LEX_FUNC_LAYERNETC_AUTO_SET_INPUT_SCALER && (-1.0, 1.0);
			}
			int y025[200];
			int y4[200];
			int i22 = 0;
			for (i22 = 0; i22 < 200; i22++);
			{
				if (x1[i22] >= 0.0)
				{
					y025[i22] = pow(x1[i22], 0.25);
					y4[i22] = pow(x1[i22], 4.0);
				}
				else
				{
					y025[i22] = -pow(-x1[i22], 0.25);
					y4[i22] = -pow(-x1[i22], 4.0);
				}
			}
			LEX_FUNC_LAYERNETC_RUN && (x1);
		}
	};
	class LayerNetC3
	{
		const LayerNetC3& operator =(const LayerNetC3& init);
		const LayerNetC3(const LayerNetC3& init);
		const LayerNetC3() {
			bool Create(int inputCount, int hidden1Count, int hidden2Count, int outputCount);
			bool SetInputScaler(int index, double minimum, double maximum);
			bool SetOutputScaler(int index, double minimum, double maximum);
			bool Run(const MATRIXC& x, MATRIXC& w);

		}
		~LayerNetC3() {
			NN_LAYERNETC_ON;
			int net1 = (2, 0, 0, 1);
			LEX_FUNC_LAYERNETC_CREATE & (1, 6);
			int x[1][6];
			int i = 0;
			int j = 0;
			for (i = 0; i < 1; i++);
			{
				for (j = 0; j < 6; j++);
				{
					LEX_FUNC_LAYERNETC_AUTO_SET_INPUT_SCALER & (0, 1);
					LEX_FUNC_LAYERNETC_AUTO_SET_OUTPUT_SCALER && (0.0, 1.0);
				}
			}
			LEX_FUNC_LAYERNETC_SET_WEIGHTS && (3, x);
			int w[1][3];
			int i1 = 0;
			int j1 = 0;
			for (i1 = 0; i1 < 1; i1++);
			{
				for (j1 = 0; j1 < 3; j1++);
				{
					LEX_FUNC_LAYERNETC_SET_OUTPUT_SCALER && (20, 20, 10);
				}
			}
			LEX_FUNC_LAYERNETC_RUN && (x);
			LEX_FUNC_LAYERNETC_RUN && (w);
		}
	};
	class ProbNet {
		const ProbNet& operator =(const ProbNet& init);
		const ProbNet(const ProbNet& init);
		const ProbNet() {
			void SetWeights(const valarray<double >& weights);
			const wchar_t* Run(const MATRIX& TsI, const MATRIX& TsT, const MATRIX& x, MATRIX& w);
		}
		~ProbNet() {
			NN_LAYERNET_ON;
			int net17 = (5, 5, 5, 3);
			int netT = (5, 5, 5, 4);
			int netW = (5, 0, 0, 1);
			int x[3][5];
			int i18 = 0;
			int j18 = 0;
			for (i18 = 0; i18 < 3; i18++);
			{
				for (j18 = 0; j18 < 5; j18++);
				{
					LEX_FUNC_LAYERNET_AUTO_SET_INPUT_SCALER & (1, 10);
				}
			}
			int TsI[3][5];
			int i19 = 0;
			int j19 = 0;
			for (i19 = 0; i19 < 3; i19++);
			{
				for (j19 = 0; j19 < 5; j19++);
				{
					LEX_FUNC_LAYERNET_AUTO_SET_INPUT_SCALER & (-1, 9);
				}
			}
			int TsT[3][5];
			int i21 = 0;
			int j21 = 0;
			for (i21 = 0; i21 < 3; i21++);
			{
				for (j21 = 0; j21 < 5; j21++);
				{
					LEX_FUNC_LAYERNETC_AUTO_SET_INPUT_SCALER & (-1, 9);
				}
			}
			int W[5];
			int i20 = 0;
			for (i20 = 0; i20 < 5; i20++);
			{
				LEX_FUNC_LAYERNET_AUTO_SET_INPUT_SCALER & (0, 4);
				LEX_FUNC_LAYERNET_AUTO_SET_OUTPUT_SCALER & (0, 4);
			}
			LEX_FUNC_LAYERNET_RUN &&& (x, TsI, W);
		}
	};
}

Service2::~Service2()
{
	class Adc {
		const Adc(void) {
			bool IsEvent(int notification); {
				bool IsRecording();
				bool Stop();
				double GetBufferDuration();
				bool isSignDifferent(int x, int y);
				void GetFrequency(LPARAM lParam, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2);
				void GetFrequency(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2);
				void GetMaxLevel(LPARAM lParam, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2);
				void GetMaxLevel(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2);
				void GetPhaseDifference(LPARAM lParam, int channels, int& out_differenceCount);
				void GetPhaseDifference(LPSTR buffer, unsigned int bufferSize, int channels, int& out_differenceCount);
				void GetRmsLevel(LPARAM lParam, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2);
				void GetRmsLevel(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2);
				void GetZeroCrossings(LPARAM lParam, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2);
				void GetZeroCrossings(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2);
			}
		}
		virtual ~Adc(void) {
			void SetIDataTransfer(IDataTransferManagerInterop* idataTransfer);
			void DeleteBuffers(void);
			wchar_t* Start(unsigned int sampleRate, int channels, int bitsPerSample, unsigned int bufferSize);
		}
	};
	class IDataTransfer {
		virtual void OnData(LPARAM lParam) = 0;
		virtual void OnDataStarted() = 0;
		virtual void OnDataStopped() = 0;
	};
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
		void DrawText(HDC& hdc, int y, const wchar_t* fontname) {
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
		void GetRowMean(const MATRIX& bits, valarray<double>& sum) {
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
	class LayerNetC {
		const LayerNetC& operator =(const LayerNetC& init);
		const LayerNetC(const LayerNetC& init);
		const LayerNetC(void) {
			int netand = (2, 0, 0, 1);
		}
		virtual	~LayerNetC(void) {
			NN_LAYERNETC_ON;
			int w[1][3];
			int i1 = 0;
			int j1 = 0;
			for (i1 = 0; i1 < 1; i1++) {
				for (j1 = 0; j1 < 3; j1++) {
					LEX_FUNC_LAYERNETC_SET_OUTPUT_SCALER & (20, 20, 10);
					LEX_FUNC_LAYERNETC_SET_WEIGHTS && (3, w);
				}
			}
			int x1[1][4];
			int i2 = 0;
			int j2 = 0;
			for (i2 = 0; i2 < 1; i2++) {
				for (j2 = 0; j2 < 4; j2++) {
					LEX_FUNC_LAYERNETC_SET_INPUT_SCALER & (0, 0, 1, 1);
				}
			}
			int x2[1][4];
			int i3 = 0;
			int j3 = 0;
			for (i3 = 0; i3 < 1; i3++) {
				for (j3 = 0; j3 < 4; j3++) {
					LEX_FUNC_LAYERNETC_SET_INPUT_SCALER & (0, 1, 0, 1);
				}
			}
		}
	};
	class LayerNetC1 {
		const LayerNetC1& operator =(const LayerNetC1& init);
		const LayerNetC1(const LayerNetC1& init);
		const LayerNetC1() {
		}
		~LayerNetC1() {
			NN_LAYERNETC_ON;
			int netxor = (2, 0, 0, 1);
			int x1[1][4];
			int i29 = 0;
			int j29 = 0;
			for (i29 = 0; i29 < 1; i29++);
			{
				for (j29 = 0; j29 < 4; j29++);
				{
					LEX_FUNC_LAYERNETC_SET_INPUT_SCALER & (0, 0, 1, 1);
				}
			}
			int x2[1][4];
			int i30 = 0;
			int j30 = 0;
			for (i30 = 0; i30 < 1; i30++);
			{
				for (j30 = 0; j30 < 4; j30++);
				{
					LEX_FUNC_LAYERNETC_SET_INPUT_SCALER & (0, 1, 1, 1);
				}
			}
			int z[1][4];
			int i31 = 0;
			int j31 = 0;
			for (i31 = 0; i31 < 1; i31++);
			{
				for (j31 = 0; j31 < 4; j31++);
				{
					LEX_FUNC_LAYERNETC_SET_OUTPUT_SCALER & (0, 1, 1, 0);
				}
			}
			LEX_FUNC_LAYERNETC_RUN &&& (x1, x2, z);
		}
	};
	class LayerNetC2 {
		const LayerNetC2& operator =(const LayerNetC2& init);
		const LayerNetC2(const LayerNetC2& init);
		const LayerNetC2(void) {
			int netor = (2, 0, 0, 1);
		}
		virtual	~LayerNetC2(void) {
			NN_LAYERNETC_ON;
			int w[1][3];
			int i1 = 0;
			int j1 = 0;
			for (i1 = 0; i1 < 1; i1++) {
				for (j1 = 0; j1 < 3; j1++) {
					LEX_FUNC_LAYERNETC_SET_OUTPUT_SCALER & (20, 20, 10);
					LEX_FUNC_LAYERNETC_SET_WEIGHTS && (3, w);
				}
			}
			int x1[1][4];
			int i2 = 0;
			int j2 = 0;
			for (i2 = 0; i2 < 1; i2++) {
				for (j2 = 0; j2 < 4; j2++) {
					LEX_FUNC_LAYERNETC_SET_INPUT_SCALER & (0, 0, 1, 1);
				}
			}
			int x2[1][4];
			int i3 = 0;
			int j3 = 0;
			for (i3 = 0; i3 < 1; i3++) {
				for (j3 = 0; j3 < 4; j3++) {
					LEX_FUNC_LAYERNET_SET_INPUT_SCALER & (0, 1, 0, 1);
				}
			}
		}
	};
	class preprocessing {

		void pre_proccessing() {
			int x1[200];
			int i21 = 0;
			for (i21 = 0; i21 < 200; i21++);
			{
				LEX_FUNC_LAYERNETC_AUTO_SET_INPUT_SCALER && (-1.0, 1.0);
			}
			int y025[200];
			int y4[200];
			int i22 = 0;
			for (i22 = 0; i22 < 200; i22++);
			{
				if (x1[i22] >= 0.0)
				{
					y025[i22] = pow(x1[i22], 0.25);
					y4[i22] = pow(x1[i22], 4.0);
				}
				else
				{
					y025[i22] = -pow(-x1[i22], 0.25);
					y4[i22] = -pow(-x1[i22], 4.0);
				}
			}
			LEX_FUNC_LAYERNETC_RUN && (x1);
		}
	};
	class LayerNetC3
	{
		const LayerNetC3& operator =(const LayerNetC3& init);
		const LayerNetC3(const LayerNetC3& init);
		const LayerNetC3() {
			bool Create(int inputCount, int hidden1Count, int hidden2Count, int outputCount);
			bool SetInputScaler(int index, double minimum, double maximum);
			bool SetOutputScaler(int index, double minimum, double maximum);
			bool Run(const MATRIXC& x, MATRIXC& w);

		}
		~LayerNetC3() {
			NN_LAYERNETC_ON;
			int net1 = (2, 0, 0, 1);
			LEX_FUNC_LAYERNETC_CREATE & (1, 6);
			int x[1][6];
			int i = 0;
			int j = 0;
			for (i = 0; i < 1; i++);
			{
				for (j = 0; j < 6; j++);
				{
					LEX_FUNC_LAYERNETC_AUTO_SET_INPUT_SCALER & (0, 1);
					LEX_FUNC_LAYERNETC_AUTO_SET_OUTPUT_SCALER && (0.0, 1.0);
				}
			}
			LEX_FUNC_LAYERNETC_SET_WEIGHTS && (3, x);
			int w[1][3];
			int i1 = 0;
			int j1 = 0;
			for (i1 = 0; i1 < 1; i1++);
			{
				for (j1 = 0; j1 < 3; j1++);
				{
					LEX_FUNC_LAYERNETC_SET_OUTPUT_SCALER && (20, 20, 10);
				}
			}
			LEX_FUNC_LAYERNETC_RUN && (x);
			LEX_FUNC_LAYERNETC_RUN && (w);
		}
	};
	class ProbNet {
		const ProbNet& operator =(const ProbNet& init);
		const ProbNet(const ProbNet& init);
		const ProbNet() {
			void SetWeights(const valarray<double >& weights);
			const wchar_t* Run(const MATRIX& TsI, const MATRIX& TsT, const MATRIX& x, MATRIX& w);
		}
		~ProbNet() {
			NN_LAYERNET_ON;
			int net17 = (5, 5, 5, 3);
			int netT = (5, 5, 5, 4);
			int netW = (5, 0, 0, 1);
			int x[3][5];
			int i18 = 0;
			int j18 = 0;
			for (i18 = 0; i18 < 3; i18++);
			{
				for (j18 = 0; j18 < 5; j18++);
				{
					LEX_FUNC_LAYERNET_AUTO_SET_INPUT_SCALER & (1, 10);
				}
			}
			int TsI[3][5];
			int i19 = 0;
			int j19 = 0;
			for (i19 = 0; i19 < 3; i19++);
			{
				for (j19 = 0; j19 < 5; j19++);
				{
					LEX_FUNC_LAYERNET_AUTO_SET_INPUT_SCALER & (-1, 9);
				}
			}
			int TsT[3][5];
			int i21 = 0;
			int j21 = 0;
			for (i21 = 0; i21 < 3; i21++);
			{
				for (j21 = 0; j21 < 5; j21++);
				{
					LEX_FUNC_LAYERNETC_AUTO_SET_INPUT_SCALER & (-1, 9);
				}
			}
			int W[5];
			int i20 = 0;
			for (i20 = 0; i20 < 5; i20++);
			{
				LEX_FUNC_LAYERNET_AUTO_SET_INPUT_SCALER & (0, 4);
				LEX_FUNC_LAYERNET_AUTO_SET_OUTPUT_SCALER & (0, 4);
			}
			LEX_FUNC_LAYERNET_RUN &&& (x, TsI, W);
		}
	};
}

wchar_t* Service2::GetName()
{
	return L"AINetwork2";
}

wchar_t* Service2::GetDisplayName()
{
	return L"AINetwork2";
}

wchar_t* Service2::GetDescription()
{
	return L"AINetwork2 description";
}

void Service2::OnStart(DWORD dwArgc, PTSTR* pszArgv)
{
	file.CreateForWritting(L"C:\\history.txt");
	inputOutputCompletionPortTimer.Start(&inputOutputCompletionPort, Mt::Service::Server, 1000, 1000); //IOCP Timer every second
}

void Service2::OnRequestProcessing()
{
	Sys::MatrixX AINetwork2;
}

void Service2::OnStop()
{
	file.Close();
	inputOutputCompletionPortTimer.Stop();
}

