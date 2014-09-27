#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<string>
#include<hash_map>
#include <sstream>
#include<random>
#include<math.h>
using namespace std;

class Node{
	int name;
	string news, time, vistime;
public:
	Node(){}
	Node(int name, string news, string time, string vistime){
		this->name = name;
		this->news = news;
		this->time = time;
		this->vistime = vistime;
	}
	string getNews(){
		return news;
	}
	int getName(){
		return name;
	}
};
class CCF{
public:
	vector<string> mylog[52187];
	hash_map<int, vector<int>> net;
	int cnt = 0;
	CCF(){
		cout << "ok" << endl;
	}
	~CCF(){

	}

	void split(const string& src, const string& separator, vector<string>& dest)
	{
		string str = src;
		string substring;
		string::size_type start = 0, index;

		do
		{
			index = str.find_first_of(separator, start);
			if (index != string::npos)
			{
				substring = str.substr(start, index - start);
				dest.push_back(substring);
				start = str.find_first_not_of(separator, index);
				if (start == string::npos) return;
			}
		} while (index != string::npos);

		//the last token
		substring = str.substr(start);
		dest.push_back(substring);
	}
	void init(){
		string ff;
		hash_map<int, int> user;
		ifstream fin("out");
		int k = 0;

		while (true){
			if (fin.eof())break;
			fin >> ff;
			vector<string> tmp;
			split(ff, ",", tmp);
			stringstream ss;
			ss << tmp[0];
			int tmp0;
			ss >> tmp0;
			if (mylog[tmp0].size() == 0){
				vector<string> newVector;
				mylog[tmp0] = newVector;
				user[k++] = tmp0;
			}

			mylog[tmp0].push_back(tmp[1]);
		}
		fin.close();
		for (int i = 0; i < 5218792; i++){
			if (mylog[i].empty())continue;
			vector<int> v;
			net[i] = v;
			for (int i = 0; i < 5; i++){
				int ran = rand() % 9999;
				net[i].push_back(user[ran]);
			}
		}
	}
	int getNum(int follow, int leader){
		int count = 0;
		int size1 = mylog[follow].size();
		int size2 = mylog[leader].size();

		for (int i = 0; i < size1; i++){
			for (int j = 0; j < size2; j++){
				cnt++;
				string first = mylog[follow][i];
				string second = mylog[leader][j];
				if (first == second)
					count++;
			}
		}
		return count;
	}
	int getNum2(int follow, int leader){
		hash_map<string, string> vis1;
		vector<string> vis2;
		for (int i = 0; i < mylog[follow].size(); i++){
			vis1[mylog[follow][i]] = mylog[follow][i];
		}
		for (int i = 0; i < mylog[leader].size(); i++){
			vis2.push_back(mylog[leader][i]);
		}
		int count = 0;
		for (int i = 0; i < vis2.size(); i++){
			if (vis1.find(vis2[i]) == vis1.end()){
				count++;
			}
		}
		return count;
	}
	double sim(int follow, int leader){
		double t1 = getNum(follow, leader) - getNum2(follow, leader);
		double t2 = mylog[leader].size();
		double t3 = 1 - 1 / sqrt(mylog[leader].size());
		double res = t1 / t2 * t3;
		return res;
	}
	bool in(int first, vector<int> second){
		for (int i = 0; i < second.size(); i++)
		if (first == second[i])
			return true;
		return false;
	}
	void replace(int user){

		double min = 1000;
		int minI = -1;
		for (int i = 0; i < net[user].size(); i++){
			double tmp = sim(user, net[user][i]);
			if (min > tmp){
				min = tmp;
				minI = i;
			}
		}
		double max = -10000;
		int kk;
		for (int i = 0; i < 5218792; i++){
			if (mylog[i].empty())continue;
			if (in(i, net[user])){
				continue;
			}
			double tmp = sim(user, i);
			if (max < tmp){
				max = tmp;
				kk = i;
			}
		}
		if (min < max){
			net[user][minI] = kk;
		}
	}
	void del(){

	}
};

int main(){
	cout << sizeof(int);
	CCF c;
	c.init();
	cout << c.sim(5218791, 52550) << endl;
	int k = 0;
	for (int i = 0; i < 5218792; i++){
		if (c.mylog[i].empty())continue;
		cout << k++ << endl;
		cout << c.cnt << endl;
		for (int j = 0; j < 5; j++){
			c.replace(i);
		}
	}


	for (int i = 0; i < 5; i++){
		cout << c.sim(5218791, c.net[5218791][i]);
	}
}
