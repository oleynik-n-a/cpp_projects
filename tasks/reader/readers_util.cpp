#include "readers_util.h"

#include <memory>
#include <vector>

TeeReader MakeTee(const std::vector<std::string>& chunks) {
    std::vector<std::unique_ptr<Reader>> readers;
    for (auto c : chunks) {
        readers.emplace_back(MakeStringReader(c));
    }
    return TeeReader(std::move(readers));
}
