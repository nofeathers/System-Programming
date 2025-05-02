#include "pch.h"

namespace fs = std::filesystem;

// ���� �ñ״�ó �б�
static bool ReadFileSignature(const std::string& filePath, unsigned char* outHeader, std::size_t length = 4) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return false;
    file.read(reinterpret_cast<char*>(outHeader), length);
    return file.gcount() == length;
}

// �ñ״�ó ���ڿ��� ��ȯ
static std::string GetSignatureString(const unsigned char* header, std::size_t length) {
    std::ostringstream oss;
    for (std::size_t i = 0; i < length; ++i) {
        oss << std::hex << std::uppercase << std::setfill('0')
            << std::setw(2) << static_cast<int>(header[i]) << " ";
    }
    return oss.str();
}

// Ȯ���� ���͸� �Լ�
static bool MatchExtension(const fs::path& filePath, const std::string& pattern) {
    if (pattern.size() < 2 || pattern[0] != '*') return true; 
    std::string ext = filePath.extension().string(); 
    return ext == pattern.substr(1); 
}

int main(int argc, char* argv[]) { // ����� ��� �μ� ó��
    if (argc < 2) {
        std::cout << "������ �����ϴ�\n"; // ���丮 ���� �� *.zip ���� X
        return 1;
    }

    std::string inputPattern = argv[1];
    fs::path fullPath(inputPattern);
    fs::path folderPath = fullPath.parent_path();
    std::string pattern = fullPath.filename().string();

    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        std::cerr << "���丮 ������ �����ϴ� " << folderPath << "\n"; //���丮 ��� X
        return 1;
    }

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && MatchExtension(entry.path(), pattern)) {
            unsigned char header[4] = { 0 };
            if (ReadFileSignature(entry.path().string(), header)) {
                std::cout << entry.path().string() << ": " // ���� ���� �ñ״�ó �Լ� ���
                    << GetSignatureString(header, 4) << std::endl;
            }
        }
    }

    return 0;
}
