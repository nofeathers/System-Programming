#include <stdio.h>
#include <locale>

int main()
{
	std::locale::global(std::locale("Korean"));
	char szTest1[] = "안녕하세요! ABC";
	wchar_t szTest2[] = L"안녕하세요! ABC";
	printf("%s\n", szTest1);
	wprintf(L"%s\n", szTest2);
	return 0;
}
