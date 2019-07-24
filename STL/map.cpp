#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    map<string, size_t> student{{"Ann", 25}, {"Bill", 46}};
    map<string, size_t> person {begin(student), end(student)};
    
    student.insert(make_pair("Jack", 32));
    student.insert(pair<string, size_t>("Jill", 56));
    person.insert(pair<string, size_t>("Daniel", 23));
    map<string, size_t>::iterator iter;
    //C++11
    student.emplace("Ann",25); 
    student.emplace("Cnn",25); 
    
    for(iter = student.begin(); iter != student.end(); iter++)
       cout<<iter->first<<' '<<iter->second<<endl;
    
    string key;
    try{
    	key = string("Jack");
    	size_t age = student.at(key);
    	cout << key << " : " << age << endl;
    } catch (const out_of_range &e) {
    	cerr << e.what() << "\n" << key << "was no found." << endl;
    }
    
    try{
    	key = string("Daniel");
    	size_t age = student.at(key);
    	cout << key << " : " << age << endl;
    } catch (const out_of_range &e) {
    	cerr << e.what() << "\n" << key << "was no found." << endl;
    }
    
    //相对的下标运算符如果没有该元素会产生一个新的元素
    size_t new_val = student["Daniol"];

    cout << "student['Daniol'] : " << new_val << endl;

    cout << "student.find('Daniel') : " << student.find("Daniel");
    cout << "student.count('Daniel') : " << student.count("Daniel");
    return 0;
}
