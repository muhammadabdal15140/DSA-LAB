#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Stu {
    int id;
    char name[100];
    char dept[10];     // FIXED size
    int sem;
    float gpa;
    int cred;
    int yr;
    Stu* nxt;
};

Stu* first = nullptr;
int total = 0;

void load() {
    first = nullptr;
    total = 0;

    ifstream in("students_data.txt");
    if (!in) {
        cout << "Cant open\n";
        return;
    }

    in >> total;
    Stu* lastone = nullptr;

    for (int i = 0; i < total; i++) {
        Stu* n = new Stu;

        in >> n->id;
        in.ignore();
        in.getline(n->name, 100);
        in >> n->dept >> n->sem >> n->gpa >> n->cred >> n->yr;

        n->nxt = nullptr;

        if (!first)
            first = n;
        else
            lastone->nxt = n;

        lastone = n;
    }
    in.close();
}

/* SAFE DATA-ONLY SWAP */
void swapStu(Stu* a, Stu* b) {
    int id = a->id;
    char name[100], dept[10];
    int sem = a->sem, cred = a->cred, yr = a->yr;
    float gpa = a->gpa;

    strcpy(name, a->name);
    strcpy(dept, a->dept);

    a->id = b->id;
    strcpy(a->name, b->name);
    strcpy(a->dept, b->dept);
    a->sem = b->sem;
    a->gpa = b->gpa;
    a->cred = b->cred;
    a->yr = b->yr;

    b->id = id;
    strcpy(b->name, name);
    strcpy(b->dept, dept);
    b->sem = sem;
    b->gpa = gpa;
    b->cred = cred;
    b->yr = yr;
}

/* ================= FILE 1 ================= */
void makeFile1() {
    Stu* copyHead = nullptr;
    Stu* copyLast = nullptr;

    for (Stu* o = first; o; o = o->nxt) {
        Stu* n = new Stu(*o);
        n->nxt = nullptr;

        if (!copyHead)
            copyHead = n;
        else
            copyLast->nxt = n;

        copyLast = n;
    }

    for (Stu* c = copyHead; c; c = c->nxt) {
        Stu* maxN = c;
        for (Stu* t = c->nxt; t; t = t->nxt) {
            if (t->gpa > maxN->gpa ||
                (t->gpa == maxN->gpa && t->cred > maxN->cred))
                maxN = t;
        }
        if (maxN != c)
            swapStu(c, maxN);
    }

    ofstream out("ranked_by_cgpa.txt");
    out << "STUDENTS RANKED BY CGPA\n\n";

    int r = 1;
    for (Stu* c = copyHead; c; c = c->nxt) {
        out << r++ << ". " << c->id << " " << c->name << " "
            << c->dept << " Sem" << c->sem
            << " CGPA:" << fixed << setprecision(2) << c->gpa << endl;
    }

    while (copyHead) {
        Stu* t = copyHead;
        copyHead = copyHead->nxt;
        delete t;
    }
    out.close();
}

/* ================= FILE 2 ================= */
void makeFile2() {
    Stu* copyHead = nullptr;
    Stu* copyLast = nullptr;

    for (Stu* o = first; o; o = o->nxt) {
        Stu* n = new Stu(*o);
        n->nxt = nullptr;

        if (!copyHead)
            copyHead = n;
        else
            copyLast->nxt = n;

        copyLast = n;
    }

    for (Stu* c = copyHead; c; c = c->nxt) {
        Stu* minN = c;
        for (Stu* t = c->nxt; t; t = t->nxt) {
            if (t->yr < minN->yr ||
                (t->yr == minN->yr && t->id < minN->id))
                minN = t;
        }
        if (minN != c)
            swapStu(c, minN);
    }

    ofstream out("sorted_by_enrollment.txt");
    out << "SORTED BY ENROLLMENT YEAR\n\n";

    int curYr = -1;
    float sum = 0;
    int cnt = 0;

    for (Stu* c = copyHead; c; c = c->nxt) {
        if (c->yr != curYr) {
            if (curYr != -1)
                out << "Average CGPA: " << fixed << setprecision(2)
                    << sum / cnt << "\n\n";

            curYr = c->yr;
            sum = 0;
            cnt = 0;
            out << "Year " << curYr << endl;
        }

        out << c->id << " " << c->name
            << " CGPA:" << c->gpa << endl;

        sum += c->gpa;
        cnt++;
    }

    if (cnt > 0)
        out << "Average CGPA: " << fixed << setprecision(2)
            << sum / cnt << endl;

    while (copyHead) {
        Stu* t = copyHead;
        copyHead = copyHead->nxt;
        delete t;
    }
    out.close();
}

