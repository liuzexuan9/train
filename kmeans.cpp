//
//  main.cpp
//  kmeans
//
//  Created by 刘泽轩 on 2020/5/17.
//  Copyright © 2020 刘泽轩. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace  std;
double caldistance(vector<double>&a,vector<double>&b)
{
    int n=a.size();
    double sum=0;
    for(int i=0;i<n;i++)
    {
        sum+=(a[i]-b[i])*(a[i]-b[i]);
    }
    return sum;
}
vector<vector<double>> kmeans(vector<vector<double>> &data,int k,int steps=1000)
{
    vector<vector<double>> means;
    for(int i=0;i<k;i++)
        means.push_back(data[i]);
    int n=data.size();
    vector<int> loc(n,-1);
    
    bool change=false;
    int m=data[0].size();
    while(steps--)
    {
        change=false;
        vector<vector<double>> dis(k,vector<double>(m,0));
        vector<int> cnt(k,0);
        for(int i=0;i<n;i++)
        {
            int mini=-1;
            double mindis=-1;
            for(int j=0;j<k;j++)
            {
                
                double t=caldistance(data[i], means[j]);
                if(mini==-1)
                {
                    mindis=t;
                    mini=j;
                }
                else if(mindis>t)
                {
                    mini=j;
                    mindis=t;
                }
            }
            cnt[mini]++;
            for(int j=0;j<m;j++)
                dis[mini][j]+=data[i][j];
            if(loc[i]!=mini)
            
            {
                loc[i]=mini;
                change=true;
            }
            
        }
        if(change==false) break;
        for(int j=0;j<k;j++)
        {
           
            for(int t=0;t<m;t++)
                means[j][t]=dis[j][t]/cnt[j];
        }
    }
    return means;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    
    return 0;
}
