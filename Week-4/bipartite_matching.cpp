#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

void display(vector<vector<int>> matrix);
void display(vector<int> matrix);
vector<vector<int>> ford_fulkerson(vector<vector<int>> G, int s, int t);
vector<vector<int>> residual(vector<vector<int>> G, vector<vector<int>> F);
bool find_path(vector<vector<int>> G, int s, int t, vector<int> &path);
vector<vector<int>> augment_flow(vector<vector<int>> F, vector<vector<int>> G, vector<int> P, int s, int t);


int main()
{
    //input
    int m,n;
    cin >> n;//people
    cin >> m;//jobs
    vector<vector<int>>  graph(n,vector<int>(m,0));
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            int m1;
            cin >> m1;
            graph[i][m1-1]=1;
        }
    }

    //convert into graph for max-flow
    vector<vector<int>>  G(n+m+2,vector<int>(n+m+2,0));
    for (int i = 0; i < n+m+2; i++)
    {
        for (int j = 0; j < n+m+2; j++)
        {
            if(i==0 && j>=2 && j<=n+1)//s->P[j]
            {
                G[i][j]=1;
            }
            if(j==1 && i>=n+2)//J[i]->t
            {
                G[i][j]=1;
            }
            if(i>=2 && i<=n+1 && j>=n+2 && graph[i-2][j-n-2]==1)//P[i]->J[j]
            {
                G[i][j]=1;
            }
        }
    }

    //ford-fulkerson algorithm
    vector<vector<int>> max_flow=ford_fulkerson(G,0,1);
    int sum=0;
    for (int i = 0; i < m+n+2; i++)
    {
        sum+=max_flow[0][i];
    }
    if(sum<m)
    {
        cout<<-1;
        return 0;
    }
    for (int i = 2; i <= n+1; i++)
    {
        cout << i-1 << " ";
        bool flag=false;
        for (int j = n+2; j < m+n+2; j++)
        {
            if(max_flow[i][j]==1)
            {
                cout << j-n-1 << "\n";
                flag=true;
            }
        }
        if(!flag)
        {
            cout << "NO JOB\n";
        }
    }
    
}

vector<vector<int>> ford_fulkerson(vector<vector<int>> G, int s, int t)
{
    vector<vector<int>>  F(G.size(),vector<int>(G.size(),0));
    vector<int> path(G.size(),0);
    while (find_path(residual(G,F),0,1,path))
    {
        F=augment_flow(F,G,path,0,1);
        G=residual(G,F);
    }
    return F;
}

vector<vector<int>> augment_flow(vector<vector<int>> F, vector<vector<int>> G, vector<int> P, int s, int t)
{
    vector<vector<int>> Gf=residual(G,F);
    int i=t;
    int min_cap=Gf[P[i]][i];
    while(i!=s)
    {
        int curr_cap=Gf[P[i]][i];
        if(curr_cap < min_cap)
        {
            min_cap=curr_cap;
        }
        i=P[i];
    }
    i=t;
    while(i!=s)
    {
        if(G[P[i]][i]>0)
        {
            F[P[i]][i]+=min_cap;
        }
        else
        {
            F[P[i]][i]-=min_cap;
        }
        i=P[i];
    }
    return F;
}

bool find_path(vector<vector<int>> G, int s, int t, vector<int> &path)
{
    queue<int> q;
    //vector<int> parent(G.size(),0);
    vector<int> visited(G.size(),0);
    bool flag=false;
    visited[s]=1;
    q.push(s);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        if(v==t)
        {
            flag=true;
            break;
        }
        for (int i = 0; i < G.size(); i++)
        {
            if(G[v][i]>0 && visited[i]==0)
            {
                visited[i]=1;
                q.push(i);
                path[i]=v;
            }
        }
    }
    return flag;
}

vector<vector<int>> residual(vector<vector<int>> G, vector<vector<int>> F)
{
    int size=G.size();
    vector<vector<int>>  res(size,vector<int>(size,0));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(G[i][j]!=0)
            {
                res[i][j]=G[i][j]-F[i][j];
                res[j][i]=F[i][j];
            }
        }
    }
    return res;
}

void display(vector<vector<int>> matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void display(vector<int> matrix)
{
    int rows = matrix.size();
    for (int i = 0; i < rows; ++i) {
        cout << matrix[i] << " ";
    }
    cout << "\n";
}