#include "Operation.h"

Operation::Operation(){
    _reader = 0;
    _book = 0;
    _date = 0;
}

Operation::Operation(unsigned book, unsigned reader, unsigned date) {
    _book = book;
    _reader = reader;
    _date = date;
}

Operation *Operation::from_raw_string(const std::string &line) {
    unsigned int book_id;
    unsigned int reader_id;
    unsigned int optime;

    if(line.empty()) {
        return nullptr;
    }

    ::sscanf(line.c_str(),"%u|%u|%u", &reader_id, &book_id, &optime);

    Operation *result = new Operation();
    result->_book = book_id;
    result->_reader = reader_id;
    result->_date = optime;

    return result;
}

unsigned int Operation::get_book() const {
    return _book;
}

unsigned int Operation::get_reader() const {
    return _reader;
}

unsigned int Operation::get_date() const {
    return _date;
}