#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <cctype>

// T will be either an operator char
// or a long long
struct tree_node {
  long double operator()(void) {
    /*if(!left || !right) {
      std::cerr << "operator node is missing a child. returning.\n";
      return data;
      }*/
    switch(op) {
    case '+':
      return (*left)() + (*right)();
    case '-':
      return (*left)() - (*right)();
    case 'x':
      return (*left)() * (*right)();
    case '*':
      return (*left)() * (*right)();
    case '/':
      return (*left)() / (*right)();
    case '%':
      return fmod((*left)(), (*right)());
    default:
      //std::cout << "defaulting to regular operator.\n";
      return data;
    }
  }
  
  char op;
  long double data;
  tree_node *left, *right, *parent;
  tree_node(long double _data = 0)
    : data(_data), left(NULL), right(NULL), parent(NULL), op(' ') { }
  //tree_node(void)\
    : op(' '), data(0), left(NULL), right(NULL), parent(NULL) { }
  tree_node(char _op)
    : op(_op), data(0), left(NULL), right(NULL), parent(NULL) { }
};


bool is_valid(const std::string input) {
  std::istringstream validator(input);
  std::stack<char> S;
  char c;
  while(validator.get(c)) {
    if(c == '(') {
      S.push(c);
    } else if(c == ')') {
      S.pop();
    }
  }
  return S.empty();
}

/* 
   Expressions will come in the form of
   8 - 3
   (3 x 5) + 7
   ((3x9)/(9x1) + 7) % 23

   We need to validate before we evaluate 
*/
bool is_operator(const char c) {
  char operators[6] = {'+', '-', 'x', '*', '/', '%'};
  for(register short i = 0; i < 6; ++i) {
    if(c == operators[i]) {
      return true;
    }
  }
  return false;
}

bool is_AS(const char a) { return a == '+' or a == '-'; }

bool is_MD(const char a) { return a == 'x' or a == '/' or a == '%';}

bool is_paren(const char a) { return a == '(' or a == ')'; }

// does operator a have precedence over operator b
bool has_precedence(const char a, const char b) {
  if(is_paren(a)) { // if operator a is + or -
    return false;
  } else if(is_MD(a) and is_AS(b)) {
    return false;
  } else {
    return true;
  }
}



void delete_subtree(tree_node* root) {
  if(!root) {
    return;
  }
  delete_subtree(root -> left);
  delete_subtree(root -> right);
  delete root;
}


long double evaluate_expression(char oper,
				double long a, double long b) {
  tree_node* eval = new tree_node(oper);
  eval -> left = new tree_node(a);
  eval -> right = new tree_node(b);
  double long value = (*eval)();
  delete_subtree(eval);
  return value;
}

std::string fix_input(std::string input) {
  std::istringstream to_fix(input);
  std::string new_string;
  char c;
  to_fix >> c;
  while(!to_fix.eof()) {
    if(!isspace(c)) {
      c = tolower(c);
      if(is_operator(c) or is_paren(c) or isdigit(c)) {
	new_string.push_back(c);
      } else {
	std::cerr << "invalid character, skipping\n";
      }
    }
    to_fix >> c;
  }
  return new_string;
}

