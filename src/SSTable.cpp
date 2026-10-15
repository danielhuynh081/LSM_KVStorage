#include "SSTable.h"

#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;

void SSTable::Flush(const MemTable &memtable)
{
    // Create a new SSTable file
    std::ofstream file(filePath_, std::ios::out | std::ios::trunc);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open SSTable file");
    }

    // Iterate through the MemTable
    for (const auto &[key, entry] : memtable)
    {
        // Get current byte offset before writing
        uint64_t offset = static_cast<uint64_t>(file.tellp());

        // Write entry to disk
        file << entry.sequence_number << " "
             << entry.is_tombstone << " "
             << std::quoted(key) << " "
             << std::quoted(entry.value) << "\n";

        if (!file)
        {
            throw std::runtime_error("Failed to write SSTable entry");
        }

        // Store key and offset in the index
        index_[key] = offset;
    }

    file.flush();

    if (!file)
    {
        throw std::runtime_error("Failed to flush SSTable");
    }

    file.close();

    if (!file)
    {
        throw std::runtime_error("Failed to close SSTable");
    }
}

uint64_t SSTable::FindNextSSTableId()
{
    uint64_t maxId = 0;

    fs::create_directories("data");

    for (const auto &file : fs::directory_iterator("data"))
    {
        if (!file.is_regular_file())
            continue;

        std::string filename = file.path().filename().string();

        if (filename.rfind("sst_", 0) != 0 ||
            file.path().extension() != ".db")
            continue;

        std::string number = filename.substr(4, filename.size() - 7);

        try
        {
            size_t parsed = 0;
            uint64_t id = std::stoull(number, &parsed);

            if (parsed == number.size())
                maxId = std::max(maxId, id);
        }
        catch (const std::exception &)
        {
            continue;
        }
    }

    return maxId + 1;
}
