#pragma once
#include "memtable.h"
#include <string>
#include <vector>
#include <optional>

// An SSTable file is created from one MemTable flush
class SSTable
{
public:
    SSTable()
    {
        uint64_t id = FindNextSSTableId();
        filePath_ = "data/sst_" + std::to_string(id) + ".db";
    }
    ~SSTable() {}

    // Getters
    std::string getpath() { return filePath_; }
    std::optional<Entry> Get(const std::string &key) const;

    // Disk interaction
    void Flush(const MemTable &memtable);

private:
    std::string filePath_;
    std::map<std::string, uint64_t> index_;
    uint64_t FindNextSSTableId();
};