//
// Pofxcalc.cpp
//
// Calculator that reads arithmetic expressions from a file using postfix
// notation. Each line of the file is considered one expression.
//
// Project 6
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 10/21/2015
//

#include "Pofxcalc.hpp"

Pofxcalc::Pofxcalc() {
   expression_cnt = 0;
   valid = false;
   expr = new char[EXPR_CAP];
}

Pofxcalc::~Pofxcalc() {
   delete expr;
}

// evaluate
//
// Adds a token to the expression. If the token is an operand it applies the
// operand to it's operators. If the token is an operator it stores the value
// for later use.
//
// Returns false if an error is encountered. True otherwise.
//
// Pre-condition: a token
// Post-condition: that token evaluated
//
bool Pofxcalc::evaluate(Token token) {
   bool negative = false;
   valid = false;

   // handle the negative numbers
   if (token[0] == '-' && token[1] >= '0' && token[1] <= '9') {
      negative = true;
      token[0] = '0';
   }

   if (token[0] >= '0' && token[0] <= '9') {
      // token is a digit
      Number n = 0;
      // convert token to integer
      for (int i = 0; token[i] != '\0'; i++) {
         if (!(token[i] >= '0' && token[i] <= '9')) {
            cerr << "Pofxcalc: In expression " << expression_cnt << ": ";
            cerr << "'" << token << "' is not a valid operand.\n";
            return false;
         }
         n = n * 10 + (token[i] - '0');
      }

      if (negative)
         n = n * -1;

      stack.push(n);
   }
   else if (token[1] != '\0') {
      // invalid token
      cerr << "Pofxcalc: In expression " << expression_cnt << ": ";
      cerr << "'" << token << "' is not a valid operator.\n";
   }
   else if (token[0] == '+') {
      // do operation
      if (stack.size() < 2) {
         cerr << "Pofxcalc: In expression " << expression_cnt << ": ";
         cerr << "Not enough operands for operator '" << token << "'.\n";
         return false;
      }

      stack.push(stack.pop() + stack.pop());

      if (stack.size() == 1) {
         valid = true;
      }
   }
   else if (token[0] == '-') {
      // do operation
      if (stack.size() < 2) {
         cerr << "Pofxcalc: In expression " << expression_cnt << ": ";
         cerr << "Not enough operands for operator '" << token << "'.\n";
         return false;
      }

      Number right_val = stack.pop();
      stack.push(stack.pop() - right_val);

      if (stack.size() == 1) {
         valid = true;
      }
   }
   else if (token[0] == '*') {
      // do operation
      if (stack.size() < 2) {
         cerr << "Pofxcalc: In expression " << expression_cnt << ": ";
         cerr << "Not enough operands for operator '" << token << "'.\n";
         return false;
      }

      stack.push(stack.pop() * stack.pop());


      if (stack.size() == 1) {
         valid = true;
      }
   }
   else if (token[0] == '/') {
      // do operation
      if (stack.size() < 2) {
         cerr << "Pofxcalc: In expression " << expression_cnt << ": ";
         cerr << "Not enough operands for operator '" << token << "'.\n";
         return false;
      }

      Number right_val = stack.pop();
      stack.push(stack.pop() / right_val);

      if (stack.size() == 1) {
         valid = true;
      }
   }
   else {
      cerr << "Pofxcalc: In expression " << expression_cnt << ": '";
      cerr << token << "' is not a valid operator.\n";
      return false;
   }

   return true;
}

// operator>>
//
// Takes one line from istream evaluating the expression as it goes.
//
// Pre-condition: an in stream and a Pofxcalc object
// Post-condition: one expression read from the stream and evaluated
//
istream& operator>>(istream& is, Pofxcalc& calc) {
   char c, last = ' ';
   Pofxcalc::Token token;
   int tsize = 0, esize = 0;
   bool parsing_err = false;

   calc.expression_cnt++;
   calc.stack.clear();
   calc.valid = false;
   calc.expr[0] = '\0';

   token[0] = '\0';
   is.get(c);
   // evaluate all but the last token
   while (is.good() && c != '\n') {

      if (!parsing_err) {
         // ignore spaces and tabs
         if (c != ' ' && c != '	') {

            // add a space before the new token if it's not the first token
            if (tsize == 0 && esize != 0) {
               calc.expr[esize++] = ' ';
               calc.expr[esize] = '\0';
            }

            if (tsize < TOKEN_CAP - 1) {
               token[tsize++] = c;
               token[tsize] = '\0';

               calc.expr[esize++] = c;
               calc.expr[esize] = '\0';
            }
            else {
               cerr << "Pofxcalc: In expresion " << calc.expression_cnt;
               cerr << ": Token '" << token << "' excedes token capacity.\n";
               parsing_err = true;
            }
         }
         else if (last != ' ' && last != '	') {
            // if c is a space but last is not then the token is done
            if (!calc.evaluate(token))
               parsing_err = true;
            tsize = 0;
         }
      }

      last = c;
      is.get(c);
   }

   // if no tokens were entered do nothing
   if (token[0] == '\0') {
      calc.expression_cnt--;
   }
   // if tsize is 0 then this token was already evaluated
   else if (!parsing_err && tsize != 0) {
      // evaluate last token
      calc.evaluate(token);
   }
 
   return is;
}

// expression
//
// Returns the current expression.
//
// Pre-condition: none
// Post-condition: the expression returned.
//
char* Pofxcalc::expression() {
   return expr;
}

// operator<<
//
// Checks that the result is valid then writes it to ostream.
//
// Pre-condition: a Pofxcalc object
// Post-condition: The result of the most recently input expression
//
ostream & operator<<(ostream& os, Pofxcalc& calc) {
   if (!calc.valid) {
      os << "invalid expression";
   }
   else {
      Pofxcalc::Number tmp;
      tmp = calc.stack.pop();
      os << tmp;
      calc.stack.push(tmp);
   }
   return os;
}