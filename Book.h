#ifndef KURS_SEM2_BOOK_H
#define KURS_SEM2_BOOK_H

#include <string>
#include <iostream>

class Book {
    unsigned int _id;
    std::string _title;
    std::string _author;
    unsigned int _avail;

public:
    unsigned int get_id() const;
    std::string get_title() const;
    std::string get_author() const;
    unsigned int get_avail() const;

    Book() : _id(0), _title(), _author(), _avail(0) {
    }

    static Book *from_raw_string(std::string line);
    void give();
    void ret();
    void println() const;

};


#endif //KURS_SEM2_BOOK_H
