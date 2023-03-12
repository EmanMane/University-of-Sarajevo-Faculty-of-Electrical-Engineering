//TP 2016/2017: Tutorijal 1, Zadatak 2
#include <iostream>
#include <cmath>
#include <math.h>
int main ()
{
    std::cout<<"Unesite tri broja: ";
    double a,b,c;
    std::cin>>a>>b>>c;
    if(a<=0 || b<=0 || c<=0 || a+c<=b || a+b<=c || b+c<=a) goto ende;

    double O; O=a+b+c;
    double s; s=O/2;
    double P; P=std::sqrt(s*(s-a)*(s-b)*(s-c));

    double alfa,beta,gama;
    alfa=std::acos((c*c-a*a-b*b)/((-1)*2*a*b));
    beta=std::acos((a*a-c*c-b*b)/((-1)*2*c*b));
    gama=std::acos((b*b-a*a-c*c)/((-1)*2*a*c));

    double umin;
    if(alfa<=beta && alfa<=gama) umin=alfa;
    else if(beta<=alfa && beta<=gama) umin=beta;
    else umin=gama;
    umin*=180/(4*std::atan(1));
    
    int step,min,sec;
    step=umin;
    min=(umin-step)*60;
    sec=(umin-step-(double)min/60)*3600;

    std::cout<<"Obim trougla sa duzinama stranica "<<a<<", "<<b<<" i "<<c<<" iznosi "<<O<<".\n";
    std::cout<<"Njegova povrsina iznosi "<<P<<".\n";
    std::cout<<"Njegov najmanji ugao ima "<<step<<" stepeni, "<<min<<" minuta i "<<sec<<" sekundi.";
    return 0;
    ende:
    std::cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!";
	return 0;
}