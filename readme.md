

Salmon is a small text editor library written in C++. It is very handy if you need to make the same changes to many files. For example, you want to add a header to 100 CSV files. 

## Example

```cpp
  // Editor created.
  Salmon::Editor editor{};

  editor.file.Open("sample.txt");
  
  // Check if file starts with a specefic signature
  if (editor.content.StartsWith("Edinburgh")){
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
  editor.content.ReplaceText(1,3,11,"rare warm sunny");
  editor.content.InsertText(3, 43, ", because of covid-19");
  editor.content.FindReplace("haggis", "Irn Bru");

  // Copy-Paste
  editor.content.Copy(1,26,2,24);
  editor.content.Paste(5,8);

  // save the file
  editor.file.Save();

  // Save as new file, drop the old file
  // and work on the new file from here.
  editor.file.SaveAs("sample_copy.txt");
  editor.content.DeleteLine({1,3,2});
  editor.file.Save();
```

## Compile

You need CMake to compile Salmon. Clone this repo. To compile the example in a terminal run

```sh
./build.sh
```


