        #include "newBag.h"
        #include <string>
        #include <iostream>
        #include <cassert>
        using namespace std;

        void test()
        {
            Bag sb;
            assert(sb.insert("cumin"));
            assert(sb.insert("turmeric"));
            assert(sb.insert("cumin"));
            assert(sb.insert("coriander"));
            assert(sb.insert("cumin"));
            assert(sb.insert("turmeric"));
            assert(sb.size() == 6  &&  sb.uniqueSize() == 3);
            assert(sb.count("turmeric") == 2);
            assert(sb.count("cumin") == 3);
            assert(sb.count("coriander") == 1);
            assert(sb.count("cardamom") == 0);
        }

        int main()
        {
            test();
            cout << "Passed all tests" << endl;
        }