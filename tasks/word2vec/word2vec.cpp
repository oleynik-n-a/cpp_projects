#include "word2vec.h"

#include <vector>

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<std::string> output;
    int max = INT32_MIN;
    for (int i = 1; i < static_cast<int>(vectors.size()); ++i) {
        int scalar = vectors[0][0] * vectors[i][0] + vectors[0][1] * vectors[i][1] + vectors[0][2] * vectors[i][2];
        if (max < scalar) {
            max = scalar;
        }
    }
    for (int i = 1; i < static_cast<int>(vectors.size()); ++i) {
        int scalar = vectors[0][0] * vectors[i][0] + vectors[0][1] * vectors[i][1] + vectors[0][2] * vectors[i][2];
        if (max == scalar) {
            output.push_back(words[i]);
        }
    }
    return output;
}
