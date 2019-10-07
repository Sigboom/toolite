#include<set>    
#include<iostream>    

using namespace std;

int main() {
    int val[] = {78, 12, 45, 75, 68};
    set<int> s, another(val, val + 5);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.insert(x);
	cout << "s.insert(" << x << ")" << endl;
    }
    
    for(set<int>::iterator it = s.begin(); it != s.end(); it++)
        printf("%d\n",*it); 
    
    for(set<int>::reverse_iterator it = s.rbegin(); it != s.rend(); it++)
        printf("%d\n",*it); 
    
    cout << "*s.begin() *s.end() " << *s.begin() <<" "<< *s.end() << endl;
    cout << "*s.lower_buond(3)" << *s.lower_bound(3) << endl; 
    cout << "*s.upper_bound(3)" << *s.upper_bound (3) << endl;
    cout << "*s.find(3) = " << *s.find(3) << endl;
    pair<set<int>::const_iterator, set<int>::const_iterator> eq = s.equal_range(2);
    cout << "*eq.first = " << *eq.first << endl;
    cout << "*eq.second = " << *eq.second << endl;
    s.erase(3);
    cout << "s.erase(3)" << endl;
    cout << "s.count(1) = " << s.count(1) << endl;
    cout <<"s.size() =" << s.size() << endl;
    cout <<"s.max_size() =" << s.max_size() << endl;
    s.swap(another);
    cout <<"s.swap(another) => s.size() = " << s.size() << endl;
    s.swap(another);
    cout <<"s.swap(another) => s.size() = " << s.size() << endl;
    
    set<int>::value_compare mycomp = s.value_comp(); //same to key_comp
    int highest = *s.rbegin();
    set<int>::iterator it = s.begin();
    
    do {
        cout << ' ' << *it;
    } while ( mycomp(*(it++), highest) );
    cout << endl; 
    s.clear();
    cout << "have called s.clear() s.size() = " << s.size() << endl;
    cout << "s.empty() = " << s.empty() << endl;
    
    std::set<int> myset;
    int * p;
    unsigned int i;

    // allocate an array of 5 elements using myset's allocator:
    p=myset.get_allocator().allocate(5);

    // assign some values to array
    for (i=0; i<5; i++) p[i]=(i+1)*10;

    std::cout << "The allocated array contains:";
    for (i=0; i<5; i++) std::cout << ' ' << p[i];
    std::cout << '\n';

    myset.get_allocator().deallocate(p,5); 
    return 0;
}
