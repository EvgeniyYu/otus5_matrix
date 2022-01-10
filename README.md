# otus5_matrix  
Sparse matrix  
  
Matrix is filled with values by default and stores only the elements that have been used. Matrix realizes the following functions:  
- returns the total size (how many cells are used);  
- used elements output  
- indexation operator []  
- reading from a free cell returns a value by default  
- realization of a canonical form of operator= like this:  
((matrix[100][100] = 314) = 0) = 217  
  
Example:   
    Matrix<int, -1> matrix;   
    assert(matrix.size() == 0); // all cells are free   
    
    auto a = matrix[0][0];   
    assert(a == -1);   
    assert(matrix.size() == 0);   
    
    matrix[100][100] = 314;   
    assert(matrix[100][100] == 314);   
    assert(matrix.size() == 1);   
    
    // print one string   
    // 100100314   
    for(auto c: matrix)   
    {   
        int x;   
        int y;   
        int v;   
        std::tie(x, y, v) = c;   
        std::cout << x << y << v << std::endl;   
    }  
  
