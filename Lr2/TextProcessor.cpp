#include "TextProcessor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <stdexcept>

void TextProcessor::processFile(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + filename);

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();

    if (text.empty())
        throw std::runtime_error("File is empty.");

    std::string current, longest;
    int count = 0;

    auto processWord = [&](const std::string& w) {
        if (w.empty()) return;
        if (w.size() > longest.size()) {
            longest = w;
            count = 1;
        }
        else if (w == longest) {
            ++count;
        }
        };

    for (char c : text) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            current += c;
        }
        else {
            processWord(current);
            current.clear();
        }
    }

    processWord(current);

    if (longest.empty())
        throw std::runtime_error("No words found in the file.");

    std::cout << "Longest word: " << longest << "\n";
    std::cout << "Occurrences: " << count << "\n";
}