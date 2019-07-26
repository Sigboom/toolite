#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> first;
    vector<int> second(4, 100);
    vector<int> thrid(second.begin(), second.end());
    vector<int> fourth(thrid);

    int myints[] = {12, 56, 48, 23};
    first.assign(7, 100); 
    for (vector<int>::iterator it = first.begin(); it != first.end(); ++it)
	    cout << " " << *it;
    cout << endl;

    second.assign(myints, myints + 3);
    for (vector<int>::iterator it = first.begin(); it != first.end(); ++it)
	    cout << " " << *it;
    cout << endl;

    vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
    for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
	    cout << " " << *it;
    cout << endl;
    return 0;
}
