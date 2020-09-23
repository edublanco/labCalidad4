
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>

using namespace std;
const long double PI = 3.14159265358979323846;
class Calculo{

private:

 long double pAbajo(long double dof){
   //cout <<"pAbajo dof: " <<dof<< "\n";
   long double aux1 = pow((dof*PI),0.5);
   long double aux3 = dof/2.0;

   long double aux2 = tgamma(aux3);

   return (pow((dof*PI),0.5))* aux2;
 }


 long double pArriba(long double dof){
     //cout <<"pArriba: " <<tgamma((dof+1)/2.0) << "\n";
     //cout <<"gamma " <<gamma(dof/2)<< "\n";
    return tgamma((dof+1)/2);
 }

long double pDerecha(long double x,long double dof){
    //cout <<"pDer en metodo: " <<pow((1+((pow(x,2))/dof)),-((dof+1)/2))<< "\n";
    //cout<<"w: "<<x<<"\n";
    long double aux1 =(1+((pow(x,2))/dof));
    //long double aux2 =-((dof+1)/2);
    //cout<<"aux1: "<<aux1<<"\n";
    return pow((1+((pow(x,2))/dof)),-((dof+1)/2));

 }

public:

    long double simpson(long double x, long double dof, long double num_seg){
        long double p1 =0;
        long double p2 =0;

        long double w = x / num_seg;
        //cout<<"w: "<<w<<"\n";
        long double i =1;
        while(i<= (num_seg - 1 )){
            long double f = ((pArriba(dof)/pAbajo(dof))*pDerecha((w*i),dof));
            //long double p1aux = 4.0*f*(w/3);
            //cout <<"p1 individual: " <<p1aux << "\n";
            p1 += 4.0*f*(w/3);
            //cout <<"f: " << ((pArriba(dof)/pAbajo(dof))*pDerecha((w*i),dof))<< "\n";
            //cout <<"p1: " <<p1<< "\n";
             //cout <<"contador: " <<i/2 << "\n";
            i += 2.0;
        }
        long double j =2;

        while(j<= (num_seg - 2 )){
            long double f = ((pArriba(dof)/pAbajo(dof))*pDerecha((w*j),dof));
            //long double p2aux = 2.0*f*(w/3);
            //cout <<"p2 individual: " <<p2aux << "\n";
            p2 +=2.0*f*(w/3);
           // cout <<"contador: " <<j/2 << "\n";
            j += 2;

        }
       // exit(0);
        return (((w/3)*((pArriba(dof)/pAbajo(dof))*pDerecha(0, dof))) + p1 + p2 + ((w/3)*((pArriba(dof)/pAbajo(dof))*pDerecha(x, dof))));

    }

};

class Respuesta{
//.d=10
//.m=4
    public:

        void resultados(long double x, long double dof, long double p){
                float fx = (float) x;
                printf("x = %.5f \n", fx);
                cout << "dof: " <<dof <<setprecision(5)<< "\n";
                float px = (float) p;
                printf("p = %.5f \n", px);
               /* cout << "x: " << x <<setprecision(5) << "\n";
                cout << "dof: " <<dof <<setprecision(5)<< "\n";
                cout << "p: " <<p  <<setprecision(5)<< "\n";*/
        }


};

//.b=86

//.d=18
//.m=5
int main (){


long double dof =0;
long double x =0;
long double  E = 0.0000001;
long double num_seg = 10;
long double p =1;
long double r1 = 0;
long double r2 = 0;
long double oldR = 0;

cin >> x;
cin >> dof;
Calculo calculo;
Respuesta respuesta;

if( !(x > 0 || dof > 0) ){
     cout <<"-----datos incorrecto ---------"<< "\n";
     exit(0);
}




while(p > E){
    if(r1== 0){
       r1 = calculo.simpson(x,dof, num_seg);
    }
    cout <<"r1 en el while: "<< r1 << "\n";
    num_seg = num_seg*2;


    r2 = calculo.simpson(x,dof, num_seg);

    cout <<"r2 en el while: " <<r2 << "\n";
    p = r1 - r2;
    //p = abs(p);
    cout <<"p en el while: " <<p << "\n";
    r1 = p;
    oldR = r2;


}




respuesta.resultados(x, dof, oldR);


}
