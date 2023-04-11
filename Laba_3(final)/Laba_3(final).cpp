
#include <iostream>
#include <math.h>
#include<complex>
#include <fstream>

using namespace std;
////////////////////////////////////////////////          Task 1          ////////////////////////////////////////////////
class Square
{
    short a; // сторона
    unsigned int color;

public://Конструктори зі стандартними або заданими значеннями для параметрів
    Square() : a(0), color(0) {}
    Square(short ai, short c) : a(ai), color(c) {}

    double getA() const { return a; }
    void setA(double a)
    {
        if (a < 0 || a > 1.e+100)
        {
            cout << "Error setting a" << endl;
            return;
        }
        this->a = a;
    }
    unsigned int getColor() const { return color; }
    void setColor(unsigned int c)
    {
        if (c < 0 || c > 10000)
        {
            cout << "Error setting color" << endl;
            return;
        }
        this->color = c;
    }

    double S() const { return a * a; }
    double P() const { return a * 4; }
    double r() const { return a / 2; }
    double R() const { return a / (sqrt(2)); }
    // Друк інформації про квадрат
    void printInfo() const
    {
        cout << " a = " << a << endl << " color = " << color << endl;
        cout << endl << "Your result:" << endl;
        cout << endl << " S = " << S() << "\t P = " << P() << endl << " r= " << r() << endl << " R= " << R() << endl;
    }
};
////////////////////////////////////////////////          Task 2         /////////////////////////////////////////////////////////////////////////
#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#pragma warning(disable : 4996)
typedef complex<unsigned int> ComplexUnInt;
class ComplexVector
{
    ComplexUnInt* v; // вказівник на масив комплексних чисел
    int num;// кількість елементів у масиві
    int state; // стан вектора
public:
    //1
    ComplexVector() : v(NULL), num(0), state(0) {}
    //виділяє простір для одного елемента та ініціалізує його нулем

    ComplexVector(int n);// конструктор, який створює вектор розміром n
    ComplexVector(int n, ComplexUnInt&); //конструктор, який створює вектор розміром n та ініціалізує його комплексним числом
    ComplexVector(int n, ComplexUnInt*);
    // конструктор, який створює вектор розміром n та ініціалізує його масивом комплексних чисел
    ComplexVector(const ComplexVector& s);
    // конструктор копіювання, який створює копію іншого вектора
    ComplexVector& operator=(const ComplexVector& s);
    // копіювати оператор присвоювання, який створює копію іншого вектора


    // 5 деструктор, який видаляє масив комплексних чисел
    ~ComplexVector() {
        cout << " del vec";
        if (v) delete[] v;//It also prints a message that the vector is being deleted.
    }


    void Output();
    void Output1();
    void Input();
    // метод встановлення елемента вектора за певним індексом
    void SetElement(int index, ComplexUnInt value);
    ComplexVector Add(ComplexVector& b);

    ComplexVector Subtraction(ComplexVector& b);
    ComplexUnInt GetElement(int index) const; // getter for a single element
    void ScalarMultiply(int scalar);

    bool Compare(const ComplexVector& other) const;

};
//2
ComplexVector::ComplexVector(int n) {//конструктор, який створює вектор розміром n;
    if (n <= 0) { v = NULL; num = 0; state = -1; cout << " Vec --> 0 "; }

    num = n;
    v = new ComplexUnInt[n];

    for (int i = 0; i < n; i++) {
        v[i] = 0.0;
    }
}
//3 n-це розмір вектора, b-значення, яке буде використано для ініціалізації всіх елементів вектора
ComplexVector::ComplexVector(int n, ComplexUnInt& b) {//конструктор, який створює вектор розміром n та ініціалізує його комплексним числом;
    if (n <= 0) { v = NULL; num = 0; state = -1; cout << " Vec --> 0 "; }
    num = n;
    v = new ComplexUnInt[n];
    for (int i = 0; i < n; i++) {
        v[i] = b;
    }
}

ComplexVector::ComplexVector(int n, ComplexUnInt* p) {// конструктор, який створює вектор розміром n та ініціалізує його масивом комплексних чисел;
    if (n <= 0 || p == NULL) { v = NULL; num = 0; state = -1; cout << " Vec --> 0 "; }
    //Цей рядок перевіряє, чи вхідні дані nменші або дорівнюють нулю. Якщо n менше або дорівнює нулю, конструктор встановлює покажчик v на NULL
    num = n;
    v = new ComplexUnInt[n];
    //  Цей рядок динамічно виділяє пам'ять для вектора v
    for (int i = 0; i < n; i++) {
        v[i] = p[i];
    }
}

