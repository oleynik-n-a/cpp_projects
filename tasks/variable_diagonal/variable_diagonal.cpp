#include "variable_diagonal.h"

int** BuildDiagonalArray(size_t lines, size_t columns) {
    int i_lines = static_cast<int>(lines);
    int i_columns = static_cast<int>(columns);

    int** table = new int*[i_lines];
    for (int i = 0; i < i_lines; i++) {
        table[i] = new int[i_columns];
    }

    for (int i = 0; i < i_lines; ++i) {
        for (int j = 0; j < static_cast<int>(i_columns); ++j) {
            table[i][j] = i + j < i_lines
                    ? (i + j) * (i + j + 1) / 2 + i
                    : i_lines * i_columns -
                      (i_lines + i_columns - (i + j) - 2) * (i_lines + i_columns - (i + j) - 1) /
                      2 - i_lines + i;
        }
    }
    return table;
}
