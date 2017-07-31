//#include <iostream>
#include <string>
#include <stack>
//#include <cassert>
using namespace std;

int evaluate(const string& infix, bool values[], string& postfix, bool& result){
          // Evaluates a boolean expression


          // Precondition: infix is an infix boolean expression consisting of
          //   the digits 0 through 9, the operators |, &, and !, and parentheses,
	      //   with embedded blanks allowed for readability.

	int paren=0;

	const int DIGIT=0;
	const int OPERATOR=1;
	int want=DIGIT;

	/////////////////////////////////////////
	//CHECK IF INFIX IS SYNTACTICALLY VALID//
	/////////////////////////////////////////

	for(int i=0;i<infix.size();i++){ //check to make sure the infix statement is wellformed
		if(infix[i]=='('){ //keep track of parentheses (left paran is pos, right is neg)
			paren++;
			if(want==OPERATOR){ //if an operator is expected because the paren could be following a digit, when that would not be valid, return 1
				return 1;
			}
		}else if (infix[i]==')'){
			paren--;
			if(want==DIGIT){ //if a DIGIT is expected, because the paren could be closing after an operator or with nothing in it at all, return 1
				return 1;
			}
		}

		if(paren<0){ //if the "count" of paren is negative (meaning that a right paren must have come before its left counterpart) return 1
			return 1;
		}

		if(infix[i]>='0'&&infix[i]<='9'){ //if the character is a digit
			if(want==OPERATOR){ //but an operator was expected
				return 1;
			}
			want=OPERATOR; //otherwise, take note that an operator is expected next
		}else if(infix[i]=='|'||infix[i]=='&'){ //if an AND or OR operator is encountered
			if(want==DIGIT){ //but a digit was expected
				return 1;
			}
			want=DIGIT; //otherwise, take note that an operator is expected next
		}else if(infix[i]=='!'){ //if the inverse operator is found
			if(want==OPERATOR){ //but a logic operator was expected ('!' can work where ever a DIGIT works - a Digit must follow, though)
				return 1; 
			}
		}else if(infix[i]=='('||infix[i]==')'||infix[i]==' '){ //if a '(', ')', or ' ' is found, skip over it (parenthases are already checked and spaces do not matter).
			continue;
		}else{ //if it is any other character, return 1
			return 1;
		}
	}

	if(paren!=0||want==DIGIT){ //if the count of paren is not zero (as in, there werent an equal number of both left and right paren) OR if a DIGIT is wanted (as in, it ended on an operator)
		return 1;
	}

          // Postcondition: If infix is a syntactically valid infix boolean
          //   expression, then postfix is set to the postfix form of that
          //   expression, 
	stack<char> operators;
	postfix="";

	/////////////////////////////
	//CREATE POSTFIX EXPRESSION//
	/////////////////////////////
	for(int i=0;i<infix.size();i++){//cycle through each character in infix
		if(infix[i]==' '){ //if the current character is a space, then skip it (unneeded in postfix)
				continue;
		}
			
		if(infix[i]>='0'&&infix[i]<='9'){ //if it is a digit, then push it straight onto the postfix string
			postfix+=infix[i];
		}else{ //otherwise, it must be an operator or paren
			char top;
			if(!operators.empty()){ //if the operator stack is empty, then set 'top' to be empty
				top=operators.top();
			}else{
				top=' ';
			}

			char curr=infix[i]; //save the value of the current infix character

			if(top==' '||curr=='!'||curr=='('||top=='('||top==curr){ //push the operator straight to the stack in these conditions
				operators.push(curr);
			}
			else if(curr==')'){ //if a right paren is met
				while(operators.top()!='('){ //cycle until the matching left paren is met on the stack
					postfix+=operators.top(); //push the operators that were still within the parentheses onto the postfix equation
					operators.pop();
				}
				operators.pop(); //take off the left paren on teh stack
			}
			else if(curr=='&'){ //if an AND operator is encountered
				while(!operators.empty()&&operators.top()=='!'){ //remove all operators that are of a higher precedence that are immediately before it (stack should always be in order, but a left paren could stop this - "||&&!!(|&!" )
					postfix+=operators.top(); //push the operators that are removed in order to put the AND operator on the stack into the postfix equation
					operators.pop();
				}
				operators.push(curr); //push the AND operator onto the stack
			}
			else if(curr=='|'){ //if an OR operator is encountered
				while(!operators.empty()&&(operators.top()=='!'||operators.top()=='&')){ //remove all operators that are of higher precedence (& and !)
					postfix+=operators.top(); //push the operators that are removed onto the postfix expression
					operators.pop();
				}
				operators.push(curr); //push the OR operator onto the stack
			}
		}
	}
	while(!operators.empty()){ //while the operators stack still has stuff in it
		if(operators.top()!='('&&operators.top()!=')'){
			postfix+=operators.top(); //push it on the end of the postfix string
		}
		operators.pop();
	}

	//Evaluate the final value of the expression
	stack<bool> vals;

	///////////////////////////////////
	//EVALUATE THE POSTFIX EXPRESSION//
	///////////////////////////////////
	for(int i=0;i<postfix.size();i++){ //cycle through every value of postfix
		if(postfix[i]>='0'&&postfix[i]<='9'){ //if the character represents a digit (that can then be used to get a bool value from the values array)
			vals.push(values[postfix[i]-'0']); //then push the bool value of the digit onto the stack
		}else{
			if(postfix[i]=='!'){ //if the inverse operator is found
				bool top=vals.top();
				vals.pop(); //pop of the top item
				top=!top; //invert it
				vals.push(top); //and push it back on
			}else if(postfix[i]=='&'||postfix[i]=='|'){ //if an AND or OR operator are found
				bool first=vals.top(); //pop off the first two values from the stack (they represent the left and right operands
				vals.pop();
				bool second=vals.top();
				vals.pop();
				
				bool calc; //this is a calculation of the operation
				if(postfix[i]=='&'){
					calc=first&&second;
				}
				else if(postfix[i]=='|'){
					calc=first||second;
				}
				vals.push(calc); //push the calculation, because it will be used for the next operation
			}
		}
	}
	result=vals.top();

		  //   result is set to the value of the expression (where
          //   each digit k represents the kth element of the values array), and
          //   the function returns zero.  If infix is a malformed expression,
          //   the return value is 1. (In that case, postfix may or may not be
          //   changed and but result must be unchanged.)

	return 0;
}


 /*       int main()
        {
            for(int i=0;i<1000;i++){
				bool ba[10] = {
              //  0      1      2      3      4      5      6      7      8      9
                true,  true,  true,  false, false, false, true,  false, true,  false
            };

            string pf;
            bool answer;
            assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
            assert(evaluate("8|", ba, pf, answer) == 1);
            assert(evaluate("4 5", ba, pf, answer) == 1);
            assert(evaluate("01", ba, pf, answer) == 1);
            assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
            assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
                                   &&  pf == "43!03&&|"  &&  !answer);

			//custom error testing:
			assert(evaluate("6|)5(&6", ba, pf, answer) == 1);
			assert(evaluate("6()", ba, pf, answer) == 1);
			assert(evaluate("6&", ba, pf, answer) == 1);
			assert(evaluate("6&&6", ba, pf, answer) == 1);
			assert(evaluate("69", ba, pf, answer) == 1);
			assert(evaluate("&", ba, pf, answer) == 1);
			assert(evaluate("!", ba, pf, answer) == 1);
			assert(evaluate("6&!", ba, pf, answer) == 1);
			assert(evaluate("6(5|4)", ba, pf, answer) == 1);
			assert(evaluate("6!(5|4)", ba, pf, answer) == 1);
			assert(evaluate("6&(5|a)", ba, pf, answer) == 1);
			assert(evaluate("((((()))))", ba, pf, answer) == 1);


            assert(evaluate("", ba, pf, answer) == 1);
            assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
			assert(evaluate("(9)&(1)", ba, pf, answer) == 0  &&  pf == "91&"  &&  !answer);



			assert(evaluate("1&!(9|1&1|9) | !!!(9&1&9)", ba, pf, answer) == 0  &&  pf == "1911&9||!&919&&!!!|" &&  answer);
			assert(evaluate("2", ba, pf, answer) == 0  &&  pf == "2" &&  answer);
			assert(evaluate("(3)", ba, pf, answer) == 0  &&  pf == "3" &&  !answer);
			assert(evaluate("2&(3)", ba, pf, answer) == 0  &&  pf == "23&" &&  !answer);
			assert(evaluate("2&(3)", ba, pf, answer) == 0  &&  pf == "23&" &&  !answer);
			assert(evaluate("0 & !9", ba, pf, answer) == 0  &&  pf == "09!&" &&  answer);
			assert(evaluate("!(7|8)", ba, pf, answer) == 0  &&  pf == "78|!" &&  !answer);
			assert(evaluate("!7|8", ba, pf, answer) == 0  &&  pf == "7!8|" &&  answer);
			assert(evaluate("6|4&5", ba, pf, answer) == 0  &&  pf == "645&|" &&  answer);
			
			ba[2] = false;
            ba[9] = true;
            assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
            assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
			assert(evaluate("2&!(1|2|3|4)|6&(4|(6|(3&7)))", ba, pf, answer) == 0  &&  pf == "21234|||!&64637&||&|" &&  answer);
			assert(evaluate("", ba, pf, answer) == 1);

			}

            cout << "Passed all tests" << endl;
			return 0;
        }
		
		*/ 