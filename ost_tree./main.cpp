#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

/// ��� ��������� ��������� ����������� �������� �����

/// ���� ����� �� �����:
///    - ���-�� ������
///    - ���������� ����� ���������: 2 ������� � �����
/// �� ������� ������������ ������� ���������. ���������� ������ ������� � ������������ ���������� ����� ��� � �����
/// ���������� � ��� ���������. �� ���� ���������� ���������� � ����������� � ��������� ������ ���������� ������.
/// ��������� ������� ���������� �� ��������:
///    - ���� ���-�� �������� ������ �� ����� ���-�� ������
///    - ���������� ���� ���������� ������ � �������
///    - ��� ������ �������:
///        - ��������, ���� �� � �� ���������� ������
///        - ���� ���� - ����� ����� ��������� ������, ��������� � ��� ������������ ����� ��������� ������� �, ����
///        ����� ������, ������ � � �������.
///    - ���������� ����� ������� � ��� �������� � ��������� ���������� �� �� � ����� ������� ���������
/// �� ������ - ������� ��������� ��������� ������.

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
    // ������������� ���������� � �������
    ifstream file("test.txt");
    int top_num;
    file >> top_num;

    int matr[top_num][top_num];
    int result[top_num][top_num];
    bool used [top_num];

    //������� ������
    for (int i=0; i < top_num; i++)
        used[i] = false;

    for (int i=0; i<top_num; i++)
        for (int j=0; j<top_num; j++)
        {
            matr[i][j] = -1;
            result[i][j] = 0;
        }

    //�������� ������� ���������
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
    //�������� ��� ���������
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

    //�������� �����
    for (int i=0; i<top_num; i++)
    {
        for (int j=0; j<top_num; j++)
            cout << result[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
