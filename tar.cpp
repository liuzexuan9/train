//
//  main.cpp
//  huawei
//
//  Created by 刘泽轩 on 2020/4/17.
//  Copyright © 2020 刘泽轩. All rights reserved.
//

#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;
#define maxnode 30007
vector<unsigned int> links[maxnode];
unsigned int nextnode[maxnode];
//vector<unsigned int>early_time(maxnode,maxnode);
set<pair<unsigned int,unsigned int>> divlink;
unordered_map<unsigned int,unsigned int>mp,remp;
set<vector<unsigned int>> ans_set[maxnode];
//vector<unsigned int>temp(maxnode);
unsigned int temp[maxnode];
set<unsigned int> nodenum_set;
bool VIS[maxnode]={false};
void dfs(unsigned int now,vector<bool> &vis,unsigned int nowtime,vector<unsigned int> &times)
{
    //printf("?");
   // printf("%u\n",now);
    VIS[now]=true;
    if(vis[now]==true)
    {
        int t=nowtime-times[now];
        
       //printf("%d  %d\n",nowtime,times[now]);
        if(t>2&&t<=7)
        {
            int n=0;
          // printf("%d",remp[now]);
            temp[n++]=remp[now];
            int mini=0;
            int node=nextnode[now];
            while(node!=now)
            {
               // printf(",%d",remp[node]);
                temp[n++]=remp[node];
                if(temp[n-1]<temp[mini]) mini=n-1;
                node=nextnode[node];
                //early_time[node]=min(early_time[node],now);
            }
            vector<unsigned int>t;
            
            for(int i=0;i<n;i++)
                t.push_back(temp[(i+mini)%n]);
            ans_set[t.size()].insert(t);
            nodenum_set.insert(t.size());
           // printf("\n");
        }
        
        
        return;
    }
    vis[now]=true;
    
    times[now]=nowtime;
    nowtime++;
    
    int m=links[now].size();
    
    for(int i=0;i<m;i++)
    {
        unsigned int x=links[now][i];
        nextnode[now]=x;
       
        dfs(x,vis,nowtime,times);
        
    }
    
    vis[now]=false;
}
static bool cmp(vector<unsigned int>&a,vector<unsigned int>&b)
{
    int n=a.size();
    for(int i=0;i<n;i++)
    {
        if(a[i]!=b[i]) return a[i]<b[i];
    }
    return false;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";
    freopen("test_data.txt", "r", stdin);
    
    unsigned int x,y,z;
    unsigned int now=0;
    while(scanf("%u,%u,%u",&x,&y,&z)!=EOF)
    {
        if(mp.find(x)==mp.end())
        {
            mp[x]=now;
            remp[now]=x;
            now++;
        }
        if(mp.find(y)==mp.end())
        {
            mp[y]=now;
            remp[now]=y;
            now++;
        }
        x=mp[x];
        y=mp[y];
        links[x].push_back(y);
        
       // printf("%d,%d\n",x,y);
    }
   // printf("%u\n",now);
    vector<unsigned int> times(maxnode);
    vector<bool> vis(maxnode);
    //vector<unsigned int> seq;
    for(int i=0;i<now;i++)
    if(VIS[i]==false)
    dfs(i,vis,0,times);
    //printf("%d",ans_set.size());
    vector<unsigned int> nodenum;
    for(unsigned int x:nodenum_set)
        nodenum.push_back(x);
    sort(nodenum.begin(),nodenum.end());
    int sum=0;
    for(int x:nodenum)
        sum+=(ans_set[x].size());
    printf("%u\n",sum);
    for(int x:nodenum)
    {
    int n=ans_set[x].size();
    vector<vector<unsigned int>>ans(n);
    int i=0;
    for(set<vector<unsigned int>>::iterator it=ans_set[x].begin();it!=ans_set[x].end();it++)
    {
        ans[i++]=*it;
    }
        sort(ans.begin(),ans.end(),cmp);
        for(vector<unsigned int> i:ans)
        {
            bool first=true;
            for(unsigned int j:i)
            {
                if(!first) printf(",");
                first=false;
                printf("%u",j);
            }
            printf("\n");
        }
        
    }
    return 0;
}
