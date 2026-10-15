#pragma once
#include "memtable.h"
#include <vector>

// An SSTable file is created from one MemTable flush
class SSTable
{
public:
    SSTable(const std::string &path) : filePath_(path) {}
    ~SSTable() {}
    void Flush(const MemTable &memtable);
    // std::optional<Entry> Get(const std::string &key) const;

private:
    std::string filePath_;
    std::map<std::string, uint64_t> index_;
};