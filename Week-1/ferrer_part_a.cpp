#include <iostream>
#include <string>
using namespace std;

int main() {
    
    string in;
    cout << "Enter partition: ";
    getline(cin, in, '\n');// assuming input of form (a, b, c, ... y, z)
    in=in.substr(1,in.length()-2);

    cout << "\nFerrer diagram is - \n\n";
    string delim = ", ";
    while(in.length()>0)
    {
        string token = in.substr(0,in.find(delim));
        in.erase(0, in.find(delim) + delim.length());

        for (int i = 0; i < stoi(token); i++)
        {
            cout << "*";
        }
        cout << "\n";
    }
    
    return 0;
}
