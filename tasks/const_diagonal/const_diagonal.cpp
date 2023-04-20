#include "const_diagonal.h"

void BuildDiagonalArray(TableType table) {
    for (int i = 0; i < LINES; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            table[i][j] = i + j <= LINES + COLUMNS ?
                          (i + j) * (i + j + 1) / 2 + i :
                          LINES * COLUMNS - (LINES + COLUMNS - (i + j) - 2) *
                          (LINES + COLUMNS - (i + j) - 1) / 2 + LINES - i;
        }
    }
}