// 4 конструктор копіювання, який створює копію іншого вектора.
ComplexVector::ComplexVector(const ComplexVector& s) {
    num = s.num;
    v = new ComplexUnInt[num];
    state = 0;
    for (int i = 0; i < num; i++) v[i] = s.v[i];
}

// 4 Оператор присвоєння
ComplexVector& ComplexVector::operator=(const ComplexVector& s) {
    if (num != s.num)
    {  //Якщо вони різні, функція видаляє старий вектор v і створює новий із відповідним розміром.
        //Потім він копіює кожен елемент з об’єкта, який призначається поточному об’єкту
        if (v) delete[] v;
        num = s.num;
        v = new ComplexUnInt[num];
        state = 0;
    }
    return *this;
}

// 6 
void ComplexVector::SetElement(int index, ComplexUnInt value) {
    if (index < 0 || index >= num) {
        throw std::out_of_range("Index out of bounds"); //Індекс поза межами
    }
    v[index] = value;
}

//7
ComplexUnInt ComplexVector::GetElement(int index) const {
    if (index < 0 || index >= num) {
        throw std::out_of_range("Invalid index");
    }
    return v[index];
}
void ComplexVector::Input() {

    if (num == 0) {
        if (v) delete[] v;
        do {
            cout << "Input size Vec\n";
            cin >> num;
        } while (num <= 0);
        v = new ComplexUnInt[num];
    }
    for (int i = 0; i < num; i++) {
        unsigned int RE;
        cout << " v [ " << i << " ] real img ";
        cin >> RE;
        v[i] = ComplexUnInt(RE);
    }
}

void ComplexVector::Output() {
    if (num != 0) {
        for (int i = 0; i < num; i++) {
            cout << " v [ " << i << " ] " << v[i].real() << '\t';
            cout << endl;
        }
    }
}
void ComplexVector::Output1() {
    if (num != 0) {
        for (int i = 0; i < num; i++) {
            cout << " v [ " << i << " ] " << v[i].real() << '\t';
            cout << endl;
        }
    }
}
ComplexVector ComplexVector::Add(ComplexVector& b) {
    int tnum;
    tnum = num < b.num ? num : b.num;
    /* Цей рядок оголошує цілочисельну змінну tnum та ініціалізує
         її мінімальною кількістю елементів між поточним вектором(num)
         і вхідним вектором(b.num).Оператор ? використовується для вибору мінімального значення.*/
    if (tnum >= 0) {
        ComplexVector tmp(tnum);
        for (int i = 0; i < tnum; i++) tmp.v[i] = v[i] + b.v[i];
        /* Цей рядок запускає цикл, який перебирає перші tnumелементи обох векторів
             і додає їх поелементно, зберігаючи результат у відповідному елементі вектора tmp.*/
        return tmp;
    }
    return ComplexVector(0);
}
ComplexVector ComplexVector::Subtraction(ComplexVector& b) {
    int tnum;
    tnum = num < b.num ? num : b.num;
    /* Цей рядок оголошує цілочисельну змінну tnumта ініціалізує
         її мінімальною кількістю елементів між поточним вектором(num)
         і вхідним вектором(b.num).Оператор ? використовується для вибору мінімального значення.*/
    if (tnum >= 0) {
        ComplexVector tmp(tnum);
        for (int i = 0; i < tnum; i++) tmp.v[i] = v[i] - b.v[i];
        /* Цей рядок запускає цикл, який перебирає перші tnumелементи обох векторів
             і додає їх поелементно, зберігаючи результат у відповідному елементі вектора tmp.*/
        return tmp;
    }
    return ComplexVector(0);
}
void ComplexVector::ScalarMultiply(int scalar) {
    for (int i = 0; i < num; i++) {
        v[i] *= scalar;
    }
}
//Проблема з ScalarMultiply функцією полягає в тому, що вхідним аргументом scalar є символ без знака, 
//максимальне значення якого дорівнює 255. Перемноження складної короткої змінної зі значенням, більшим за 255,
//призведе до переповнення, що може призвести до неочікуваних результатів.


bool ComplexVector::Compare(const ComplexVector& other) const {
    if (num != other.num) {
        return false;
    }
    for (int i = 0; i < num; i++) {
        if (v[i] != other.v[i]) {
            return false;
        }
    }
    return true;
}

