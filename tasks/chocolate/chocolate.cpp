#include "chocolate.h"

bool CanBreakSlices(int height, int width, int slices_amount) {
    return (height % slices_amount == 0 || width % slices_amount == 0 || slices_amount % height == 0 ||
            slices_amount % width == 0) &&
           (height * width > slices_amount);
};
