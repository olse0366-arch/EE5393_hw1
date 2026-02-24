//EE5393
//Aaron Olsen
//hw1p3
//olse0366@umn.edu

#include <iostream>
using namespace std;
//c version of 2^x for x<=0
//as a general rule, the rate of a reaction determines its
//order or precidence within an interative loop
//However, it is not absolute, and depending on context,
//it can be coded in disagrance to this order.
//This simulation is deterministic, but very true to the 
//concepts and ideas of CRNs


int exp_2(int x){   //ideal non-crn computation
    int y=1;
    while(x){
        y=2*y;
        x--;
    }
    return y;
}
int log_2(int x){   //ideal non-crn computation
    int y=0;
    while(x!=1){
        x=x/2;
        y++;
    }
    return y;
}
int simulate_log2(int Y0){
    //1 B -> A + B                slowest
    //2 A + 2Y -> C + Y' + A      fastest
    //3 2C -> C                   fastest
    //4 A -> ∅                    fast
    //5 Y' -> Y                   medium
    //6 C -> W                    medium
    if(Y0<=0){
        cout << "Domain Error" << endl;
        return -1;
    }
    int Y=Y0,Yp=0,A=0,C=0,W=0;
    int B=1;              // B is a small nonzero catalyst species.
    A=B;                  // Reaction (1): B produces A, which enables halving cycles.
    while(A==1){          // As long as A exists, halving continues.
        while(Y>=2){      // accounts for reaction (2)
            Y-=2;         // two Y are consumed
            Yp++;         // one Y' produced
            C++;          // one C produced
        }
        while(C>=2){C--;} // accounts for reaction (3): 2C -> C
                          // C is effectivly a flag for increasing output W(or X)
        if(Y==1){         // termination condition when Y cannot halve further
           // Y=0; //redundant and not in origrnal reactions
            A=0;          // accounts for reaction (4): A -> ∅
        }
        Y=Yp;Yp=0;        // accounts for reaction (5): Y' -> Y
        if(C==1){         // accounts for reaction (6): C -> W
            W++;
            C=0;
        }
    }
    return W;             // W accumulates once per halving → log2(Y0)
}
int simulate_multiply(int W0, int X0){
    //1 W -> D                slowest
    //2 D + X -> D + X' + Z   fastest
    //3 X' -> X               fast
    //4 D -> ∅                slow

    int W = W0;
    int X = X0;
    int Xp = 0;
    int Z = 0;
    int D = 1;  // controller species gets triggered by presence of of W
                // and is slightly slower than z generating reaction (2)
                // so as long as w input has molecules, D will be in supply.
                // The simulation doesn't numerically keep track of the amount
                // of D molecules but instead uses it as a logical flag.
    while (W > 0 && D == 1) {
        while (X > 0) { //accounts for reaction (2)
            X--;
            Xp++;
            Z++;
        }
        while (Xp > 0) {Xp--;X++;}  //accouns for reaction (3)
        W--;    //accounts for reaction (1)
        if (W == 0) {D=0;}  //accounts for (4)
    }
    return Z;
}
int simulate_exp2(int X0){
    //1 X -> E                slow
    //2 E + Y -> E + 2Y'      faster
    //3 Y' -> Y               fast
    //4 E -> ∅                medium
    int X = X0;
    int Y = 1;      // initial condition: Y starts at 1 so repeated doubling
                    // produces Y_inf = 2^X0
    int Yp = 0;
    int E = 0;      // controller species produced by X.
                    // Each X molecule generates one E which triggers
                    // a full doubling cycle of Y.
                    // E is consumed at the end of the cycle, so one
                    // doubling occurs per X molecule.
    while (X > 0) {
        X--;        // accounts for reaction (1): X -> E
        E++;        // produce controller species
        while (Y > 0) {     // accounts for reaction (2)
            Y--;            // each Y is converted
            Yp += 2;        // into two Y'
        }
        while (Yp > 0) {    // accounts for reaction (3)
            Yp--;
            Y++;            // restore Y after doubling
        }
        E--;        // accounts for reaction (4): E -> ∅
                    // completes one doubling cycle
    }
    return Y;
}

int main(void){
    int Y0;
    cout << "CRN Computation of Zinf=X0*log_2(Y0)" << endl;
    for(int X0=0; X0<5; X0++){
        for(int i=1; i<5; i++){
            Y0=exp_2(i);
            cout << "X0=" << X0 <<", Y0=" << Y0;
            cout << ", X0*log_2(Y0)=";
            cout << simulate_multiply(simulate_log2(Y0),X0)<<endl;
        }
    }
    cout << endl;
    int X0;
    cout << "CRN Computation of Yinf=2^log_2(X0)" << endl;
    for(int i=1; i<11; i++){
        X0=exp_2(i);//this to get good interger values for input and output of log fucnction
        cout << "X0=" << X0 <<", 2^log_2(X0)=";
        cout << simulate_exp2(simulate_log2(X0)) << endl;   
    }

    cout << endl << "Please appericate my program this took"
    <<"way too long to make"<<endl;

    return 0;
}

//console output
// C:\Users\aaron\Documents\EE5393>.\hw1_3
// CRN Computation of Zinf=X0*log_2(Y0)
// X0=0, Y0=2, X0*log_2(Y0)=0
// X0=0, Y0=4, X0*log_2(Y0)=0
// X0=0, Y0=8, X0*log_2(Y0)=0
// X0=0, Y0=16, X0*log_2(Y0)=0
// X0=1, Y0=2, X0*log_2(Y0)=1
// X0=1, Y0=4, X0*log_2(Y0)=2
// X0=1, Y0=8, X0*log_2(Y0)=3
// X0=1, Y0=16, X0*log_2(Y0)=4
// X0=2, Y0=2, X0*log_2(Y0)=2
// X0=2, Y0=4, X0*log_2(Y0)=4
// X0=2, Y0=8, X0*log_2(Y0)=6
// X0=2, Y0=16, X0*log_2(Y0)=8
// X0=3, Y0=2, X0*log_2(Y0)=3
// X0=3, Y0=4, X0*log_2(Y0)=6
// X0=3, Y0=8, X0*log_2(Y0)=9
// X0=3, Y0=16, X0*log_2(Y0)=12
// X0=4, Y0=2, X0*log_2(Y0)=4
// X0=4, Y0=4, X0*log_2(Y0)=8
// X0=4, Y0=8, X0*log_2(Y0)=12
// X0=4, Y0=16, X0*log_2(Y0)=16

// CRN Computation of Yinf=2^log_2(X0)
// X0=2, 2^log_2(X0)=2
// X0=4, 2^log_2(X0)=4
// X0=8, 2^log_2(X0)=8
// X0=16, 2^log_2(X0)=16
// X0=32, 2^log_2(X0)=32
// X0=64, 2^log_2(X0)=64
// X0=128, 2^log_2(X0)=128
// X0=256, 2^log_2(X0)=256
// X0=512, 2^log_2(X0)=512
// X0=1024, 2^log_2(X0)=1024

// Please appericate my program this tookway too long to make