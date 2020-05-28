#ifndef KURS_SEM2_BOOKLIST_H
#define KURS_SEM2_BOOKLIST_H

#include <string>
#include <iostream>
#include <fstream>

#include "Book.h"
#include "GenericList.h"

class BookList : public GenericList {

public:

    int save(const std::string &fname);
    int load(const std::string &fname);
    Book *find_by_id(unsigned int id);
    Book *find_by_title(const std::string& title);
    BookList *avail_by_author(const std::string& author);

};


#endif //KURS_SEM2_BOOKLIST_H
