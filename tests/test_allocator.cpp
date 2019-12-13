/*!
 * minter_tx.
 * test_allocator.cpp
 *
 * \date 2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#include <gtest/gtest.h>
#include <sodium.h>
#include <string>

template<typename _CharT>
class sodium_s_alloc {
public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef _CharT* pointer;
    typedef const _CharT* const_pointer;
    typedef _CharT& reference;
    typedef const _CharT& const_reference;
    typedef _CharT value_type;

    typedef bool propagate_on_container_move_assignment;
    typedef bool is_always_equal;

    template<class _Up>
    struct rebind {
        typedef sodium_s_alloc<_Up> other;
    };

    // return address of values
    pointer address(reference value) const {
        return &value;
    }
    const_pointer address(const_reference value) const {
        return &value;
    }

    sodium_s_alloc() {
        std::cout << "Alloc init\n";
    }
    inline sodium_s_alloc(const sodium_s_alloc&) {
        std::cout << "Alloc copy\n";
    }

    template<class _Up>
    sodium_s_alloc(const sodium_s_alloc<_Up>& up) throw() {
    }

    ~sodium_s_alloc() throw() {
    }

    // return maximum number of elements that can be allocated
    size_type max_size() const throw() {
        return std::numeric_limits<std::size_t>::max() / sizeof(_CharT);
    }

    // initialize elements of allocated storage p with value value
    void construct(pointer p, const _CharT& value) {
        // initialize memory with placement new
        std::cout << "Construct \n";
        new ((void*) p) _CharT(value);
    }

    pointer allocate(size_type __n, std::allocator<void>::const_pointer = 0) {
        std::cout << "Alloc: " << __n << "elements for common size: " << (__n * sizeof(_CharT)) << "\n";
        auto ptr = static_cast<pointer>(sodium_allocarray(__n * sizeof(_CharT), __alignof(_CharT)));
        std::cout << "mlock sodium... \n";
        sodium_mlock(ptr, __n);

        return ptr;
    }

    // destroy elements of initialized storage p
    void destroy(pointer p) {
        std::cout << "Destroy \n";
        // destroy objects by calling their destructor
        p->~_CharT();
    }

    // deallocate storage p of deleted elements
    void deallocate(pointer p, size_type num) {
        std::cout << "munlock sodium...\n";
        sodium_munlock(p, num);
        std::cout << "Dealloc: " << num << " elements "
                  << "\n";
        sodium_free((void*) p);
    }
};

template<class T1, class T2>
bool operator!=(const sodium_s_alloc<T1>& a,
                const sodium_s_alloc<T2>& b) throw() {
    return a != b;
}

// return that all specializations of this allocator are interchangeable
template<class T1, class T2>
bool operator==(const sodium_s_alloc<T1>& a,
                const sodium_s_alloc<T2>& b) throw() {
    return a == b;
}

using sec_string = std::basic_string<char, std::char_traits<char>, sodium_s_alloc<char>>;

TEST(SodiumAllocator, InitString) {
    auto ret = sodium_init();

    std::cout << "REt" << ret << "\n";

    sec_string pass = "password";
    sec_string s = std::move(pass);

    std::cout << s << "\n";
    //    std::vector<std::string, sodium_s_alloc<std::string>> sec_strings;
    //    sec_strings.push_back("a");
    //    sec_strings.push_back("b");
    //    sec_strings.push_back("c");

    //    for(auto &item: sec_strings) {
    //        std::cout << item << "\n";
    //    }
}
