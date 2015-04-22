#include <iostream>
#include <locale>
#include <stdlib.h>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstddef>

using namespace std;

// ��������� ��� �������� ������ � �������
struct Matrix{
    int** massRef = nullptr;
    int line, column;
    char name = ' '; // ����������� �������
};

//����� ���������� �������(���������� �������� � ������� ��������� ������)
void massShow(Matrix &mass){
    if(mass.massRef){
        cout << "\t\t������� "<< mass.name <<" ["<<mass.line<<"]"<<"["<<mass.column<<"]" << endl;
        for(int i = 0; i<mass.line; ++i)
        {
            cout << "������ "<<i << "\t";

            for(int n = 0; n < mass.column; ++n)
            {
                cout << mass.massRef[i][n] << "\t";
            }
            cout << endl;
        }
        cout << endl; // ������ ����� �������
    }else printf("������� %c �� ����������! \n", mass.name);
}

//�������� ����� ������� � ���������� � �������������
void massCreateAuto(Matrix &mass){
    if(mass.massRef)
    {
        printf("�������� ������ ������� %c ... \n", mass.name);
        for (int i = 0 ; i < mass.line; ++i)
        {
            delete mass.massRef[i];
        }
        delete mass.massRef;
    }
    cout << "������� ������ ������� "<< mass.name <<" [������][�������]" << endl;
    cout << "[������] = ";
    cin >> mass.line;
    cout << "[�������] = ";
    cin >> mass.column;
    cout << "����� �������� " << sizeof(int)*mass.line*mass.column << " ���� ����������� ������" << endl;
    srand(time(NULL));// �������������� ��������� ��������� �����
    //������ ������� � � ��������� ���������� �������
    mass.massRef = new int*[mass.line];
    for (int i = 0 ; i < mass.line; ++i)
    {
        mass.massRef[i] = new int[mass.column]();
        for (int m = 0 ; m < mass.column; ++m) mass.massRef[i][m] = (rand() % 100);
    }
}

//�������� ����� ������� ���� �� �������
void massCreate(Matrix &mass){
    if(mass.massRef)
    {
        printf("�������� ������ ������� %c ... \n", mass.name );
        for (int i = 0 ; i < mass.line; ++i)
        {
            delete mass.massRef[i];
        }
        delete mass.massRef;
    }

    printf("\n������� ������ ������� %c [������][�������] ",mass.name );
    printf("\n[������] = ");
    while(!scanf("%i",&(mass.line)))
    {
        cout << "������� �����!" << endl;
        fflush(stdin);
        //scanf("%*c"); // ������� ��� Linux
    }

    printf("\n[�������] = ");
    while(!scanf("%i",&(mass.column)))
    {
        cout << "������� �����!" << endl;
        fflush(stdin);
        //scanf("%*c"); // ������� ��� Linux
    }

    mass.massRef = new int*[mass.line];
    for (int i = 0 ; i < mass.line; ++i)
    {
        mass.massRef[i] = new int[mass.column]();
        for (int m = 0 ; m < mass.column; ++m)
        {

            printf("������� %c [%i][%i] ",mass.name ,i,m);
            if(!scanf("%i",&(mass.massRef[i][m])))
            {
                cout << "������� �����!" << endl;
                m--;
            }
            fflush(stdin);
            //scanf("%*c"); // ������� ��� Linux
        }

    }

}

//�������� ���� ������
void massPlus(Matrix& massA,Matrix& massB,Matrix& massC){
    if(massA.massRef&&massB.massRef){
        if(massC.massRef)
        {
        printf("�������� ������ ������� %c ... \n", 'C');
        for (int i = 0 ; i < massC.line; ++i)
            {
                delete massC.massRef[i];
            }
        delete massC.massRef;
        }

        // ������� ���������� ����� � ������� � �������������� �������
        massC.line = (massA.line<massB.line)? massA.line:massB.line;
        massC.column = (massA.column<massB.column)? massA.column:massB.column;
        massC.massRef = new int*[massC.line];
        for (int i = 0 ; i < massC.line; ++i)
            {
                massC.massRef[i] = new int[massC.column]();
                for (int m = 0 ; m < massC.column; ++m) massC.massRef[i][m] = massA.massRef[i][m]+massB.massRef[i][m];
            }
    }else printf("������ ��� ������������ �� ����������! \n");
}

//��������� ���� ������
void massMinus(Matrix& massA,Matrix& massB,Matrix& massC){
    if(massA.massRef&&massB.massRef){
        if(massC.massRef)
        {
        printf("�������� ������ ������� %c ... \n", 'C');
        for (int i = 0 ; i < massC.line; ++i)
            {
                delete massC.massRef[i];
            }
        delete massC.massRef;
        }

        // ������� ���������� ����� � ������� � �������������� �������
        massC.line = (massA.line<massB.line)? massA.line:massB.line;
        massC.column = (massA.column<massB.column)? massA.column:massB.column;
        massC.massRef = new int*[massC.line];
        for (int i = 0 ; i < massC.line; ++i)
            {
                massC.massRef[i] = new int[massC.column]();
                for (int m = 0 ; m < massC.column; ++m) massC.massRef[i][m] = massA.massRef[i][m]-massB.massRef[i][m];
            }
    }else printf("������ ��� ��������� �� ����������! \n");
}

//��������� ���� ������
void massProduct(Matrix& massA,Matrix& massB,Matrix& massC){
    if(massA.massRef&&massB.massRef){
        // ��������, ������������� �� ���������� �������� ������� �
        // ���������� ����� ������� �
        if(massA.column == massB.line){
        // ���� ��� ���, �� �������� �� ������� �� ������� �
            if(massC.massRef)
            {// ���� ��� �����, ������ �
            printf("�������� ������ ������� %c ... \n", 'C');
            for (int i = 0 ; i < massC.line; ++i)
                {
                    delete massC.massRef[i];
                }
            delete massC.massRef;
            }

            // ������� ���������� ����� � ������� � �������������� �������
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
    }else printf("������ ��� ��������� �� ����������! \n");
}

//������� � ������� ����� ����� ��������� � ���������
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
// TODO : ������� ��������, ���������, ���������, ������� ������
// �-� �������� ���������� �������, ��������� ����������������� ������� �� ��������, ���������� ��������� �������

int main(){
    setlocale(LC_ALL,"Russian");
    string command = ""; // ������� ��� ���������� ����������
    Matrix a;// ������� �
    a.name = 'A';
    Matrix b;// ������� �
    b.name = 'B';
    Matrix c;// ������� c
    c.name = 'C';
    help(); // ������� � ������� ����� ����� ��������� � ���������
    // ���� ���������
    while(command != "exit")
    {
        printf("������� �������: ");
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
