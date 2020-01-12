#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_STACK 100 // max size of any stack
#define NUMBER '0' // signal that a number was found

int getop(char []);
void push1(double);
void push2(int);

void multi(int, double[]);  //does multiplication and alters value stack
void divis(int, double[]);
void addit(int, double[]);
void subtr(int, double[]);

int searchp1(char[]);   //returns next * position and alters opstack
int searchp2(char[]);
int searchp3(char[]);
int searchp4(char[]);

double valstack[MAX_STACK]; //value stack
char opstack[MAX_STACK];    //operator stack

int main() {
    int type;
    char s[MAX_STACK];
    
    while ((type = getop(s)) != EOF && type != '\n') {
        switch (type) {
            case NUMBER:
                push1(atof(s));
                break;
            case '+':
                push2(type);
                break;
            case '*':
                push2(type);
                break;
            case '-':
                push2(type);
                break;
            case '/':
                push2(type);
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    
    int p;
    while((p = searchp1(opstack)) != -1) {
        multi(p, valstack);
    }
    while((p = searchp2(opstack)) != -1) {
        divis(p, valstack);
    }
    while((p = searchp3(opstack)) != -1) {
        addit(p, valstack);
    }
    while((p = searchp4(opstack)) != -1) {
        subtr(p, valstack);
    }
    printf("The answer is... %.8g\n", valstack[0]);
    
    return 0;
}

int sp1 = 0;
int sp2 = 0;

void push1(double f) {
    if (sp1 < MAX_STACK)
        valstack[sp1++] = f;
    else
        printf("error: stack full, cant push %g\n", f);
}

void push2(int c) {
    if (sp2 < MAX_STACK) {
        opstack[sp2++] = c;
    }
    else
        printf("error: stack full, cant push %c\n", c);
}

int getch(void);
void ungettch(int);

int getop(char s[]) {
    int i = 0;
    int c, next1;
    
    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    
    if(!isdigit(c) && c != '.' && c != '-')
        return c;
    if(c == '-') {
        next1 = getch();
        if(!isdigit(next1) && next1 != '.') {
            return c;
        }
        c = next1;
    }
    else
        c = getch();
    while(isdigit(s[++i] = c))
        c = getch();
    if(c == '.')
        while(isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if(c != EOF)
        ungettch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungettch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int searchp1(char opstack[]) {
    int i = 0;
    int m, l;
    char opbuf[MAX_STACK];
    
    while (opstack[i] != '\0') {
        if (opstack[i] == '*') {
            for (m = 0, l = 0; opstack[m] != '\0'; m++, l++) {
                if (m == i) {
                    m++;
                }
                opbuf[l] = opstack[m];
                if (opbuf[l] == '\0') {
                    break;
                }
            }
            opbuf[l] = '\0';
            int k;
            for (k = 0; opbuf[k] != '\0'; k++) {
                opstack[k] = opbuf[k];
            }
            opstack[k] = '\0';
            return i;
        }
        i++;
    }
    return -1;
}

int searchp2(char opstack[]) {
    int i = 0;
    int m, l;
    char opbuf[MAX_STACK];
    
    while (opstack[i] != '\0') {
        if (opstack[i] == '/') {
            for (m = 0, l = 0; opstack[m] != '\0'; m++, l++) {
                if (m == i) {
                    m++;
                }
                opbuf[l] = opstack[m];
                if (opbuf[l] == '\0') {
                    break;
                }
            }
            opbuf[l] = '\0';
            int k;
            for (k = 0; opbuf[k] != '\0'; k++) {
                opstack[k] = opbuf[k];
            }
            opstack[k] = '\0';
            return i;
        }
        i++;
    }
    return -1;
}

int searchp3(char opstack[]) {
    int i = 0;
    int m, l;
    char opbuf[MAX_STACK];
    
    while (opstack[i] != '\0') {
        if (opstack[i] == '+') {
            for (m = 0, l = 0; opstack[m] != '\0'; m++, l++) {
                if (m == i) {
                    m++;
                }
                opbuf[l] = opstack[m];
                if (opbuf[l] == '\0') {
                    break;
                }
            }
            opbuf[l] = '\0';
            int k;
            for (k = 0; opbuf[k] != '\0'; k++) {
                opstack[k] = opbuf[k];
            }
            opstack[k] = '\0';
            return i;
        }
        i++;
    }
    return -1;
}

int searchp4(char opstack[]) {
    int i = 0;
    int m, l;
    char opbuf[MAX_STACK];
    
    while (opstack[i] != '\0') {
        if (opstack[i] == '-') {
            for (m = 0, l = 0; opstack[m] != '\0'; m++, l++) {
                if (m == i) {
                    m++;
                }
                opbuf[l] = opstack[m];
                if (opbuf[l] == '\0') {
                    break;
                }
            }
            opbuf[l] = '\0';
            int k;
            for (k = 0; opbuf[k] != '\0'; k++) {
                opstack[k] = opbuf[k];
            }
            opstack[k] = '\0';
            return i;
        }
        i++;
    }
    return -1;
}

void multi(int p, double valstack[]) {
    int i = 0;
    int j = 0;
    double valbuf[MAX_STACK];
    
    while (valstack[i] != '\0') {
        if (i == p) {
            valbuf[j] = (valstack[i] * valstack[i+1]);
            i = i + 2;
            j++;
        }
        valbuf[j] = valstack[i];
        if (valstack[i] == '\0') {
            i--;
            j--;
        }
        i++;
        j++;
    }
    valbuf[j] = '\0';
    int k = 0;
    while (valbuf[k] != '\0') {
        valstack[k] = valbuf[k];
        k++;
    }
    valstack[k] = '\0';
}

void divis(int p, double valstack[]) {
    int i = 0;
    int j = 0;
    double valbuf[MAX_STACK];
    
    while (valstack[i] != '\0') {
        if (i == p) {
            valbuf[j] = (valstack[i] / valstack[i+1]);
            i = i + 2;
            j++;
        }
        valbuf[j] = valstack[i];
        if (valstack[i] == '\0') {
            i--;
            j--;
        }
        i++;
        j++;
    }
    valbuf[j] = '\0';
    int k = 0;
    while (valbuf[k] != '\0') {
        valstack[k] = valbuf[k];
        k++;
    }
    valstack[k] = '\0';
}

void addit(int p, double valstack[]) {
    int i = 0;
    int j = 0;
    double valbuf[MAX_STACK];
    
    while (valstack[i] != '\0') {
        if (i == p) {
            valbuf[j] = (valstack[i] + valstack[i+1]);
            i = i + 2;
            j++;
        }
        valbuf[j] = valstack[i];
        if (valstack[i] == '\0') {
            i--;
            j--;
        }
        i++;
        j++;
    }
    valbuf[j] = '\0';
    int k = 0;
    while (valbuf[k] != '\0') {
        valstack[k] = valbuf[k];
        k++;
    }
    valstack[k] = '\0';
}

void subtr(int p, double valstack[]) {
    int i = 0;
    int j = 0;
    double valbuf[MAX_STACK];
    
    while (valstack[i] != '\0') {
        if (i == p) {
            valbuf[j] = (valstack[i] - valstack[i+1]);
            i = i + 2;
            j++;
        }
        valbuf[j] = valstack[i];
        if (valstack[i] == '\0') {
            i--;
            j--;
        }
        i++;
        j++;
    }
    valbuf[j] = '\0';
    int k = 0;
    while (valbuf[k] != '\0') {
        valstack[k] = valbuf[k];
        k++;
    }
    valstack[k] = '\0';
}
