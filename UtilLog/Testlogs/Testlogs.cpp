// Testlogs.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include "../UtilLog/UtilLogShell.h"
using namespace std;
#pragma comment(lib, "F:\\Git\\UtilLog\\Debug\\UtilLog.lib")

DWORD WINAPI Fun1(LPVOID lpParamter)
{
	int *pThreadId = (int*)lpParamter;
	while (1) 
	{
		bool b = 1;
		char c = 'a';
		signed short ss = 121;
		unsigned short us = 123;
		int i = 2;
		unsigned int ui = 124;
		signed long sl = 125;
		unsigned long ul = 126;
		long long ll = 127;
		unsigned long long ull = 128;
		float f = 1.0;
		double d = 1.000000;
		const char *p = "a";
		const std::string &str = "running";

		LOG_RUN << b << c << ss << us << i << ui << sl << ul << ll << ull << f << d << *p << str;
		LOG_DEBUG << b << c << ss << us << i << ui << sl << ul << ll << ull << f << d << *p << str;
		LOG_WARN << b << c << ss << us << i << ui << sl << ul << ll << ull << f << d << *p << str;
		LOG_INFO << b << c << ss << us << i << ui << sl << ul << ll << ull << f << d << *p << str;
		LOG_ERROR << b << c << ss << us << i << ui << sl << ul << ll << ull << f << d << *p << str;

		Sleep(10);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int threadId1 = 1, threadId2 = 2, threadId3 = 3, threadId4 = 4;
	CreateThread(NULL, 0, Fun1, &threadId1, 0, NULL);
	CreateThread(NULL, 0, Fun1, &threadId2, 0, NULL);
	CreateThread(NULL, 0, Fun1, &threadId3, 0, NULL);
	CreateThread(NULL, 0, Fun1, &threadId4, 0, NULL);

	while (1);
	return 0;
}