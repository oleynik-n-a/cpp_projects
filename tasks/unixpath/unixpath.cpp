#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    if (path.empty()) {
        return std::string(current_working_dir);
    }
    for (size_t current = 0; current < path.size() - 1; ++current) {
        if (path[current] == '/') {
            continue;
        } else if (path[current] == '.') {
            if (path[current + 1] == '.') {
                current_working_dir = current_working_dir.substr(0, current_working_dir.find_last_of('/'));
                ++current;
            }
        } else {
            int j = 0;
            while (current + j < path.size() && !(path[current + j] == '.' || path[current + j] == '/')) {
                ++j;
            }
            current_working_dir =
                std::string_view(std::string(current_working_dir) + (current_working_dir.ends_with('/') ? "" : "/") +
                std::string(path.substr(current, j)));
            current += j - 1;
        }
    }
    if (current_working_dir.empty()) {
        return "/";
    }
    return std::string(current_working_dir);
}
