#include "SSTable.h"
#include <iostream>
#include <cassert>

void test_flush()
{
    MemTable mt;
    uint64_t id = FindNextSSTableId();

    std::string filename = "data/sst_1.db";
    SSTable sTable(filename);
    mt.Put("apple", "pen", 1);
    mt.Put("apple2", "pen2", 2);
    mt.Put("apple3", "pen3", 3);
    mt.Put("apple4", "pen4", 4);
    mt.Put("apple5", "pen5", 5);
    sTable.flush(mt);

    std::cout
        << "test_put_and_get passed" << std::endl;
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