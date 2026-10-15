#include "LSM.h"

#include <algorithm>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

uint64_t LSM::FindNextSSTableId()
{
    uint64_t maxId = 0;

    fs::create_directories("data");

    for (const auto &file : fs::directory_iterator("data"))
    {
        if (!file.is_regular_file())
            continue;

        std::string filename = file.path().filename().string();

        if (filename.rfind("sst_", 0) != 0 ||
            file.path().extension() != ".db")
            continue;

        std::string number = filename.substr(4, filename.size() - 7);

        try
        {
            size_t parsed = 0;
            uint64_t id = std::stoull(number, &parsed);

            if (parsed == number.size())
                maxId = std::max(maxId, id);
        }
        catch (const std::exception &)
        {
            continue;
        }
    }

    return maxId + 1;
}
