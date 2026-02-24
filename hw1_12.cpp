#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define maxr 1e6
#define maxi 1e6
#define steps 7
#define SIZE 100

long long combination(int n, int k){
    long long result = 1;
    for(int i = 1; i <= k; i++)
    {
        result = result * (n - k + i) / i;
    }
    return result;
}
void fire_reaction(int &x1,int &x2,int &x3, double k1, double k2, double k3){

    double a1 = (x1>=2 && x2>=1) ? k1*combination(x1,2)*combination(x2,1) : 0;
    double a2 = (x1>=1 && x3>=2) ? k2*combination(x1,1)*combination(x3,2) : 0;
    double a3 = (x2>=1 && x3>=1) ? k3*combination(x2,1)*combination(x3,1) : 0;//ternary operator so fancy

    double p1=a1/(a1+a2+a3);
    double p2=a2/(a1+a2+a3);
    double p3=a3/(a1+a2+a3);

    double r=(double)rand()/RAND_MAX;
    
    if(r<=p1&&(x1>=2)&&(x2>=1)){
        x1-=2;
        x2-=1;
        x3+=4;
    }
    else if(p1<r && r<=(p1+p2)&&(x1>=1)&&(x3>=2)){
        x1-=1;
        x3-=2;
        x2+=3;
    }
    else if(r>(p1+p2)&&(x2>=1)&&(x3>=1)){
        x2-=1;
        x3-=1;
        x1+=2;        
    }
}
void one_sim(int &x1, int &x2, int &x3){
    x1=9;
    x2=8;
    x3=7;
    
    double k1=1.0;
    double k2=2.0;
    double k3=3.0;

    int i=0;

    while(i<steps){
        fire_reaction(x1,x2,x3,k1,k2,k3);
        i++;
    }
}
void final_sim(void){
    int x1,x2,x3;
    double X1[SIZE];
    double X2[SIZE];
    double X3[SIZE];
    for(int i=0; i<SIZE; i++){
        X1[i]=0;
        X2[i]=0;
        X3[i]=0;
    }

    int i=0;
    while(i<maxi){
        one_sim(x1,x2,x3);
        X1[x1]++;
        X2[x2]++;
        X3[x3]++;
    i++;
    }
    //continue fuction to normalize
    for(int i=0; i<SIZE; i++){
        X1[i]=X1[i]/(double)maxi;
        X2[i]=X2[i]/(double)maxi;
        X3[i]=X3[i]/(double)maxi;
    }
    //now Xn[i] should be PMF

    double mean1 = 0;
    double mean2 = 0;
    double mean3 = 0;

    for(int i=0; i<SIZE; i++){
        mean1 += i * X1[i];
        mean2 += i * X2[i];
        mean3 += i * X3[i];
    }

    double second1 = 0;
    double second2 = 0;
    double second3 = 0;

    for(int i=0; i<SIZE; i++){
        second1 += i*i * X1[i];
        second2 += i*i * X2[i];
        second3 += i*i * X3[i];
    }

    double var1 = second1 - mean1*mean1;
    double var2 = second2 - mean2*mean2;
    double var3 = second3 - mean3*mean3;

    cout << "X1: Mean = " << mean1 << ", Variance = " << var1 << endl;
    cout << "X2: Mean = " << mean2 << ", Variance = " << var2 << endl;
    cout << "X3: Mean = " << mean3 << ", Variance = " << var3 << endl;
}


int main(void){
    srand(time(0));

    
    final_sim();
   
    return 0;
}

// X1: Mean = 5.83479, Variance = 5.89743
// X2: Mean = 12.4974, Variance = 8.93808
// X3: Mean = 7.80336, Variance = 8.93605