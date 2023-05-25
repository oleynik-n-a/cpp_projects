#include "word2vec.h"

#include <vector>

int Scalar(std::vector<int> vector1, std::vector<int> vector2) {
    int scalar = 0;
    for (int i = 0; i < static_cast<int>(vector1.size()); ++i) {
        scalar += vector1[i] * vector2[i];
    }
    return scalar;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<std::string> output;
    int max = Scalar(vectors[0], vectors[1]);
    for (int i = 1; i < static_cast<int>(vectors.size()); ++i) {
        int scalar = Scalar(vectors[0], vectors[i]);
        if (max < scalar) {
            max = scalar;
        }
    }
    for (int i = 1; i < static_cast<int>(vectors.size()); ++i) {
        int scalar = Scalar(vectors[0], vectors[i]);
        if (max == scalar) {
            output.push_back(words[i]);
        }
    }
    return output;
}
