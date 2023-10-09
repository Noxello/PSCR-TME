template<typename iterator>
size_t count(iterator begin, iterator end){
    size_t count = 0;
    for(iterator it = begin; it != end; ++it)
        count++;
    
    return count;
}
template<typename iterator, typename T>
size_t count_if_equal(iterator begin, iterator end, const T& val){
    size_t count = 0;
    for(iterator it = begin; it != end; ++it)
        count+= (int) (*it == val);

    return count;
}