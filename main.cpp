#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
/*
МозгРаботай это диалект brainfuck 
> перейти на следующюю ячейку
< перейти на предыдущюю ячейку
- вычесть 1 из текущей ячейки
+ прибавить 1 из текущей ячейки
( открыть блок который выполнится если условие верно
) закрыть блок который выполнится если условие верно
[ открытие цикла который будет работать пока одна из ячейек которая используется в цикле не станет 0
] закрытие цикла
? сравнить текущую ячейку со следующей ячейкой
. вывести символ
, получить данные от пользователя
* прибавить 5 к текущей ячейке
/ вычитает 5 из текущей ячейки
! обнуляет текущую ячейку
# показывает состояние текущей ячейки
^ переводит символ в нижний регистр
& переводит символ в верхний регистр
всё что не является <>[]-+,./?#()!* это комментарий
*/
using namespace std;
int main() {
    ifstream f("/storage/emulated/0/brainf#ck/src/source.bf");
    if (!f) {
        cout << "error 404";
        return 1;
    }
    vector<char> p;
    char c;
    while (f >> c) p.push_back(c);
    vector<char> n(30000, 0);
    auto np = n.begin();
    vector<vector<char>::iterator> s;
    vector<vector<char>::iterator> t;
    for (auto i = p.begin(); i < p.end(); ++i) {
        switch(*i) {
            case '>': ++np; break;
            case '<': --np; break;
            case '+': ++(*np); break;
            case '-': --(*np); break;
            case '.': cout << (*np); break;
            case ',': cin >> (*np); break;
            case '[':
                if (*np == 0) {
                    int depth = 1;
                    while (depth > 0) {
                        ++i;
                        if (i == p.end()) break;
                        if (*i == '[') ++depth;
                        else if (*i == ']') --depth;
                    }
                } else {
                    s.push_back(i);
                }
                break;
            case ']':
                if (*np != 0) {
                    i = s.back();
                } else {
                    s.pop_back();
                }
                break;
            case '(': break;
            case ')': break;
            case '?': if(*np != *(np + 1)){
            int depth = 1;
                while(depth > 0){
                    ++i;
                    if(i == p.end())
                    break;
                    if(*i == '(')
                    ++depth;
                    else if(*i == ')')
                    --depth;
                }
        }
            break;
            case '!': *np = 0; break;
            case '*': *np += 5; break;
            case '/': *np -= 5; break;
            case '#': printf("текущая ячейка: %i\n", *np);
            break;
            case '^': if(*np >= 'A' && *np <= 'Z'){ *np += 32; } break;
            case '&': if(*np >= 'a' && *np <= 'z'){ *np -= 32; } break;
        }
    }
    return 0;
}