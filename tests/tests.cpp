#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../third_party/doctest.h"
#include <type_traits>
#include <sstream>  // for operator<< test

#include "../vector/include/functions.h"
#include "../vector/include/student.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Vector

TEST_CASE("Vector construction and basic properties") {
    SUBCASE("Default constructor") {
        Vector<int> v;
        CHECK(v.size() == 0);
        CHECK(v.capacity() == 0);
        CHECK(v.empty() == true);
    }
    
    SUBCASE("Initializer list constructor") {
        Vector<int> v{1, 2, 3, 4, 5};
        CHECK(v.size() == 5);
        CHECK(v.capacity() >= 5);
        CHECK(v.empty() == false);
        CHECK(v[0] == 1);
        CHECK(v[4] == 5);
    }
    
    SUBCASE("Empty initializer list") {
        Vector<int> v{};
        CHECK(v.size() == 0);
        CHECK(v.empty() == true);
    }
}

TEST_CASE("Vector copy constructor and copy assignment") {
    SUBCASE("Copy constructor") {
        Vector<int> original{10, 20, 30};
        Vector<int> copy(original);
        
        CHECK(copy.size() == 3);
        CHECK(copy[0] == 10);
        CHECK(copy[1] == 20);
        CHECK(copy[2] == 30);
        
        // Ensure deep copy
        copy[0] = 999;
        CHECK(original[0] == 10);
        CHECK(copy[0] == 999);
    }
    
    SUBCASE("Copy assignment") {
        Vector<int> original{1, 2, 3, 4};
        Vector<int> assigned;
        
        assigned = original;
        CHECK(assigned.size() == 4);
        CHECK(assigned[3] == 4);
        
        // Self-assignment safety
        assigned = assigned;
        CHECK(assigned.size() == 4);
        CHECK(assigned[0] == 1);
    }
    
    SUBCASE("Copy empty vector") {
        Vector<int> empty;
        Vector<int> copy(empty);
        CHECK(copy.size() == 0);
        CHECK(copy.empty() == true);
    }
}

TEST_CASE("Vector move constructor and move assignment") {
    SUBCASE("Move constructor") {
        Vector<int> original{100, 200, 300};
        size_t orig_size = original.size();
        
        Vector<int> moved(std::move(original));
        CHECK(moved.size() == orig_size);
        CHECK(moved[0] == 100);
        CHECK(moved[2] == 300);
        CHECK(original.size() == 0);  // moved-from state
    }
    
    SUBCASE("Move assignment") {
        Vector<int> original{5, 10, 15};
        Vector<int> target{99, 88};  // non-empty target
        
        target = std::move(original);
        CHECK(target.size() == 3);
        CHECK(target[1] == 10);
        CHECK(original.size() == 0);
    }
}

TEST_CASE("Vector push_back and capacity management") {
    SUBCASE("Basic push_back") {
        Vector<int> v;
        v.push_back(42);
        CHECK(v.size() == 1);
        CHECK(v[0] == 42);
        CHECK(v.capacity() >= 1);
    }
    
    SUBCASE("Multiple push_back operations") {
        Vector<int> v;
        for (int i = 0; i < 10; ++i) {
            v.push_back(i * 10);
        }
        CHECK(v.size() == 10);
        CHECK(v[0] == 0);
        CHECK(v[9] == 90);
    }
    
    SUBCASE("Capacity growth") {
        Vector<int> v;
        size_t prev_cap = 0;
        
        for (int i = 0; i < 20; ++i) {
            v.push_back(i);
            if (v.capacity() > prev_cap) {
                CHECK(v.capacity() >= v.size());
                prev_cap = v.capacity();
            }
        }
    }
}

TEST_CASE("Vector pop_back") {
    SUBCASE("Basic pop_back") {
        Vector<int> v{1, 2, 3};
        v.pop_back();
        CHECK(v.size() == 2);
        CHECK(v[0] == 1);
        CHECK(v[1] == 2);
    }
    
    SUBCASE("Pop until empty") {
        Vector<int> v{10};
        v.pop_back();
        CHECK(v.size() == 0);
        CHECK(v.empty() == true);
    }
    
    SUBCASE("Pop from empty vector throws") {
        Vector<int> v;
        CHECK_THROWS_AS(v.pop_back(), std::out_of_range);
    }
}

TEST_CASE("Vector element access") {
    SUBCASE("Operator[] access") {
        Vector<int> v{10, 20, 30};
        CHECK(v[0] == 10);
        CHECK(v[1] == 20);
        CHECK(v[2] == 30);
        
        v[1] = 999;
        CHECK(v[1] == 999);
    }
    
    SUBCASE("at() method with bounds checking") {
        Vector<int> v{5, 15, 25};
        CHECK(v.at(0) == 5);
        CHECK(v.at(2) == 25);
        
        CHECK_THROWS_AS(v.at(3), std::out_of_range);
        CHECK_THROWS_AS(v.at(100), std::out_of_range);
    }
    
    SUBCASE("front() and back()") {
        Vector<int> v{100, 200, 300};
        CHECK(v.front() == 100);
        CHECK(v.back() == 300);
        
        v.front() = 111;
        v.back() = 333;
        CHECK(v[0] == 111);
        CHECK(v[2] == 333);
    }
    
    SUBCASE("front() and back() on single element") {
        Vector<int> v{42};
        CHECK(v.front() == 42);
        CHECK(v.back() == 42);
        CHECK(&v.front() == &v.back());  // same element
    }
}

