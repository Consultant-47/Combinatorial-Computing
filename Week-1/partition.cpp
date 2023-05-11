 #include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int pow(int a, int b);
int fact(int n);
vector <int> bin(int n);
bool comp(vector<vector<int>> P, vector<vector<int>> Q);//P<Q
vector< vector <int>> eval(vector<int> bin, vector<int> N);
void display(vector<int> vec);
void display(vector<vector<int>> vec);
void display(vector<vector<vector<int>>> vec);
bool is_valid(vector<vector<int>> in, vector<vector<vector <int>>> part);

bool comp(vector<vector<int>> P, vector<vector<int>> Q)//Problem!!!!
{
    if(P.at(0).size()<Q.at(0).size())
    {
        return true;
    }
    else if(P.at(0).size()==Q.at(0).size())
    {
        for (int i = 0; i < P.at(0).size(); i++)
        {
            if(P.at(0).at(i)>Q.at(0).at(i))
            {
                break;
            }
            if(P.at(0).at(i)<Q.at(0).at(i))
            {
                return true;
            }
        }
    }
    if(P.at(0) == Q.at(0))
    {
        vector<vector<int>> P_P1;
        vector<vector<int>> Q_Q1;
        for (int i = 1; i < P.size(); i++)
        {
            P_P1.push_back(P.at(i));
        }
        for (int i = 1; i < Q.size(); i++)
        {
            Q_Q1.push_back(Q.at(i));
        }
        return comp(P_P1,Q_Q1);
    }
    return false;
}

bool is_valid(vector<vector<int>> in, vector<vector<vector <int>>> part)
{
    //not repeat
    //min(Pi)<min(Pj) for all i<j
    for (int i = 0; i < in.size(); i++)
    {
        for (int j = i+1; j < in.size(); j++)
        {
            if(*min_element(in.at(i).begin(), in.at(i).end()) > *min_element(in.at(j).begin(), in.at(j).end()))
            {
                return false;
            }
        }
        
    }
    //display(part);
    for (int i = 0; i < part.size(); i++)
    {
        //compare part.at(i) with in
        if(in == part.at(i) && in.size()==part.at(i).size())
        {
            bool flag = false;
            for (int k = 0; k < in.size(); k++)
            {
                if(in.at(k).size()!=part.at(i).at(k).size())
                {
                    flag = true;
                }
            }
            if(flag)
            {
                continue;
            }
            //cout << "Boom equal!\n";
            //display(in);
            //display(part.at(i));
            //cout <<"\n\n";
            return false;
        }
    }
    
    return true;
}

void display(vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec.at(i) << " ";
    }
    cout << "\n";
    
}

void display(vector<vector<int>> vec)
{
    
    for (int k = 0; k < vec.size(); k++)
    {
        for (int l = 0; l < vec.at(k).size(); l++)
        {
            cout << vec.at(k).at(l) << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void display(vector<vector<vector<int>>> vec)
{
    
    for (int k = 0; k < vec.size(); k++)
    {
        for (int l = 0; l < vec.at(k).size(); l++)
        {
            for (int m = 0; m < vec.at(k).at(l).size(); m++)
            {
                cout << vec.at(k).at(l).at(m) << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    cout << "\n";
}

vector< vector <int>> eval(vector<int> bin, vector<int> N)
{
    int ctr=0;
    vector< vector <int>> ret;
    vector<int> temp;
    for (int i = 0; i < N.size(); i++)
    {
        if(i>0 && bin.at(i-1)==1)
        {
            ret.push_back(temp);
            sort(ret.at(ctr).begin(),ret.at(ctr).end());
            ctr++;
            temp.clear();
        }
        temp.push_back(N.at(i));
    }
    ret.push_back(temp);
    sort(ret.at(ctr).begin(),ret.at(ctr).end());
    return ret;
}

int fact(int n)
{
    return n==0 ? 1 : n*fact(n-1);
}

int pow(int a, int b)
{
    return b==0 ? 1 : a*pow(a,b-1);
}

vector<int> bin(int n, int i, vector<int> pre)
{
    if(n==0)
    {
        return pre;
    }
    pre.at(i)=n%2;
    pre=bin(n/2, i+1, pre);
    return pre;
}

int main() {
    int N=0,k=0;
    cin >> N;
    cin >> k;

    int len=fact(N);
    int len_part = pow(2,N-1);
    vector<vector<vector <int>>> partitions;
    vector<int> set(N);
    for (int i = 0; i < N; i++)
    {
        set.at(i)=i+1;
    }
    
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len_part; j++)
        {
            vector<int> b(N-1);
            vector<int> bn = bin(j,0,b);
            vector<vector<int>> fin = eval(bn,set);
            if(is_valid(fin,partitions))
            {
                partitions.push_back(fin);
            }
        }
        next_permutation(set.begin(),set.end());
    }

    //ascending order
    for (int i = 0; i < partitions.size(); i++)
    {
        for (int j = 0; j < partitions.size()-i-1; j++)
        {;
            if(comp(partitions.at(j+1), partitions.at(j)))//j+1 < j
            {;
                vector<vector <int>> temp = partitions.at(j);
                partitions.at(j) = partitions.at(j+1);
                partitions.at(j+1) = temp;
            }
        }
    } 
    display(partitions.at(k-1));
}