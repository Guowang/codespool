//#include <iostream>
//#include <fstream>
//#include <string.h>
//#include <sstream>
//
//using namespace std;
//
//char words[101][101];
//int word_length[101];
//int word_count;
//
//int sequence_count;
//
//int output_id[10001];
//
//int output_start[10001];
//
//int output_end[10001];
//
//int ptr;
//
//int score[1000001];
//
//string text;
//
//void input();
//
//void process(int);
//
//void push_in(int, int, int);
//
//void output();
//
//int main()
//{
//    input();
//    output();
//    return 0;
//}
//
//void input()
//{
//    string word_file = "/Users/zishirs/Documents/workspace/test/test/codes2.cod";
//    ifstream word_in(word_file.c_str(),ios::in);
//    word_in >> word_count;
//    for (int i = 1; i <= word_count; i++) {
//        string s;
//        word_in >> s;
//        int j;
//        for (j = 1; ; j++) {
//            if (s[j-1] != 0) {
//                words[i][j] = s[j-1];
//            }
//            else
//                break;
//        }
//        word_length[i] = j-1;
//    }
//    word_in.close();
//    
//    string text_file = "/Users/zishirs/Documents/workspace/test/test/codes10.inp";
//    ifstream text_in(text_file.c_str(),ios::in);
//    text_in >> text;
//    //initialization
//    score[0] = 0;
//    ptr = 1;
//    sequence_count = 0;
//    while (1) {
//        if (text[ptr - 1] != 0) {
//            process(ptr);
//            ptr++;
//        }
//        else
//            break;
//    }
//    ptr--;
//    text_in.close();
//}
//
//void process(int in)
//{
//    int id, word_ptr;
//    int index, start, end;
//    bool flag;
//    score[in] = score[in - 1];
//    id = 0;
//    start = 0;
//    end = 0;
//    flag = 0;
//
//    //check every word
//    for (int i = 1; i <= word_count; i++) {
//        word_ptr = word_length[i];
//        index = in - 1;
//        if (text[index] == words[i][word_ptr]) {
//            if (word_length[i] == 1) {
//                if (score[index] + word_length[i] > score[in]) {
//                    flag = 1;
//                    score[in] = score[index] + word_length[i];
//                    id = i;
//                    start = index + 1;
//                    end = in;
//                }
//                break;
//            }
//            else {
//                word_ptr--;
//                index--;
//                while (1) {
//                    if (index < 0) {
//                        break;
//                    }
//                    if (text[index] == words[i][word_ptr]) {
//                        if (word_ptr == 1) {
//                            // check whether to count this word
//                            if (score[index] + word_length[i] > score[in]) {
//                                flag = 1;
//                                score[in] = score[index] + word_length[i];
//                                id = i;
//                                start = index + 1;
//                                end = in;
//                            }
//                            break;
//                        }
//                        word_ptr--;
//                        index--;
//                    }
//                    else
//                        index--;
//                }
//            }
//        }
//    }
//    //write to output
//    if (flag) {
//        push_in(id,start,end);
//    }
//}
//void push_in(int id, int start, int end)
//{
//    int sum;
//    sum = 0;
//    for (int i = 1; i <= sequence_count; i++) {
//        if (output_end[i] >= start) {
//            sum += word_length[output_id[i]];
//        }
//    }
//    if (word_length[id] > sum) {
//        int count;
//        count = sequence_count;
//        for (int i = 1; i <= count; i++) {
//            if (output_end[i] >= start) {
//                sequence_count--;
//                output_id[i] = 0;
//                output_start[i] = 0;
//                output_end[i] = 0;
//            }
//        }
//        sequence_count++;
//        output_id[sequence_count] = id;
//        output_start[sequence_count] = start;
//        output_end[sequence_count] = end;
//    }
//    
//}
//void output()
//{
//    sequence_count--;
//    cout<<score[ptr]<<endl;
//    for (int i = 1; i <= sequence_count; i++) {
//        cout<< output_id[i] << "\t" << output_start[i] << "\t" << output_end[i] <<endl;
//    }
//    
//}
