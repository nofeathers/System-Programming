#include "pch.h"

namespace fs = std::filesystem;

// 파일 시그니처 읽기
static bool ReadFileSignature(const std::string& filePath, unsigned char* outHeader, std::size_t length = 4) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return false;
    file.read(reinterpret_cast<char*>(outHeader), length);
    return file.gcount() == length;
}

// 시그니처 문자열로 변환
static std::string GetSignatureString(const unsigned char* header, std::size_t length) {
    std::ostringstream oss;
    for (std::size_t i = 0; i < length; ++i) {
        oss << std::hex << std::uppercase << std::setfill('0')
            << std::setw(2) << static_cast<int>(header[i]) << " ";
    }
    return oss.str();
}

// 확장자 필터링 함수
static bool MatchExtension(const fs::path& filePath, const std::string& pattern) {
    if (pattern.size() < 2 || pattern[0] != '*') return true; 
    std::string ext = filePath.extension().string(); 
    return ext == pattern.substr(1); 
}

int main(int argc, char* argv[]) { // 디버깅 명령 인수 처리
    if (argc < 2) {
        std::cout << "파일이 없습니다\n"; // 디렉토리 폴더 안 *.zip 존재 X
        return 1;
    }

    std::string inputPattern = argv[1];
    fs::path fullPath(inputPattern);
    fs::path folderPath = fullPath.parent_path();
    std::string pattern = fullPath.filename().string();

    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        std::cerr << "디렉토리 폴더가 없습니다 " << folderPath << "\n"; //디렉토리 경로 X
        return 1;
    }

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && MatchExtension(entry.path(), pattern)) {
            unsigned char header[4] = { 0 };
            if (ReadFileSignature(entry.path().string(), header)) {
                std::cout << entry.path().string() << ": " // 파일 존재 시그니처 함수 출력
                    << GetSignatureString(header, 4) << std::endl;
            }
        }
    }

    return 0;
}
