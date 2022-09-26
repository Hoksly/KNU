
typedef int iterator; // maybe i will write it later

template <class T>
class victor
{
private:
    int _size = 0;
    int _capacity = 0;

    _get_element(const int index);

public:
    inline bool size() { return _size; }

    void clear();
    void erase(const iterator position);
    void erase(const iterator first, const iterator last); // removes elements in range [first, last]

    void insert(const iterator &position, const &T element);
    void push_pack(const &T);
    T pop_back();

    void resize(const iterator target_size);
    void reserve(const iterator additional_space);
    void shrink_to_fit();

    void swap(const iterator first, const iterator second);
    int position search(const &T);
    int position search(const T);
};