#include <iostream>
#include "tester.h"


int main() {
    int cache_size, range;
    std::cin>>cache_size>>range;

    Cache<int, int> cache(cache_size) ;

    for (int i = 0; i < range; i++) {
        int key;
        std::cin >> key;
        cache.PutValue({key, 0 });
    }
    std::cout<<cache.GetHit();

    //Test test;
    /*double sum = 0.0;
    for (int i = 0; i < 1000; i++)
    {
        test.test1(cache, range);
       // std::cout<< "Result is "<< test.Result()<<std::endl;
        sum+= test.Result();
    }

    std::cout<<std::endl<<"The middle result(Cash Miss): "<<sum/1000.0<<std::endl;*/
    return 0;
}
