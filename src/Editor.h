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