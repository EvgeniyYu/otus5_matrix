#include <iostream>
#include "matrix.h"

int main()
{
    const size_t MAX_SIZE = 10;
    Matrix<int, 0> matrix;
    
    assert(matrix.size() == 0 && "size must be zero!"); 
    assert(matrix[10][10] == 0 && "matrix[10][10] must be zero!");
    
    for (size_t i = 0; i < MAX_SIZE; i++)
    {
    	matrix[i][i] = i;
    	matrix[i][MAX_SIZE - i - 1] = MAX_SIZE - i - 1;
    }
    
    for (size_t i = 1; i < 9; i++)
    {
    	for (size_t j = 1; j < 9; j++)
    	{
    		std::cout << matrix[i][j] << " ";
    	}
    	std::cout << std::endl;
    }
        
    std::cout << matrix.size() << std::endl;
    assert(matrix.size() == 20 && "size must be 20!");     

	for (const auto& c: matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        
        std::cout << "(" << x << ", " << y << ") = " << v << std::endl;
    }
    
    return 0;
}

