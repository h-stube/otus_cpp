#include <iostream>
#include <initializer_list>


static constexpr double resize_coeff = 1.6;
template<typename T>
class Array;

template<typename T>
class Array {
    public:
        Array() = default;
        Array(const size_t init_size);
        Array(std::initializer_list<T> init);
        Array(const Array& other) = delete;   
        Array(Array&& other) = delete;
        Array& operator=(const Array& other) = delete;
        Array& operator=(Array&& other) = delete;
        ~Array();

        void push_back(const T& element);
        void erase(const size_t index);
        void insert(const T& element, const size_t index);
        void resize(const size_t new_size);
        size_t size() const;
        
        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        friend std::ostream& operator<<(std::ostream& stream, const Array<T>& arr);

    private:
        void _copy(T* old_array, T* new_array);   

        size_t m_current_length{0};
        size_t m_max_length{0};
        T* m_data{nullptr};


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
        return;
    }

    if (m_current_length + 1 > m_max_length) {
        resize(m_current_length + 1);
    }

    for (size_t i = m_current_length; i > index; i--) {
            m_data[i] = m_data[i - 1];
        }
        m_data[index] = element;
        m_current_length += 1;
};


template <typename T>
void Array<T>::resize(const size_t new_size){
    m_max_length = static_cast<size_t>(new_size * resize_coeff);

    if (m_max_length < new_size) {
        m_max_length = new_size;
    }

    T* new_data = new T[m_max_length];
    _copy(m_data, new_data);
    delete[] m_data;
    m_data = new_data;
};


template <typename T>
void Array<T>::_copy(T *old_array, T* new_array){
    for (size_t i = 0; i < m_current_length; i++) {
        new_array[i] = old_array[i];
    }
};


template <typename T>
T& Array<T>::operator[](size_t index) {
    return m_data[index];
}

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
