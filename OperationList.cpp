#include "OperationList.h"

void OperationList::add(Operation *operation) {
    push(operation);
}

void OperationList::remove(Operation *o) {
    erase(o);
    delete o;
}

int OperationList::load(const std::string &fname) {
    int total_read = 0;
    std::ifstream opFile(fname);
    while(opFile.good()) {
        std::string line;
        std::getline(opFile, line);

        if(line.empty()) {
            continue;
        }

        Operation *newOperation = Operation::from_raw_string(line);
        if(newOperation != nullptr) {
            push(newOperation);
            total_read++;
        } else {
            std::cerr << "Line error" << std::endl;
        }
    }
    return total_read;
}

int OperationList::save(const std::string &fname) {
    std::ofstream ofile(fname);
    if(ofile.bad()) {
        return  -1;
    }
    ListElem *elem = get_head();

    if(elem == nullptr) {
        return -1;
    }

    if(size() > 0) {
        do {
            Operation *operation = (Operation *) ((ListElem *) (elem)->_payload);
            ofile << operation->get_reader() << "|" << operation->get_book() << "|" << operation->get_date()
                  << std::endl;
            elem = get_next(elem);
        } while (elem != nullptr);
    }
    ofile.close();
    return 0;

}

OperationList *OperationList::find_by_reader(const unsigned int id) {
    OperationList *result = new OperationList();
    ListElem *current_elem = get_head();

    if(current_elem == nullptr) {
        return nullptr;
    }

    do {
        Operation *operation = (Operation *) current_elem->_payload;
        if(operation->get_reader() == id) {
            result->add(operation);
        }
        current_elem = GenericList::get_next(current_elem);
    } while(current_elem != nullptr);

    return result;
}

Operation *OperationList::find_by_book_and_reader(unsigned int book_id, unsigned int reader_id) {
    ListElem *current_elem = get_head();
    do {
        Operation *operation = (Operation *) current_elem->_payload;
        if(operation->get_book() == book_id && operation->get_reader() == reader_id) {
            return operation;
        }
        current_elem = get_next(current_elem);
    } while(current_elem != nullptr);

    return nullptr;
}

ReaderList *OperationList::get_readers_with_books() {
    ReaderList *result = new ReaderList();
    ListElem *e = get_head();
    while(e != nullptr) {
        Operation *operation = (Operation *) e->_payload;
        if(result->find_by_id(operation->get_reader()) == nullptr) {
            result->push(new Reader(operation->get_reader()));
        }
        e = get_next(e);
    }
    if(result->size() == 0) {
        delete result;
        return nullptr;
    }
    return result;
}
