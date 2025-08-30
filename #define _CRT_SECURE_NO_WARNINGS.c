#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <iomanip> 
using namespace std;

struct PolyNode {
    float coef;
    int exp;
    PolyNode* next;

    PolyNode(float c = 0.0f, int e = 0, PolyNode* n = nullptr)
        : coef(c), exp(e), next(n) {
    }
};

PolyNode* create() {
    PolyNode* head = new PolyNode(); 
    head->next = nullptr;

    float c;
    int e;

    cout << "输入系数和指数（输入指数为-1结束，格式：系数,指数）：";

    while (true) {
        char comma; 
        if (!(cin >> c >> comma >> e) || comma != ',') {
            cout << "输入格式错误！请使用 '系数,指数' 格式，例如：3.5,2\n";
            cin.clear(); 
            cin.ignore(10000, '\n');  
            continue;
        }

        if (e == -1) break;

        PolyNode* p = new PolyNode(c, e);
        p->next = head->next;
        head->next = p;

        cout << "输入系数和指数（输入指数为-1结束）：";
    }

    return head;
}

void PolyAdd(PolyNode* polya, PolyNode* polyb) {
    PolyNode* pa = polya->next;
    PolyNode* pb = polyb->next;
    PolyNode* pre = polya;
    PolyNode* temp;

    while (pa != nullptr && pb != nullptr) {
        if (pa->exp < pb->exp) {
            pre->next = pa;
            pre = pa;
            pa = pa->next;
        }
        else if (pa->exp == pb->exp) {
            float sum = pa->coef + pb->coef;
            if (sum != 0.0f) {
                pa->coef = sum;
                pre->next = pa;
                pre = pa;
                pa = pa->next;
            }
            else {
                temp = pa;
                pa = pa->next;
                delete temp;

                temp = pb;
                pb = pb->next;
                delete temp;
                continue;  
            }

            temp = pb;
            pb = pb->next;
            delete temp;
        }
        else {
            pre->next = pb;
            pre = pb;
            pb = pb->next;
        }
    }

    if (pa != nullptr) {
        pre->next = pa;
    }
    else {
        pre->next = pb;
    }

    delete polyb; 
}

void Print(PolyNode* head) {
    PolyNode* p = head->next;
    cout << "\n多项式: ";

    bool first = true;
    while (p != nullptr) {
        if (!first) {
            if (p->coef > 0) cout << " + ";
            else { cout << " - "; p->coef = -p->coef; }
        }
        else {
            if (p->coef < 0) { cout << "-"; p->coef = -p->coef; }
        }

        if (p->coef == 1.0f && p->exp != 0) {
        }
        else {
            cout << fixed << setprecision(2) << p->coef;
        }

        if (p->exp == 0) {
        }
        else if (p->exp == 1) {
            cout << "x";
        }
        else {
            cout << "x^" << p->exp;
        }

        first = false;
        p = p->next;
    }

    if (first) cout << "0";
    cout << endl;
}

int main() {
    PolyNode* pa, * pb;

    cout << "创建多项式 A:\n";
    pa = create();

    cout << "创建多项式 B:\n";
    pb = create();

    PolyAdd(pa, pb);
    Print(pa);

    delete pa;

    return 0;
}