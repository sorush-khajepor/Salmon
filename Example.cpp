#include <iostream>
#include <filesystem>
#include "include/Salmon.h"

namespace fs = std::filesystem;
using namespace std;

int main()
{

  // copy sample file to build directory
  const auto copyOptions = fs::copy_options::overwrite_existing;
  fs::copy("../sample.txt", ".", copyOptions);

  // Editor created.
  Salmon::Editor editor{};

  editor.file.Open("sample.txt");

  // Check if file starts with a specefic signature
  if (editor.content.StartsWith("Edinburgh"))
  {
    // do stuff
  };

  // Editing lines
  editor.content.AppendLine("I like haggis.");
  editor.content.InsertLine(3, "I am looking forward to summer.");
  editor.content.ReplaceLine(2, "A usual rainy day in Edinburgh.");
  editor.content.DeleteLine(1);

  // Editing text
  editor.content.AppendText(3, " It's OK.");
  editor.content.DeleteText(4, 9, 13);
  editor.content.ReplaceText(1, 3, 11, "rare warm sunny");
  editor.content.InsertText(3, 43, ", because of covid-19");
  editor.content.FindReplace("haggis", "Irn Bru");

  // Copy-Paste
  editor.content.Copy(1, 26, 2, 24);
  editor.content.Paste(5, 8);

  // save the file
  editor.file.Save();

  // Save as new file, drop the old file
  // and work on the new file from here.
  editor.file.SaveAs("sample_copy.txt");
  editor.content.DeleteLine({1, 3, 2});
  editor.file.Save();

  return 0;
}