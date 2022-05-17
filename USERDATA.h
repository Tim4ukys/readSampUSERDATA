#ifndef SAMP_USERDATA_H
#define SAMP_USERDATA_H

#include <string>
#include <fstream>
#include <vector>

/**
 * @author Tim4ukys
 * @date 17.05.2022
 */
class USERDATA {
public:

    struct stServerInfo {
        std::string m_IP;
        unsigned int m_uPort;
        std::string m_ServerName;
    };

    /**
     * @param fileName путь до файла USERDATA.DAT
     */
    USERDATA(const char* fileName);
    ~USERDATA();

    std::vector<stServerInfo>& getServerInfo();
    stServerInfo& operator[] (size_t index);

private:
    std::ifstream m_file;
    std::vector<stServerInfo> m_arrServersList;
};


#endif
