#pragma once
#include <string>
#include <fstream>
#include <sstream>
std::string load_file(const std::string& path) {
    auto ss = std::ostringstream{};
    std::ifstream file(path);
    ss << file.rdbuf();
    return ss.str();
}
