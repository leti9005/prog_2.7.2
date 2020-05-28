#ifndef KURS_SEM2_GENERICLIST_H
#define KURS_SEM2_GENERICLIST_H

#include <cstddef>

class ListElem {

public:

    ListElem *_prev;
    void *_payload;
    ListElem *_next;

    ListElem() {
        _prev = nullptr;
        _payload = nullptr;
        _next = nullptr;
    }

};

class GenericList {

    ListElem *_elems;
    size_t _count;

public:
    GenericList();
    ~GenericList();
    size_t size() const;
    void push(void *elem);
    void erase(void *p);
    ListElem *get_head() const;
    static ListElem *get_next(const ListElem *listElem);

};


#endif //KURS_SEM2_GENERICLIST_H
