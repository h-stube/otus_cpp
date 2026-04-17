#include <iostream>
#include <initializer_list>


static constexpr double resize_coeff = 1.6;
template<typename T>
class Array;

template<typename T>
class Array {
    public:
        Array(const size_t init_size);
        Array(std::initializer_list<T> init);
        Array(const Array& other);   
        Array(Array&& other);
        Array& operator=(const Array& other);
        Array& operator=(Array&& other);
        ~Array();

        void push_back(const T& element);
        void erase(const size_t index);
        void insert(const T& element, const size_t index);
        void resize(const size_t new_size);
        size_t size() const;
        
        const T& operator[](size_t index) const;
        friend std::ostream& operator<<(std::ostream& stream, const Array<T>& arr);

    private:
        void _copy(T* old_array, T* new_array);   

        size_t m_current_length{0};
        size_t m_max_length{0};
        T* m_data{nullptr};
        T* m_new_data{nullptr};


};

template <typename T>
Array<T>::Array(const size_t init_size) {
    m_current_length = init_size;
    m_max_length = static_cast<size_t>(init_size * resize_coeff);
    m_data = new T[m_max_length];
};

template <typename T>
Array<T>::~Array() {
    delete[] m_data;
}

template <typename T>
Array<T>::Array(std::initializer_list<T> init) {
    m_current_length = init.size();
    m_max_length = static_cast<size_t>(init.size() * resize_coeff);
    m_data = new T[m_max_length];

    size_t index = 0;
    for(auto it = init.begin(); it != init.end(); ++it){
        m_data[index] = *it;
        index = index + 1; 
    }
};

template <typename T>
size_t Array<T>::size() const{
    return m_current_length;
};

template <typename T>
void Array<T>::push_back(const T& element) {
    if (m_current_length < m_max_length){
        m_data[m_current_length] = element;
        m_current_length += 1;
    } else {
        resize(m_max_length);
        m_data[m_current_length] = element; 
        m_current_length += 1;    
    }
};

template <typename T>
void Array<T>::erase(const size_t index) {
    if(index >= m_current_length){
        return;
    }
    for(size_t i = index; i < m_current_length - 1; i++){
        m_data[i] = m_data[i + 1];
    }
    m_current_length -= 1;
};

template <typename T>
void Array<T>::insert(const T& element, const size_t index) {
    if (index > m_current_length){
        resize(m_max_length);
    }
    T next_element;
    T temp = element;
    for (size_t i = index; i <= m_current_length; i++){
        next_element = m_data[i];
        m_data[i] = temp;
        temp = next_element;
    } 
    m_current_length += 1;
};


template <typename T>
void Array<T>::resize(const size_t new_size){
    m_max_length = static_cast<int>(new_size * resize_coeff);
    m_new_data = new T[m_max_length];
    _copy(m_data, m_new_data);
    delete[] m_data;
    m_data = m_new_data;
    m_new_data = nullptr;
    m_current_length = new_size;
};


template <typename T>
void Array<T>::_copy(T *old_array, T* new_array){
    for (size_t i = 0; i < m_current_length; i++) {
        new_array[i] = old_array[i];
    }
};


template <typename T>
const T& Array<T>::operator[](size_t index) const {
    return m_data[index];
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Array<T>& arr){
    for(size_t  i =  0; i < arr.size(); i++){
        stream << arr[i];
        if (i < arr.size() - 1){
            stream << ", ";
        }

    }
    return stream;
}
