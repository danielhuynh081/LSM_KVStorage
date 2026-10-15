#include "SSTable.h"

#include <fstream>
#include <iomanip>
#include <stdexcept>

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