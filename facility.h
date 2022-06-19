#pragma once
#include<vector>
#include <string>
using namespace std;

struct term {
    int pos[6] = { -1, -1, -1,-1, -1, -1 };
};
struct calc_term {
    int termsize = 1;
    term terms[5];
};
void print_calc_term(calc_term c) {
    cout << "size: " << c.termsize << endl;;
    for (int i = 0; i < c.termsize; i++) {
        for (int j = 0; j < 6; j++) {
            cout << c.terms[i].pos[j] ;
        }
        cout << endl;
    }
}
term and_term(term a, term b) {
    term c=a;
    for (int i = 0; i < 6; i++) {
        if (b.pos[i] == 1) {
            c.pos[i] = 1;
        }
    }
    return c;
}
bool is_false(term a) {//check if there is any X X'
    if (a.pos[0] == a.pos[3] && a.pos[3] == 1)
        return true;
    if (a.pos[1] == a.pos[4] && a.pos[4] == 1)
        return true;
    if (a.pos[2] == a.pos[5] && a.pos[5] == 1)
        return true;
    return false;
}
vector<int> get_min(term a) {
    int x = -1, y = -1, z = -1;
    if (a.pos[0] == 1) x = 1;
    if (a.pos[1] == 1) y = 1;
    if (a.pos[2] == 1) z = 1;
    if (a.pos[3] == 1) x = 0;
    if (a.pos[4] == 1) y = 0;
    if (a.pos[5] == 1) z = 0;
    vector<int> mins;
    mins.push_back(0);
    if (x != -1) {
        mins.at(0) += x * 4;
    }
    else {
        mins.at(0) += 0 * 4;
        mins.push_back(1 * 4);
    }
    if (y != -1) {
        for (int i = 0; i < mins.size(); i++) {
            mins.at(i) += y * 2;
        }
    }
    else {
        int cur_size = mins.size();
        for (int i = 0; i < cur_size; i++) {
            mins.push_back(mins.at(i) + 1 * 2);
        }
    }
    if (z != -1) {
        for (int i = 0; i < mins.size(); i++) {
            mins.at(i) += z ;
        }
    }
    else {
        int cur_size = mins.size();
        for (int i = 0; i < cur_size; i++) {
            mins.push_back(mins.at(i) + 1*1);
        }
    }
    
    return mins;
}
calc_term or_term(calc_term op1, calc_term op2) {
    for (int i = 0; i < op2.termsize; i++) {
        op1.terms[op1.termsize] = op2.terms[i];
        op1.termsize++;
    }
    return op1;
}
calc_term and_calc_term(calc_term op1, calc_term op2) {
    calc_term ret;
    int cnt = 0;
    for (int i = 0; i < op1.termsize; i++) {
        for (int j = 0; j < op2.termsize; j++) {
            ret.terms[cnt]=and_term(op1.terms[i], op2.terms[j]);
            cnt++;
        }
    }
    ret.termsize = cnt;
    return ret;
    
}

calc_term get_term(string s) {
    calc_term ret;
    
    if (s == "X") {
        ret.terms[0] = { {  1, -1, -1, -1, -1, -1 } };
    }
    if (s == "Y") {
        ret.terms[0] = { {  -1, 1, -1, -1, -1, -1} };
    }
    if (s == "Z") {
        ret.terms[0] = { { -1, -1, 1, -1, -1, -1} };
    }
    if (s == "X'") {
        ret.terms[0] = { { -1, -1, -1, 1, -1, -1 } };
    }
    if (s == "Y'") {
        ret.terms[0] = { { -1, -1, -1, -1, 1, -1} };
    }
    if (s == "Z'") {
        ret.terms[0] = { { -1, -1, -1, -1, -1, 1} };
    }
    return ret;

}

