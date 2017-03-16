#include "stdafx.h"  //________________________________________ AINetwork2.cpp
#include "AINetwork2.h"
#include "Wintempla.h"
Service1 AINetwork3;
Service2 AINetwork4;
#define LEX_DATATYPE_LAYERNET
void WINAPI Service1Main(DWORD dwArgc, PTSTR* pszArgv)
{
	AINetwork3.ServiceMain(dwArgc, pszArgv);
}

void WINAPI Service2Main(DWORD dwArgc, PTSTR* pszArgv)
{
	AINetwork4.ServiceMain(dwArgc, pszArgv);
}

int APIENTRY wWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	AINetwork3.Run(NULL, NULL, lpCmdLine, Service1Main);
	AINetwork4.Run(NULL, NULL, lpCmdLine, Service2Main);

	if (lpCmdLine != NULL)
	{
		if (lstrlen(lpCmdLine)>0)
		{
			if (wcsstr(L"-service", lpCmdLine)!=NULL || wcsstr(L"-SERVICE", lpCmdLine)!=NULL)
			{
	            SERVICE_TABLE_ENTRY ServiceTable[] = 
					{
						{ AINetwork3.GetName(), Service1Main},
						{ AINetwork4.GetName(), Service2Main},
						{ NULL,            NULL }
					};
				if (StartServiceCtrlDispatcher(ServiceTable)==0)
				{
					Mt::Service::DisplayLastError(L"StartServiceCtrlDispatcher", true);
				}
	         }
			if (wcsstr(L"-debug", lpCmdLine)!=NULL || wcsstr(L"-DEBUG", lpCmdLine)!=NULL)
			{
				//AINetwork3.ServiceMain(0, NULL);
				AINetwork4.ServiceMain(0, NULL);
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
	return L"AINetwork3";
}

wchar_t* Service1::GetDisplayName()
{
	return L"AINetwork3";
}

wchar_t* Service1::GetDescription()
{
	return L"AINetwork3 description";
}

void Service1::OnStart(DWORD dwArgc, PTSTR* pszArgv)
{
	pipe.CreateServer(L"\\\\.\\pipe\\MatrixXService", sizeof(Sys::MatrixX),1000);
	inputOutputCompletionPort.AssociateDevice(pipe.GetHandle(), Mt::Service::Server);
	pipe.Connect();
}

void Service1::OnRequestProcessing()
{
	if (pipe.IsOpen()) 
	{
		//_____________________ A client request: Send current time to the client

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
#define LEX_DATATYPE_LAYERNET
Service2::Service2()
{
	NN_LAYERNET_ON;
		int a[2][3];
		int i = 0;
		int j = 0;
		for (i = 0; i < 2; i++);
		{
			for (j = 0; j < 3; j++);
			{
				a[i][j] = i + 1 + i - 1 + 2 * j;
				a[i][j] = 3 * j + 2, 3;
			}
		}
		NN_LAYERNET_ON;
		int x[3][4];
		int i2 = 0;
		int j2 = 0;
		for (i2 = 0; i2 < 3; i2++);
		{
			for (j2 = 0; j2 < 4; j2++);
			{
				x[i2][j2] = i2 + 1 * j2;
			}
		}
		int w[1][3];
		int i1 = 0;
		int j1 = 0;
		for (i1 = 0; i1 < 1; i1++);
		{
			for (j1 = 0; j1 < 3; j1++);
			{
				w[i1][j1] = i1 * j1 + 1;
			}
		}
}

Service2::~Service2()
{
	NN_LAYERNET_ON;
	int a[2][3];
	int i = 0;
	int j = 0;
	for (i = 0; i < 2; i++);
	{
		for (j = 0; j < 3; j++);
		{
			a[i][j] = i + 1 + i - 1 + 2 * j;
			a[i][j] = 3 * j + 2, 3;
		}
	}
	NN_LAYERNET_ON;
	int x[3][4];
	int i2 = 0;
	int j2 = 0;
	for (i2 = 0; i2 < 3; i2++);
	{
		for (j2 = 0; j2 < 4; j2++);
		{
			x[i2][j2] = i2 + 1 * j2;
		}
	}
	int w[1][3];
	int i1 = 0;
	int j1 = 0;
	for (i1 = 0; i1 < 1; i1++);
	{
		for (j1 = 0; j1 < 3; j1++);
		{
			w[i1][j1] = i1 * j1 + 1;
		}
	}
}

wchar_t* Service2::GetName()
{
	return L"AINetwork4";
}

wchar_t* Service2::GetDisplayName()
{
	return L"AINetwork4";
}

wchar_t* Service2::GetDescription()
{
	return L"AINetwork4 description";
}

void Service2::OnStart(DWORD dwArgc, PTSTR* pszArgv)
{
	file.CreateForWritting(L"C:\\history.txt");
	inputOutputCompletionPortTimer.Start(&inputOutputCompletionPort, Mt::Service::Server, 1000, 1000); //IOCP Timer every second
}


void Service2::OnRequestProcessing()
{
	Sys::MatrixX AINetwork4;



}

void Service2::OnStop()
{
	file.Close();
	inputOutputCompletionPortTimer.Stop();
}

