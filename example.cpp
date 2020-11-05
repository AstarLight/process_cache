
#include <iostream>
#include "object.cpp"

using namespace std;

class skill
{
public:
	int iLevel;
	int isAdvace;
	XTOSTRUCT(O(iLevel, isAdvace)); // add XTOSTRUCT at the end of struct/class
};

class User
{
public:
	int usernum;
	int iGrade;
	int iSchool;
	int iCash;
	std::string strName;
	std::vector<int> vecFriends;
	std::map<int, skill> mpSkillList;
	XTOSTRUCT(O(usernum, iGrade, iSchool, iCash, strName, mpSkillList, vecFriends)); // add XTOSTRUCT at the end of struct/class
};


int main()
{
	auto p = new object<int, User>(1000, "./game_users");

   	// 2000个玩家数据，1000大小的lru,执行查询请求100W次

	User u1;
	u1.iGrade = 109;
	u1.iSchool = 2;
	u1.strName = "sandaojieshu";
	u1.vecFriends = {90281, 28981, 28811, 2173};
	map<int, skill> m;
	skill s1;
	s1.iLevel = 90;
	s1.isAdvace = 0;
	skill s2;
	s2.iLevel = 90;
	s2.isAdvace = 0;
	m[311] = s1;
	m[567] = s2;
	u1.mpSkillList = m;

    for (int i=0; i<2000; i++)
    {
    	u1.usernum = i;
    	p->set_object(i, u1);
    }

    for (int i=0; i<10000; i++)
    {
    	User x;
    	x = p->get_object(rand()%2000);
    	cout << "usernum:" << x.usernum << ",hitrate=" << p->get_cache_hitrate() << endl;;
    }
	return 0;
}