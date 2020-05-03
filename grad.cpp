//
//  main.cpp
//  grad
//
//  Created by 刘泽轩 on 2020/4/2.
//  Copyright © 2020 刘泽轩. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <random>
using namespace std;
double multi(vector<double> &a,vector<double> &b)
{
    int n=a.size();
    double sum=0;
    for(int i=0;i<n;i++)
    {
        sum+=a[i]*b[i];
    }
    return sum;
}
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
vector<double> adagrad(vector<vector<double>>&x,vector<double>&y,double lr,int epoch=100)
{
    int n=x.size();
    int m=x[0].size();
    double sum=0.0,sumb=0;
    vector<double> w(m,0);
    vector<double> gw(m);
    double rmsofgrad2=0;
    while(epoch--)
    {
        for(int j=0;j<m;j++)
        
        {
            sum=0;
            for(int i=0;i<n;i++)
            {
                sum+=(2*(x[i][j]*w[j]-y[i])*x[i][j]);
            }
            gw[j]=sum/n;
        }
        //参数更新
        rmsofgrad2+=multi(gw,gw);
        for(int j=0;j<m;j++)
        {
            w[j]-=lr/sqrt(rmsofgrad2)*gw[j];
        }
    }
    vector<double>ans(m+1);
    for(int i=0;i<m;i++)
    {
        ans[i]=w[i];
        
    }
    return ans;
}
vector<double> sgd(vector<vector<double>>&x,vector<double>&y,double lr,int batch_size,int epoch=100)
{
    int n=x.size();
    int m=x[0].size();
    double sum=0.0,sumb=0;
    vector<double> w(m,0);
    vector<double> gw(m);
    int batchs=(n+batch_size-1)/batch_size;
    while(epoch--)
    {
        unsigned seed = std::chrono::system_clock::now ().time_since_epoch ().count ();
        std::shuffle (x.begin (), x.end (), std::default_random_engine (seed));
        for(int batch=0;batch<batchs;batch++)
        {
            int left=batch*batch_size;
            int right=min((batch+1)*batch_size,n);
        for(int j=0;j<m;j++)
            
        {
            sum=0;
            for(int i=left;i<right;i++)
            {
                sum+=(2*(x[i][j]*w[j]-y[i])*x[i][j]);
            }
            gw[j]=sum/(right-left);
        }
        //参数更新
       
        for(int j=0;j<m;j++)
        {
            w[j]-=lr*gw[j];
        }
        }
    }
    
    return w;
}
double cal_error(vector<double>&y,vector<double> &y_hat)
{
    int n=y.size();
    double sum=0;
    
    for(int i=0;i<n;i++)
    {
        sum+=(y[i]-y_hat[i])*(y[i]-y_hat[i]);
    }
    return sum/n;
}
double f(vector<double>&x,vector<double>&w)
{
    int n=x.size();
    double sum=0;
    for(int i=0;i<n;i++)
    {
        sum+=(x[i]*w[i]);
    }
    return sum;
}
vector<double> adam(vector<vector<double>> &x,vector<double>&y,double lr,int batch_size,int epoch=100 )
{
    double alpha = 0.01;  // 学习率
    double momentum = 0.1;  // 冲量
    double threshold = 0.0001;  //停止迭代的错误阈值
    int epochs = 3000;  //迭代次数
    double error = 0; //初始错误为0
    int n=x.size();
    int m=x[0].size();
    vector<double> w(m+1,0);//参数
    int batchs=(n+batch_size-1)/batch_size;
    double sum=0;
    vector<double> y_(n);
    vector<double> g(m);
    double p1=0.9,p2=0.999;//钜估计的指数衰减速率，按论文的建议为0.9，0.999
    double p1t=p1,p2t=p2;
    vector<double> s(m,0),r(m,0);//一阶和二阶矩变量
    double stepsize=0.001;//步长，按建议为0.001
    for(int t=1;t<=epochs;t++)
    {
        for(int i=0;i<n;i++)
        {
            y_[i]=f(x[i],w);
        }
        error=cal_error(y,y_);
        if(error<threshold) break;
        unsigned seed = std::chrono::system_clock::now ().time_since_epoch ().count ();
        std::shuffle (x.begin (), x.end (), std::default_random_engine (seed));
        
        for(int batch=0;batch<batchs;batch++)
        {
            int left=batch*batch_size;
            int right=min((batch+1)*batch_size,n);
            for(int j=0;j<m;j++)
                
            {
                sum=0;
                for(int i=left;i<right;i++)
                {
                    sum+=(2*(x[i][j]*w[j]-y[i])*x[i][j]);
                }
                g[j]=sum/(right-left);
            }
            //参数更新
            for(int j=0;j<m;j++)
            {
                s[j]=(p1*s[j]+(1-p1)*g[j])/(1-p1t);
                r[j]=(p2*r[j]+(1-p2)*g[j]*g[j])/(1-p2t);
                w[j]-=stepsize*(s[j]/(sqrt(r[j])+10e-8));
            }
            p1t*=p1;
            p2t*=p2;
            
            
        }
    }
    return w;
}
vector<vector<int>> confusion_matrix(vector<int> &a,vector<int> &b,vector<int >&type)
{
    int n=type.size();
    vector<vector<int>> cnt(n,vector<int>(n,0));
    int m=a.size();
    for(int i=0;i<m;i++)
    {
        cnt[a[i]][b[i]]++;
    }
    return cnt;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
