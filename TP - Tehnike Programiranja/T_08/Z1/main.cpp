//TP 2021/2022: LV 8, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>


struct Vrijeme{
    int sati,minute,sekunde;
};

void TestirajVrijeme(Vrijeme x){
    if(x.sati>24 || x.sati<0 || x.minute>59 || x. minute<0 || x.sekunde>59 || x.sekunde<0 || (x.sati==24 && (x.minute>0 || x.sekunde>0)))
    throw std::domain_error("Neispravno vrijeme");
}

void IspisiVrijeme(Vrijeme x){
    try{
        TestirajVrijeme(x);
    }
    catch(...){
        throw;
    }
    if(x.sati<10) std::cout<<"0"; std::cout<<x.sati<<":";
    if(x.minute<10) std::cout<<"0"; std::cout<<x.minute<<":";
    if(x.sekunde<10) std::cout<<"0"; std::cout<<x.sekunde<<std::endl;
}

Vrijeme SaberiVrijeme(Vrijeme x, Vrijeme y){
    try{
        TestirajVrijeme(x); TestirajVrijeme(y);
    }
    catch(...){
        throw;
    }
    Vrijeme z;
    z.sekunde=x.sekunde+y.sekunde,z.minute=x.minute+y.minute,z.sati=x.sati+y.sati;
    while(z.sekunde-60>=0){
        z.sekunde-=60;
        z.minute++;
    } 
    while(z.minute-60>=0){
        z.minute-=60;
        z.sati++;
        if(z.sati>=24) z.sati-=24;
    }
    return z;
}

int main ()
{
    Vrijeme t1,t2,t3;
    try{
        std::cout<<"Unesite prvo vrijeme (h m s): "; std::cin>>t1.sati>>t1.minute>>t1.sekunde;
        TestirajVrijeme(t1);
    }
    catch(std::domain_error error){
        std::cout<<error.what();
        return 0;
    }
    
    try{
        std::cout<<"Unesite drugo vrijeme (h m s): "; std::cin>>t2.sati>>t2.minute>>t2.sekunde;
        TestirajVrijeme(t2);
    }
    catch(std::domain_error error){
        std::cout<<error.what();
        return 0;
    }

    try{
        t3=SaberiVrijeme(t1,t2);
        TestirajVrijeme(t3);
    }
    catch(std::domain_error error){
        std::cout<<error.what();
        return 0;
    }
    
    std::cout<<"Prvo vrijeme: "; IspisiVrijeme(t1);
    std::cout<<"Drugo vrijeme: "; IspisiVrijeme(t2);
    std::cout<<"Zbir vremena: "; IspisiVrijeme(t3);
	return 0;
}
