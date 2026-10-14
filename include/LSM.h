#pragma once

#include "memtable.h"
#include "WAL.h"
#include "SSTable.h"

class LSM
{
private:
    MemTable memtable;
    WAL wal;
    uint64_t sequence = 0;

public:
    LSMStore() : wal("data/wal.log") {}

    void Put(const std::string &key, const std::string &value)
    {
        uint64_t next = sequence + 1;
        // Log into WAL before memtable
        wal.Put(key, value, next);
        memtable.Put(key, value, next);
        sequence = next;
    }

    void Delete(const std::string &key)
    {
        uint64_t next = sequence + 1;
        wal.Delete(key, next);
        memtable.Delete(key, next);
        sequence = next;
    }
    bool flushSSTable()
    {
        // Implement logic to flush memtable to SSTable
        // Return true if successful, false otherwise
        return true;
    }
};