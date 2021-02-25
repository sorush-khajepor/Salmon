#include <fstream>
#include "Content.h"

namespace Salmon
{

    class FileManager
    {

        std::string fileName;
        Content &content;

    public:
        FileManager(Content &content_) : content(content_){};

        auto FindNewFileName()
        {

            std::string newFile = "temp";
            while (std::filesystem::exists(newFile))
            {
                newFile += "0";
            };
            return newFile;
        }

        auto ReplaceFile(std::string newFileName)
        {

            auto tempFile = FindNewFileName();
            rename(fileName.c_str(), tempFile.c_str());
            rename(newFileName.c_str(), fileName.c_str());
            remove(tempFile.c_str());
        }

        auto Read()
        {
            std::ifstream in(fileName);
            std::string line;
            while (getline(in, line))
            {
                content.AppendLine(line);
            }
            in.close();
        }

        auto Open(std::string fileName_)
        {

            fileName = fileName_;

            content.Clear();

            Read();
        }

        auto Write(std::string fileName)
        {

            std::ofstream out(fileName);

            for (auto line : content)
                out << line << '\n';

            out.close();
        }

        auto Save()
        {

            auto temp = FindNewFileName();
            Write(temp);
            ReplaceFile(temp);
        }

        auto SaveAs(std::string newFile)
        {
            Write(newFile);
            fileName = newFile;
        }
    };

} // namespace Salmon