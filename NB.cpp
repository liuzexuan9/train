//
//  main.cpp
//  NB
//
//  Created by 刘泽轩 on 2020/4/8.
//  Copyright © 2020 刘泽轩. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;
class NB
{
private:
    //vector<vector<double>> x;
    //vector<int>y;
    map<int,int> py;
    vector< map<pair<double,int>,int>> px_y;
    set<int> y_set;
    vector<set<int>>x_set;
    int N,M;
    int laplace;
public:
    NB(vector<vector<double> >&x,vector<int> &y,int lap=0){
        //x=x0;
        //y=y0;
        laplace=lap;
        N=x.size();
        x_set.resize(M);
        map<int,int>mpy;
        for(int i=0;i<N;i++)
        {
            py[y[i]]++;
            y_set.insert(y[i]);
            
        }
        int M=x[0].size();
        pair<double,int> t;
        px_y.resize(M);
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<M;j++)
            {
                t.first=x[i][j];
                t.second=y[i];
                x_set[j].insert(x[i][j]);
                px_y[j][t]++;
            }
        }
        
        
    }
    //计算先验概率
    double prior(int y)
    {
       // return double(py[y])/N;
        return double(py[y]+laplace)/(N+laplace*y_set.size());
    }
    //计算条件概率
    double condition(vector<double>&x,int y)
    {
        int m=x.size();
        double ans=1.0;
        pair<double,int> t;
        t.second=y;
        for(int i=0;i<m;i++)
        {
            t.first=x[i];
            //ans*=double(px_y[i][t])/py[y];
            ans*=double(px_y[i][t]+laplace)/(py[y]+laplace*x_set[i].size());
        }
        return ans;
    }
    //计算后验,由于p(x)对于我们的预测没有影响，所以这里也不计算p(x)
    double post(int y,vector<double>&x)
    {
       // int m=x.size();
        return prior(y)*condition(x,y);
        
    }
    //根据输入的特征向量预测
    int predict(vector<double>&x)
    {
        
        
        double p=-1;
        int ans;
        for(int y:y_set)
        {
            double t=post(y,x);
            if(t>p)
            {
                p=t;
                ans=y;
            }
        }
        return ans;
    }
    int argmax(vector<double>&x)
    {
        return predict(x);
    }
    void  set_laplace(int k)
    {
        laplace=k;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "该程序是朴素贝叶斯的实现，主要有先验概率、条件概率、后验概率和argmax,也就是预测\n";
    return 0;
}
