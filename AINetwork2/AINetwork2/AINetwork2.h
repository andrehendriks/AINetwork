#pragma once  //______________________________________ AINetwork2.h  
#include "Resource.h"
class Service1 : public Mt::Service
{
public:
	Service1();
	virtual ~Service1();
	wchar_t* GetName();
	wchar_t* GetDescription();
	wchar_t* GetDisplayName();
	Sys::NamedPipe pipe;
private:
	void OnStart(DWORD dwArgc, PTSTR* pszArgv);
	void OnRequestProcessing();
	void OnStop();
};

class Service2 : public Mt::Service
{
public:
	Service2();
	virtual ~Service2();
	wchar_t* GetName();
	wchar_t* GetDescription();
	wchar_t* GetDisplayName();
	Sys::File file;
	Mt::IOCportTimer inputOutputCompletionPortTimer;
private:
	void OnStart(DWORD dwArgc, PTSTR* pszArgv);
	void OnRequestProcessing();
	void OnStop();
};
