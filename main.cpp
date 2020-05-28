#include <string>
#include <iostream>
#include <chrono>
#include "ReaderList.h"
#include "BookList.h"
#include "Operation.h"
#include "OperationList.h"

const std::string readers_file = "readers.txt";
const std::string books_file = "books.txt";
const std::string operations_file = "operations.txt";

ReaderList readerList;
BookList bookList;
OperationList opList;

void show_main_menu() {
    std::cout << "Введите команду:" << std::endl;
    std::cout << "s - поиск по ФИО читателья" << std::endl;
    std::cout << "i - поиск по номеру читательского билета" << std::endl;
    std::cout << "g - выдать книгу читателю" << std::endl;
    std::cout << "r - вернуть книгу в библиотеку" << std::endl;
    std::cout << "a - список доступных к выдаче книг" << std::endl;
    std::cout << "b - список читателей с книгами на руках" << std::endl;
    std::cout << "f - поиск доступных книг по автору" << std::endl;
    std::cout << "n - поиск доступных книг по названию" << std::endl;
    std::cout << std::endl << "q - выйти из программы" << std::endl;
}

std::string read_line(const std::string &prompt) {
    std::string result;
    std::cout << std::endl << prompt << ": ";
    std::getline(std::cin, result, '\n');
    return result;
}

unsigned int read_int(const std::string &prompt) {
    unsigned int result;
    std::cout << std::endl << prompt << ": ";
    std::cin >> result;
    return result;
}

bool read_bool(const std::string &prompt) {
    std::cout << prompt << "[y/n]:";
    char choice;
    std::cin >> choice;
    if(choice == 'y') {
        return true;
    }
    return false;
}

void give_book() {
    std::cout << "Выдача книги." << std::endl;
    std::string book_name = read_line("Название книги");
    Book *b = bookList.find_by_title(book_name);
    if(b == nullptr) {
        std::cout << "Книга не найдена." << std::endl;
        return;
    }

    unsigned int avail = b->get_avail();
    if(avail == 0) {
        std::cout << "К сожалению, сейчас выдать книгу невозможно." << std::endl;
        return;
    } else {
        std::cout << "Доступно " << avail << " экземпляров." << std::endl;
    }

    unsigned int reader_id = read_int("Ведите номер читательского билета");
    Reader *reader = readerList.find_by_id(reader_id);
    if(reader == nullptr) {
        std::cout << "Читательский билет " << reader_id << "не найден." << std::endl;
        return;
    }
    std::string request = "Выдать книгу " + b->get_title() + " читателю " + reader->get_name() +" ?";
    bool give = read_bool(request);
    if(!give) {
        std::cout << "Как скажете." << std::endl;
        return;
    }

    Operation *op = new Operation(b->get_id(), reader->get_id(), (unsigned int ) time(nullptr));
    opList.add(op);
    b->give();
}

void books_on_reader(unsigned int reader_id) {
    OperationList *readers_books = opList.find_by_reader(reader_id);
    if(readers_books == nullptr) {
        std::cout << "Операций выдачи не зафиксировано." << std::endl;
        return;
    }

    std::cout << "У читателя "
              << readerList.find_by_id(reader_id)->get_name() << " "
              << readers_books->size()
              << " книг."
              << std::endl;

    if(readers_books->size() == 0) {
        delete readers_books;
        return;
    }

    ListElem *e = readers_books->get_head();
    do {
        Operation *op = (Operation *) e->_payload;
        Book *book = bookList.find_by_id(op->get_book());
        if(book == nullptr) {
            std::cerr << "Непредвиденная ошибка" << std::endl;
            delete op;
            break;
        }
        std::cout << op->get_book() << " " << book->get_title() << ", " << book->get_author() << std::endl;
        e = GenericList::get_next(e);
    } while (e!= nullptr);
    delete readers_books;

}

