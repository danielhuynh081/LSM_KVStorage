#include "memtable.h"

// Insertion
void MemTable::Put(const std::string& key, const std::string& value, uint64_t seq){
    auto it = table_.find(key); // check if this is a new key or overwrite
    
    if (it != table_.end()) {
        size_bytes_ -= it->second.value.size();   // key string value already counted once
    //  table_[key] = Entry{value, seq, false};  
        it->second = Entry{value, seq, false};    // entry already exists 
    } else {
        size_bytes_ += key.size() + sizeof(seq) + sizeof(bool); 
        table_[key] = Entry{value, seq, false};   // creates a new entry in the map
    }
    size_bytes_ += value.size();
}


// Deletion
void MemTable::Delete(const std::string& key, uint64_t seq){
    auto it = table_.find(key); 
   
    if (it != table_.end()) { // key exists in memtable
        size_bytes_ -= it->second.value.size();   // keys string value already counted once
    //  table_[key] = Entry{"", seq, true};  
        it->second = Entry{"", seq, true};        // mark as tombstone 

    } else { // key isn't in this memtable, but it may exist in an SSTable
        size_bytes_ += key.size() + sizeof(seq) + sizeof(bool);
        table_[key] = Entry{"", seq, true};
    }
}

// Retrieval
std::optional<Entry> MemTable::Get(const std::string& key) const{
    auto it = table_.find(key);

    if (it == table_.end()) { // key isn't in this memtable, add logic for SSTable in future
        return std::nullopt;
    }
    if (it->second.is_tombstone) { // key was deleted
        return std::nullopt;
    }
    return it->second; // return entry object
}

size_t MemTable::getSize() const{
    return size_bytes_;
}