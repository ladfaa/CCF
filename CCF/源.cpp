#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<string>
#include<hash_map>
#include<random>
#include<math.h>
using namespace std;

class Node{
	string name, news, time, vistime;
public:
	Node(){}
	Node(string name, string news, string time, string vistime){
		this->name = name;
		this->news = news;
		this->time = time;
		this->vistime = vistime;
	}
	string getNews(){
		return news;
	}
};
hash_map<string, vector<Node>> mylog;
hash_map<string, vector<string>> net;
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
	hash_map<int, string> user;
	ifstream fin("in");
	int k = 0;

	while (true){
		if (fin.eof())break;
		fin >> ff;
		vector<string> tmp;
		split(ff, ",", tmp);
		hash_map<string, vector<Node>>::iterator it = mylog.find(tmp[0]);
		if (it == mylog.end()){
			vector<Node> newVector;
			mylog[tmp[0]] = newVector;
			user[k++] = tmp[0];
		}

		mylog[tmp[0]].push_back(Node(tmp[0], tmp[1], tmp[2], tmp[3]));
	}
	fin.close();
	hash_map<string, vector<Node>>::iterator it;
	for (it = mylog.begin(); it != mylog.end(); it++){
		vector<string> v;
		net[it->first] = v;
		for (int i = 0; i < 5; i++){
			int ran = rand() % 9999;
			net[it->first].push_back(user[ran]);
		}
	}
}
int getNum(string follow, string leader){
	int count = 0;
	for (int i = 0; i < mylog[follow].size(); i++){
		for (int j = 0; j < mylog[leader].size(); j++){
			if (mylog[leader][j].getNews() == mylog[follow][i].getNews()){
				count++;
			}
		}
	}
	return count;
}
int getNum2(string follow, string leader){
	hash_map<string, string> vis1;
	vector<string> vis2;
	for (int i = 0; i < mylog[follow].size(); i++){
		vis1[mylog[follow][i].getNews()] = mylog[follow][i].getNews();
	}
	for (int i = 0; i < mylog[leader].size(); i++){
		vis2.push_back(mylog[leader][i].getNews());
	}
	int count = 0;
	for (int i = 0; i < vis2.size(); i++){
		if (vis1.find(vis2[i]) == vis1.end()){
			count++;
		}
	}
	return count;
}
double sim(string follow, string leader){
	double t1 = getNum(follow, leader) - getNum2(follow, leader);
	double t2 = mylog[leader].size();
	double t3 = 1 - 1 / sqrt(mylog[leader].size());
	return t1 / t2*(t3);
}
bool in(string first, vector<string> second){
	for (int i = 0; i < second.size(); i++)
	if (first == second[i])
		return true;
	return false;
}
void replace(string user){

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
	string kk;
	hash_map<string, vector<Node>>::iterator it;
	for (it = mylog.begin(); it != mylog.end(); it++){
		if (in(it->first, net[user])){
			continue;
		}
		double tmp = sim(user, it->first);
		if (max < tmp){
			max = tmp;
			kk = it->first;
		}
	}
	if (min < max){
		net[user][minI] = kk;
	}
}
void del(){

}

int main(){
	init();
	cout << sim("5218791", "52550") << endl;
	int k = 0;
	for (hash_map<string, vector<Node>>::iterator it = mylog.begin(); it != mylog.end(); it++){
		cout << k++;
		for (int i = 0; i < 5; i++){
			replace(it->first);
		}
	}


	for (int i = 0; i < 5; i++){
		cout << sim("5218791", net["5218791"][i]);
	}
}
