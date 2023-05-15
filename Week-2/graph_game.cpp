#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int P1_P2_dyn(vector<vector<int>> arr, int m, int n);

int P1_P2_dyn(vector<vector<int>> arr, int m, int n)
{
    vector<vector<int>> move(2*m,vector<int>(n));
    for (int j = 0; j < n; j++)
    {
        move[2*m-1][j]=*max_element(arr[j].begin(),arr[j].end());
    }
    for (int i = 2*m-2; i >= 0; i--)
    {
        
        for (int j = 0; j < n; j++)
        {
            int max;
            for (int k = 0; k < n; k++)
            {
                if(k==j){continue;}
                max = arr[j][k]-move[i+1][k];
                break;
            }
            for (int k = 0; k < n; k++)
            {
                if(k==j){continue;}
                int nmax = arr[j][k]-move[i+1][k];
                if (nmax>max)
                {
                    max=nmax;
                }
            }
            move[i][j]=max;
        }
    }
    return move[0][0] > 0 ? 1 : 2;
}

int main()
{
    int m,n;
    cin >> n;
    cin >> m;
    vector<vector<int>> arr;
    for (int i = 0; i < n; i++)
    {
        vector<int> temp;
        for (int j = 0; j < n; j++)
        {
            int t=-1;
            if(i!=j)
            {
                cin >> t;
            }
            temp.push_back(t);
        }
        arr.push_back(temp);
    }
    cout << P1_P2_dyn(arr,m,n);
}