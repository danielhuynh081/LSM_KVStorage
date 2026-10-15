#pragma once
#include "memtable.h"
#include <string>
#include <vector>

// An SSTable file is created from one MemTable flush
class SSTable
{
public:
    SSTable()
    {
        uint64_t id = FindNextSSTableId();
        filePath_ = "data/sst_" + std::to_string(id) + ".db";
    }
    SSTable(const std::string &path) : filePath_(path)
    {
    }
    ~SSTable() {}
    std::string getpath() { return filePath_; }

    void Flush(const MemTable &memtable);
    // std::optional<Entry> Get(const std::string &key) const;

private:
    std::string filePath_;
    std::map<std::string, uint64_t> index_;
    uint64_t FindNextSSTableId();
};