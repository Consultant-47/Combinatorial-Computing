#include <iostream>
#include <string>
using namespace std;

int Q(int n, int k);
int R(int n, int k, int max);

int main() {
    
    int n,k;
    cin >> n;
    cin >> k;
    int q = Q(n,k);
    int r = R(n,k,n);
    cout << q << " "<< r;
    return 0;
}

int Q(int n, int k)// k is max number
{
    if(k==1 || n==1 || n==0)//k = 1 => 1+1+...+1 ; n=1 => 1 ; n=0 => {} 
    {
        return 1;
    }
    if(n<0)//partition not possible
    {
        return 0;
    }
    int sum=0;
    for (int i = 1; i <= k; i++)//sum over all possible partitions
    {
        sum+= Q(n-i,i);//pass i to restrict to descending order numbers
    }
    return sum;
}

int R(int n, int k, int max)//k is number of numbers
{

    if(n<0)//negative number => partition not possible
    {
        return 0;
    }
    if(k==0 && n>0)//0 places & non-zero number => not possible
    {
        return 0;
    }
    if(max*k<n)//maximum sum < number => not possible
    {
        return 0;
    }
    if(n==1 || k==1 || n==0 || max==1)// n=1 => 1 ; k=1 => n ; n=0 => {} ; max=1 => 1+1+...+1
    {
        return 1;
    }
    int sum=0;
    for (int i = 1; i <= max; i++)//sum over all partitions maintaining descending order
    {
        sum+=R(n-i,k-1,i);
    }
    return sum;
}
