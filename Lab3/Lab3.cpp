// Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SharedMemory.h"

/*char timeBuffer[80];

char* CurrentTime()
{
	struct tm * timeinfo = new tm;
	time_t rawtime;
	
	
	time(&rawtime);
	localtime_s(timeinfo,&rawtime);
	strftime(timeBuffer,80,"%I:%M:%S",timeinfo);
	return timeBuffer;
}*/

int main()
{
	
	

	SharedMemory*  memory = new SharedMemory(L"My",L"MMutex");
	DWORD id = GetCurrentProcessId();
	DWORD* data;
	while (true)
	{
		std::cout << id << ": " << CurrentTime()  << " TryEnter " << std::endl;
		memory->Set(&id);
	//	std::cout << id << ": " << CurrentTime()  << " Set " << id << std::endl;
		data = (DWORD*)memory->Get();
		//std::cout << id << ": " << CurrentTime()  << " Get " << *data << std::endl;
	}
	return 0;
}

