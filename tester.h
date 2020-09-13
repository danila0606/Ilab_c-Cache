#include "Cache.h"
#include <ctime>

class Test {
public:
    Test() : info(0.0) {};
    void test1(Cache<int, int> &cache, int range);

    const double Result() { return info;};
private:

    double info;
};

void Test::test1(Cache<int, int> &cache, int range) { //range - possible number of different keys
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 100; i++) {
        int r = rand() % range;
        cache.PutValue({r, i});
    }
    //std::cout<<std::endl;
    //cache.printHash();
    int t;
    for (t = 1; t < 150; t++) {
        try {
            int r = rand() % range;
            cache.GetValue(r);
        } catch (std::exception &ex) {
            std::cout<< ex.what()<<std::endl;
            info = 1.0 / t;
            return;
        }
    }
    info = 1.0 / t;
}