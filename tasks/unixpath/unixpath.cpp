#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string result = std::string(current_working_dir);
    if (path == "/") {
        return "/";
    }
    if (path.starts_with('/') && path.size() > 1) {
        result.clear();
        result.push_back('/');
        for (size_t i = 1; i < path.size(); i++) {
            if (!(path[i] == '/' && result.ends_with('/'))) {
                result.push_back(path[i]);
            }
        }
        if (result.ends_with('/')) {
            return result.substr(0, result.size() - 1);
        }
        return result;
    }
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
            result = result + (result.ends_with('/') ? "" : "/") + std::string(path.substr(current, j));
            current += j - 1;
        }
    }
    if (result.empty() || result == "/") {
        return "/";
    }
    if (result.ends_with('/')) {
        return result.substr(0, result.size() - 1);
    }
    return result;
}
