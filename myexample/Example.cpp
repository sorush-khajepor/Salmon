#include <iostream>
#include <vector>
#include <functional>
#include <filesystem>
#include "../include/Salmon.h"

namespace fs = std::filesystem;
using namespace std;

int main(){

  // Editor created.
  

  std::string path = ".";
  for (const auto & entry : fs::directory_iterator(path)){
    auto file = entry.path().filename().string();
    if (file.starts_with("d_")){

      std::cout << file << std::endl;
      Salmon::Editor editor{};
      editor.file.Open(file);
      editor.content.DeleteLine({1,2,3,4,5,6,7,8});
      editor.content.DeleteText(1, 1, 12);
      editor.file.Save();
    }
  }
  
  return 0;
}