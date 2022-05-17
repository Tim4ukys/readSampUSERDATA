#include <iostream>
#include "USERDATA.h"

int main() {
    constexpr const char* const FL_NAME = "USERDATA.DAT";

    USERDATA userdata{FL_NAME};

    std::cout << "--- SERVER INFO ---" << std::endl;
    for (const auto& inf : userdata.getServerInfo()) {
        std::cout << inf.m_ServerName << ": " << inf.m_IP << ":" << inf.m_uPort << std::endl;
    }

    return 0;
}