TEST_CASE("Vector resize") {
    SUBCASE("Resize to larger size with default value") {
        Vector<int> v{1, 2};
        v.resize(5);
        CHECK(v.size() == 5);
        CHECK(v[0] == 1);
        CHECK(v[1] == 2);
        CHECK(v[2] == 0);  // default int value
        CHECK(v[4] == 0);
    }
    
    SUBCASE("Resize to larger size with custom value") {
        Vector<int> v{10};
        v.resize(4, 99);
        CHECK(v.size() == 4);
        CHECK(v[0] == 10);
        CHECK(v[1] == 99);
        CHECK(v[3] == 99);
    }
    
    SUBCASE("Resize to smaller size") {
        Vector<int> v{1, 2, 3, 4, 5};
        v.resize(2);
        CHECK(v.size() == 2);
        CHECK(v[0] == 1);
        CHECK(v[1] == 2);
    }
    
    SUBCASE("Resize to zero") {
        Vector<int> v{1, 2, 3};
        v.resize(0);
        CHECK(v.size() == 0);
        CHECK(v.empty() == true);
    }
}

TEST_CASE("Vector insert") {
    SUBCASE("Insert at beginning") {
        Vector<int> v{2, 3, 4};
        auto it = v.insert(v.begin(), 1);
        CHECK(v.size() == 4);
        CHECK(v[0] == 1);
        CHECK(v[1] == 2);
        CHECK(v[3] == 4);
        CHECK(*it == 1);
    }
    
    SUBCASE("Insert in middle") {
        Vector<int> v{1, 3, 4};
        auto it = v.insert(v.begin() + 1, 2);
        CHECK(v.size() == 4);
        CHECK(v[0] == 1);
        CHECK(v[1] == 2);
        CHECK(v[2] == 3);
        CHECK(v[3] == 4);
        CHECK(*it == 2);
    }
    
    SUBCASE("Insert at end") {
        Vector<int> v{1, 2, 3};
        auto it = v.insert(v.end(), 4);
        CHECK(v.size() == 4);
        CHECK(v[3] == 4);
        CHECK(*it == 4);
    }
    
    SUBCASE("Insert into empty vector") {
        Vector<int> v;
        auto it = v.insert(v.begin(), 42);
        CHECK(v.size() == 1);
        CHECK(v[0] == 42);
        CHECK(*it == 42);
    }
}

TEST_CASE("Vector erase") {
    SUBCASE("Erase from beginning") {
        Vector<int> v{1, 2, 3, 4};
        auto it = v.erase(v.begin());
        CHECK(v.size() == 3);
        CHECK(v[0] == 2);
        CHECK(v[1] == 3);
        CHECK(v[2] == 4);
        CHECK(it == v.begin());
    }
    
    SUBCASE("Erase from middle") {
        Vector<int> v{10, 20, 30, 40};
        auto it = v.erase(v.begin() + 1);
        CHECK(v.size() == 3);
        CHECK(v[0] == 10);
        CHECK(v[1] == 30);  // 20 was erased
        CHECK(v[2] == 40);
        CHECK(*it == 30);
    }
    
    SUBCASE("Erase last element") {
        Vector<int> v{1, 2, 3};
        auto it = v.erase(v.begin() + 2);
        CHECK(v.size() == 2);
        CHECK(v[0] == 1);
        CHECK(v[1] == 2);
        CHECK(it == v.end());
    }
    
    SUBCASE("Erase invalid position") {
        Vector<int> v{1, 2};
        auto it = v.erase(v.end());  // past-the-end
        CHECK(it == v.end());
        CHECK(v.size() == 2);  // unchanged
    }
}

TEST_CASE("Vector equality and comparison") {
    SUBCASE("Equality operator") {
        Vector<int> v1{1, 2, 3};
        Vector<int> v2{1, 2, 3};
        Vector<int> v3{1, 2, 4};
        Vector<int> v4{1, 2};
        
        CHECK(v1 == v2);
        CHECK_FALSE(v1 == v3);
        CHECK_FALSE(v1 == v4);
        CHECK(v1 != v3);
        CHECK(v1 != v4);
    }
    
    SUBCASE("Empty vector equality") {
        Vector<int> empty1;
        Vector<int> empty2;
        Vector<int> nonEmpty{1};
        
        CHECK(empty1 == empty2);
        CHECK_FALSE(empty1 == nonEmpty);
    }
    
    SUBCASE("Less-than comparison") {
        Vector<int> v1{1, 2, 3};
        Vector<int> v2{1, 2, 4};
        Vector<int> v3{1, 2};
        Vector<int> v4{2, 1, 1};
        
        CHECK(v1 < v2);  // lexicographical: 3 < 4
        CHECK(v3 < v1);  // shorter vector is less
        CHECK(v1 < v4);  // first element: 1 < 2
        CHECK_FALSE(v2 < v1);
    }
}