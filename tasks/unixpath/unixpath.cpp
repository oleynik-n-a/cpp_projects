#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string result = std::string(current_working_dir);
    if (path.empty()) {
        return result;
    }
    for (size_t current = 0; current < path.size(); ++current) {
        if (path[current] == '/') {
            continue;
        } else if (path[current] == '.') {
            if (current + 1 < path.size() && path[current + 1] == '.') {
                result = result.substr(0, result.find_last_of('/'));
                ++current;
            }
        } else {
            int j = 0;
            while (current + j < path.size() && !(path[current + j] == '.' || path[current + j] == '/')) {
                ++j;
            }
            if (result.substr(result.find_last_of('/') + 1, result.size() -
                    result.find_last_of('/') - 1) != path.substr(current, j)) {
                result = result + (result.ends_with('/') ? "" : "/") + std::string(path.substr(current, j));
                current += j - 1;
            }
        }
    }
    if (result.empty()) {
        return "/";
    }
    return result;
}
