#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

#define FILE_IN "test2.in"
#define FILE_OUT "test2.out"
//используется алгоритм ФФ
int main (int argc, char** argv)
{
    ifstream file_in(FILE_IN);
	int from =0;
	int to = 1;
	int v_count;

	file_in >> v_count ;
	int m_steps[v_count][v_count];
	int path[v_count];
	for (int i=0; i<v_count; i++)
        path[i] = 0;
	bool used[v_count];

	for (int i=0; i<v_count; ++i)
        used[i]=false;

	for (int i=0; i<v_count; ++i)
	{
	    for (int j=0; j<v_count; j++)
		{
		    int a;
            file_in >> a;
            m_steps[i][j] = a;
		}
	}

	queue<int> q;
	q.push(from);

	while (!q.empty())
	{
		int now;
		now = q.front();
		q.pop();
		for (int i=0; i<v_count; ++i)
        {
            if (m_steps[now][i] && !used[i])
            {
                if (path[i] < (path[now]+m_steps[now][i]))
                    path[i]=path[now]+m_steps[now][i];
                q.push(i);
            }
        }
        used[now] = true;
	}

	cout << path[to] << endl;
	cout << "Need : ";
	ifstream file_out(FILE_OUT);
	int qw;
	file_out >> qw;
	cout << qw;

	return 0;
}
