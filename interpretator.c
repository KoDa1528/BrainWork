#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 100
#define COLS 100
#define MAX_CODE 10000

int main() {
    FILE *f = fopen("/storage/emulated/0/kaknibyd.bf", "r");
    if (!f) {
        printf("error 404\n");
        return 1;
    }
    
    // Читаем весь код в массив
    char code[MAX_CODE];
    size_t len = 0;
    char ch;
    while (len < MAX_CODE - 1 && fread(&ch, 1, 1, f) == 1) {
        code[len++] = ch;
    }
    code[len] = '\0';
    fclose(f);
    
    // 2. Создаём память (100x100)
    unsigned char memory[ROWS][COLS] = {0};
    int mp = 0;        // текущая строка (row)
    int np = 0;        // текущая колонка (col)
    
    // 3. Стек для циклов
    int stack[MAX_CODE];
    int top = -1;
    
    // 4. Исполняем код
    for (int i = 0; i < len; i++) {
        switch(code[i]) {
            case '>': np++; break;
            case '<': np--; break;
            case '@': mp++; np = 0; break;
            case '%': mp--; np = 0; break;
            case '+': memory[mp][np]++; break;
            case '-': memory[mp][np]--; break;
            case '.': 
    putchar(memory[mp][np]);
    fflush(stdout);
    break;
            case ',': memory[mp][np] = getchar(); break;
            
            case '[':
                if (memory[mp][np] == 0) {
                    // Пропустить цикл
                    int depth = 1;
                    while (depth > 0) {
                        i++;
                        if (i >= len) break;
                        if (code[i] == '[') depth++;
                        else if (code[i] == ']') depth--;
                    }
                } else {
                    // Запомнить позицию начала цикла
                    stack[++top] = i;
                }
                break;
                
            case ']':
                if (memory[mp][np] != 0) {
                    // Вернуться к началу цикла
                    i = stack[top];
                } else {
                    // Выйти из цикла
                    top--;
                }
                break;
                
            case '(':  // Условный блок
                if (memory[mp][np] == 0) {
                    int depth = 1;
                    while (depth > 0) {
                        i++;
                        if (i >= len) break;
                        if (code[i] == '(') depth++;
                        else if (code[i] == ')') depth--;
                    }
                }
                break;
                
            case ')':  // Конец условного блока
                break;
                
            case '!': memory[mp][np] = 0; break;
            case '*': memory[mp][np] += 5; break;
            case '/': memory[mp][np] -= 5; break;
            case '#': printf("\nтекущая ячейка: %d\n", memory[mp][np]); break;
            case '^': 
                if (memory[mp][np] >= 'A' && memory[mp][np] <= 'Z') 
                    memory[mp][np] += 32; 
                break;
            case '&': 
                if (memory[mp][np] >= 'a' && memory[mp][np] <= 'z') 
                    memory[mp][np] -= 32; 
                break;
        }
    }
    return 0;
}