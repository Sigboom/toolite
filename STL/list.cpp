#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main () {
    // constructors used in the same order as described above:
    list<int> first;                                // empty list of ints
    list<int> second (4,100);                       // four ints with value 100
    list<int> third (second.begin(),second.end());  // iterating through second
    list<int> fourth (third);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16,2,77,29};
    list<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

    cout << "The contents of fifth are: ";
    for (list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
        cout << *it << ' ';
    cout << endl;

    for (int i = 0; i < 5; ++i) first.push_back(i);
    list<int>::iterator it = first.begin();
    ++it;
    first.insert(it, 10);
    first.insert(it, 2, 20);
    it--;
    vector<int> myvector(2, 30);
    first.insert(it, myvector.begin(), myvector.end());
    for (list<int>::iterator it = first.begin(); it != first.end(); ++it) {
    	cout << " " << *it;
    }
    cout << endl;

    it = first.end();
    //first.erase(it); it is danger
    it--;
    first.erase(it);
    for (list<int>::iterator it = first.begin(); it != first.end(); ++it) {
    	cout << " " << *it;
    }
    cout << endl;
    return 0;
}
