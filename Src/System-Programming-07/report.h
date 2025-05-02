#pragma once
struct ST_EVENT : public core::IFormatterObject
{
    std::tstring EngineName;
    std::tstring EngineVersion;
    std::tstring TargetID;
    std::tstring Name;
    std::tstring AnalysisCode;
    int Severity;
    std::tstring Desc;

    void OnSync(core::IFormatter& formatter)
    {
        formatter
            + core::sPair(TEXT("EngineName"), EngineName)
            + core::sPair(TEXT("EngineVersion"), EngineVersion)
            + core::sPair(TEXT("TargetID"), TargetID)
            + core::sPair(TEXT("Name"), Name)
            + core::sPair(TEXT("AnalysisCode"), AnalysisCode)
            + core::sPair(TEXT("Severity"), Severity)
            + core::sPair(TEXT("Desc"), Desc)
            ;
    }
};

struct ST_SUMMARY : public core::IFormatterObject
{
    std::tstring Result;
    std::tstring DetectName;
    std::tstring EngineName;
    std::tstring EngineVersion;
    int Severity;
    std::tstring SampleName;
    std::tstring SampleExt;
    double TotalElapsedTime;
    bool ReachedFileLoopLimit;
    bool ReachedUrlLoopLimit;

    void OnSync(core::IFormatter& formatter)
    {
        formatter
            + core::sPair(TEXT("Result"), Result)
            + core::sPair(TEXT("DetectName"), DetectName)
            + core::sPair(TEXT("EngineName"), EngineName)
            + core::sPair(TEXT("EngineVersion"), EngineVersion)
            + core::sPair(TEXT("Severity"), Severity)
            + core::sPair(TEXT("SampleName"), SampleName)
            + core::sPair(TEXT("SampleExt"), SampleExt)
            + core::sPair(TEXT("TotalElapsedTime"), TotalElapsedTime)
            + core::sPair(TEXT("ReachedFileLoopLimit"), ReachedFileLoopLimit)
            + core::sPair(TEXT("ReachedUrlLoopLimit"), ReachedUrlLoopLimit)
            ;
    }
};

struct ST_DETECTION : public core::IFormatterObject
{
    std::vector<ST_EVENT> Event;
    void OnSync(core::IFormatter& formatter)
    {
        formatter
            + core::sPair(TEXT("Event"), Event)
            ;
    }
};

struct ST_ANALYSIS_REPORT : public core::IFormatterObject
{
    ST_SUMMARY Summary;
    ST_DETECTION Detection;
    void OnSync(core::IFormatter& formatter)
    {
        formatter
            + core::sPair(TEXT("Summary"), Summary)
            + core::sPair(TEXT("Detection"), Detection)
            ;
    }
};