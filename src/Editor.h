#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <filesystem>
#include <ranges>
#include "FileManager.h"

namespace Salmon
{
    class Editor
    {

    public:
        Editor() : content(), file(content) {}
        FileManager file;
        Content content;
    };
} // namespace Salmon