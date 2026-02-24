#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define maxi 1e5
#define maxr 1e6

long long combination(int n, int k){
    long long result = 1;
    for(int i = 1; i <= k; i++)
    {
        result = result * (n - k + i) / i;
    }
    return result;
}

int end_cond_1(int x1){
    return (x1>=150);
}
int end_cond_2(int x2){
    return (x2<10);
}
int end_cond_3(int x3){
    return (x3>100);
}
int end_cond(int x1, int x2, int x3){
    if(end_cond_1(x1)){
        return 1;
    }
    else if(end_cond_2(x2)){
        return 2;
    }
    else if(end_cond_3(x3)){
        return 3;
    }
    else{ 
        return 0;} 
}
void fire_reaction(int &x1,int &x2,int &x3, double k1, double k2, double k3){

    double a1=k1*combination(x1,2)*combination(x2,1);
    double a2=k2*combination(x1,1)*combination(x3,2);
    double a3=k3*combination(x2,1)*combination(x3,1);

    double p1=a1/(a1+a2+a3);
    double p2=a2/(a1+a2+a3);
    double p3=a3/(a1+a2+a3);

    double r=(double)rand()/RAND_MAX;
    //cout << r << endl;
    if(r<=p1){
        x1-=2;
        x2-=1;
        x3+=4;
    }
    else if(p1<r && r<=(p1+p2)){
        x1-=1;
        x3-=2;
        x2+=3;
    }
    else{
        x2-=1;
        x3-=1;
        x1+=2;        
    }
}
int one_sim(void){
    int x1=110;
    int x2=26;
    int x3=55;
    
    double k1=1.0;
    double k2=2.0;
    double k3=3.0;

    int max_reactions=maxr;

    int i=0;
    while(i<max_reactions){
        fire_reaction(x1,x2,x3,k1,k2,k3);
        if(end_cond(x1,x2,x3)){
            break;
        }
        //cout << i << endl;
        i++;
        if(i==max_reactions){
            cout <<"Warning: Reaction Uncomplete" << endl;
            return 0;
        }
    }
    return end_cond(x1,x2,x3);
}

void full_sim(void){
    int max_iterations=maxi;
    int c1=0,c2=0,c3=0;
    int incompletes=0;
    int result;
    for(int i=0; i<max_iterations;i++){
        result=one_sim();
        if(result==1){
        c1++;   
        cout << "C1 Incremented: " << c1 << endl;
        }
        if(result==2){
        c2++;
        cout << "C2 Incremented: " << c2 << endl;
        }
        if(result==3){
        c3++;
        cout << "C3 Incremented: " << c3 << endl;
        }
        if(result==0){
        incompletes++;
        }
    }
    cout << "Results of Simulation:" << endl;
    cout << "C1: " << c1 << endl;
    cout << "C2: " << c2 << endl;
    cout << "C3: " << c3 << endl;
    cout << "Nulls: " << incompletes << endl;
}


int main(void){
    srand(time(0));
    
    full_sim();
   
    return 0;
}
//Console Output
//
// Results of Simulation:
// C1: 0
// C2: 0
// C3: 100000
// Nulls: 0