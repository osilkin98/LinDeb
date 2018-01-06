#include <iostream>
#include "lin_alg.h"
#include <stdio.h>
#include <climits>
#include <cctype>

using namespace std;

void print_menu(void) {
  cerr << "1. View Table\n"
       << "2. Create Tables\n"
       << "3. Delete Tables\n"
       << "4. Operations\n"
       << "0. Exit\n\n";
}

bool is_valid(const char c) {
  const char opts[5] = {'0', '1', '2', '3', '4'};
  for(char i = opts[0]; i < '6'; ++i) {
    if(c == i) {
      return true;
    }
  }
  return false;
}

template<typename t>
void cinput(t& c) {
  cin >> c;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
}

template<typename t>
void diminput(int& rows, int& cols) {
  std::cout << "Rows: " << std::flush;
  cinput(rows);
  std::cout << "Columns: " << std::flush;
  cinput(cols);
}
  
template<typename t>
void view_tables(t*** table, int** sizes) {
  int n = sizes[0][0];
  for(int i = 0; i < n; ++i) {
    cout << "Table " << i+1 << "\n";
    for(int j = 0; j < sizes[i+1][0]; ++j) {
      cout << "[ ";
      for(int k = 0; k < sizes[i+1][1]; ++k) {
	cout << table[i][j][k] << " ";
	//if(!(k+1 == sizes[i+1][1])) {
      }
      cout << "]\n";
    }
    cout << "\n\n";
  }
  cout << endl;  
}

template<typename t>
t*** reallocate_table(t***& tables, int**& sizes, int add_size) {
  t*** temp = NULL;
  int n = sizes[0][0];
  temp = new t**[n + add_size];
  if(temp != NULL) {
    for(int matrix = 0; matrix < n; ++matrix) {
      temp[matrix] = new t*[sizes[matrix + 1][0]];
      if(temp[matrix] != NULL) {
	for(int i = 0; i < sizes[matrix + 1][0]; ++i) {

	}
      } else {
	for(int k = matrix - 1; matrix >= 0; ++matrix) {
	  for(int l = 0; l < sizes[k+1][0]; ++l) {
	    for(int m = 0; m < sizes[k+1][1]; ++m) {
	      delete temp[k][l][m];
	      temp[k][l][m] = NULL;
	    }
	    delete[] temp[k][l];
	    temp[k][l] = NULL;
	  }
	  delete[][] temp[k];
	  temp[k]
	      
	}
      }
    }
  }
}

template<typename t>
bool create_entries(t***& tables, int**& sizes) {
  char use = 'y';
  cout << "New Entry?[y/n] " << flush;
  cinput(use);
  while(tolower(use) == 'y') {
    int rows = 0, cols = 0;
    diminput(rows, cols);
    while(rows < 1 || cols < 1) {
      std::cerr << "Error: Dimensions cannot be less than 1\n";
      diminput(rows, cols);
    }
    t** new_mat = NULL;
    new_mat = allocate_mat<t>(rows, cols);
    if(new_mat != NULL) {
      
	
  }
}
int main(void) {
  cout << "Linear Algebra Debugger\n\n" << endl;
  char c = '9';
  double*** d_table = NULL;
  int** sizes = NULL;
  //int n = 0;
  sizes = new int*[1];
  sizes[0] = new int[1];
  sizes[0][0] = 0;
  while(c != '0') {
    print_menu();
    cout << ">> " << flush;
    cinput(c);
    while(!is_valid(c)) {
      cout << "Sorry, that option is invalid, please try again.\n>> ";
      cinput(c);
    }

    switch(c) {
    case '0':
      return 0;
    case '1':
      view_tables(d_table, sizes);
      break;
    case '2':
      create_entries(d_table, sizes);
    default:
      cerr << "Feature unavailable\n";
    }
  }
  return 0;
}
