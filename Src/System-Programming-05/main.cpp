#include "pch.h"

namespace fs = std::filesystem;

// 파일 시그니처 읽기 함수
static bool ReadFileSignature(const std::string& filePath, unsigned char* outHeader, std::size_t length = 4) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return false;
    file.read(reinterpret_cast<char*>(outHeader), length);
    return file.gcount() == length;
}

// 시그니처를 문자열로 변환
static std::string GetSignatureString(const unsigned char* header, std::size_t length) {
    std::ostringstream oss;
    for (std::size_t i = 0; i < length; ++i) {
        oss << std::hex << std::uppercase << std::setfill('0')
            << std::setw(2) << static_cast<int>(header[i]) << " ";
    }
    return oss.str();
}

int main() {
    std::string folderPath = "D:\\Sample"; //시그니처 파일 읽는 위치

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            unsigned char header[4] = { 0 };
            if (ReadFileSignature(entry.path().string(), header)) {
                std::cout << entry.path().string() << ": "
                    << GetSignatureString(header, 4) << std::endl;
            }
        }
    }

    return 0;
}
