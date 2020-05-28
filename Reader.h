#ifndef KURS_SEM2_READER_H
#define KURS_SEM2_READER_H

#include <string>
#include <iostream>

class Reader {
    unsigned int _id;
    std::string _name;

public:

    Reader();
    explicit Reader(unsigned int id);
    unsigned int get_id() const;
    std::string get_name() const;
    static Reader *from_raw_string(std::string line);
    void println() const;

};


#endif //KURS_SEM2_READER_H
