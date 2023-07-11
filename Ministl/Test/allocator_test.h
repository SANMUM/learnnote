#ifndef MYTINYSTL_ALLOCATOR_TEST_H_
#define MYTINYSTL_ALLOCATOR_TEST_H_
#include<vector>
#include "../Source/allocator.h"
#include "test.h"
namespace mystl {

namespace test{

namespace allocator_test{

void allocator_test(){
    std::cout << "[===============================================================]\n";
    std::cout << "[----------------- Run allocator test : allocator --------------]\n";
    std::cout << "[-------------------------- API test ---------------------------]\n";
    int arr[5] = {0,1,2,3,4};
    std::vector<int,mystl::allocator<int> > iv(arr,arr+5);
    // vector<int, myAllocator::allocator<int> > iv(arr, arr + 5);

	for (size_t i = 0; i < iv.size(); i++) {
		std::cout << iv[i] << ' ';	
	}

	std::cout << std::endl;
}
}
}
}



#endif