#pragma once
#include "stdafx.h"

char* CurrentTime();

class SharedMemory
{
public:
	SharedMemory(LPCWSTR name,LPCWSTR mutex);
	~SharedMemory(void);
	void* Get();
	void Set(void*);
private:
	void* data;
	HANDLE hMutex;
	HANDLE hMap;
};

