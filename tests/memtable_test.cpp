#include "memtable.h"
#include <iostream>
#include <cassert>

void test_put_and_get()
{
    MemTable mt;
    mt.Put("apple", "pen", 1);

    auto entry = mt.Get("apple");
    assert(entry.has_value());
    assert(entry->value == "pen");
    assert(entry->sequence_number == 1);
    assert(entry->is_tombstone == false);

    std::cout << "test_put_and_get passed" << std::endl;
}

void test_delete()
{
    MemTable mt;
    mt.Put("delete", "me", 1);
    mt.Delete("delete", 2);

    auto entry = mt.Get("delete");
    assert(!entry.has_value()); // Get returns null for tombstones

    std::cout << "test_delete passed" << std::endl;
}

void test_size()
{
    MemTable mt;
    size_t initial_size = mt.getSize();

    mt.Put("a", "b", 1);
    assert(mt.getSize() > initial_size);

    std::cout << "test_size passed" << std::endl;
}

int main()
{
    test_put_and_get();
    test_delete();
    test_size();

    std::cout << "\nAll tests passed" << std::endl;
    return 0;
}