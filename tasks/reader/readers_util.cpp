#include "readers_util.h"

#include <iostream>

LimitReader::LimitReader(std::unique_ptr<Reader> reader, size_t limit) : reader_(std::move(reader)), limit_(limit) {
}

size_t LimitReader::Read(char* buf, size_t len) {
    size_t r_max = std::min(len, limit_);
    size_t result = reader_->Read(buf, r_max);
    limit_ -= result;
    return result;
}

TeeReader::TeeReader(std::vector<std::unique_ptr<Reader>> readers) : readers_(std::move(readers)) {
}

size_t TeeReader::Read(char* buf, size_t len) {
    while (true) {
        if (current_ == readers_.size()) {
            return 0;
        }
        size_t result = readers_[current_]->Read(buf, len);
        if (result == 0) {
            ++current_;
            continue;
        }
        return result;
    }
}

HexDecodingReader::HexDecodingReader(std::unique_ptr<Reader> reader) : reader_(std::move(reader)) {
}

char Hex2Num(char ch) {
    const int ten = 10;
    return static_cast<char>(ch >= '0' && ch <= '9' ? ch - '0' : ch - 'A' + ten);
}

size_t HexDecodingReader::Read(char* buf, size_t len) {
    std::string raw(len * 2, '\0');
    size_t r_len = reader_->Read(&(raw[0]), raw.size());
    for (size_t i = 0; i < r_len; i += 2) {
        buf[i / 2] = (Hex2Num(raw[i]) << 4) | (Hex2Num(raw[i + 1]));
    }
    return r_len / 2;
}
