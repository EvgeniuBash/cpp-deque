#include "calculator.h"

bool ReadNumber(Number& result) { 
if (!(std::cin >> result)) {
    std::cerr << "Error: Numeric operand expected" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        return false;
} 
        return true; 
 }


bool RunCalculatorCycle() {
        Number result = 0.0;
        Number value = 0.0;
        Number save_value = 0.0;
        bool is_save_memory_empty = true;
        std::string operation; 

if (!ReadNumber(result)) {
        return false;  
    }

    while (std::cin >> operation) {
        if (operation == "q") {
            return true; 
        } else if (operation == "s") {
            save_value = result;
        is_save_memory_empty = false;
        } else if (operation == "l") {
            if (is_save_memory_empty) {
                std::cerr << "Error: Memory is empty" << std::endl;
                return false; 
            } else {
                result = save_value;
            }
        } else if (operation == "=") {
            std::cout << result << std::endl; 
        }  else if (operation == "c") {
            result = 0; 
        }  else if (operation == "+" || operation == "-" || operation == "*" || operation == "/" || operation == "**" || operation == ":") {
            if (operation == ":") {
                    if (!ReadNumber(value)) {      
                        return false; 
                    }
                    result = value; 
                } else if (operation == "**") {
                    if (!ReadNumber(value)) {      
                        return false; 
                    }
                    result = std::pow(result, value); 
                } else {
                    if (!ReadNumber(value)) {      
                        return false;
                    }
                    if (operation == "+") {
                        result += value;
                    } else if (operation == "-") {
                        result -= value;
                    } else if (operation == "*") {
                        result *= value;
                    } else if (operation == "/") {
                        if (value == 0) {
                            result = std::numeric_limits<Number>::infinity(); 
                        } else {
                            result /= value;
                        } 
                    }
                }
            } else {
                std::cerr << "Error: Unknown token " << operation << std::endl; 
                return false; 
            }
    }
return false;
    }
