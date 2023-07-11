#ifndef MYTINYSTL_VECTOR_TEST_H_
#define MYTINYSTL_VECTOR_TEST_H_

#include <vector>
#include "../Source/vector.h"
#include "test.h"
namespace mystl
{
namespace test 
{
namespace vector_test
{
void vector_test()
{
    
    std::cout << "[===============================================================]\n";
    std::cout << "[----------------- Run container test : vector -----------------]\n";
    std::cout << "[-------------------------- API test ---------------------------]\n";

    int a[] = {1,2,3,4,5};
    mystl::vector<int> v1;
    FUN_AFTER(v1,v1.assign(8,8));
}
}
}    
}
#endif