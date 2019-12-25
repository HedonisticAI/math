#include <iostream>
#include <fstream>

#define FILE_IN  "tests/test7.in"
#define FILE_OUT "tests/test7.out"

using namespace std;

int **mat;
int size_m;
int res = 0;
bool *used;
int mini = -1;
int **path;
/*јлгоритм просматривает все вершины v первой доли графа: v = 1
 n_1. ≈сли текуща€ вершина v уже насыщена текущим паросочетанием
 (т.е. уже выбрано какое-то смежное ей ребро), то эту вершину пропускаем.
 »наче Ч алгоритм пытаетс€ насытить эту вершину,
дл€ чего запускаетс€ поиск увеличивающей цепи, начинающейс€ с этой вершины.*/
void Mat_new()
{
    int a;
    ifstream stream_in(FILE_In);
    stream_in >> a;
    size_m=a;
    stream_in >> a;
    size_m+=a+2;
    mat = new int* [size_m];
    for(int i=0; i<size_m; i++)
    {
        mat[i] = new int [size_m];
        for (int j=0; j<size_m;j++)
            mat[i][j] = 0;
    }
}

void Mat_in ()
{
    ifstream stream_in(stream_in);

    int a, b, c;
    stream_in >> a >> b;

    for(int i=0; i<a; i++)
    {
        stream_in >> b;
        for(int j=0; j<b; j++)
        {
            stream_in >> c;
            mat[0][i+2] = 1;
            mat[i+2][c+2] = 1;
            mat[c+2][1] = 1;
        }
    }
}

void repeat(int versh)
{
    if (versh == 1)
        return;
    used[versh] = true;
    for (int i=0; i < size_m; i++)
    {
        if (mat[versh][i] && !used[i])
        {
            if (mini == -1)
                mini = mat[versh][i];
            else
                if (mini>mat[versh][i])
                    mini = mat[versh][i];
            path[versh][i] = 1;
            repeat (i);
            return;
        }
    }
    mini = -2;
}

void cut_path()
{
    for (int i=0; i<size_m; i++)
        for (int j=0; j<size_m; j++)
        {
            if (path[i][j])
            {
                mat[i][j] -= mini;
                mat[j][i] += mini;
                path[i][j] = 0;
            }
        }
}

int main()
{
    Mat_new();
    path = mat;
    Mat_new();
    Mat_in();

//    for (int i=0; i<size_m; i++)
//    {
//        for (int j=0; j<size_m;j++)
//            cout << mat[i][j];
//        cout << endl;
//    }

    used = new bool[size_m];

    while (1)
    {
        mini=-1;
        for (int i=0; i<size_m; i++)
            used[i]=false;
        repeat(0);
        cut_path();
        if (mini == -2)
            break;
        else
            res +=mini;
    }
    cout << res;

    int nado;
    ifstream stream_out(FILE_OUT);
    stream_out >> nado;

    cout << endl << "And needed: " << nado;

    return 0;
}
