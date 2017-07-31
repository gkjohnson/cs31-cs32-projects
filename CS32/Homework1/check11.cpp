        #include "newBag.h"
        #include <iostream>
        #include <cassert>
        using namespace std;

        void test()
        {
            Bag ulb;
            assert(ulb.insert(20));
            assert(ulb.insert(10));
            assert(ulb.insert(20));
            assert(ulb.insert(30));
            assert(ulb.insert(20));
            assert(ulb.insert(10));
            assert(ulb.size() == 6  &&  ulb.uniqueSize() == 3);
            assert(ulb.count(10) == 2);
            assert(ulb.count(20) == 3);
            assert(ulb.count(30) == 1);
            assert(ulb.count(40) == 0);
        }

        int main()
        {
            test();
            cout << "Passed all tests" << endl;
        }