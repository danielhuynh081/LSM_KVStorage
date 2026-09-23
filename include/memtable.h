#pragma once

#include <string>
#include <map>
#include <optional>
#include <cstdint>
#include <cstddef>

struct Entry {
    std::string value;
    uint64_t sequence_number;  
    bool is_tombstone;         //this is true if the entry is deleted
};

class MemTable {
public:
    void Put(const std::string& key, const std::string& value, uint64_t seq);
    void Delete(const std::string& key, uint64_t seq);
    std::optional<Entry> Get(const std::string& key) const;
    size_t getSize() const;

    // Sorted iteration
    std::map<std::string, Entry>::const_iterator begin() const;
    std::map<std::string, Entry>::const_iterator end() const;

private:
    std::map<std::string, Entry> table_;
    size_t size_bytes_ = 0;
};