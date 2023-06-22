#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <sstream>
using namespace std;
typedef struct node node;

void display(vector<vector<int>> matrix);
void display(node* root, int l);
void insert_even(vector<int> arr, node* root);
void insert_odd(vector<int> arr, node* root);
node* search_even(node* root);
node* search_odd(node* root);

struct node
{
    int data;
    node *left;
    node *right;
};

int main()
{
    //input
    int n;
    cin >> n;
    cin.ignore();
    vector<vector<int>> part(n);
    for (int i = 0; i < n; i++) {
        string input;
        getline(cin, input);
        stringstream ss(input);
        int num;
        while (ss >> num) {
            part[i].push_back(num);
        }
    }
    display(part);
    //data cleansing
    for (int i = 0; i < n; i++)
    {
        sort(part[i].begin(),part[i].end());
    }
    sort(part.begin(), part.end(), [](vector<int>& row1, vector<int>& row2) {
        return row1[0] < row2[0];
    });

    cout<<"\n";
    struct node root = {-1,nullptr,nullptr};
    for (int i = 0; i < n; i++)
    {
        if(part[i][0]%2==0)
        {
            insert_even(part[i],&root);
        }
        else
        {
            insert_odd(part[i],&root);
        }
    }
    display(&root,0);
}

void insert_odd(vector<int> arr, node* root)
{
    node* parent = search_odd(root);
    for (int i = 0; i < arr.size(); i++)
    {
        node* temp = new node;
        temp->data=arr[i];
        temp->right=nullptr;
        temp->left=nullptr;

        parent->right=temp;
        parent=parent->right;
    }
}

void insert_even(vector<int> arr, node* root)
{
    node* parent = search_even(root);
    for (int i = 0; i < arr.size(); i++)
    {
        node* temp = new node;
        temp->data=arr[i];
        temp->right=nullptr;
        temp->left=nullptr;

        parent->left=temp;
        parent=parent->left;
    }
}

node* search_odd(node* root)
{
    queue<node*> q;
    q.push(root);
    while (q.empty() == false)
    {
        node* node = q.front();
        if(node->right==nullptr && node->left!=nullptr)
        {
            return node;
        }
        q.pop();
        if (node->left != nullptr)
        {
            q.push(node->left);
        }
        if (node->right != nullptr)
        {
            q.push(node->right);
        }
    }
    return nullptr;
}

node* search_even(node* root)
{
    if(root->left==nullptr && root->right==nullptr)
    {
        return root;
    }
    queue<node*> q;
    q.push(root);
    while (q.empty() == false)
    {
        node* node = q.front();
        if(node->right!=nullptr && node->left==nullptr)
        {
            return node;
        }
        q.pop();
        if (node->left != nullptr)
        {
            q.push(node->left);
        }
        if (node->right != nullptr)
        {
            q.push(node->right);
        }
    }
    return nullptr;
}

void display(vector<vector<int>> matrix)
{
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void display(node* root, int l)
{
    if(root==nullptr)
    {
        return;
    }
    for (int i = 0; i < l; i++)
    {
        cout << "\t";
    }
    cout << root->data << "\n";
    display(root->left, l+1);
    display(root->right,l+1);
}