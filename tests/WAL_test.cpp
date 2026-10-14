#include "WAL.h"
#include <cassert>
#include <iostream>
#include <string>

// File checking
bool logFileContains(const std::string &filePath, const std::string &content)
{
    std::ifstream file(filePath);
    std::string line;

    if (!file.is_open())
    {
        return false;
    }
    while (std::getline(file, line))
    { // Read line by line
        if (line.find(content) != std::string::npos)
        {
            // std::cout << "Found match on line: " << line << std::endl;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool clearTestLog()
{
    std::ofstream file("data/WALtest.log", std::ios::trunc);
    if (!file.is_open())
    {
        std::cerr << "Error opening the log file!" << std::endl;
        return 1;
    }

    file.close();
    return 0;
}
// File creation
void test_WAL_creation()
{
    WAL log("data/WALtest.log");
    std::ifstream file("data/WALtest.log");
    assert(file.good());
    file.close();
    std::cout << "test_WAL_creation passed" << std::endl;
}

// Put
void test_WAL_Put()
{
    WAL log("data/WALtest.log");
    log.Put("key1", "value1", 1);
    assert(logFileContains("data/WALtest.log", "PUT 1 \"key1\" \"value1\""));
    log.Close();
    std::cout << "test_WAL_Put passed" << std::endl;
}

// Delete
void test_WAL_Delete(const std::string &key, uint64_t sequence)
{
    WAL log("data/WALtest.log");
    log.Delete(key, sequence);
    assert(logFileContains("data/WALtest.log", "DELETE " + std::to_string(sequence) + " \"" + key + "\""));
    log.Close();
    std::cout << "test_WAL_Delete passed" << std::endl;
}

int main()
{
    test_WAL_creation();
    test_WAL_Put();
    test_WAL_Delete("key1", 2);
    clearTestLog();

    std::cout << "\nAll tests passed" << std::endl;
    return 0;
}