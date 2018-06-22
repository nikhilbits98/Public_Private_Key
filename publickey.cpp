#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<string>

using namespace std;

unsigned long prime(unsigned long random){
    int flag = 1;
    for(int i = 2; i < random/2 && flag == 1; i++){
        if(random%i == 0){
            flag = 0;
            break;
        }
    }
    if(flag == 1){
        return random;
    }
    return prime(random+1);
}

unsigned long primeGen(int size){
    srand(0);
    unsigned long random = size + rand()%size;
    int flag = 1;    
    for(int i = 2; i < size && flag == 1; i++){
        if(random%i == 0){
            flag = 0;
            break;
        }
    }
    if(flag == 1){
        return random;
    }
    return prime(random+1);
}

int main(){
    string msg;
    unsigned long p,q,d,e,n, totient;
    int ms[10];
    //int opms[300];
    unsigned long long data = 0;
    cout<<"Enter String of max length 4 to be encrypted:  ";
    getline(cin,msg);    
    unsigned int length = msg.length();

    for(int i = 0; i< msg.length();i++){
        ms[i] = msg[i] -'a' + 1;
        data = data*100 + ms[i];
    }
    cout<<"String in Int format: "<<data<<endl;

    p = primeGen(2*data);
    cout<<"Prime #1: "<<p<<endl;
    
    q = primeGen(5*data);
    cout<<"Prime #2: "<<q<<endl;

    n = p*q;
    totient = (p-1)*(q-1);
               
    for(unsigned long j = 2;j<totient;j++){
        if(totient%j == 0)
            continue;
        else{
            e = j;
            break;
        }
    }
    cout<<"Public Key is: ( "<<n<<","<<e<<" )"<<endl;
    
    for(int j = 2;;j++){
        if((j*e) % totient == 1){
            d = j;
            break;
        }
    }
    cout<<"Private Key is: ( "<<n<<","<<d<<" )"<<endl;


    unsigned long long crypt = data;
    for(int i = 1; i < e ; i++){
        crypt = crypt*data;
        crypt = crypt % n;
    }
    cout<<"Encrypted string is: "<<crypt<<endl;

    unsigned long long decrypt = crypt;
    for(int i = 1; i<d; i++){
        decrypt = decrypt*crypt;
        decrypt = decrypt%n;
    }
    cout<<"Decrypted string is: "<<decrypt<<endl;

    unsigned long long temp = decrypt;
    int count = 0;
    while(temp>0){
        temp = temp/10;
        count++;
    }

    int dmsg[10];
    temp = decrypt;
    for(int i = 0; i<=(count/2) ; i++){
        int index = (count/2) - i;
        int tmp = temp%100;
        temp = temp/100;
        dmsg[index] = tmp + 'a' -1;
    }

    cout<<"Decrypted message is: ";
    for(int i = 0; i <=count/2; i++){
        printf("%c",dmsg[i]);
    }
    cout<<endl;

    /*for(int i = 0;i<length ; i++){
        int index = 3*i;
        if(ms[i] < 10){
            opms[index] = 0;
            opms[index+1] = 0;
            opms[index+2] = ms[i];
        }
        else if(ms[i]<100){
            opms[index] = 0;
            opms[index+1] = ms[i] /10;
            opms[index+2] = ms[i] % 10;
        }
        else{
            opms[index] = ms[i] /100;
            opms[index+1] = ms[i] /10;
            opms[index+2] = ms[i] % 10;
        }
    }*/
    return 0;
}