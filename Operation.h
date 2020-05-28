#ifndef KURS_SEM2_OPERATION_H
#define KURS_SEM2_OPERATION_H

#include <string>
#include <iostream>
#include "GenericList.h"

class Operation {
    unsigned int _book;
    unsigned int _reader;
    unsigned int _date;

public:

    Operation();
    Operation(unsigned _book, unsigned _reader, unsigned _date);

    static Operation *from_raw_string(const std::string &line);
    unsigned int get_book() const;
    unsigned int get_reader() const;
    unsigned int get_date() const;
};


#endif //KURS_SEM2_OPERATION_H
