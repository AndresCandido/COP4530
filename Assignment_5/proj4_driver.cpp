#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "bet.h"

int main() {
   BET<std::string> myinfix1;
   BET<std::string> myinfix2("4 5 + 5 6 + /");
   BET<std::string> myinfix3;
   BET<std::string> myinfix4(myinfix2);
   myinfix2.printInfixExpression();
   std::cout << "Number of Leaf Nodes in myinfix2: " << myinfix2.leaf_nodes() << std::endl;
   std::cout << "Size of myinfix2: " << myinfix2.size() << std::endl;
   std::string instr;
   std::cout << "Enter a postfix notation: ";
   std::getline(std::cin, instr);
   myinfix1.buildFromPostfix(instr);
   myinfix1.printInfixExpression();
   std::cout << "Number of Leaf Nodes in myinfx1: " << myinfix1.leaf_nodes() << std::endl;
   std::cout << "Size of myinfix1: " << myinfix1.size() << std::endl;
   std::cout << "Testing the assignment operator= overload" << std::endl;
   myinfix3 = myinfix2;
   std::cout << "Size of myinfix3 (copied from myinfx2) is: " << myinfix3.size() << std::endl;
   myinfix3.printInfixExpression();
   std::cout << "Testing the copy constructor, creating myinfix4." << std::endl;
   std::cout << "Size of myinfix4 is: " << myinfix4.size() << std::endl;
   myinfix4.printInfixExpression();

   return 0;
}

