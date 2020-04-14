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
        //数据集
    vector<string> attribute_name;
    vector<vector<string>> x;
    vector<string> y;
   typedef struct tree{
        string attribute;
       string type;
       vector<string > value;
        vector< struct tree *> next;
        
    }Tree ;
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
       vector<vector<double>> T(vector<vector<double>>&x)
    {
        int n=x.size();
        int m=x[0].size();
        vector<vector<double>> b(m,vector<double>(n));
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
                b[j][i]=a[i][j];
        }
        return b;
    }
        Tree * create(vector<int> attributelist)
    {
        double maxentropy=0;
        int maxi=-1;
        int n=attributelist.size();
        if(n==0) return NULL;
        for(int i:attributelist)
        {
            double entropy=g(y,x[i]);
            if(maxentropy<entropy)
            {
                maxentropy=entropy;
                maxi=i;
            }
        }
        //if(maxi==-1) return NULL;
        Tree *node=new Tree;
        if(maxi==-1)
        {
            node->type=y[attributelist[0]];
            return node;
        }
        map<string,vector<int>> mp;
        for(int i=0;i<n;i++)
        {
            mp[x[i][attributelist[maxi]]].push_back(i);
        }
        for(map<string,vector<int>>::iterator it=mp.begin();it!=mp.end();it++)
        {
            node->value.push_back(it->first);
            Tree *t=create(it->second);
            node->next.push_back(t);
            
        }
        return node;
    }
    
};
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "决策树\n";
    return 0;
}
