#include "../include/Figure.h"


std::ostream &operator<<(std::ostream &stream, const Figure *obj) {
    if (obj) {
        return obj->print(stream);  
    } else {
        stream << "Ошибка: объект Figure равен nullptr"; 
        return stream;
    }
}


std::istream &operator>>(std::istream &stream, Figure *obj) {
    if (obj) {
        return obj->read(stream); 
    } else {
        stream.setstate(std::ios::failbit); 
        return stream;
    }
}