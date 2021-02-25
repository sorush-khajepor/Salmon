#include <string>
#include <vector>
#include <functional>
#include <filesystem>


namespace Salmon
{
    class Content
    {

        std::vector<std::string> lines;
        std::vector<std::string> clipboard;

    public:
        auto Clear()
        {
            lines.clear();
        }

        auto begin() { return lines.begin(); }

        auto end() { return lines.end(); }

        auto getDataIter(int iLine)
        {
            return lines.begin() + iLine - 1;
        }

        auto StartsWith(std::string line)
        {
            return lines[0].rfind(line, 0) == 0;
        }

        auto AppendLine(std::string line)
        {
            lines.push_back(line);
        }
        auto ReplaceLine(int iLine, std::string line)
        {
            lines[iLine - 1] = line;
        }

        auto DeleteLine(int iLine)
        {
            lines.erase(getDataIter(iLine));
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

        auto InsertLine(int iLine, std::string line)
        {
            lines.insert(getDataIter(iLine), line);
        }

        auto AppendText(size_t iLine, std::string word)
        {
            lines[iLine - 1].append(word);
        }

        auto DeleteText(size_t iLine, size_t iCol, size_t lenght)
        {
            lines[iLine - 1].erase(iCol - 1, lenght);
        }

        auto InsertText(size_t iLine, size_t iCol, std::string word)
        {
            lines[iLine - 1].insert(iCol - 1, word);
        }

        auto ReplaceText(size_t iLine, size_t iCol, size_t length, std::string word)
        {
            lines[iLine - 1].replace(iCol - 1, length, word);
        }

        auto Copy(size_t iFromLine, size_t iFromCol, size_t iToLine, size_t iToCol )
        {
            clipboard.clear();
            clipboard.push_back(lines[iFromLine-1].substr(iFromCol-1));
            for(size_t iLine=iFromLine+1;iLine<iToLine;iLine++){
                clipboard.push_back(lines[iLine]);
            }
            clipboard.push_back(lines[iToLine-1].substr(0, iToCol));
                
        }
        auto Paste(size_t iLine, size_t iCol)
        {
            auto rest = lines[iLine-1].substr(iCol-1);
            lines[iLine-1].erase(iCol-1);
            InsertText(iLine, iCol, clipboard[0]);
            for(size_t i=1;i<clipboard.size()-1;i++){
                InsertLine(iLine+i, clipboard[i]);
            }
            auto last = iLine+clipboard.size()-1;
            if (lines.size()>= last){
                InsertText(last, 1, clipboard.back());
            } else{
                InsertLine(last, clipboard.back());
            }
            AppendText(lines.size(), rest);
        }

        auto find(std::string str)
        {
            size_t iCol = 0, iLine = 0;

            for (size_t i = 0; auto &line : lines)
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