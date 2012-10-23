//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//void convertIntsToChars(char *);
//
//void convert(const char *, int, char *, int);
//
//bool isConvertable(char *);
//
//char int2c(const char *, int, int);
//
//int main() {
//    
//    char s1[6] = "12259";
//    
//    convertIntsToChars(s1);
//    
//    return 0;
//}
//
//void convertIntsToChars(char * s) {
//    if (!isConvertable(s))
//        printf("Not convertable.\n");
//    char* output = (char*) malloc(strlen(s) + 1);
//    convert(s, 0, output, 0);
//    free(output);
//}
//
//bool isConvertable(char * s) {
//    int n = (int) strlen(s);
//    if (n == 0)
//        return false;
//    for (int i = n - 1; i > 0; i--) {
//        if (s[i] == 0 && (s[i - 1] != 1 || s[i - 2] != 2))
//            return false;
//    }
//    return true;
//}
//
//char int2c(const char* s, int i, int len){
//    if (len == 1)
//        return s[i] - '1' + 'a';
//    return (s[i] - '0')*10 + s[i + 1] - '1' + 'a';
//}
//
//void convert(const char* s, int i, char* output, int j) {
//    if (s[i] == '\0') {
//        output[j] = '\0';
//        printf("%s\n", output);
//        return;
//    }
//    if (s[i] == 0) {
//        return;
//    }
//    output[j] = int2c(s, i, 1);
//    convert(s, i + 1, output, j + 1);
//    
//    if (s[i + 1] == '\0')
//        return;
//    
//    if (s[i] == '1' || (s[i] == '2' && s[i + 1] < '7')) {
//        output[j] = int2c(s, i, 2);
//        convert(s, i + 2, output, j + 1);
//    }
//}
