#include "SSTable.h"
#include <iostream>
#include <cassert>
#include <fstream>

// File checking
bool SSTableFlushContains(SSTable table, const std::string &content)
{
    std::ifstream file(table.getpath());
    std::string line;

    if (!file.is_open())
    {
        return false;
    }
    while (std::getline(file, line))
    { // Read line by line
        if (line.find(content) != std::string::npos)
        {
            // std::cout << "Found match on line: " << line << std::endl;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void test_flush()
{
    MemTable mt;
    SSTable sTable;

    mt.Put("apple", "pen", 1);
    mt.Put("apple2", "pen2", 2);
    mt.Put("apple3", "pen3", 3);
    mt.Put("apple4", "pen4", 4);
    mt.Put("apple5", "pen5", 5);
    sTable.Flush(mt);
    assert(SSTableFlushContains(sTable, "1 0 \"apple\" \"pen\""));
    assert(SSTableFlushContains(sTable, "2 0 \"apple2\" \"pen2\""));
    assert(SSTableFlushContains(sTable, "3 0 \"apple3\" \"pen3\""));
    assert(SSTableFlushContains(sTable, "4 0 \"apple4\" \"pen4\""));
    assert(SSTableFlushContains(sTable, "5 0 \"apple5\" \"pen5\""));
    std::cout
        << "test_flush passed" << std::endl;
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
    test_flush();
    test_delete();
    test_size();

    std::cout << "\nAll tests passed" << std::endl;
    return 0;
}