//
//  main.cpp
//  decision_tree
//
//  Created by 刘泽轩 on 2020/4/11.
//  Copyright © 2020 刘泽轩. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <string>
using namespace  std;
class decision_tree
{
private:
public:
    //数据集的经验熵
    double H(vector<string> &y)
    {
        int n=y.size();
        map<string,int>mp;
        for(string x:y)
            mp[x]++;
        double sum=0;
        for(map<string,int>::iterator it=mp.begin();it!=mp.end();it++)
        {
            if(it->second!=0)
            {
                sum+=(double(it->second)/n)*log(double(it->second)/n)/log(2.0);
            }
        }
        return -sum;
    }
    double condition_entropy(vector<string> &x,vector<string>&y)
    {
        double sum=0;
        map<string,vector<int>> x_mp;//将x按其取值划分成各自对应的部分
        int n=x.size();
        for(int i=0;i<n;i++)
        {
            x_mp[x[i]].push_back(i);
        }
        //int m=x_mp.size();//特征x取值的种类
        for(map<string,vector<int>> ::iterator it=x_mp.begin();it!=x_mp.end();it++)
        {
            int m=(it->second).size();
            map<string,int>y_mp;
            vector<int>temp=it->second;
            for(int x:temp)
            {
                y_mp[y[x]]++;
            }
            double t=0;
            for(map<string,int>::iterator ity=y_mp.begin();ity!=y_mp.end();ity++)
            {
                if(ity->second!=0)
                {
                    t+=(ity->second*1.0/m)*(log((ity->second*1.0/m)/log(2)));
                }
            }
            sum+=(m*1.0/n)*t;
        }
        
        
        return sum;
    }
    double g(vector<string>&y,vector<string>&x)//计算信息增益
    {
        return H(y)-condition_entropy(x,y);
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "决策树\n";
    return 0;
}
