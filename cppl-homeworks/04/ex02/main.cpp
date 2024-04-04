#include <iostream>
#include <catch2/catch_all.hpp>

struct ListNode {
public:
    ListNode(int value, ListNode *prev = nullptr, ListNode *next = nullptr)
            : value(value), prev(prev), next(next) {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode *prev;
    ListNode *next;
};


class List {
public:
    List()
            : m_head(new ListNode(static_cast<int>(0))), m_size(0),
              m_tail(new ListNode(0, m_head)) {
    }

    virtual ~List() {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value) {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value) {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront() {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack() {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear() {
        auto current = m_head->next;
        while (current != m_tail) {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode *extractPrev(ListNode *node) {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode *m_head;
    ListNode *m_tail;
    unsigned long m_size;
};

TEST_CASE("Checking the functions of adding and getting items from a doubly-linked list") {
    List list;

    SECTION("1. PushBack check"){
        CHECK(list.Empty() == true);
        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);
        CHECK(list.Size() == 3);
        CHECK(list.PopBack() == 3);
        CHECK(list.Size() == 2);
        list.PushBack(4);
        list.PopBack();
        CHECK(list.PopBack() == 2);
        CHECK(list.PopBack() == 1);
    }

    SECTION("2. PushFront check"){
        CHECK(list.Empty() == true);
        list.PushFront(1);
        list.PushFront(2);
        list.PushFront(3);
        CHECK(list.Size() == 3);
        CHECK(list.PopBack() == 1);
        CHECK(list.PopFront() == 3);
        CHECK(list.Size() == 1);
        CHECK(list.PopFront() == 2);
        CHECK(list.Size() == 0);
        list.PushFront(99);
    }

    SECTION("3. PopBack check empty list"){
        CHECK(list.Size() == 0);
        try{
            list.PopBack();
        }catch(std::runtime_error){
            CHECK(list.Empty() == true);
        }
    }

    SECTION("4. PopFront check empty list"){
        list.PushBack(99);
        list.PopBack();
        try{
            list.PopFront();
        }catch(std::runtime_error){
            CHECK(list.Size() == 0);
        }
    }
}


int main(int argc, char *argv[]) {
    return Catch::Session().run(argc, argv);
}
