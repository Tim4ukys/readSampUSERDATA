#include "main.h"

namespace fs = std::filesystem;

int main() {
    constexpr const char* const FL_NAME = "USERDATA.DAT";

    // Проверяем, есть ли такой файл
    if (!fs::exists(fs::path(FL_NAME))){
        std::cout << "File \"USERDATA.DAT\" is not exists." << std::endl;
        return 1;
    }

    // Открываем файл
    std::ifstream file{FL_NAME, std::ios_base::binary};
    if (!file.is_open()) {
        std::cout << "Fail open file." << std::endl;
        return 1;
    }

    // Считываем сигнатуру файла
    char signature[4];
    file.read(signature, 4u);
    if (memcmp(signature, "SAMP", 4u) != 0) {
        std::cout << "File is not SAMP \"USERDATA.DAT\"." << std::endl;
        return 1;
    }
    // Перекидываем позицию считывающей головки(курсора, ... мн. других названий)
    file.seekg(4u, std::ios_base::cur);

    // Считываем кол-во серверов в списке(+0xC)
    unsigned int countServerList;
    file.read((char*)&countServerList, 4u);

    // Создаём дин. массив из псевдоструктуры
    struct serverInfo {
        std::string m_sIP;
        std::uint32_t m_uPort;
        std::string m_sServerName;
    };
    std::vector<serverInfo> arrServerInfo;
    arrServerInfo.resize(countServerList);

    // Проходимся по списку
    for (size_t i{}; i < countServerList; ++i) {
        auto readString = [](std::ifstream &file, std::string &str) {
          unsigned int size_str;
          file.read((char*)&size_str, 4u);
          str.resize(size_str);
          file.read((char*)(str.data()), size_str);
        };

        auto &inf = arrServerInfo[i];

        // Считываем IP
        readString(file, inf.m_sIP);

        // Считываем PORT
        file.read((char*)&inf.m_uPort, sizeof(std::uint32_t));

        // Считываем имя сервака
        readString(file, inf.m_sServerName);

        file.seekg(8, std::ios_base::cur);
    }

    std::cout << "--- SERVER INFO(count: " << arrServerInfo.size() << ") ---" << std::endl;
    for (const auto& inf : arrServerInfo) {
        std::cout << inf.m_sServerName << ": IP = " << inf.m_sIP << ":" << inf.m_uPort << std::endl;
    }

    return 0;
}
