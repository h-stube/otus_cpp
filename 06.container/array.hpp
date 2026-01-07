#include <iostream>
#include <initializer_list>


#define resize_coeff 1.6
template<typename T>
class Array;

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Array<T>& arr);

template<typename T>
class Array {
    public:
        Array(const size_t init_size);
        Array(std::initializer_list<T> init);

        void push_back(const T& element);
        void erase(const size_t index);
        void insert(const T& element, const size_t index);
        void resize(const size_t new_size);
        size_t size() const;
        
        const T& operator[](size_t index) const;
        friend std::ostream& operator<<<T> (std::ostream& stream, const Array<T>& arr);

    private:
        void _copy(T* old_array, T* new_array);   

        size_t current_lenght{0};
        size_t last_element{0};
        size_t max_lenght{0};
        T* data{nullptr};
        T* new_data{nullptr};


};

template <typename T>
Array<T>::Array(const size_t init_size) {
    current_lenght = init_size;
    max_lenght = static_cast<int>(init_size * resize_coeff);
    data = new T[max_lenght];
};

template <typename T>
Array<T>::Array(std::initializer_list<T> init) {
    current_lenght = init.size();
    max_lenght = static_cast<int>(init.size() * resize_coeff);
    data = new T[max_lenght];

    size_t index = 0;
    for(auto it = init.begin(); it != init.end(); ++it){
        data[index] = *it;
        index = index + 1; 
    }
};

template <typename T>
size_t Array<T>::size() const{
    return current_lenght;
};

template <typename T>
void Array<T>::push_back(const T& element) {
    if (current_lenght < max_lenght){
        data[current_lenght] = element;
        current_lenght += 1;
    } else {
        resize(current_lenght);
        data[current_lenght] = element; 
        current_lenght += 1;    
    }
};

template <typename T>
void Array<T>::erase(const size_t index) {
    if(index > max_lenght){
        return;
    }
    for(size_t i = index; i < current_lenght; i++){
        data[i] = data[i + 1];
    }
    current_lenght -= 1;
};

template <typename T>
void Array<T>::insert(const T& element, const size_t index) {
    if (index >= max_lenght){
        resize(max_lenght);
    }
    T next_element;
    T temp = element;
    for (size_t i = index; i <= current_lenght; i++){
        next_element = data[i];
        data[i] = temp;
        temp = next_element;
    } 
    current_lenght += 1;
};


template <typename T>
void Array<T>::resize(const size_t new_size){
    max_lenght = static_cast<int>(new_size * resize_coeff);
    new_data = new T[max_lenght];
    _copy(data, new_data);
    delete[] data;
    data = new_data;
    new_data = nullptr;
    current_lenght = new_size;
};


template <typename T>
void Array<T>::_copy(T *old_array, T* new_array){
    for (size_t i = 0; i <= (sizeof(old_array)); i++) {
        old_array[i] = new_array[i];
    }
};


template <typename T>
std::ostream& operator<<(std::ostream& stream, const Array<T>& arr){
    for(size_t  i =  0; i < arr.size(); i++){
        if (i == arr.size()){
            stream << arr.data[i];
        } else {
            stream << arr.data[i] << ", ";
        }

    }
    return stream;
}
