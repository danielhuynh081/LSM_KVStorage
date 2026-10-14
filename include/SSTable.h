#pragma once
#include "memtable.h"
#include <vector>

// An SSTable file is created from one MemTable flush
class SSTable
{
public:
    SSTable() {}
    ~SSTable() {}
    void Flush(const MemTable &memtable, uint64_t seq);
    // std::optional<Entry> Get(const std::string &key) const;

private:
    std::string filePath_;
    // std::map<std::string, uint64_t> index_;
};