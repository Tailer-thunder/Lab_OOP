#include "../include/Thirteen.hpp"
#include <iostream>



bool isThirteen(unsigned char t) {
    return (t >= '0' && t <= '9') || (t >= 'A' && t <= 'C');
}

Thirteen::Thirteen() {
    size = 1;
    array = new unsigned char[1]{'0'};
}


Thirteen::Thirteen(const size_t& n, unsigned char t) {
    if (!isThirteen(t)) throw std::invalid_argument("Некорректный символ");
    if (t == '0') {
        size = 1;
        array = new unsigned char[1]{'0'};
    } else {
        size = n;
        array = new unsigned char[n];
        for (size_t i = 0; i < n; i++) {
            array[i] = t;
        }
    }
}


Thirteen::Thirteen(const std::initializer_list<unsigned char>& t) {
    for (auto a : t) {
        if (!isThirteen(a)) throw std::invalid_argument("Некорректный символ");
    }

    size_t zeros = 0;
    for (auto c : t) {
        if (c == '0') {
            zeros += 1;
        } else break;
    }
    size = t.size() - zeros;
    if (size == 0) {
        size = 1;
        array = new unsigned char[1]{'0'};
    } else {
        array = new unsigned char[size];
        size_t i = 0;
        for (auto it = t.end() - 1; it != t.begin() - 1 + zeros; --it) {
            array[i++] = *it;
        }
    }
}


Thirteen::Thirteen(const std::string& t) {
    for (size_t i = 0; i < t.size(); i++) {
        if (!isThirteen(t[i])) throw std::invalid_argument("Некорректный символ");
    }

    size_t zeros = 0;
    for (size_t i = 0; i < t.size(); i++) {
        if (t[i] == '0') {
            zeros += 1;
        } else break;
    }
    size = t.size() - zeros;
    if (size == 0) {
        size = 1;
        array = new unsigned char[1]{'0'};
    } else {
        array = new unsigned char[size];
        for (size_t i = 0; i < size; i++) {
            array[i] = t[t.size() - 1 - i];
        }
    }
}


Thirteen::Thirteen(const Thirteen& other) {
    size = other.size;
    array = new unsigned char[size];
    for (size_t i = 0; i < size; i++) {
        array[i] = other.array[i];
    }
}

Thirteen::Thirteen(Thirteen&& other) noexcept {
    size = other.size;
    array = other.array;
    other.size = 0;
    other.array = nullptr;
}


bool Thirteen::operator==(const Thirteen& other) const {
    if (size != other.size) return false;
    for (size_t i = 0; i < size; i++) {
        if (array[i] != other.array[i]) return false;
    }
    return true;
}

bool Thirteen::operator!=(const Thirteen& other) const {
    return !(*this == other);
}


bool Thirteen::operator<(const Thirteen& other) const {
    if (size < other.size) {
        return true;
    } else if (size > other.size) {
        return false;
    } else {
        int a, b;
        for (int i = static_cast<int>(size) - 1; i >= 0; i--) {
            a = (array[i] >= 'A') ? (array[i] - 'A' + 10) : (array[i] - '0');
            b = (other.array[i] >= 'A') ? (other.array[i] - 'A' + 10) : (other.array[i] - '0');
            if (a < b) return true;
            else if (a > b) return false;
        }
    }
    return false;
}


bool Thirteen::operator>(const Thirteen& other) const {
    if (size < other.size) {
        return false;
    } else if (size > other.size) {
        return true;
    } else {
        int a, b;
        for (int i = static_cast<int>(size) - 1; i >= 0; i--) {
            a = (array[i] >= 'A') ? (array[i] - 'A' + 10) : (array[i] - '0');
            b = (other.array[i] >= 'A') ? (other.array[i] - 'A' + 10) : (other.array[i] - '0');
            if (a < b) return false;
            else if (a > b) return true;
        }
    }
    return false;
}


Thirteen& Thirteen::operator=(const Thirteen& other) {
    if (this != &other) {
        delete[] array;
        size = other.size;
        array = new unsigned char[size];
        for (size_t i = 0; i < size; i++) {
            array[i] = other.array[i];
        }
    }
    return *this;
}

Thirteen& Thirteen::operator+=(const Thirteen& other) {
    std::string res = "";
    int num1, num2, sum;
    int remainder = 0;
    for (size_t i = 0; i < std::max(size, other.size); i++) {
        num1 = i < size ? ((array[i] >= 'A') ? (array[i] - 'A' + 10) : (array[i] - '0')) : 0;
        num2 = i < other.size ? ((other.array[i] >= 'A') ? (other.array[i] - 'A' + 10) : (other.array[i] - '0')) : 0;
        sum = num1 + num2 + remainder;

        if (sum >= 13) {
            remainder = 1;
            sum %= 13;
        } else remainder = 0;

        res += (sum < 10) ? (sum + '0') : (sum - 10 + 'A');
    }

    if (remainder > 0) res += '1';

    delete[] array;

    size = res.size();
    array = new unsigned char[size];
    
    for (size_t i = 0; i < size; i++) {
        array[i] = res[i];
    }

    return *this;
}


Thirteen& Thirteen::operator-=(const Thirteen& other) {
    if (other > *this) throw std::logic_error("Разность не может быть отрицательной");
    std::string res = "";
    int num1, num2, diff;
    int borrow = 0;

    for (size_t i = 0; i < size; i++) {
        num1 = i < size ? ((array[i] >= 'A') ? (array[i] - 'A' + 10) : (array[i] - '0')) : 0;
        num2 = i < other.size ? ((other.array[i] >= 'A') ? (other.array[i] - 'A' + 10) : (other.array[i] - '0')) : 0;

        diff = num1 - num2 - borrow;

        if (diff < 0) {
            borrow = 1;
            diff += 13;
        } else {
            borrow = 0;
        }

        res += (diff < 10) ? (diff + '0') : (diff - 10 + 'A');
    }

    while (res.size() > 1 && res.back() == '0') {
        res.pop_back();
    }

    delete[] array;

    size = res.size();
    array = new unsigned char[size];

    for (size_t i = 0; i < size; i++) {
        array[i] = res[i];
    }

    return *this;
}


std::ostream& Thirteen::print(std::ostream& os) const {
    for (size_t i = size; i > 0; i--) {
        os << array[i - 1];
    }
    return os;
}


Thirteen::~Thirteen() {
    if (size > 0) {
        size = 0;
        delete[] array;
        array = nullptr;
    }
}