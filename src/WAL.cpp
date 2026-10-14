#include "WAL.h"
#include <stdexcept>
#include <iomanip>

WAL::WAL(const std::string &path) : filePath(path)
{
    // Sets our logfile private member to file path
    logFile.open(filePath, std::ios::app);

    if (!logFile.is_open())
    {
        throw std::runtime_error("Failed to open WAL");
    }
}

WAL::~WAL()
{
    Close();
}

void WAL::Put(const std::string &key,
              const std::string &value,
              uint64_t sequence)
{

    logFile << "PUT "
            << sequence << " "
            << std::quoted(key) << " "
            << std::quoted(value) << "\n";

    logFile.flush();

    if (!logFile)
    {
        throw std::runtime_error("WAL write failed");
    }
}

void WAL::Delete(const std::string &key,
                 uint64_t sequence)
{

    logFile << "DELETE "
            << sequence << " "
            << std::quoted(key) << "\n";

    logFile.flush();

    if (!logFile)
    {
        throw std::runtime_error("WAL delete failed");
    }
}