long double evaluate(std::string input) {
  if(!is_valid(input)) {
    std::cerr << "invalid expression. exiting.\n";
  } else {
    //tree_node* root = new tree_node;
    std::istringstream expression(fix_input(input));
    std::stack<long double> values;
    std::stack<char> operators;
    long double d;
    char c;
    //if(isdigit(expression.peek())
    //expression >> c;
    while(!expression.eof()) {
      if(isdigit(expression.peek())) {
	expression >> d;
	values.push(d);
      } else if(expression.peek() == '(') {
	expression >> c;
	operators.push(c);
      } else if(expression.peek() == ')') {
	expression >> c;
	while(operators.top() != '(') {
	  char op = operators.top();
	  operators.pop();
	  long double a, b;
	  b = values.top();
	  values.pop();
	  a = values.top();
	  values.pop();
	  values.push(evaluate_expression(op, a, b));
	}
	operators.pop();
      } else if(is_operator(expression.peek())) {
	expression >> c;
	// while the operator stack is non-empty and
	// the operator at the top of the stack has an equal
	// or higher precedence than operator c
	while(!operators.empty() and
	      (has_precedence(operators.top(), c))) {
	  char op = operators.top();
	  operators.pop();
	  double long a, b;
	  b = values.top();
	  values.pop();
	  a = values.top();
	  values.pop();
	  values.push(evaluate_expression(op, a, b));
	}
	operators.push(c);
      } /*else {
	std::cerr << "character not recognized: "
		  << expression.peek() << "\n";
	throw "error: Character not recognized";
	}*/
    }
    // now we should have a stack of operators
    // and values
    while(!operators.empty()) {
      /* evaluating purely with stacks, 
	 need to convert this into a tree based implementation
      */
      
      char op = operators.top();
      operators.pop();
      double long a, b;
      b = values.top();
      values.pop();
      a = values.top();
      values.pop();
      std::cout << a << " " << b << " " << op << " ";
      values.push(evaluate_expression(op, a, b));
    }
    return values.top();
  }
}

std::string infix_to_postfix(std::string input) {
  std::string infix = fix_input(input);
  std::ostringstream postfix;
  std::stack<char> operators;
  operators.push('(');
  infix.push_back(')');
  std::istringstream expression(infix);
  char c;
  double d;
  //expression >> c;
  while(!expression.eof()) {
    if(isdigit(expression.peek())) {
      expression >> d;
      postfix << d;
      postfix << ":";
    } else if(expression.peek() == '(') {
      expression >> c;
      operators.push(c);
    } else if(is_operator(expression.peek())) {
      expression >> c;
      while(!operators.empty() and has_precedence(operators.top(), c)) {
	postfix << operators.top();
	operators.pop();
      }
      operators.push(c);
    } else if(expression.peek() == ')') {
      expression >> c;
      while(operators.top() != '(') {
	postfix << operators.top();
	operators.pop();
      }
      operators.pop();
    }
  }
  return postfix.str();
}

tree_node* expression_tree(std::string input) {
  std::stack< tree_node* > tree_stack;
  std::istringstream postfix(input);
  tree_node *a, *b, *c;
  long double d;
  char ch;
  while(!postfix.eof()) {
    if(isdigit(postfix.peek())) {
      postfix >> d;
      postfix >> ch;
      a = new tree_node(d);
      tree_stack.push(a);
    } else if(is_operator(postfix.peek())) {
      postfix >> ch;
      a = new tree_node(ch);
      b = tree_stack.top();
      tree_stack.pop();
      c = tree_stack.top();
      tree_stack.pop();
      a -> left = c;
      a -> right = b;
      tree_stack.push(a);
    }
  }
  a = tree_stack.top();
  tree_stack.pop();
  return a;
}

void print_inorder(tree_node* v) {
  if(!v) {
    return;
  } else if(!(v -> left) and !(v -> right)) {
    std::cout << v -> data << " ";
  } else {
    print_inorder(v -> left);
    std::cout << v -> op << " ";
    print_inorder(v -> right);
  }
  
}

int main(void) {
  
  std::cout << "enter a string: " << std::flush;
  std::string in;
  std::getline(std::cin, in);
  std::cout << in << " -> postfix = " << infix_to_postfix(in) << "\n";
  std::cout << in << " = " << evaluate(in);
  std::cout << std::endl;
  
  tree_node* root = expression_tree(infix_to_postfix(in));
  print_inorder(root);
  std::cout << "\nValue: " << (*root)() << std::endl;

  delete_subtree(root);
  
  /*tree_node* root = new tree_node((long double)3.0);
  root -> parent = new tree_node('+');
  root -> parent -> left = root;
  root -> parent -> right = new tree_node('x');
  root -> parent -> right -> left = new tree_node((long double)10);
  root -> parent -> right -> right = new tree_node((long double)77);
  std::cout << "3 + 10 x 77 = " << (*(root -> parent))() << std::endl;*/
  return 0;
}