/* ================= FILE 3 ================= */
void makeFile3() {
    Stu* copyHead = nullptr;
    Stu* copyLast = nullptr;

    for (Stu* o = first; o; o = o->nxt) {
        Stu* n = new Stu(*o);
        n->nxt = nullptr;

        if (!copyHead)
            copyHead = n;
        else
            copyLast->nxt = n;

        copyLast = n;
    }

    for (Stu* c = copyHead; c; c = c->nxt) {
        Stu* best = c;
        for (Stu* t = c->nxt; t; t = t->nxt) {
            if (strcmp(t->dept, best->dept) < 0 ||
                (strcmp(t->dept, best->dept) == 0 && t->sem < best->sem) ||
                (strcmp(t->dept, best->dept) == 0 && t->sem == best->sem && t->gpa > best->gpa))
                best = t;
        }
        if (best != c)
            swapStu(c, best);
    }

    ofstream out("department_analysis.txt");
    out << "DEPARTMENT ANALYSIS\n\n";

    char cur[10] = "";
    float sum = 0;
    int cnt = 0;
    float maxG = -1, minG = 5;

    for (Stu* c = copyHead; c; c = c->nxt) {
        if (strcmp(c->dept, cur) != 0) {
            if (cnt > 0) {
                out << "Avg CGPA: " << sum / cnt << endl;
                out << "High: " << maxG << " Low: " << minG << "\n\n";
            }
            strcpy(cur, c->dept);
            sum = 0;
            cnt = 0;
            maxG = -1;
            minG = 5;
            out << "Department " << cur << endl;
        }

        out << c->name << " GPA:" << c->gpa << endl;
        sum += c->gpa;
        cnt++;
        if (c->gpa > maxG) maxG = c->gpa;
        if (c->gpa < minG) minG = c->gpa;
    }

    if (cnt > 0) {
        out << "Avg CGPA: " << sum / cnt << endl;
        out << "High: " << maxG << " Low: " << minG << endl;
    }

    while (copyHead) {
        Stu* t = copyHead;
        copyHead = copyHead->nxt;
        delete t;
    }
    out.close();
}

/* ================= FILE 4 ================= */
void insertNameSort(Stu** h, Stu* n) {
    if (!*h || strcmp(n->name, (*h)->name) < 0) {
        n->nxt = *h;
        *h = n;
    } else {
        Stu* c = *h;
        while (c->nxt && strcmp(n->name, c->nxt->name) > 0)
            c = c->nxt;

        n->nxt = c->nxt;
        c->nxt = n;
    }
}

void makeFile4() {
    Stu *elite = nullptr, *high = nullptr, *good = nullptr, *sat = nullptr, *need = nullptr;
    int e = 0, h = 0, g = 0, s = 0, n = 0;

    for (Stu* c = first; c; c = c->nxt) {
        Stu* x = new Stu(*c);
        x->nxt = nullptr;

        if (c->gpa >= 3.7) insertNameSort(&elite, x), e++;
        else if (c->gpa >= 3.3) insertNameSort(&high, x), h++;
        else if (c->gpa >= 3.0) insertNameSort(&good, x), g++;
        else if (c->gpa >= 2.5) insertNameSort(&sat, x), s++;
        else insertNameSort(&need, x), n++;
    }

    ofstream out("performance_tiers.txt");
    out << "PERFORMANCE TIERS\n\n";

    auto print = [&](Stu* h) {
        for (; h; h = h->nxt)
            out << h->name << " (" << h->gpa << ")\n";
    };

    out << "ELITE\n"; print(elite);
    out << "\nHIGH\n"; print(high);
    out << "\nGOOD\n"; print(good);
    out << "\nSATISFACTORY\n"; print(sat);
    out << "\nNEEDS IMPROVEMENT\n"; print(need);

    while (elite) { Stu* t = elite; elite = elite->nxt; delete t; }
    while (high) { Stu* t = high; high = high->nxt; delete t; }
    while (good) { Stu* t = good; good = good->nxt; delete t; }
    while (sat) { Stu* t = sat; sat = sat->nxt; delete t; }
    while (need) { Stu* t = need; need = need->nxt; delete t; }

    out.close();
}

void freeAll() {
    while (first) {
        Stu* t = first;
        first = first->nxt;
        delete t;
    }
}

int main() {
    load();
    if (total == 0) {
        cout << "No data\n";
        return 1;
    }

    makeFile1();
    makeFile2();
    makeFile3();
    makeFile4();

    freeAll();
    cout << "Files done\n";
    return 0;
}