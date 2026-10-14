#pragma once

#include "memtable.h"
#include "WAL.h"
#include "SSTable.h"
#include <vector>

class LSM
{
public:
    LSM() : wal("data/wal.log") {}
    ~LSM() {}

    void Put(const std::string &key, const std::string &value)
    {
        // increments the sequence number for each new entry
        mtSequence += 1;
        // Log into WAL before memtable
        wal.Put(key, value, mtSequence);
        memtable.Put(key, value, mtSequence);
    }

    void Delete(const std::string &key)
    {
        mtSequence += 1;
        wal.Delete(key, mtSequence);
        memtable.Delete(key, mtSequence);
    }
    bool flushSSTable()
    {
        // Implement logic to flush memtable to SSTable
        // Return true if successful, false otherwise
        return true;
    }

private:
    MemTable memtable;
    std::vector<SSTable> sstables;
    WAL wal;
    uint64_t mtSequence = 0;
    uint64_t sstSequence = 0;
};