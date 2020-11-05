

#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>
#include "x2struct/x2struct.hpp" 

using namespace std;

template<typename key_t, typename value_t>
class disk_persist
{
public:
	string file_path;  // file path
	int save_disk(const key_t& key, const value_t& val);
	value_t get_from_disk(const key_t& key);
};


template<typename key_t, typename value_t>
int disk_persist<key_t, value_t>::save_disk(const key_t& key, const value_t& val)
{
	string obj_path = file_path + "/" + to_string(key) + ".dat";
	cout << "path:" << obj_path << endl;

	if (access(file_path.c_str(), F_OK) == -1)
	{
		cout << "无法访问文件夹：" <<  file_path << endl;
		mkdir(file_path.c_str(), S_IRWXU);
	} 

    string json = x2struct::X::tojson(val);  // C++ object to json
    cout<<json<<endl;

    ofstream out(obj_path);
    out << json << endl;
    out.close();

    return 0;
}

template<typename key_t, typename value_t>
value_t disk_persist<key_t, value_t>::get_from_disk(const key_t& key)
{

	string obj_path = file_path + "/" + to_string(key) + ".dat";
	if (access(obj_path.c_str(), F_OK) == -1)
	{
		throw std::range_error("There is no such file in disk");
	} 
    string file_json;
    ifstream in(obj_path);
    in >> file_json;
    in.close();

    value_t x;
    x2struct::X::loadjson(file_json, x ,false);
	return x;
}



