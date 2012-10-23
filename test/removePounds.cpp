//#include <iostream>
//
//using namespace std;
//
//int main () {
//    char s[] = "}{-#-{##}-{#a#}}{#####}}{#-{}";
//    int prev, cur = 0, tail = 0;
//    bool flag = true;
//
//    while (s[cur] != '\0') {
//        if ((s[cur] == '{')&&(s[cur + 1] == '#')) {
//            prev = tail;
//            flag = false;
//        }
//        else if ((s[cur] == '}') && (!flag)) {
//            tail = prev;
//            flag = true;
//            cur++;
//        }
//        else if (s[cur] != '#') 
//            flag = true;
//        
//        s[tail++] = s[cur++];
//    }
//    s[tail] = '\0';
//    cout << s << endl;
//    return 0;
//}
