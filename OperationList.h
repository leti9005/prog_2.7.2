#ifndef KURS_SEM2_OPERATIONLIST_H
#define KURS_SEM2_OPERATIONLIST_H

#include <fstream>
#include <iostream>
#include "GenericList.h"
#include "Operation.h"
#include "Book.h"
#include "ReaderList.h"

class OperationList : public GenericList {

public:

    void add(Operation *operation);
    void remove(Operation *o);
    int load(const std::string &fname) ;
    int save(const std::string &fname);
    OperationList *find_by_reader(unsigned int id);
    Operation *find_by_book_and_reader(unsigned int book_id, unsigned int reader_id);
    ReaderList *get_readers_with_books();

};


#endif //KURS_SEM2_OPERATIONLIST_H
