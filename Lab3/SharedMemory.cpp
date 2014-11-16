#include "stdafx.h"
#include "SharedMemory.h"


SharedMemory::SharedMemory(LPCWSTR name,LPCWSTR mutex)
{
	bool exists = true;
	hMap = OpenFileMapping(FILE_MAP_ALL_ACCESS,false,name);

	if(hMap == NULL )
	{
		
		hMutex =	CreateMutex(NULL,false, mutex);
		hMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0,256,name);
	}
	else
	{
		hMutex =	OpenMutex(MUTEX_ALL_ACCESS,false,mutex);
	}
	data =  MapViewOfFile(hMap,FILE_MAP_ALL_ACCESS,0,0,256);
	

}


SharedMemory::~SharedMemory(void)
{
	 UnmapViewOfFile(data);
	 CloseHandle(hMap);
}


char timeBuffer[80];

char* CurrentTime()
{
	struct tm * timeinfo = new tm;
	time_t rawtime;
	
	
	time(&rawtime);
	localtime_s(timeinfo,&rawtime);
	strftime(timeBuffer,80,"%I:%M:%S",timeinfo);
	return timeBuffer;
}

void* SharedMemory::Get()
{
	void* localData;
	WaitForSingleObject(hMutex,INFINITE);
	localData = data;
	std::cout << CurrentTime() <<  " Get " << std::endl;
	ReleaseMutex(hMutex);

	return localData;
}




void SharedMemory::Set(void* val)
{
	WaitForSingleObject(hMutex,INFINITE);
	memcpy(data,val,255);
	std::cout << CurrentTime() <<  " Set " << std::endl;
	Sleep(10000);
	ReleaseMutex(hMutex);
	std::cout << CurrentTime() <<  " Exit set " << std::endl;

}