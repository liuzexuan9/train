//
//  main.cpp
//  grad
//
//  Created by 刘泽轩 on 2020/4/2.
//  Copyright © 2020 刘泽轩. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;
vector<double> grad(vector<vector<double>>&x,vector<double>&y,double lr,int epoch=100)
{
    int n=x.size();
    int m=x[0].size();
    double sum=0.0,sumb=0;
    vector<double> w(m,0);
    double b=0;
    vector<double> gw(m);
    double gb=0;
    
    while(epoch--)
    {
        for(int j=0;j<m;j++)
        
        {
            sum=0;
            sumb=0;
            for(int i=0;i<n;i++)
            {
                sum+=(2*(x[i][j]*w[j]+b-y[i])*x[i][j]);
                sumb+=2*(x[i][j]*w[j]+b-y[i]);
                
            }
            gw[j]=sum/n;
            gb=sumb/n;
            
        }
        //参数更新
        for(int j=0;j<m;j++)
        {
            w[j]-=lr*gw[j];
        }
        b-=lr*gb;
    }
    
    vector<double>ans(m+1);
    for(int i=0;i<m;i++)
    {
        ans[i]=w[i];
        
    }
        ans[m]=b;
    return ans;
    
}
vector<vector<double>> addhalt(vector<vector<double>> &x)
{
    int n=x.size();
    int m=x[0].size();
    vector<vector<double>>x_(n,vector<double>(m+1));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            x_[i][j]=x[i][j];
        }

    }
    for(int i=0;i<n;i++)
    {
        x_[i][m]=1.0;
    }
    return x_;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
