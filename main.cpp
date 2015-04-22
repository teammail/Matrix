#include <iostream>
#include <locale>
#include <stdlib.h>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstddef>

using namespace std;

// Структура для хранения данных о матрице
struct Matrix{
    int** massRef = nullptr;
    int line, column;
    char name = ' '; // Обозначение матрицы
};

//Вывод двумерного массива(необходимо передать в функцию двумерный массив)
void massShow(Matrix &mass){
    if(mass.massRef){
        cout << "\t\tМатрица "<< mass.name <<" ["<<mass.line<<"]"<<"["<<mass.column<<"]" << endl;
        for(int i = 0; i<mass.line; ++i)
        {
            cout << "Строка "<<i << "\t";

            for(int n = 0; n < mass.column; ++n)
            {
                cout << mass.massRef[i][n] << "\t";
            }
            cout << endl;
        }
        cout << endl; // Отступ после матрицы
    }else printf("Матрицы %c не существует! \n", mass.name);
}

//Создание новой матрицы и заполнение её автоматически
void massCreateAuto(Matrix &mass){
    if(mass.massRef)
    {
        printf("Удаление старой матрицы %c ... \n", mass.name);
        for (int i = 0 ; i < mass.line; ++i)
        {
            delete mass.massRef[i];
        }
        delete mass.massRef;
    }
    cout << "Введите размер матрицы "<< mass.name <<" [строки][столбцы]" << endl;
    cout << "[строки] = ";
    cin >> mass.line;
    cout << "[столбцы] = ";
    cin >> mass.column;
    cout << "Будет выделено " << sizeof(int)*mass.line*mass.column << " байт оперативной памяти" << endl;
    srand(time(NULL));// Инициализируем генератор случайных чисел
    //Создаём матрицу а и заполняем случайными числами
    mass.massRef = new int*[mass.line];
    for (int i = 0 ; i < mass.line; ++i)
    {
        mass.massRef[i] = new int[mass.column]();
        for (int m = 0 ; m < mass.column; ++m) mass.massRef[i][m] = (rand() % 100);
    }
}

//Создание новой матрицы ввод из консоли
void massCreate(Matrix &mass){
    if(mass.massRef)
    {
        printf("Удаление старой матрицы %c ... \n", mass.name );
        for (int i = 0 ; i < mass.line; ++i)
        {
            delete mass.massRef[i];
        }
        delete mass.massRef;
    }

    printf("\nВведите размер матрицы %c [строки][столбцы] ",mass.name );
    printf("\n[строки] = ");
    while(!scanf("%i",&(mass.line)))
    {
        cout << "Введите число!" << endl;
        fflush(stdin);
        //scanf("%*c"); // Очистка для Linux
    }

    printf("\n[столбцы] = ");
    while(!scanf("%i",&(mass.column)))
    {
        cout << "Введите число!" << endl;
        fflush(stdin);
        //scanf("%*c"); // Очистка для Linux
    }

    mass.massRef = new int*[mass.line];
    for (int i = 0 ; i < mass.line; ++i)
    {
        mass.massRef[i] = new int[mass.column]();
        for (int m = 0 ; m < mass.column; ++m)
        {

            printf("Элемент %c [%i][%i] ",mass.name ,i,m);
            if(!scanf("%i",&(mass.massRef[i][m])))
            {
                cout << "Введите число!" << endl;
                m--;
            }
            fflush(stdin);
            //scanf("%*c"); // Очистка для Linux
        }

    }

}

//Сложение двух матриц
void massPlus(Matrix& massA,Matrix& massB,Matrix& massC){
    if(massA.massRef&&massB.massRef){
        if(massC.massRef)
        {
        printf("Удаление старой матрицы %c ... \n", 'C');
        for (int i = 0 ; i < massC.line; ++i)
            {
                delete massC.massRef[i];
            }
        delete massC.massRef;
        }

        // Зададим количество линий и колонок в результирующей матрице
        massC.line = (massA.line<massB.line)? massA.line:massB.line;
        massC.column = (massA.column<massB.column)? massA.column:massB.column;
        massC.massRef = new int*[massC.line];
        for (int i = 0 ; i < massC.line; ++i)
            {
                massC.massRef[i] = new int[massC.column]();
                for (int m = 0 ; m < massC.column; ++m) massC.massRef[i][m] = massA.massRef[i][m]+massB.massRef[i][m];
            }
    }else printf("Матриц для суммирования не существует! \n");
}

