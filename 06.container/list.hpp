#include <iostream>
#include <initializer_list>


template <typename T>
struct TwoWayNode {
    void *next;
    void *prev;
    T data{};
};

template <typename T>
struct OneWayNode {
    void *next;
    size_t index;
    T data{};
};

template<typename T>
class List;

template<typename T>
std::ostream& operator<<(std::ostream& stream, const List<T>& arr);

template<typename T>
class List {
    public:
        List(std::initializer_list<T> init);

        void create_node();

        void push_back(const T element);
        TwoWayNode<T>* get_next(TwoWayNode<T>* current_node) const ;
        TwoWayNode<T>* get_prev(TwoWayNode<T>* current_node) const;
        void erase(const size_t index);
        void insert(const T& element, const size_t index);
        size_t size() const;
        
        const T operator[](size_t index) const;
        friend std::ostream& operator<< <T>(std::ostream& stream, const List<T>& list);

    private:
        void _copy(T* old_array, T* new_array);
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
void List<T>::push_back(const T value) {
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
TwoWayNode<T>* List<T>::get_next(TwoWayNode<T>* current_node) const {
    return static_cast<TwoWayNode<T>*>(current_node->next);
}

template <typename T>
TwoWayNode<T>* List<T>::get_prev(TwoWayNode<T>* current_node) const{
    return static_cast<TwoWayNode<T>*>(current_node->prev);
}

template <typename T>
void List<T>::erase(const size_t index){
    if (index > m_size){
        return;
    }

    TwoWayNode<T>* node_to_delete = m_first;
    for(size_t i = 0; i < index; i++){
        node_to_delete = get_next(node_to_delete);
    }

    TwoWayNode<T>* next_node = get_next(node_to_delete);
    TwoWayNode<T>* prev_node = get_prev(node_to_delete);


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
        current_node = get_next(current_node);
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
    if (index > m_size) {
        return m_last->data;
    }
    TwoWayNode<T>* current_node = m_first;
    for(size_t i = 0; i < index; i++){
        current_node = get_next(current_node);
    }
    return current_node->data;
}

template <typename T>
std::ostream& operator<< <T>(std::ostream& stream, const List<T>& list){
    for(size_t  i =  0; i < list.size(); i++){
        if (i + 1 == list.size()){
            stream << list[i];
        } else {
            stream << list[i] << ", ";
        }

    }
    return stream;
}
