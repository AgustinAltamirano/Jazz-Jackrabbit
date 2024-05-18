#include "stdin_handler.h"

#include <sstream>

StdinHandler::StdinHandler() {}

std::vector<std::string> StdinHandler::tokenize_line(const std::string& line) {
    std::stringstream ss(line);
    std::vector<std::string> tokens;
    std::string token = "";
    while (std::getline(ss, token, ' ')) {
        if (token == "")
            continue;
        tokens.push_back(token);
    }
    return tokens;
}