void return_book() {
    std::cout << "Возврат книги." << std::endl;
    unsigned int reader_id = read_int("Ведите номер читательского билета");
    Reader *reader = readerList.find_by_id(reader_id);
    if(reader == nullptr) {
        std::cout << "Читательский билет " << reader_id << "не найден." << std::endl;
        return;
    }

    books_on_reader(reader_id);

    unsigned int book_id = read_int("Какую книгу вернуть ");
    Operation *revert_operation = opList.find_by_book_and_reader(book_id,reader_id);

    if(revert_operation != nullptr) {
        opList.remove(revert_operation);
        bookList.find_by_id(book_id)->ret();
    }
}

void list_avail_books() {
    std::cout << "Список книг доступных к выдаче:" << std::endl;
    ListElem *e = bookList.get_head();
    while(e != nullptr) {
        Book *book = (Book *) e->_payload;
        if( book->get_avail() > 0) {
            book->println();
        }
        e = BookList::get_next(e);
    }
}

void list_bad_readers() {
    std::cout << "Читатели с книгами на руках:" << std::endl;
    ReaderList *readers = opList.get_readers_with_books();
    ListElem *e = readers->get_head();
    while(e!= nullptr) {
        Reader *reader = (Reader *) e->_payload;
        readerList.find_by_id(reader->get_id())->println();
        e = GenericList::get_next(e);
    }
}

void list_books_by_author(const std::string &author) {
    BookList *books = bookList.avail_by_author(author);
    if(books == nullptr) {
        std::cout << "Нет свободных экземпляров" << std::endl;
        return;
    }
    ListElem *elem = books->get_head();
    while(elem != nullptr) {
        Book *b = (Book *) elem->_payload;
        b->println();
        elem = GenericList::get_next(elem);
    }
}

void list_books_by_title(const std::string &title) {
    Book *book = bookList.find_by_title(title);
    if(book == nullptr) {
        std::cout << "Книга не найдена. Попробуйте изменить запрос." << std::endl;
        return;
    }
    if(book->get_avail() > 0) {
        book->println();
    } else {
        std::cout << "Нет свободных экземпляров." << std::endl;
    }
}


int main() {
    int readers_count = readerList.load(readers_file);
    int total_books = bookList.load(books_file);
    opList.load(operations_file);

    std::cout << "Каталог содержит " << total_books << " книг" << std::endl;
    std::cout << "Читательских билетов " << readers_count << std::endl;
    std::string cmd;
    for(;;) {
        show_main_menu();
        cmd = read_line("Введите команду");
        std::cout << "====================" << std::endl << std::endl;
        if(cmd == "q") {
            break;
        } else if(cmd == "s") {
            std::string name = read_line("Имя читателя");
            Reader *r = readerList.find_by_name(name);
            if(r != nullptr) {
                books_on_reader(r->get_id());
            } else {
                std::cout << "Читатель '" << name << "' не найден." << std::endl;
            }
        } else if(cmd == "i") {
            unsigned int id = read_int("Номер читательского билета");
            Reader *r = readerList.find_by_id(id);
            if(r != nullptr) {
                books_on_reader(r->get_id());
            } else {
                std::cout << "Билет " << id << " не найден." << std::endl;
            }
        } else if(cmd == "g") { // Give a _book
            give_book();
        } else if(cmd == "r") {
            return_book();
        } else if(cmd == "a") {
            list_avail_books();
        } else if(cmd == "b") {
            list_bad_readers();
        } else if(cmd == "f") {
            std::string author = read_line("Введите автора");
            list_books_by_author(author);
        } else if(cmd == "n") {
            std::string title = read_line("Введите полное название книги");
            list_books_by_title(title);
        }
        std::cout << std::endl;
        std::cout << "Нажмите любую клавишу для продолжения..." << std::endl;
        std::cin.get();
    }
    std::cout << "Сохранение..." << std::endl;
    bookList.save(books_file);
    opList.save(operations_file);
    std::cout << "До свидания." << std::endl;
    
    return 0;
}
