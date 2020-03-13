#include <string>
#include <vector>

struct C1 {
    int a = 1;
    char b = 2;
};

struct C2 {
    std::string a;
    C2() : a("aiueo"){}
};

struct C3 {
    C1 a;
    C2 b;
    int c = 10;
};

struct C4 {
    std::vector<C1> a;
    double b;
    C4() {
        a.push_back(C1());
        a.push_back(C1());
        a.push_back(C1());
        b = 1.0f;
    }
};

#include <iostream>
#include <map>
#include <typeindex>

#include "picojson.h"
#include <algorithm>

#define TO_STRING(VariableName) # VariableName
//#define NNN(C,M) (TO_STRING(C)##TO_STRING)

// mattann
void f(picojson::object& p, std::string label, int s) {
    std::cout << label << std::endl;
    p.insert(std::make_pair(label, picojson::value(static_cast<double>(s))));
}
void f(picojson::object& p, std::string label, bool s) {
    std::cout << label << std::endl;
    p.insert(std::make_pair(label, picojson::value(s)));
}
void f(picojson::object& p, std::string label, std::string s) {
    std::cout << label << std::endl;
    p.insert(std::make_pair(label, picojson::value(s)));
}

template <typename T>
void f(picojson::object& p, std::string label, const std::vector<T>& s) {
    std::for_each(s.begin(), s.end(), [&](T&rs){
        f(p, label, rs);
    });
}

void f(picojson::object& p, std::string label, const C1& s) {
    picojson::object p2;
    f(p2, "a", s.a);
    f(p2, "b", s.b);
    p.insert(std::make_pair(label, picojson::value(p2)));
}
void f(picojson::object& p, std::string label, const C2& s) {
    picojson::object p2;
    f(p2, "a", s.a);
    p.insert(std::make_pair(label, picojson::value(p2)));
}
void f(picojson::object& p, std::string label, const C3& s) {
    picojson::object p2;
    f(p2, "a", s.a);
    f(p2, "b", s.b);
    f(p2, "c", s.c);
    p.insert(std::make_pair(label, picojson::value(p2)));
}

/*
void f(picojcon::object& p, std::string s) {}

// 
template <typename T>
void f(picojcon::object& p, std::vector<T> s) {
    std::for_each(s.begin(), s.end(), [p](T &n) {
        //*p += n;
        std::cout << n << std::endl;
    });
}
*/


int main() {
    std::map<std::type_index, int> m = {
        { typeid(int), 10 },
        { typeid(C1), 12 },
        { typeid(C4), 13 }
    };

    //std::cout << m.at(typeid(C1)) << std::endl;

    std::vector<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    //f(&m, x);

    C4 a;



    picojson::object p;
    //f(p, "a", 10);
    //f(p, "b", "10");

    C3 b;
    f(p, "C3", b);
    std::cout << "================================" << std::endl;
    std::cout << picojson::value(p) << std::endl;
    return 0;
}