void Task1_1() {

    system("cls");
    short a;
    unsigned int color;

    cout << "Enter a: ";
    cin >> a;

    cout << "Enter color: ";
    cin >> color;

    Square obj(a, color);//// Створює об'єкт паралелограм за допомогою введених користувачем даних
    obj.printInfo();
}
void Task1_2() {

    system("cls");
    double a, b, h;
    unsigned int color;

    a = rand() % 1000;
    color = rand() % 1000;
    cout << "a=" << a << endl;
    cout << "color=" << color << endl;


    Square obj(a, color);//// Створює об'єкт паралелограм за допомогою введених користувачем даних
    obj.printInfo();
}
void readfile() {
    short a;

    unsigned int color;
    ifstream readfile("NewFile.txt");
    readfile >> a >> color;
}
//Передбачити введення початкових даних : з файлу
void Task1_3()
{
    system("cls");
    ofstream fout1;
    fout1.open("NewFile.txt");


    short a;

    unsigned int color;
    cout << "Enter size" << endl;

    cout << "Enter a: ";
    cin >> a;



    fout1 << "a: " << a << endl;
    cout << "Enter color: ";

    cin >> color;
    fout1 << "color: " << color << endl;
    fout1.close();

    readfile();


    Square obj(a, color);//// Створює об'єкт паралелограм за допомогою введених користувачем даних
    obj.printInfo();

}

