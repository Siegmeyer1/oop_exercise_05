#ifndef OOP_EXERCISE_05_QUEUE_H
#define OOP_EXERCISE_05_QUEUE_H

#include <iterator>
#include <memory>

namespace containers {
    //namespace
    //
    template<class T>
    class queue {
    private:
        struct element;
        size_t size = 0;
    public:
        queue() = default;

        class forward_iterator {
        public:
            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;
            explicit forward_iterator(element* ptr);
            T& operator*();
            forward_iterator& operator++();
            forward_iterator operator++(int);
            bool operator== (const forward_iterator& other) const;
            bool operator!= (const forward_iterator& other) const;
        private:
            element* it_ptr;
            friend queue;
        };

        forward_iterator begin();
        forward_iterator end();
        void push(const T& value);
        T& top();
        void pop();
        size_t length();
        void delete_by_it(forward_iterator d_it);
        void delete_by_number(size_t N);
        void insert_by_it(forward_iterator ins_it, T& value);
        void insert_by_number(size_t N, T& value);
        queue& operator=(queue& other);
    private:
        struct element {
            T value;
            std::unique_ptr<element> next_element = nullptr;
            forward_iterator next();
        };

        static std::unique_ptr<element> push_impl(std::unique_ptr<element> cur, const T& value);
        std::unique_ptr<element> first = nullptr;
    };//===============================end-of-class-queue======================================//

    template<class T>
    typename queue<T>::forward_iterator queue<T>::begin() {
        if (size == 0) {
            return forward_iterator(nullptr);
        }
        return forward_iterator(first.get());
    }

    template<class T>
    typename queue<T>::forward_iterator queue<T>::end() {
        return forward_iterator(nullptr);
    }
//=========================base-methods-of-queue==========================================//
    template<class T>
    size_t queue<T>::length() {
       return size;
    }

    template<class T>
    void queue<T>::push(const T& value) {
       first = push_impl(std::move(first), value);
       size++;
    }

    template<class T>
    std::unique_ptr<typename queue<T>::element> queue<T>::push_impl(std::unique_ptr<element> cur, const T& value) {
        if (cur != nullptr) {
            cur->next_element = push_impl(std::move(cur->next_element), value);
            return cur;
        }
        return std::unique_ptr<element>(new element{value});
    }

    template<class T>
    void queue<T>::pop() {
        if (size == 0) {
            throw std::logic_error ("can`t pop from empty queue");
        }
        first = std::move(first->next_element);
        size--;
    }

    template<class T>
    T& queue<T>::top() {
        if (size == 0) {
            throw std::logic_error ("queue is empty, lol, it has no top");
        }
        return first->value;
    }
//=================================advanced-methods========================================//
    template<class T>
    queue<T>& queue<T>::operator=(queue<T>& other){
        size = other.size;
        first = std::move(other.first);
    }

    template<class T>
    void queue<T>::delete_by_it(containers::queue<T>::forward_iterator d_it) {
        queue<T> res;
        int flag = 0;
        T tmp;
        forward_iterator i = this->begin(), end = this->end();
        while(i != end) {
            if (i == d_it) {
                ++i;
                flag = 1;
                this->pop();
            } else {
                ++i;
                tmp = this->top();
                res.push(tmp);
                this->pop();
            }
        }
        if (!flag) throw std::logic_error ("no such element in queue");
        *this = res;
    }

    template<class T>
    void queue<T>::delete_by_number(size_t N) {
        forward_iterator it = this->begin();
        for (size_t i = 1; i <= N; ++i) {
            if (i == N) break;
            ++it;
        }
        this->delete_by_it(it);
    }

    template<class T>
    void queue<T>::insert_by_it(containers::queue<T>::forward_iterator ins_it, T& value) {
        queue<T> res;
        int flag = 0;
        T tmp;
        forward_iterator i = this->begin(), end = this->end();
        do {
            if ((i == end) && (i == ins_it)) {
                res.push(value);
                flag = 1;
            } else if (i == ins_it) {
                ++i;
                flag = 1;
                res.push(value);
                tmp = this->top();
                res.push(tmp);
                this->pop();
            } else {
                ++i;
                tmp = this->top();
                res.push(tmp);
                this->pop();
            }
        }  while(i != end);
        if (!flag) throw std::logic_error ("out of queue borders");
        *this = res;
    }

    template<class T>
    void queue<T>::insert_by_number(size_t N, T& value) {
        forward_iterator it = this->begin();
        for (size_t i = 1; i <= N; ++i) {
            if (i == N) break;
            ++it;
        }
        this->insert_by_it(it, value);
    }
//==============================iterator`s-stuff=======================================//
    template<class T>
    typename queue<T>::forward_iterator queue<T>::element::next() {
        return forward_iterator(this->next_element.get());
    }

    template<class T>
    queue<T>::forward_iterator::forward_iterator(containers::queue<T>::element *ptr) {
        it_ptr = ptr;
    }

    template<class T>
    T& queue<T>::forward_iterator::operator*() {
        return this->it_ptr->value;
    }

    template<class T>
    typename queue<T>::forward_iterator& queue<T>::forward_iterator::operator++() {
        *this = it_ptr->next();
        return *this;
    }

    template<class T>
    typename queue<T>::forward_iterator queue<T>::forward_iterator::operator++(int) {
        forward_iterator old = *this;
        ++*this;
        return old;
    }

    template<class T>
    bool queue<T>::forward_iterator::operator==(const forward_iterator& other) const {
        return it_ptr == other.it_ptr;
    }

    template<class T>
    bool queue<T>::forward_iterator::operator!=(const forward_iterator& other) const {
        return it_ptr != other.it_ptr;
    }

    //
    //namespace
}



#endif //OOP_EXERCISE_05_QUEUE_H