#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
class logistic
{
private:
    int epochs=1000;
    double learn_rate=0.01;
double sigmoid(double z)
{
   
    return 1.0/(1+exp(-z));
}
    //计算内积
    double scalarProduct(vector<double>&x,vector<double>&y)
    {
        double sum=0;
        int n=x.size();
        for(int i=0;i<n;i++)
        {
            sum+=(x[i]*y[i]);
        }
        return sum;
    }
    double p(vector<double>&x,vector<double>&w)
    {
        return sigmoid(scalarProduct(x,w));
    }
    //梯度上升法求极大值
public:
    logistic(int epochs=1000,double learn_rate=0.01)
    {
        this->epochs=epochs;
        this->learn_rate=learn_rate;
    }
    vector<double> grad_ascent(vector<vector<double>>&x,vector<int> &y)//二类分类，这里的y曲子{0,1}
    {
        int epoch=this->epochs;
        int learn_rate=this->learn_rate;
        int n=x.size();
        int m=x[0].size();
        vector<double> w(m,1);
        vector<double>error(n);
        
        while(epochs--)
        {
            for(int i=0;i<n;i++)
            {
                error[i]=y[i]-p(x[i],w);
                
            }
            for(int j=0;j<m;j++)
            {
                double sum=0;
                for(int i=0;i<n;i++)
                {
                    sum+=x[i][j]*error[i];
                }
                w[j]+=learn_rate*sum;
            }
        }
        return w;
    }
    int classify(vector<double> &x, vector<double> &w)
    {
        //对数几率是线性模型。
        if (scalarProduct(x, w) > 0.5)
            return 1;
        else
            return 0;
    }
        double acc(vector<int> &y,vector<int>&y_)
    {
        int n=y.size();
        int sum=0;
        for(int i=0;i<n;i++)
        {
            sum+=(y==y_?1:0);
        }
        return double(sum)/n;
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "这个程序是逻辑斯蒂的c++实现，先挖个坑，明天继续填坑\n";
    return 0;
}
