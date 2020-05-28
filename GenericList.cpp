#include "GenericList.h"

GenericList::GenericList() {
    _elems = nullptr;
    _count = 0;
}

size_t GenericList::size() const {
    return _count;
}

void GenericList::push(void *elem) {
    if(_elems == nullptr) {
        _elems = new ListElem;
        _elems->_payload = elem;
        _count++;
        return;
    }

    ListElem *e = _elems;
    while(e->_next != nullptr) {
        e = e->_next;
    }

    ListElem *newElem = new ListElem();
    newElem->_prev = e;
    newElem->_payload = elem;
    newElem->_next = nullptr;
    e->_next = newElem;
    _count++;
}

void GenericList::erase(void *p) {
    ListElem *e = _elems;
    while(e->_next != nullptr) {
        if(e->_payload == p) {
            break;
        }
        e = e->_next;
    }
    if(e->_payload == p) {
        e->_payload = nullptr;
        if(e->_next != nullptr) {
            e->_next->_prev = e->_prev;
        }
        if(e->_prev != nullptr) {
            e->_prev->_next = e->_next;
        } else { // Erasing first element
            _elems = e->_next;
        }
        delete e;
        _count--;
    }
}

ListElem *GenericList::get_head() const {
    return _elems;
}

ListElem *GenericList::get_next(const ListElem *listElem) {
    if(listElem != nullptr) {
        return listElem->_next;
    } else {
        return nullptr;
    }
}

GenericList::~GenericList() {
    ListElem *e = _elems;
    while(e->_next != nullptr) {
        ListElem *next = e->_next;
        delete e;
        e = next;
    }
}
