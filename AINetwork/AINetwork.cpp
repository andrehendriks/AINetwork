#include "stdafx.h"  //________________________________________ AINetwork.cpp
#include "AINetwork.h"

Service1 service1;
Service2 service2;

void WINAPI Service1Main(DWORD dwArgc, PTSTR* pszArgv)
{
	service1.ServiceMain(dwArgc, pszArgv);
}

void WINAPI Service2Main(DWORD dwArgc, PTSTR* pszArgv)
{
	service2.ServiceMain(dwArgc, pszArgv);
}

int APIENTRY wWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	service1.Run(NULL, NULL, lpCmdLine, Service1Main);
	service2.Run(NULL, NULL, lpCmdLine, Service2Main);

	if (lpCmdLine != NULL)
	{
		if (lstrlen(lpCmdLine)>0)
		{
			if (wcsstr(L"-service", lpCmdLine)!=NULL || wcsstr(L"-SERVICE", lpCmdLine)!=NULL)
			{
	            SERVICE_TABLE_ENTRY ServiceTable[] = 
					{
						{service1.GetName(), Service1Main},
						{service2.GetName(), Service2Main},
						{ NULL,            NULL }
					};
				if (StartServiceCtrlDispatcher(ServiceTable)==0)
				{
					Mt::Service::DisplayLastError(L"StartServiceCtrlDispatcher", true);
				}
	         }
			if (wcsstr(L"-debug", lpCmdLine)!=NULL || wcsstr(L"-DEBUG", lpCmdLine)!=NULL)
			{
				//service1.ServiceMain(0, NULL);
				service2.ServiceMain(0, NULL);
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
	return L"Service1";
}

wchar_t* Service1::GetDisplayName()
{
	return L"Service1";
}

wchar_t* Service1::GetDescription()
{
	return L"Service1 description";
}

void Service1::OnStart(DWORD dwArgc, PTSTR* pszArgv)
{
	pipe.CreateServer(L"\\\\.\\pipe\\TimeService", sizeof(Sys::Time), 1000); 
	inputOutputCompletionPort.AssociateDevice(pipe.GetHandle(), Mt::Service::Server);
	pipe.Connect();
}

void Service1::OnRequestProcessing()
{
	if (pipe.IsOpen()) 
	{
		//_____________________ A client request: Send current time to the client
		Sys::Time st;
		DWORD numBytes;

		pipe.Write(&st, sizeof(st), &numBytes);
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
}

Service2::~Service2()
{
}

wchar_t* Service2::GetName()
{
	return L"Service2";
}

wchar_t* Service2::GetDisplayName()
{
	return L"Service2";
}

wchar_t* Service2::GetDescription()
{
	return L"Service2 description";
}

void Service2::OnStart(DWORD dwArgc, PTSTR* pszArgv)
{
	file.CreateForWritting(L"C:\\history.txt");
	inputOutputCompletionPortTimer.Start(&inputOutputCompletionPort, Mt::Service::Server, 1000, 1000); //IOCP Timer every second
}

void Service2::OnRequestProcessing()
{
	Sys::Time time;
	wchar_t text[256];
	_snwprintf_s(text, 256, _TRUNCATE, L"%02d:%02d:%02d\r\n", time.wHour, time.wMinute, time.wSecond);
	file.WriteText(text);
}

void Service2::OnStop()
{
	file.Close();
	inputOutputCompletionPortTimer.Stop();
}

