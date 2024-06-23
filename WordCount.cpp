#include <iostream>  
#include <fstream>  
#include <sstream>  
#include <string>  
#include <cctype>  
  
int countCharacters(const std::string& fileName) {  
    std::ifstream file(fileName);  
    if (!file.is_open()) {  
        std::cerr << "Error opening file: " << fileName << std::endl;  
        return 0;  
    }  
  
    int charCount = 0;  
    char ch;  
    while (file.get(ch)) {  
        ++charCount;  
    }  
  
    file.close();  
    return charCount;  
}  
  
int countWords(const std::string& fileName) {  
    std::ifstream file(fileName);  
    if (!file.is_open()) {  
        std::cerr << "Error opening file: " << fileName << std::endl;  
        return 0;  
    }  
  
    std::string line;  
    int wordCount = 0;  
    bool inWord = false;  
  
    while (std::getline(file, line)) {  
        for (char ch : line) {  
            if (std::isspace(ch) || ch == ',') {  
                if (inWord) {  
                    ++wordCount;  
                    inWord = false;  
                }  
            } else {  
                inWord = true;  
            }  
        }  
        // Check if we ended on a word  
        if (inWord) {  
            ++wordCount;  
            inWord = false;  
        }  
    }  
  
    file.close();  
    return wordCount;  
}  
  
int main(int argc, char* argv[]) {  
    if (argc != 3) {  
        std::cerr << "Usage: " << argv[0] << " [parameter] [input_file_name]" << std::endl;  
        std::cerr << "Where [parameter] is one of '-c' or '-w' and [input_file_name] is the name of the input file." << std::endl;  
        return 1;  
    }  
  
    std::string parameter = argv[1];  
    std::string fileName = argv[2];  
  
    if (parameter == "-c") {  
        int charCount = countCharacters(fileName);  
        std::cout << "字符数：" << charCount << std::endl;  
    } else if (parameter == "-w") {  
        int wordCount = countWords(fileName);  
        std::cout << "单词数：" << wordCount << std::endl;  
    } else {  
        std::cerr << "Invalid parameter '" << parameter << "'. It must be '-c' or '-w'." << std::endl;  
        return 1;  
    }  
  
    return 0;  
}