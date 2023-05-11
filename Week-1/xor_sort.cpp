#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void SWAP_res(int i, int j);

vector<pair<int,int>> result;
vector<int> a;
int n;

int main()
{
    int t;
    cin>>t;
    while(t-->0)
    {
        cin >> n;
        result.clear();
        a.assign(n,0);

        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        vector<pair<int,int>> arr(n);
        for (int i = 0; i < n; i++)
        {
            arr[i]={a[i],i};
        }
        sort(arr.begin(),arr.end());

        vector<int> curr(n);
        vector<int> pos(n);
        for (int i = 0; i < n; i++)
        {
            pos[i]=i;
            curr[i]=i;
        }
        for (int i = 0; i < n; i++)
        {
            int idx=arr[i].second;
            if(pos[idx]==i)
            {
                continue;
            }
            int from = pos[idx];
            SWAP_res(from,i);
            pos[idx]=i;
            pos[curr[i]]=from;
            swap(curr[i],curr[from]);
            swap(a[i],a[from]);
        }
        cout << result.size()<<"\n";
        for (int i = 0; i < result.size(); i++)
        {
            cout<<result[i].first<<" "<<result[i].second<<"\n";
        }
    }
}

void SWAP_res(int i, int j)
{
    result.push_back({i+1,j+1});
    result.push_back({j+1,i+1});
    result.push_back({i+1,j+1});
}