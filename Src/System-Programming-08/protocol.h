#pragma once

//strName / strGreeting / strIntroduction / nErrorCode / strMessage

#include "..\..\..\cppcore-master\Inc\cppcore.h"

struct ST_RESUME : public core::IFormatterObject
{
    std::tstring strName;
    std::tstring strGreeting;
    std::tstring strIntroduction;

    void OnSync(core::IFormatter& formatter)
    {
        formatter
            + core::sPair(TEXT("Name"), strName)
            + core::sPair(TEXT("Greeting"), strGreeting)
            + core::sPair(TEXT("Introduction"), strIntroduction)
            ;
    }
};

struct REQ_RESUME : public core::IFormatterObject
{
    static const int ID = 1001;
    ST_RESUME Resume;
    void OnSync(core::IFormatter& formatter)
    {
        formatter
            + core::sPair(TEXT("Resume"), Resume)
            ;
    }
};

struct CMD_RESUME_ACK : public core::IFormatterObject
{
    static const int ID = 1002;

    bool nErrorCode;
    std::tstring strMessage;
    
    void OnSync(core::IFormatter& formatter)
    {
        formatter
            + core::sPair(TEXT("ErrorCode"), nErrorCode)
            + core::sPair(TEXT("Message"), strMessage)
            ;
    }
};

struct REQ_INQUIRY : public core::IFormatterObject
{
    static const int ID = 1003;

    std::tstring strQuestionCode;

    void OnSync(core::IFormatter& formatter)
    {
        formatter
            + core::sPair(TEXT("QuestionCode"), strQuestionCode)
            ;
    }
};

struct ST_QUESTION : public core::IFormatterObject
{
    std::vector<std::tstring> vecSelection;
    void OnSync(core::IFormatter& formatter)
    {
        formatter
            + core::sPair(TEXT("Selection"), vecSelection)
            ;
    }
};

struct CMD_INQUIRY : public core::IFormatterObject
{
    static const int ID = 1004;
    std::vector<ST_QUESTION> vecQuestions;
    void OnSync(core::IFormatter& formatter)
    {
        formatter
            + core::sPair(TEXT("Questions"), vecQuestions)
            ;
    }
};

struct REQ_ANSWER : public core::IFormatterObject
{
    static const int ID = 1005;

    ST_QUESTION Question;

    std::tstring strAnswer;

    void OnSync(core::IFormatter& formatter)
    {
        formatter
            + core::sPair(TEXT("Question"), Question)
            + core::sPair(TEXT("Answer"), strAnswer)
            ;

    }
};

struct CMD_ANSWER_ACK : public core::IFormatterObject
{
    static const int ID = 1006;

    std::tstring strMessage;

    void OnSync(core::IFormatter& formatter)
    {
        formatter
            + core::sPair(TEXT("Message"), strMessage)
            ;
    }
};
