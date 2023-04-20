#include "const_diagonal.h"

void BuildDiagonalArray(TableType table) {
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            table[i][j] = (i + j + 1) * (i + j) / 2 + 2 * i - (i + j > LINES ? j : 0);
        }
    }
}
