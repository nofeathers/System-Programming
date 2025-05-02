#include "pch.h"
#include "GlobalRingBuffer.h"

int main()
{
    HANDLE hFile = CreateFile(TEXT("d:/report.json"), GENERIC_READ_, OPEN_EXISTING_, 0);

    std::list<char*> listTemp;
    while (true)
    {
        const DWORD dwBufferSize = 15;
        char* pBuffer = (char*)RingBuffer()->Alloc(dwBufferSize + 1);

        DWORD dwReadSize = 0;
        if (!ReadFile(hFile, pBuffer, dwBufferSize, &dwReadSize) || 0 == dwReadSize)
            break;
        pBuffer[dwReadSize] = 0;

        listTemp.push_back(pBuffer);
    }
    CloseFile(hFile);

    printf("%s", listTemp.front());
    return 0;
}