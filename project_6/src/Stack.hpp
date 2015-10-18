//
// Stack.hpp
//
// Simple array based stack implementation.
//
// Project 6
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 10/21/2015
//

#ifndef _STACK
#define _STACK

#include <cassert>

using namespace std;

class Stack {
   public:
      typedef long int Item;
      static const size_t STACK_CAP = 10;

      Stack();
      size_t size();
      void push(const Item& it);
      Item pop();
      void clear();

   private:
      Item items[STACK_CAP];
      size_t s_size;
}

#endif
