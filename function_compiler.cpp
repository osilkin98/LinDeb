#include <iostream>
#include <sstream>
#include <string>
#include <stack>

bool has_valid_parenthesis_and_one_equals(const std::string& str) {
  std::stack<char> parenthesis_stack;
  char k = 0, left_side_parenthesis = 0;
  for(register size_t i = 0; i < str.size(); ++i) {
    if(str[i] == '(') {
      parenthesis_stack.push('(');
    } else if(str[i] == ')') {
      parenthesis_stack.pop();
      if(!k) {
	++left_side_parenthesis;
      }
    } else if(str[i] == '=') {
      ++k;
    }
  }
  return !parenthesis_stack.size() && k == 1 && left_side_parenthesis == 1;
}

bool is_valid_input(const std::string& str) {
  return has_valid_parenthesis_and_one_equals(str);
}

void create_function(const std::string& input_string) {
  if(has_valid_parenthesis_and_one_equals(input_string)) {
    std::istringstream expression(input_string);
    std::ostringstream output_function;
    output_function << "double ";
    char c;
    expression >> c;
    while(c != '=') {
      output_function << c;
      expression >> c;
    }
    output_function << " { return ";
    expression >> c;
    while(!expression.eof()) {
      output_function << c;
      expression >> c;
    }
    output_function << "; }";
    std::cout << output_function.str() << std::endl;
  }
}

int main(void) {
  std::string instr;
  std::cout << "> " << std::flush;
  std::getline(std::cin, instr);
  create_function(instr);
  return 0;
}
