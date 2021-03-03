#include <string>
#include <vector>
#include <span>
#include <ranges>
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

        decltype(auto) begin() { return lines.begin(); }

        decltype(auto) end() { return lines.end(); }

        auto GetPos(const size_t& iLineOrCol)
        {
            return iLineOrCol - 1;
        }

        auto GetPos(const size_t& iLine, const size_t& iCol)
        {
            return std::tuple<size_t, size_t>(GetPos(iLine), GetPos(iCol));
        }

        auto getLinesIter(const size_t& iLine)
        {
            return lines.begin() + GetPos(iLine);
        }

        auto &GetLine(size_t iLine)
        {
            return lines[GetPos(iLine)];
        }

        auto StartsWith(const std::string& line)
        {
            return lines[0].rfind(line, 0) == 0;
        }

        auto AppendLine(std::string line)
        {
            lines.push_back(std::move(line));
        }

        auto ReplaceLine(int iLine, std::string line)
        {
            GetLine(iLine) = std::move(line);
        }

        auto DeleteLine(int iLine)
        {
            lines.erase(getLinesIter(iLine));
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
            DeleteLine(std::move(iLines));
        }

        auto InsertLine(size_t iLine, std::string line)
        {
            lines.insert(getLinesIter(iLine), std::move(line));
        }

        auto InsertLines(size_t iLine, std::vector<std::string> lines)
        {
            for (auto &line : lines | std::views::reverse)
                InsertLine(iLine, std::move(line));
        }

        auto InsertLines(size_t iLine, std::span<std::string> lines)
        {
            for (auto &line : lines | std::views::reverse)
                InsertLine(iLine, line);
        }

        auto AppendText(size_t iLine, std::string word)
        {
            GetLine(iLine).append(std::move(word));
        }

        auto DeleteText(size_t iLine, size_t iCol, size_t lenght)
        {
            GetLine(iLine).erase(GetPos(iCol), lenght);
        }

        auto InsertText(size_t iLine, size_t iCol, std::string word)
        {
            GetLine(iLine).insert(GetPos(iCol), std::move(word));
        }

        auto ReplaceText(size_t iLine, size_t iCol, size_t length, std::string word)
        {
            GetLine(iLine).replace(GetPos(iCol), length, std::move(word));
        }

        auto LineSubStr(size_t iLine, size_t iFromCol, size_t length)
        {
            return GetLine(iLine).substr(GetPos(iFromCol), length);
        }

        auto LineSubStr(size_t iLine, size_t iFromCol)
        {
            return LineSubStr(iLine, iFromCol, GetLine(iLine).size());
        }

        auto InlineCopy(size_t iLine, size_t iFromCol, size_t iToCol)
        {
            clipboard.clear();
            clipboard.push_back(LineSubStr(iLine, iFromCol, iToCol - iFromCol + 1));
        }

        auto MultiLineCopy(size_t iFromLine, size_t iFromCol, size_t iToLine, size_t iToCol)
        {
            clipboard.clear();
            clipboard.push_back(LineSubStr(iFromLine, iFromCol));
            for (size_t iLine = iFromLine + 1; iLine < iToLine; iLine++)
            {
                clipboard.push_back(GetLine(iLine));
            }
            clipboard.push_back(LineSubStr(iToLine, 1, iToCol));
        }

        auto Copy(size_t iFromLine, size_t iFromCol, size_t iToLine, size_t iToCol)
        {
            if (iFromLine == iToLine)
                InlineCopy(iFromLine, iFromCol, iToCol);
            else
                MultiLineCopy(iFromLine, iFromCol, iToLine, iToCol);
        }

        auto PasteInline(size_t iLine, size_t iCol)
        {
            InsertText(iLine, iCol, clipboard[0]);
        }

        auto PasteMultiLine(size_t iLine, size_t iCol)
        {

            auto rest = LineSubStr(iLine, iCol);
            GetLine(iLine).erase(GetPos(iCol));

            InsertText(iLine, iCol, clipboard[0]);

            InsertLines(iLine + 1, std::span(&clipboard[1], clipboard.size() - 2));

            auto iLast = iLine + clipboard.size() - 1;

            InsertLine(iLast, clipboard.back());

            AppendText(iLast, std::move(rest));
        }

        auto Paste(size_t iLine, size_t iCol)
        {
            if (clipboard.size() < 2)
                PasteInline(iLine, iCol);
            else
                PasteMultiLine(iLine, iCol);
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