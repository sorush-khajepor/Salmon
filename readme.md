

Salmon is a small text editor library written in C++. It is very handy if you need to make the same changes to many files. For example, you want to add a header to 100 CSV files. 

## Example

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include <filesystem>
#include "include/Salmon.h"

namespace fs = std::filesystem;
using namespace std;

int main(){

  // copy sample file to build directory
  const auto copyOptions = fs::copy_options::overwrite_existing;
  fs::copy("../sample.txt",".", copyOptions);

  // Editor created.
  Salmon::Editor editor{};

  editor.file.Open("sample.txt");
  
  // Editing lines
  editor.content.AppendLine("I like haggis.");
  editor.content.InsertLine("I am looking forward to summer.",3);
  editor.content.ReplaceLine(2,"A usual rainy day in Edinburgh.");
  editor.content.DeleteLine(1);

  // Editing text
  editor.content.AppendText(3, " It's OK.");
  editor.content.DeleteText(4, 9, 21-9+1);
  editor.content.ReplaceText(1,3,11,"rare warm sunny");
  editor.content.InsertText(3, 43, ", because of covid-19");
  editor.content.FindReplace("haggis", "Irn Bru");

  // save the file
  editor.file.Save();

  // Save as new file, drop the old file
  // and work on the new file from here.
  editor.file.SaveAs("sample_copy.txt");
  editor.content.DeleteLine({1,3,2});
  editor.file.Save();


  return 0;
}
```

## Compile

You need CMake to compile Salmon. Clone this repo. To compile the example in a terminal run

```sh
./build.sh
```


