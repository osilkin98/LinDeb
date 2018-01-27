#ifndef LIN_ALG_H
#define LIN_ALG_H
#define ZERO_LIM 1e-5
#include <iostream>


// to multiply two matrices, A & B such that
// A: m x n
// B: n x q
// C: m x q

/*
             [ c ]
  [ a  b ] * |   |  = (a * c) + (b * d)
             [ d ] 

   1 x 2     2 x 1      1 x 1
   m   n     n   q      m   q    
        2 = 2  -> works

 */

// attempts to allocate a matrix C and store the result of the multiplcation
// in dynamic memory and return a pointer to the address of the new matrix
template<typename t>
t** matrix_mult(t** A, t** B, const int m, const int n, const int q) {
  t** C = NULL;
  C = new t*[m];
  if(C != NULL) {
    for(int i = 0; i < m; ++i) {
      C[i] = new t[q];
      // if an allocation fails, we have to clean up all the deallocated memory
      if(C[i] == NULL) {
	for(int n = i - 1; n >= 0; ++n) {
	  delete C[n];
	  C[n] = NULL;
	}
	delete C;
	C = NULL;
	return NULL;
      }
    }
    // C is allocated and good to go!
    for(int i = 0; i < m; ++i) {
      for(int j = 0; j < q; ++j) {
	// C_i,j =
	// there's always going to be the same number of elements in the row & col
	for(int k = 0; k < n; ++k) {
	  C[i][j] += A[i][k] * B[k][j];
	}
      }
    }
    return C;
  }
  return NULL;
}


/************* UTILITY FUNCTIONS *************/ 

void clear_mat(double**& mat, int n, int m) {
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < m; ++j) {
      if(mat[i][j] < ZERO_LIM && mat[i][j] > -1 * ZERO_LIM) {
	mat[i][j] = 0;
      }
    }
  }
}


template<typename t>
void del_mat(t** mat, size_t n) {
  for(size_t i = 0; i < n; ++i) {
    delete mat[i];
    mat[i] = NULL;
  }
  delete[] mat;
  mat = NULL;

}

template<typename t>
t** copy_mat(t** A, int n, int m) {
  t** B = NULL;
  B = new t*[n];
  if(B != NULL) {
    for(int i = 0; i < n; ++i) {
      B[i] = new t[m];
      // oops we fucked up somewhere
      if(B[i] == NULL) {
	for(int k = i - 1; k >= 0; --k) {
	  delete B[k];
	  B[k] = NULL;
	}
	delete B;
	B = NULL;
	return NULL;
      }
      for(int j = 0; j < m; ++j) {
	B[i][j] = A[i][j];
      }
    }
    return B;
  }
  delete B;
  B = NULL;
  return NULL;
}

template<typename t>
void randomize_mat(t** mat, int n, int m, int mod = 12) {
  srand(time(0));
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < m; ++j) {
      mat[i][j] = static_cast<t>(rand() % mod);
    }
  }
}

template<typename t>
t** allocate_mat(int n, int m) {
  t** A = NULL;
  A = new t*[n];
  if(A != NULL) {
    for(int i = 0; i < n; ++i) {
      A[i] = new t[m];
      if(A[i] == NULL) {
	for(int k = i - 1; k >= 0; ++k) {
	  delete A[k];
	  A[k] = NULL;
	}
	delete A;
	A = NULL;
	return NULL;
      }
    }
    return A;
  }
  return NULL;
}




template<typename T>
void print_mat(T** mat, size_t n, size_t m) {
  for(size_t i = 0; i < n; ++i) {
    std::cout << "[ ";
    for(size_t j = 0; j < m; ++j) {
      std::cout << mat[i][j];
      if(j + 1 != m) {
	std::cout << ",";
      }
      std::cout << " ";
    }
    std::cout << "]\n";
  }
  std::cout << std::endl;
}

/************** END UTILITY FUNCTIONS **********/


// template<typename t>
// takes in a matrix A and outputs a matrix B
// such that A[i][j] == B[j][i]
/*
      [ a  b  c ]
  A = [ d  e  f ] 

  B = [ a  d ]
      [ b  e ]
      [ c  f ]

 */
template<typename t>
t** transpose_new(t** A, int n, int m) {
  t** B = NULL;
  B = new t*[m];
  if(B != NULL) {
    for(int i = 0; i < m; ++i) {
      B[i] = new t[n];
      // if the  running this doesnt have enough
      // memory we have to backtrack and free up all
      // the space from the computer
      if(B[i] == NULL) {
	for(int k = i - 1; k >= 0; ++k) {
	  delete B[i];
	  B[i] = NULL;
	}
	delete B;
	B = NULL;
	return NULL;
      }
      // everything was fine, ths compute rdidnt fuck up
      for(int j = 0; j < n; ++j) {
	B[i][j] = A[j][i];
      }
    }
    return B;
  }
  B = NULL;
  return NULL;
}

/**
   [ 2 3 0 ]     [ 1 0 0 ]    
   [ 4 1 5 ] ==> [ 
   [ 0 2 5 ]     [ 0 0 1]  
 **/

/*
  [ 2  5 ] =>   [ 1 0 ]     [ 2                5 ]
  [ 8  3 ]      [ -4 1 ] => [ -4 * 2 + 8 -4 * 5  


  [ a  b ]      [ a  b ]
  [ c  d ]  =>  [ -


 */

// so we find a multiply that will cause the pivot to be equal t
// the element(s) beneath it, and then we multiply that entire row
// by that multiple and



template<typename t>
t** row_reduce(t** A, int n, int m) {
  t** B = NULL;
  B = copy_mat(A, n, m);
  std::cerr << "printing matrix 2\n";
  print_mat(B, n, m);
  if(B != NULL) {
    t mult;
    // main loop to move down diagonaly along the matrix
    for(int i = 0; i < n; ++i) {
      // loop to zero out all the values beneath the ith index
      for(int j = i+1; j < n; ++j) {
	mult = -1 * B[j][i] / B[i][i];
	// this loop should perform the row reducing operation along
	// the jth row
	for(int k = i; k < m; ++k) {
	  B[j][k] = mult * B[i][k] + B[j][k];
	}
      }
    }
    return B; 
  }
  B = NULL;
  return NULL;
}


template<typename t>
void transpose_perm(t**& A, int n, int m) {
  t** B = NULL;
  B = transpose_new(A, n, m);
  if(B != NULL) {
    A = B;
    //std::cerr << "seg fault - B = NULL\n";
    B = NULL;
    // print_mat(A, m, n);
  }
}




#endif