void Task2_1() {
    system("cls");

    setlocale(LC_CTYPE, "ukr");
    int size;
    std::cout << "Enter the size of 1 the vector: ";
    std::cin >> size;

    // create a vector of the given size
    ComplexVector v1(size);

    std::cout << "Enter the elements of the vector:" << std::endl;
    for (int i = 0; i < size; i++) {
        unsigned int real_part;
        std::cout << "Enter real and imaginary parts of element " << i + 1 << ": ";
        std::cin >> real_part;
        ComplexUnInt c(real_part);
        v1.SetElement(i, c);
    }
    int size1;
    std::cout << "Enter the size of 2 the vector: ";
    std::cin >> size1;
    ComplexVector v2(size1);


    std::cout << "Enter the elements of the vector:" << std::endl;
    for (int i = 0; i < size1; i++) {
        unsigned int real_part1;
        std::cout << "Enter real and imaginary parts of element " << i + 1 << ": ";
        std::cin >> real_part1;
        ComplexUnInt c(real_part1);
        v2.SetElement(i, c);
    }
    // output the vectors
    std::cout << "v1:" << std::endl;
    v1.Output();
    std::cout << "v2:" << std::endl;
    v2.Output();

    // add the vectors
    ComplexVector v3 = v1.Add(v2);

    // output the result
    std::cout << "v1 + v2 = v3:" << std::endl;
    v3.Output();

    ComplexVector v4 = v1.Subtraction(v2);
    // output the result
    std::cout << "v1 - v2 = v4:" << std::endl;
    v4.Output();
    cout << "Введiть число для множення" << endl;
    int scalar;
    cin >> scalar;

    cout << "Результат множення" << endl;
    v1.ScalarMultiply(scalar);
    cout << "Перший вектор:" << endl;
    v1.Output();
    v2.ScalarMultiply(scalar);
    cout << "Другий вектор" << endl;
    v2.Output();
    cout << "Comparing the first and second vectors: \n";
    if (v1.Compare(v2)) {
        std::cout << "The vectors are equal." << std::endl;
    }
    else {
        std::cout << "The vectors are not equal." << std::endl;
    }
}
void Task2_2() {
    system("cls");

    setlocale(LC_CTYPE, "ukr");
    int size = rand() % 10;
    cout << "The size of 1 the vector: " << size << endl;

    // create a vector of the given size
    ComplexVector v1(size);

    cout << "Enter the elements of the vector:" << std::endl;
    for (int i = 0; i < size; i++) {
        unsigned int real_part = rand() % 100;
        std::cout << "Element " << i + 1 << ": " << real_part << endl;
        // std::cin >> real_part;
        ComplexUnInt c(real_part);
        v1.SetElement(i, c);
    }
    cout << endl;
    int size1 = rand() % 10;
    std::cout << "Enter the size of 2 the vector: " << size1 << endl;
    // std::cin >> size1;
    ComplexVector v2(size1);


    std::cout << "Enter the elements of the vector:" << std::endl;
    for (int i = 0; i < size1; i++) {
        short real_part1 = rand() % 100;
        std::cout << "Element " << i + 1 << ": " << real_part1 << endl;
        // std::cin >> real_part1;
        ComplexUnInt c(real_part1);
        v2.SetElement(i, c);
    }
    // output the vectors
    std::cout << "v1:" << std::endl;
    v1.Output();
    std::cout << "v2:" << std::endl;
    v2.Output();

    // add the vectors
    ComplexVector v3 = v1.Add(v2);

    // output the result
    std::cout << "v1 + v2 = v3:" << std::endl;
    v3.Output();

    ComplexVector v4 = v1.Subtraction(v2);
    // output the result
    std::cout << "v1 - v2 = v4:" << std::endl;
    v4.Output();
    cout << "Введiть число для множення" << endl;
    int scalar;
    cin >> scalar;

    cout << "Результат множення" << endl;
    v1.ScalarMultiply(scalar);
    cout << "Перший вектор:" << endl;
    v1.Output();
    v2.ScalarMultiply(scalar);
    cout << "Другий вектор" << endl;
    v2.Output();
    cout << "Comparing the first and second vectors: \n";
    if (v1.Compare(v2)) {
        std::cout << "The vectors are equal." << std::endl;
    }
    else {
        std::cout << "The vectors are not equal." << std::endl;
    }
}
void Task2_3() {
    system("cls");

    ofstream fout;
    fout.open("File.txt", fstream::in | fstream::out);
    setlocale(LC_CTYPE, "ukr");
    int size;
    std::cout << "Enter the size of 1 the vector: ";
    cin >> size;

    fout << "The size of 1 the vector: ";
    fout << size;

    // create a vector of the given size
    ComplexVector v1(size);
    fout << "\nv1:\n";
    std::cout << "Enter the elements of the vector:" << std::endl;
    for (int i = 0; i < size; i++) {
        unsigned int real_part;
        cout << "Enter real and imaginary parts of element " << i + 1 << ": ";
        cin >> real_part;
        fout << real_part << endl;


        ComplexUnInt c(real_part);
        v1.SetElement(i, c);
    }


    int size1;
    std::cout << "Enter the size of 2 the vector: ";
    std::cin >> size1;
    fout << "The size of 2 the vector: " << size1;

    ComplexVector v2(size1);

    fout << "\nv2:\n";

    std::cout << "Enter the elements of the vector:" << std::endl;
    for (int i = 0; i < size1; i++) {
        short real_part1;
        std::cout << "Enter real and imaginary parts of element " << i + 1 << ": ";
        std::cin >> real_part1;
        fout << real_part1 << endl;

        ComplexUnInt c(real_part1);
        v2.SetElement(i, c);
    }
    fout.close();
    ifstream readfile("File.txt");
    for (int i = 0; i < size; i++) {
        short real_part;

        readfile >> real_part;
    }
    for (int i = 0; i < size1; i++) {
        short real_part1;

        readfile >> real_part1;
    }
    // output the vectors
    std::cout << "v1:" << std::endl;
    v1.Output();
    std::cout << "v2:" << std::endl;
    v2.Output();

    // add the vectors
    ComplexVector v3 = v1.Add(v2);

    // output the result
    std::cout << "v1 + v2 = v3:" << std::endl;
    v3.Output();

    ComplexVector v4 = v1.Subtraction(v2);
    // output the result
    std::cout << "v1 - v2 = v4:" << std::endl;
    v4.Output();
    cout << "Введiть число для множення" << endl;
    int scalar;
    cin >> scalar;

    cout << "Результат множення" << endl;
    v1.ScalarMultiply(scalar);
    cout << "Перший вектор:" << endl;
    v1.Output();
    v2.ScalarMultiply(scalar);
    cout << "Другий вектор" << endl;
    v2.Output();
    cout << "Comparing the first and second vectors: \n";
    if (v1.Compare(v2)) {
        std::cout << "The vectors are equal." << std::endl;
    }
    else {
        std::cout << "The vectors are not equal." << std::endl;
    }
    fout.close();

}

void Read() {
    int n, m, val;
    ifstream readfile("Txt_File.txt");
    readfile >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            double value;
            readfile >> value;
        }
    }
}


void asd() {
    int a;
    cout << "1, 2 or 3" << endl; cin >> a;
    switch (a) {
    case 1:
        Task1_1();
        break;
    case 2:
        Task1_2();
        break;
    case 3:
        Task1_3();
        break;
    }

}
void bsd() {
    int a;
    cout << "1, 2 or 3" << endl; cin >> a;
    switch (a) {
    case 1:
        Task2_1();
        break;
    case 2:
        Task2_2();
        break;
    case 3:
        Task2_3();
        break;
    }
}

int main()
{
    int ch;
    cout << "Choose 1, 2 " << endl;
    cin >> ch;
    switch (ch) {
    case(1):
        system("cls");
        asd();
        break;
    case(2):
        system("cls");
        bsd();
        break;
    }
    return 0;
}