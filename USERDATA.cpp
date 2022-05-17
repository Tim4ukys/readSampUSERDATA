#include "USERDATA.h"
#include <exception>
#include <filesystem>
#include <iostream>
#include <memory>

USERDATA::USERDATA(const char* fileName) {
    // Проверяем, есть ли такой файл вообще
    if (!std::filesystem::exists(fileName)) {
        std::cerr << "File " << fileName << " is not exists." << std::endl;
        abort();
    }

    // Открываем файл
    m_file.open(fileName, std::ios_base::in | std::ios_base::binary);
    if (!m_file.is_open()) {
        std::cerr << "Failed open \"USERDATA.DAT\"." << std::endl;
        abort();
    }

    // Проверяем сигнатуру файла
    char sign[4];
    m_file.read(sign, 4u);
    if (memcmp(sign, "SAMP", 4u) != 0) {
        std::cerr << "File is not SAMP \"USERDATA.DAT\"." << std::endl;
        abort();
    }
    m_file.seekg(4u, std::ios_base::cur);

    //////
    // Считываем кол-во серверов в списке(+0xC)
    unsigned int countServerList;
    m_file.read((char*)&countServerList, 4u);

    // Создаём дин. массив из псевдоструктур
    m_arrServersList.resize(countServerList);

    // Заполняем массив и считываем всю информацию из файла
    for (auto &inf : m_arrServersList) {
        auto readString = [](std::ifstream &file, std::string &str) {
            unsigned int size_str;
            file.read((char*)&size_str, 4u);
            str.resize(size_str);
            file.read((char*)(str.data()), size_str);
        };

        // Считываем IP
        readString(m_file, inf.m_IP);

        // Считываем PORT
        m_file.read((char*)&inf.m_uPort, 4u);

        // Считываем имя сервака
        readString(m_file, inf.m_ServerName);

        m_file.seekg(8, std::ios_base::cur);
    }
}
USERDATA::~USERDATA() {
    m_file.close();
    m_arrServersList.clear();
}

USERDATA::stServerInfo &USERDATA::operator[](size_t index) {
    return m_arrServersList[index];
}
std::vector<USERDATA::stServerInfo> &USERDATA::getServerInfo() {
    return m_arrServersList;
}
