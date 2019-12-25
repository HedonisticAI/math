#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

/// ƒл€ написани€ программы использован алгоритм ѕрима

/// ¬вод графа из файла:
///    - кол-во вершин
///    - рассто€ни€ между вершинами: 2 вершины и число
/// ѕо второму составл€етс€ матрица смежности. ¬ыбираетс€ перва€ вершина и сравниваютс€ рассто€ни€ между ней и всеми
/// св€занными с ней вершинами. »з всех выбираетс€ наименьша€ и добавл€етс€ в булевский массив пройденных вершин.
/// —ледующа€ вершина выбираетс€ по принципу:
///    - если кол-во тронутых вершин не равно кол-ву вершин
///    - постановка всех пройденных вершин в очередь
///    - дл€ каждой вершины:
///        - проверка, есть ли у неЄ нетронутые соседи
///        - если есть - выбор самой маленькой дороги, сравнение с уже существующей самой маленькой дорогой и, если
///        нова€ меньше, замена еЄ и вершины.
///    - добавление новой вершины к уже тронутым и занесение рассто€ни€ до неЄ в новую матрицу смежности
/// Ќа выходе - матрица смежности оставного дерева.

#define INT_MAX 2147483647

int q_size(queue<int> *q)
{
    int res = 0;
    while (!q->empty())
    {
        res++;
        q->pop();
    }
    return res;
}

int main()
{
    // »нициализаци€ переменных и потоков
    ifstream file("test.txt");
    int top_num;
    file >> top_num;

    int matr[top_num][top_num];
    int result[top_num][top_num];
    bool used [top_num];

    //ќчистка мусора
    for (int i=0; i < top_num; i++)
        used[i] = false;

    for (int i=0; i<top_num; i++)
        for (int j=0; j<top_num; j++)
        {
            matr[i][j] = -1;
            result[i][j] = 0;
        }

    //—оздание матрицы смежности
    while (file)
    {
        int a, b;
        file >> a;
        file >> b;
        file >> matr[a][b];
        matr [b][a] = matr[a][b];
    }

    queue <int> q;
    used[0] = true;
    q.push(0);
    //ќсновной ход программы
    while (q_size(&q) < top_num)
    {
        for (int i=0; i<top_num; i++)
            if (true == used[i]) q.push(i);

        int min_way = INT_MAX;
        int min_top;
        int from_top;

        while (!q.empty())
        {
            int now = q.front();
            q.pop();
            for (int i=0; i<top_num; i++)
            {
                if ((min_way > matr[now][i]) && (!used[i]) && (-1 != matr[now][i]))  {
                    min_way = matr[now][i];
                    min_top = i;
                    from_top = now;
                }
            }
        }
        used[min_top] = true;
        result[min_top][from_top] = min_way;
        result[from_top][min_top] = min_way;

        for (int i=0; i<top_num; i++)
            if (true == used[i]) q.push(i);
    }

    // онечный вывод
    for (int i=0; i<top_num; i++)
    {
        for (int j=0; j<top_num; j++)
            cout << result[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
