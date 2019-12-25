#include <iostream>
#include <fstream>

#define FILE_IN  "tests/test1.in"
#define FILE_OUT "tests/test1.out"

using namespace std;

int **mat;
int size_m;
int res = 0;
bool *used;
int mini = -1;
int **path;
int a, b;

void Mat_new()
{
    ifstream file_in(FILE_IN);
    int n, m;
    file_in >> n;
    file_in >> m;
    size_m = m+n+2;
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
    int a, n, m;
    file_in >> n;
    file_in >> m;
    for (int i=2; i<size_m; i++)
    {
        for (int j=2; j<size_m; j++)
        {
            mat[i][j] = 999;
        }
    }
    for (int i=0; i<n; i++)
    {
        file_in >> a;
        mat[0][i+2] = a;
    }
    for (int i=0; i<m; i++)
    {
        file_in >> a;
        mat[i+n+2][1] = a;
    }
    for (int i=0; i<size_m; i++)
    {
        for (int j=0; j<size_m; j++)
            cout << mat[i][j] << " ";
        cout << endl;
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
            path[versh][i] = 1;
            recur (i);
            return;
        }
    }
    mini = -2;
}

void cut_path()
{
    mat[a][b] = 0;
    for (int i=0; i<size_m; i++)
        for (int j=0; j<size_m; j++)
        {
            if (path[i][j])
            {
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

    used = new bool[size_m];

    while (1)
    {
        mini=-1;
        for (int i=0; i<size_m; i++)
            used[i]=false;
        recur(0);
        cut_path();
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
