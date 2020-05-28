#include "ReaderList.h"

int ReaderList::load(const std::string &fname) {
    int total_read = 0;
    std::ifstream readersList(fname);
    while(readersList.good()) {
        std::string line;
        std::getline(readersList, line);
        if(line.empty()) {
            continue;
        }

        Reader *newReader = Reader::from_raw_string(line);
        if(newReader != nullptr) {
            push(newReader);
            total_read++;
        } else {
            std::cerr << "Line error" << std::endl;
        }
    }
    return total_read;
}

Reader *ReaderList::find_by_id(const unsigned int id) {
    ListElem *current_elem = get_head();
    if(current_elem == nullptr) {
        return nullptr;
    }
    do {
        Reader *reader = (Reader *) current_elem->_payload;
        if(reader->get_id() == id) {
            return reader;
        }
        current_elem = GenericList::get_next(current_elem);
    } while(current_elem != nullptr);

    return nullptr;
}

Reader *ReaderList::find_by_name(const std::string &name) {
    ListElem *current_elem = get_head();
    do {
        Reader *reader = (Reader *) current_elem->_payload;
        if(reader->get_name() == name) {
            return reader;
        }
        current_elem = GenericList::get_next(current_elem);
    } while(current_elem != nullptr);

    return nullptr;
}
