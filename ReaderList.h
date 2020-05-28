#ifndef KURS_SEM2_READERLIST_H
#define KURS_SEM2_READERLIST_H

#include <string>
#include <fstream>
#include <iostream>

#include "Reader.h"
#include "GenericList.h"

class ReaderList : public GenericList {

public:

    int load(const std::string &fname);
    Reader *find_by_id(const unsigned int id);
    Reader *find_by_name(const std::string &name);

};


#endif //KURS_SEM2_READERLIST_H
