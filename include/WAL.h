#pragma once

#include <string>
#include <fstream>
#include <cstdint>

class WAL
{
public:
    WAL(const std::string &path);
    ~WAL();

    void Put(const std::string &key, const std::string &value, uint64_t sequence);
    void Delete(const std::string &key, uint64_t sequence);
    void Close()
    {
        if (logFile.is_open())
            logFile.close();
    }

private:
    std::string filePath;
    std::ofstream logFile;
};