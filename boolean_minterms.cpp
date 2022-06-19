#include <iostream>
#include <vector>
#include<string>
#include<stack>
#include<algorithm>
#include"facility.h"
using namespace std;
vector<string> tokens;
vector<string> post;

char x = 'X', y = 'Y', z = 'Z';
/*transform sum of prodeuct to minterms*/
vector<int> sop_to_min(calc_term sop) {
    vector<int> min;
    for (int i = 0; i < sop.termsize; i++) {
        if (!is_false(sop.terms[i])) {
            vector<int> tmp = get_min(sop.terms[i]);
            min.insert(min.end(), tmp.begin(), tmp.end());
        }
    }
    return min;
}
/*transfer expression to sum of product form*/
calc_term calc() {
    stack<calc_term> calc_stack;
    calc_term op1;
    calc_term op2;
    for (int i = 0; i < post.size(); i++) {
        if (post[i] == "+") {
            op1 = calc_stack.top();
            calc_stack.pop();
            op2 = calc_stack.top();
            calc_stack.pop();
            calc_term tmp=or_term(op1, op2);
            calc_stack.push(tmp);
        }
        else if (post[i] == "*") {
            op1 = calc_stack.top();
            calc_stack.pop();
            op2 = calc_stack.top();
            calc_stack.pop();
            calc_term tmp=and_calc_term(op1, op2);
            calc_stack.push(tmp);
        }
        else {
            calc_term t = get_term(post[i]);
            calc_stack.push(t);
        }
        
    }
    calc_term result= calc_stack.top();
    //print_calc_term(result);
    return result;
}
/*parsing*/
void separate_token(string s) {
    int i = 0, depth = 0;
    int x_v = -1;int y_v = -1;int z_v = -1;
    while (i < s.size()) {
        char ch = s.at( i ) ;

        if (ch == x) {
            if (i+1<s.size()&&s.at(i + 1) == '\'') {//peek next
                tokens.push_back("X'");
                if (i+2<s.size() && isalpha(s.at(i+2))) {
                tokens.push_back("*");
            }
            }
            else {
                tokens.push_back("X");
                if (i+1<s.size() && isalpha(s.at(i+1))) {
                tokens.push_back("*");
            }
            }
            
        }
        if (ch == y) {
            if (i+1<s.size()&&s.at(i + 1) == '\'') {//peek next
                tokens.push_back("Y'");
                if (i+2<s.size() && isalpha(s.at(i+2))) {
                tokens.push_back("*");
            }
            }
            else {
                tokens.push_back("Y");
                if (i+1<s.size() && isalpha(s.at(i+1))) {
                tokens.push_back("*");
            }
            }
            
        }
        if (ch == z) {
            if (i+1<s.size()&&s.at(i + 1) == '\'') {
                tokens.push_back("Z'");
                if (i+2<s.size() && isalpha(s.at(i+2))) {
                tokens.push_back("*");
            }
            }
            else {
                tokens.push_back("Z");
                if (i+1<s.size() && isalpha(s.at(i+1))) {
                tokens.push_back("*");
            }
            }
            
        }
        if (ch == '(') {
            if (i - 1 >= 0 && (isalpha(s.at(i - 1))||s.at(i - 1)=='\'')) {
                tokens.push_back("*");
            }
            tokens.push_back("(");
        }
        if (ch == ')') {
            tokens.push_back(")");
            if (i+1<s.size() && isalpha(s.at(i+1))) {
                tokens.push_back("*");
            }
        }
        if (ch == '+') {
            tokens.push_back("+");
        }
        
        i++;
    }
}
/*infix to postfix*/
void postfix() {
    //int i=0;
    stack<string> s;
    for(int i=0;i<tokens.size();i++){
        if (tokens[i] == "(") {
            s.push(tokens[i]);
         }
        else if (tokens[i] == ")") {
            while (s.top() != "(") {
                post.push_back(s.top());
                s.pop();
            }
            s.pop();//pop )
         }
        else if (tokens[i] == "+") {
            while (!s.empty()&&s.top() == "*") {
                post.push_back(s.top());
                s.pop();
            }
            s.push(tokens[i]);
        }
        else if (tokens[i] == "*") {
            s.push(tokens[i]);
        }
        else {//oprand
            post.push_back(tokens[i]);
        }
    }
    while (!s.empty()) {
        post.push_back(s.top());
        s.pop();
    }
}
void print_tokens() {
    for (int i = 0; i < tokens.size(); i++) {
        cout << tokens.at(i) << " ";
    }
}
void print_post() {
    cout << endl;
    for (int i = 0; i < post.size(); i++) {
        cout << post.at(i) << " ";
    }
}
int main()
{
    cout << "please enter a boolean expression:\n";
    string f;
    getline(cin, f);
    separate_token(f);
    //print_tokens();
    postfix();
    //print_post();
    calc_term sop=calc();
    vector<int> minterms_A=sop_to_min(sop);
    sort(minterms_A.begin(), minterms_A.end());
    minterms_A.erase(unique(minterms_A.begin(),minterms_A.end()), minterms_A.end());
    cout << "minterms:" << endl;
    for (int i = 0; i < minterms_A.size(); i++) {
        cout << minterms_A.at(i) << " ";
    }
 
}