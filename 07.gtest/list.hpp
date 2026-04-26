#include <iostream>
#include <initializer_list>


template <typename T>
struct TwoWayNode {
    TwoWayNode<T> *next;
    TwoWayNode<T> *prev;
    T data{};
};

template<typename T>
class List;


template<typename T>
class List {
    public:
        List() = default;
        List(std::initializer_list<T> init);
        List(const List&) = delete;
        List& operator=(const List&) = delete;
        List(List&&) = delete;
        List& operator=(List&&) = delete;
        ~List();

        void push_back(const T& element);
        void erase(const size_t index);
        void insert(const T& element, const size_t index);
        size_t size() const;
        
        const T operator[](size_t index) const;

        friend std::ostream& operator<<(std::ostream& stream, const List<T>& list){
            for(size_t  i =  0; i < list.size(); i++){
                if (i + 1 == list.size()){
                    stream << list[i];
                } else {
                    stream << list[i] << ", ";
                }

            }
            return stream;
        }

    private:
        TwoWayNode<T>* m_first{nullptr};
        TwoWayNode<T>* m_last{nullptr};
        size_t m_size{0};

};


template <typename T>
List<T>::List(std::initializer_list<T> init){
    size_t index = 0;
    for(auto it = init.begin(); it != init.end(); ++it){
        push_back(*it);
        index = index + 1; 
    }
}

template <typename T>
List<T>::~List() {
    TwoWayNode<T>* current = m_first;
    while (current != nullptr) {
        TwoWayNode<T>* next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
void List<T>::push_back(const T& value) {
    TwoWayNode<T>* new_node = new TwoWayNode<T>{};
    new_node->data = value;
    new_node->next = nullptr;
    if (m_size == 0) {
        new_node->prev = nullptr;
        m_first = new_node;
        m_last = new_node;
    } else{
        new_node->prev = m_last;
        m_last->next = new_node;
        m_last = new_node;
    }
    m_size += 1;
}


template <typename T>
void List<T>::erase(const size_t index){
    if (index >= m_size){
        return;
    }

    TwoWayNode<T>* node_to_delete = m_first;
    for(size_t i = 0; i < index; i++){
        node_to_delete = node_to_delete->next;
    }

    TwoWayNode<T>* next_node = node_to_delete->next;
    TwoWayNode<T>* prev_node = node_to_delete->prev;


    if (prev_node != nullptr) {
        prev_node->next = next_node;
    } else {
        m_first = next_node;
    }

    if (next_node != nullptr) {
        next_node->prev = prev_node;
    } else {
        m_last = prev_node;
    }
    
    delete node_to_delete;
    m_size -= 1;
};

template <typename T>
void List<T>::insert(const T& element, const size_t index){
    if (index > m_size){
        return;
    }
    TwoWayNode<T>* new_node = new TwoWayNode<T>{};
    new_node->data = element;

    if (m_size == 0) {
        new_node->prev = nullptr;
        new_node->next = nullptr;
        m_first = new_node;
        m_last = new_node;
        m_size = 1;
        return;
    }
    

    TwoWayNode<T>* current_node = m_first;
    TwoWayNode<T>* prev_node = nullptr;
    for(size_t i = 0; i < index; i++){
        prev_node = current_node;
        current_node = current_node->next;
    }

    TwoWayNode<T>* next_node = current_node;

    new_node->prev = prev_node;
    new_node->next = current_node;

    if (prev_node != nullptr) {
        prev_node->next = new_node;
     
    } else {
        m_first = new_node;
    }

    if (next_node != nullptr) {
        next_node->prev = new_node;
    } else {
        m_last = next_node;
    }

    m_size += 1;
};

template <typename T>
size_t List<T>::size() const{
    return m_size;
}


template <typename T>
const T List<T>::operator[](const size_t index) const {
    if (index >= m_size) {
        return m_last->data;
    }
    TwoWayNode<T>* current_node = m_first;
    for(size_t i = 0; i < index; i++){
        current_node = current_node->next;
    }
    return current_node->data;
}

