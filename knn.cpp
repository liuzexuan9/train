//
//  knn.cpp
//  grad
//
//  Created by 刘泽轩 on 2020/4/5.
//  Copyright © 2020 刘泽轩. All rights reserved.
//

#include "knn.hpp"
#include <queue>
#include <map>
double dis(vector<double> &a,vector<double>&b)
{
    int n=a.size();
    double sum=0;
    for(int i=0;i<n;i++)
    {
        sum+=(a[i]-b[i])*(a[i]-b[i]);
    }
    return sqrt(sum);
}
struct cmp
{
    bool operator () (pair<double,int>&a,pair<double,int>&b)
    {
        return a.first<b.first;
    }
};
int  knn_force(vector<vector<double>> &x,vector<int>&y,vector<double>&target,int k)
{
    int n=x.size();
    int m=x[0].size();
    //vector<pair<double,int>> cache(k+1);
    priority_queue<pair<double,int>,vector<pair<double,int>>,cmp> cache;
    pair<double,int>temp;
    for(int i=0;i<k;i++)
    {
        //cache[i].first=dis(x[i],target);
        temp.first=dis(x[i],target);
        temp.second=i;
        cache.push(temp);
    }
    
    for(int i=k;i<n;i++)
    {
        temp.first=dis(x[i],target);
        temp.second=i;
        if((cache.top()).first>temp.first)
        {
            cache.pop();
            cache.push(temp);
        }
    }
    map<int,int>mp;
    while(!cache.empty())
    {
        temp=cache.top();
        cache.pop();
        mp[temp.second]++;
    }
    int maxi=-1;
    int maxnum=-1;
    for(map<int,int>::iterator it=mp.begin();it!=mp.end();it++)
    {
        if(it->second>maxnum)
        {
            maxi=it->first;
            maxnum=it->second;
        }
    }
    return maxi;
}
