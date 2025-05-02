#include "pch.h"

int main()
{
    setlocale(LC_ALL, "");
    LPCSTR pszServerIP = "192.168.0.3";

        try
    {
        CSyncTCPSocket socket;
        CJsonProtocol protocol(&socket);
        ECODE nRet = protocol.Connect(pszServerIP, g_wPort, 5000);
        if (EC_SUCCESS != nRet)
            throw exception_format(TEXT("Connect failure, %d"), nRet);

        {
            REQ_RESUME req;
            req.Resume.strName = TEXT("안계명");
                req.Resume.strGreeting = TEXT("시스템 프로그래밍 교육생");
            req.Resume.strIntroduction = TEXT("C++ 코딩 어렵습니다 HELP");
            nRet = protocol.SendPacket(&req, 5000);
            if (EC_SUCCESS != nRet)
                throw exception_format(TEXT("REQ_RESUME sending failure, %d"), nRet);

            CMD_RESUME_ACK ack;
            nRet = protocol.RecvPacket(&ack);
            if (EC_SUCCESS != nRet)
                throw exception_format(TEXT("CMD_RESUME_ACK recving failure, %d"), nRet);

            if (0 != ack.nErrorCode)
            {
                tprintf(TEXT("%s, %d\n"), ack.strMessage.c_str(), ack.nErrorCode);
                throw exception_format(TEXT("이력서 송신 실패!!"));
            }
        }

        {
            REQ_INQUIRY req;
            req.strQuestionCode = TEXT("S-Developer3rd");
            nRet = protocol.SendPacket(&req, 5000);
            if (EC_SUCCESS != nRet)
                throw exception_format(TEXT("REQ_INQUIRY sending failure, %d"), nRet);

            CMD_INQUIRY cmd;
            nRet = protocol.RecvPacket(&cmd);
            if (EC_SUCCESS != nRet)
                throw exception_format(TEXT("CMD_INQUIRY recving failure, %d"), nRet);

            for (ST_QUESTION question : cmd.vecQuestions)
            {
                int nChoice = -1;
                do
                {
                    for (DWORD i = 0; i < question.vecSelection.size(); i++)
                        tprintf(TEXT("%u: %s\n"), i + 1, question.vecSelection[i].c_str());

                    printf("응답은? ");
                    char szBuffer[100] = { 0, };
                    fgets(szBuffer, 100, stdin);
                    nChoice = IntFrom(szBuffer);
                } while (!(0 < nChoice && nChoice <= (int)question.vecSelection.size()));

                REQ_ANSWER answer;
                answer.Question = question;
                answer.strAnswer = question.vecSelection[nChoice - 1];
                nRet = protocol.SendPacket(&answer, 5000);
                if (EC_SUCCESS != nRet)
                    throw exception_format(TEXT("REQ_ANSWER sending failure, %d"), nRet);

                CMD_ANSWER_ACK ack;
                nRet = protocol.RecvPacket(&ack);
                if (EC_SUCCESS != nRet)
                    throw exception_format(TEXT("CMD_ANSWER_ACK recving failure, %d"), nRet);

                tprintf(TEXT("%s\n"), ack.strMessage.c_str());
            }
        }

        protocol.Close();
    }
    catch (const std::exception& e)
    {
        Log_Error("%s", e.what());
        return -1;
    }
    return 0;
}