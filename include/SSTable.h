#pragma once

#include "memtable.h"

struct Table
{
    const Entry _Data;
    int id;
};

class SSTable
{
public:
    void Put(const std::string &key, const std::string &value, uint64_t seq);

    // Sorted iteration
    std::map<std::string, Entry>::const_iterator begin() const { return table_.begin(); }
    std::map<std::string, Entry>::const_iterator end() const { return table_.end(); }

private:
    std::map<std::string, Entry> table_;
    size_t size_bytes_ = 0;
};