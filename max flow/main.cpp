#include <iostream>
#include <fstream>

#define FILE_IN  "tests/test2.in"
#define FILE_OUT "tests/test2.out"

using namespace std;

int **mat;
int size_m;
int res = 0;
bool *used;
int mini = -1;
int **way;
int a, b;

void Mat_new()
{
    ifstream file_in(FILE_IN);
    file_in >> size_m;
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
    ifstream file_in(FILE_IN);
    int a;
    file_in >> size_m;
    for(int i=0; i<size_m; i++)
    {
        for(int j=0; j<size_m; j++)
        {
            file_in >> a;
            mat[i][j] = a;
        }
    }
}

void recur(int versh)
{
    if (versh == 1)
        return;
    used[versh] = true;
    for (int i=0; i < size_m; i++)
    {
        if (mat[versh][i] && !used[i])
        {
            if (mini == -1)
            {
                mini = mat[versh][i];
                a = versh;
                b = i;
            }
            else
                if (mini>mat[versh][i])
                {
                    mini = mat[versh][i];
                    a = versh;
                    b = i;
                }
            way[versh][i] = 1;
            recur (i);
            return;
        }
    }
    mini = -2;
}

void cut_way()
{
    mat[a][b] = 0;
    for (int i=0; i<size_m; i++)
        for (int j=0; j<size_m; j++)
        {
            if (way[i][j])
            {
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
        {
            if (res < mini)
                res = mini;
        }
    }
    cout << res;

    int need;
    ifstream stream(FILE_OUT);
    stream >> need;

    cout << endl << "And needed: " << need;


}
