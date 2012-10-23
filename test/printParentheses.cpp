#include <iostream>
#include <stack>
#include <string.h>
using namespace std;

// print(n) = "{" + print(n - 1) +"}" || "{}" + print(n - 1) ? print(n - 1) + "{}"
// {};
// {}{}; {{}};
// {}{}{}; {}{{}}; {{}}{}; {{{}}}; {{}{}}
void printParentheses(int);

//int main() {
//    int n = 3;
//    printParentheses(n);
//    return 0;
//}

void printParentheses(int n) {
    if (n < 1) return;
    
    stack<string> s, result, temp;
    s.push("{}");
    
    while (n > 1) {
        string str = "";
        while (!s.empty()) {
            result.push("{" + s.top() + "}");
            str = "{}" + s.top();
            result.push(str);
            if (str.compare(s.top() + "{}") != 0)
                result.push(s.top() + "{}");
            s.pop();
        }
        temp = s;
        s = result;
        result = temp;
        n--;
    }
    
    while (!s.empty()) {
        cout<< s.top() <<endl;
        s.pop();
    }
}