#include "SSTable.h"

void Flush(const MemTable &memtable, uint64_t seq)
{
    // Flush
    /*
    Iterate through the MemTable.
    Copy each key and Entry into the SSTable's map.
    Write the sorted entries to a file.
    Keep the SSTable immutable after creation.
    */
    // Create File
}
std::optional<Entry> Get(const std::string &key) const;