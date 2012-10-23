////CSE20232/60732 homework 6 by Guowang Li
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//
//struct employee
//{
//    int id;
//    double hours;
//    double rate;
//    double pay;
//};
//
//using namespace std;
//
//int main (int argc, char **argv)
//{
//    string infile;
//    vector<employee> profile;
//    double total = 0, avg = 0;
//    int count = 0;
//    
//    if (argc == 1) {
//        cout << "Input the data file: " <<endl;
//        cin >> infile;
//    }
//    else if (argc == 2) {
//        infile = argv[1];
//    }
//    else {
//        cout << "Too many input." <<endl;
//        return 0;
//    }
//    
//    ifstream fin (infile.c_str(),ios::in);
//    //ifstream fin ("/Users/zishirs/Documents/workspace/test/test/employees.dat",ios::in);
//    
//    if (!fin.good()) {
//        cout << "Cannot find the file." <<endl;
//        return 0;
//    }
//
//    int i;
//    double h, r;
//    while (fin.good()) {
//        fin >> i >> h >> r;
//        if (i == -1) {
//            break;
//        }
//        employee em;
//        em.id = i;
//        em.hours = h;
//        em.rate = r;
//        em.pay = em.hours * em.rate;
//        
//        if (em.hours > 40) {
//            em.pay += (em.hours - 40) * 0.5*em.rate;
//        }
//        
//        total += em.pay;
//        count++;
//        profile.push_back(em);
//    }
//    
//    avg = total / count;
//    
//    cout << "ID: \t" << "Pay: " << endl;
//    cout.setf(ios::fixed);
//    for (vector<employee>::iterator it = profile.begin(); it < profile.end(); it++) {
//        cout<< it->id << "\t" ;
//        cout.precision(2);
//        cout<< it->pay << endl;
//    }
//    cout<< "\nTotal: "<<total<<endl;
//    cout<< "Average: "<<avg<<endl;
//    
//    return 0;
//}