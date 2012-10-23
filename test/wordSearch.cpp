//#include <iostream>
//#include <string.h>
//#include <vector>
//using namespace std;
//
//bool isExist(vector< vector<char> >&, string);
//
//bool check(vector< vector<char> >&, string, int, int, vector< vector<bool> >&);
//
//char getChar(vector< vector<char> >&, int, int, vector< vector<bool> >&);
//
//int main() {
//    char c[3][5] = {"ABCE","SFCS","ADEE"};
//    vector< vector<char> > board(3);
//    board[0].assign(c[0], c[0] + 4);
//    board[1].assign(c[1], c[1] + 4);
//    board[2].assign(c[2], c[2] + 4);
//    string word = "ABCB";
//    
//    cout<< boolalpha << isExist(board, word) <<endl;
//    return 0;
//}
//
//bool isExist(vector< vector<char> >& board, string word) {
//    if (word.length() == 0)
//        return true;
//    
//    int m = board.size();
//    int n = board[0].size();
//    
//    if (m == 0 || n == 0)
//        return false;
//    
//    for (int i = 1; i < m; i++) 
//        if (board[i].size() != n)
//            return false;
//    
//    for (int i = 0; i < m; i++)
//        for (int j = 0; j < n; j++)
//            if (board[i][j] == word[0]) {
//                if (word.length() == 1)
//                    return true;
//                vector< vector<bool> > occupied(m, vector<bool>(n, false));
//                occupied[i][j] = true;
//                if (check(board, word.substr(1, word.length() - 1), i, j, occupied))
//                    return true;
//            }
//    return false;
//}
//
//bool check(vector< vector<char> >& board, string word, int i, int j, vector< vector<bool> >& occupied) {
//    if (getChar(board, i - 1, j, occupied) == word[0]) {
//        if (word.length() == 1)
//            return true;
//        occupied[i - 1][j] = true;
//        if (check(board, word.substr(1, word.length() - 1), i - 1, j, occupied))
//            return true;
//        else
//            occupied[i - 1][j] = false;
//    }
//    
//    if (getChar(board, i + 1, j, occupied) == word[0]) {
//        if (word.length() == 1)
//            return true;
//        occupied[i + 1][j] = true;
//        if (check(board, word.substr(1, word.length() - 1), i + 1, j, occupied))
//            return true;
//        else
//            occupied[i + 1][j] = false;
//    }
//    
//    if (getChar(board, i, j - 1, occupied) == word[0]) {
//        if (word.length() == 1)
//            return true;
//        occupied[i][j - 1] = true;
//        if (check(board, word.substr(1, word.length() - 1), i, j - 1, occupied))
//            return true;
//        else
//            occupied[i][j - 1] = false;
//    }
//    
//    if (getChar(board, i, j + 1, occupied) == word[0]) {
//        if (word.length() == 1)
//            return true;
//        occupied[i][j + 1] = true;
//        if (check(board, word.substr(1, word.length() - 1), i, j + 1, occupied))
//            return true;
//        else
//            occupied[i][j + 1] = false;
//    }
//    return false;
//}
//
//char getChar(vector< vector<char> >& board, int i, int j, vector< vector<bool> >& occupied) {
//    int m = board.size();
//    int n = board[0].size();
//    
//    if (i >=0 && i < m && j >= 0 && j < n && !occupied[i][j])
//        return board[i][j];
//    return '$';
//}