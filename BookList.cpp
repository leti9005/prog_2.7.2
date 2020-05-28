#include "BookList.h"

int BookList::save(const std::string &fname) {
    std::ofstream ofile(fname);
    if(ofile.bad()) {
        return  -1;
    }
    ListElem *elem = get_head();

    if(elem == nullptr) {
        return -1;
    }

    do {
        Book *book = (Book *) elem->_payload;
        ofile << book->get_id() << "|" << book->get_author() << "|" << book->get_title() << "|" << book->get_avail() << std::endl;
        elem = get_next(elem);
    } while(elem != nullptr);

    ofile.close();
    return 0;
}

int BookList::load(const std::string &fname) {
    int total_read = 0;
    std::ifstream bookFile(fname);
    while(bookFile.good()) {
        std::string line;
        std::getline(bookFile, line);

        if(line.empty()) {
            continue;
        }

        Book *newBook = Book::from_raw_string(line);
        if(newBook != nullptr) {
            push(newBook);
            total_read++;
        } else {
            std::cerr << "Line error" << std::endl;
        }
    }
    return total_read;
}

Book *BookList::find_by_id(unsigned int id) {
    ListElem *current_elem = get_head();
    do {
        Book *book = (Book *) current_elem->_payload;
        if(book->get_id() == id) {
            return book;
        }
        current_elem = GenericList::get_next(current_elem);
    } while(current_elem != nullptr);

    return nullptr;
}

Book *BookList::find_by_title(const std::string& title) {
    ListElem *current_elem = get_head();
    do {
        Book *book = (Book *) current_elem->_payload;
        if(book->get_title() == title) {
            return book;
        }
        current_elem = GenericList::get_next(current_elem);
    } while(current_elem != nullptr);

    return nullptr;
}

BookList *BookList::avail_by_author(const std::string& author) {
    BookList *result = new BookList();
    ListElem *current_elem = get_head();
    do {
        Book *book = (Book *) current_elem->_payload;
        if(book->get_author() == author && book->get_avail() > 0) {
            result->push(book);
        }
        current_elem = GenericList::get_next(current_elem);
    } while(current_elem != nullptr);
    if(result->size() == 0) {
        return nullptr;
    }
    return result;
}
