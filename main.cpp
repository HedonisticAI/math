#include <iostream>
#include <fstream>

#define FILE_IN  "tests/test4.in"
#define FILE_OUT "tests/test4.out"

using namespace std;

int **mat;
int size_n;
int size_m;
int res = 0;
bool *used;
int mini = -1;
int **way;

void Mat_new()
{
    ifstream file_in(FILE_IN);
    file_in >> size_n;
    file_in >> size_m;
    mat = new int* [size_m+size_n+2];
    for(int i=0; i<(size_m+size_n+2); i++)
    {
        mat[i] = new int [size_m+size_n+2];
        for (int j=0; j<size_m+size_n+2;j++)
            mat[i][j] = 0;
    }
}

void Mat_in ()
{
    ifstream file_in(FILE_IN);
    int a;
    file_in >> size_n;
    file_in >> size_m;
    for(int i=2; i<size_n+2; i++)
    {
        int q;
        mat[0][i] = 1;
        file_in >> q;
        for(int j=0; j<q; j++)
        {
            file_in >> a;
//            mat[i][a+size_n+1] = 1;
//            mat[a+size_n+1][1] = 1;
//            mat[1][a+size_n+1] = 1;
//            mat[a+size_n+1][i] = 1;
        }
    }
//    for (int i=size_n; i < size_m+size_n; i++)
//    {
//        mat[1][i] = 1;
//    }
}

void recur(int versh)
{
    if (versh == 1)
        return;
    used[versh] = true;
    for (int i=0; i < size_m+size_n+2; i++)
    {
        if (mat[versh][i] && !used[i])
        {
            if (mini == -1)
                mini = mat[versh][i];
            else
                if (mini>mat[versh][i])
                    mini = mat[versh][i];
            way[versh][i] = 1;
            recur (i);
            return;
        }
    }
    mini = -2;
}

void cut_way()
{
    for (int i=0; i<size_m; i++)
        for (int j=0; j<size_m; j++)
        {
            if (way[i][j])
            {
                mat[i][j] -= mini;
                mat[j][i] += mini;
                way[i][j] = 0;
            }
        }
}

int main()
{
    Mat_new();
    way = mat;
    Mat_new();
    Mat_in();

    used = new bool[size_m];

    while (1)
    {
        mini=-1;
        for (int i=0; i<size_m; i++)
            used[i]=false;
        recur(0);
        cut_way();
        if (mini == -2)
            break;
        else
            res +=mini;
    }
    cout << res;

    int nado;
    ifstream potochek(FILE_OUT);
    potochek >> nado;

    cout << endl << "And needed : " << nado;


}