//Вычитание двух матриц
void massMinus(Matrix& massA,Matrix& massB,Matrix& massC){
    if(massA.massRef&&massB.massRef){
        if(massC.massRef)
        {
        printf("Удаление старой матрицы %c ... \n", 'C');
        for (int i = 0 ; i < massC.line; ++i)
            {
                delete massC.massRef[i];
            }
        delete massC.massRef;
        }

        // Зададим количество линий и колонок в результирующей матрице
        massC.line = (massA.line<massB.line)? massA.line:massB.line;
        massC.column = (massA.column<massB.column)? massA.column:massB.column;
        massC.massRef = new int*[massC.line];
        for (int i = 0 ; i < massC.line; ++i)
            {
                massC.massRef[i] = new int[massC.column]();
                for (int m = 0 ; m < massC.column; ++m) massC.massRef[i][m] = massA.massRef[i][m]-massB.massRef[i][m];
            }
    }else printf("Матриц для вычитания не существует! \n");
}

//Умножение двух матриц
void massProduct(Matrix& massA,Matrix& massB,Matrix& massC){
    if(massA.massRef&&massB.massRef){
        // Проверим, соответствует ли количество столбцов матрицы А
        // количеству строк матрицы В
        if(massA.column == massB.line){
        // Если это так, то проверим не создана ли матрица С
            if(massC.massRef)
            {// Если это верно, удалим её
            printf("Удаление старой матрицы %c ... \n", 'C');
            for (int i = 0 ; i < massC.line; ++i)
                {
                    delete massC.massRef[i];
                }
            delete massC.massRef;
            }

            // Зададим количество линий и колонок в результирующей матрице
            massC.line = massA.line;
            massC.column = massB.column;
            massC.massRef = new int*[massC.line];
            for (int i = 0 ; i < massC.line; ++i)
                {
                    massC.massRef[i] = new int[massC.column]();
                    for (int m = 0 ; m < massC.column; ++m){
                        int summ = 0;
                        for (int r = 0; r < massA.column; ++r) {
                            summ += massA.massRef[i][r]*massB.massRef[r][m];
                            massC.massRef[i][m] = summ;
                            }
                        }
                }
        }
    }else printf("Матриц для умножения не существует! \n");
}

//Вывести в консоль текст файла подсказки с командами
void help(){
    ifstream in(".//help.txt");
    string s;
    while(!in.eof())
    {
        getline(in,s);
        cout << s << endl;
    }
    cout << endl;
    in.close();
}
// TODO : функции сложения, вычитания, умножения, деления матриц
// ф-я создания квадратной матрицы, получения транспонированной матрицы из заданной, сортировка элементов матрицы

int main(){
    setlocale(LC_ALL,"Russian");
    string command = ""; // Команда для управления программой
    Matrix a;// Матрица а
    a.name = 'A';
    Matrix b;// Матрица б
    b.name = 'B';
    Matrix c;// Матрица c
    c.name = 'C';
    help(); // Вывести в консоль текст файла подсказки с командами
    // Тело программы
    while(command != "exit")
    {
        printf("Введите команду: ");
        cin >> command;

        if(command == "new")
        {
            massCreate(a);
            massCreate(b);
            massShow(a);
            massShow(b);
        }
        if(command == "newA")
        {
            massCreate(a);
            massShow(a);
        }
        if(command == "newB")
        {
            massCreate(b);
            massShow(b);
        }
        if(command == "newauto")
        {
            massCreateAuto(a);
            massCreateAuto(b);
            massShow(a);
            massShow(b);
        }
        if(command == "newAauto")
        {
            massCreateAuto(a);
            massShow(a);
        }
        if(command == "newBauto")
        {
            massCreateAuto(a);
            massShow(b);
        }
        if(command == "show")
        {
            massShow(a);
            massShow(b);
            massShow(c);
        }
        if(command == "showA")
        {
            massShow(a);
        }
        if(command == "showB")
        {
            massShow(b);
        }
        if(command == "showC")
        {
            massShow(c);
        }
        if(command == "help")
        {
            printf("\n***************************\n");
            help();
        }
        if(command == "plus")
        {
            massPlus(a,b,c);
            massShow(c);
        }
        if(command == "minus")
        {
            massMinus(a,b,c);
            massShow(c);
        }
        if(command == "product")
        {
            massProduct(a,b,c);
            massShow(c);
        }
    }


    return 0;
}
