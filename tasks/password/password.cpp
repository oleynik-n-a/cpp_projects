#include "password.h"

bool ValidatePassword(const std::string& password) {
    const int64_t eight = 8;
    const int64_t fourteen = 14;

    if (password.length() < eight || password.length() > fourteen) {
        return false;
    }

    int upper_exist = 0;
    int lower_exist = 0;
    int digit_exist = 0;
    int left_exist = 0;

    for (uint64_t i = 0; i < password.length(); i++) {
        if (!isgraph(password[i])) {
            return false;
        }
        if (isupper(password[i])) {
            upper_exist = 1;
        } else if (islower(password[i])) {
            lower_exist = 1;
        } else if (isdigit(password[i])) {
            digit_exist = 1;
        } else {
            left_exist = 1;
        }
    }

    if (upper_exist + lower_exist + digit_exist + left_exist < 3) {
        return false;
    }

    return true;
}
