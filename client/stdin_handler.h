#ifndef STDIN_HANDLER_H
#define STDIN_HANDLER_H


#include <string>
#include <vector>
class StdinHandler {
public:
    StdinHandler();
    std::vector<std::string> tokenize_line(const std::string& line);

    StdinHandler(const StdinHandler&) = delete;

    StdinHandler& operator=(const StdinHandler&) = delete;
};


#endif  // STDIN_HANDLER_H
