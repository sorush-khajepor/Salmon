#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <filesystem>
#include <ranges>

namespace Salmon
{
    class Content
    {

        std::vector<std::string> data;

    public:
        auto Clear()
        {
            data.clear();
        }

        auto begin() { return data.begin(); }

        auto end() { return data.end(); }

        auto getDataIter(int iLine)
        {
            return data.begin() + iLine - 1;
        }

        auto AppendLine(std::string line)
        {
            data.push_back(line);
        }
        auto ReplaceLine(int iLine, std::string line)
        {
            data[iLine - 1] = line;
        }

        auto DeleteLine(int iLine)
        {
            data.erase(getDataIter(iLine));
        }

        auto DeleteLine(std::vector<size_t> iLines)
        {
            sort(iLines.begin(), iLines.end(), std::greater<size_t>());
            for (auto &iLine : iLines)
                DeleteLine(iLine);
        }

        auto DeleteLine(std::initializer_list<size_t> iLinesList)
        {
            std::vector<size_t> iLines = iLinesList;
            DeleteLine(iLines);
        }

        auto InsertLine(std::string line, int iLine)
        {
            data.insert(getDataIter(iLine), line);
        }

        auto AppendText(size_t iLine, std::string word)
        {
            data[iLine - 1].append(word);
        }

        auto DeleteText(size_t iLine, size_t iCol, size_t lenght)
        {
            data[iLine - 1].erase(iCol - 1, lenght);
        }

        auto InsertText(size_t iLine, size_t iCol, std::string word)
        {
            data[iLine - 1].insert(iCol - 1, word);
        }

        auto ReplaceText(size_t iLine, size_t iCol, size_t length, std::string word)
        {
            data[iLine - 1].replace(iCol - 1, length, word);
        }

        auto find(std::string str)
        {
            size_t iCol = 0, iLine = 0;

            for (size_t i = 0; auto &line : data)
            {
                auto pos = line.find(str);
                if (pos != std::string::npos)
                {
                    iCol = pos + 1;
                    iLine = i + 1;
                    break;
                }
                i++;
            }
            return std::make_tuple(iLine, iCol);
        }

        auto FindReplace(std::string old, std::string fresh)
        {

            auto [iLine, iCol] = find(old);
            if (iLine > 0 && iCol > 0)
            {
                ReplaceText(iLine, iCol, old.length(), fresh);
            }
        }
    };

} // namespace Salmon