#include <iostream>
using namespace std;

int main()
{
    int n;
    cout<<"Kac iterasyon devam etsin?";
    cin>>n;

    //Başlangic durumu, hicbir bilgimiz yok
    double bel[n+1][2]; //belief
    bel[0][0] = 0.5; 
    bel[0][1] = 0.5;    

    double zx[4];
    cout<<"P(Z_t=acik algila|X_t=acik) = ";
    cin>>zx[0];
    cout<<"P(Z_t=kapali algila|X_t=acik) = ";
    cin>>zx[1];
    cout<<"P(Z_t=acik algila|X_t=kapali) = ";
    cin>>zx[2];
    cout<<"P(Z_t=kapali algila|X_t=kapali) = ";
    cin>>zx[3];

    //Robot kapiyi iterse
    double xuitx[4];
    cout<<"P(X_t=acik|U_t=it, X_t-1=acik) = ";
    cin>>xuitx[0];
    cout<<"P(X_t=kapali|U_t=it, X_t-1=acik) = ";
    cin>>xuitx[1];
    cout<<"P(X_t=acik|U_t=it, X_t-1=kapali) = ";
    cin>>xuitx[2];
    cout<<"P(X_t=kapali|U_t=it, X_t-1=kapali) = ";
    cin>>xuitx[3];

    //Robot kapiyi itmediğinde
    double xuitmex[4];
    cout<<"Asagiya 1 0 0 1 degerlerini de verebilirsiniz.\n";
    cout<<"P(X_t = acik | U_t = itme, X_t-1 = acik) = ";
    cin>>xuitmex[0];
    cout<<"P(X_t = kapali | U_t = itme, X_t-1 = acik) = ";
    cin>>xuitmex[1];
    cout<<"P(X_t = acik | U_t = itme, X_t-1 = kapali) = ";
    cin>>xuitmex[2];
    cout<<"P(X_t = kapali | U_t = itme, X_t-1 = kapali) = ";
    cin>>xuitmex[3];

    double bel_hat[n][2];
    for(int i = 0; i<n; i++)
    {
        cout << "\nu_"<<i<<" icin\n";
        cout << "It/itme (1/0)?: ";
        int push;
        cin >> push;
        //Tahmin
        for(int j=0; j<2; j++)
        {  
            if(j==0) {
                //j==0 için açık, j==1 için kapalı anlamına geliyor.
                if(push == 1){ //u = it      bel(x_0=açık)              bel(x_0=kapalı)
                    bel_hat[i][j] = xuitx[0]*bel[i][0]      +  xuitx[2]*bel[i][1];
                } else { //u = itme
                    //                         bel(x_0=açık)              bel(x_0=kapalı)
                    bel_hat[i][j] = xuitmex[0]*bel[i][0]    +  xuitmex[2]*bel[i][1]; 
                }
            } else {
                //j==0 için açık, j==1 için kapalı anlamına geliyor.
                if(push == 1){ //u = it      bel(x_0=açık)              bel(x_0=kapalı)
                    bel_hat[i][j] = xuitx[1]*bel[i][0]      +  xuitx[3]*bel[i][1];
                } else { //u = itme
                    //                         bel(x_0=açık)              bel(x_0=kapalı)
                    bel_hat[i][j] = xuitmex[1]*bel[i][0]    +  xuitmex[3]*bel[i][1]; 
                }
            } 
        }
        //Ölcüm güncelleme
        double mu=1;
        cout << "z_"<<i+1<<" icin\n";
        cout << "Acik/Kapali algila (1/0)?: ";
        int acikKapali;
        cin >> acikKapali;
        for(int j=0; j<2; j++)
        {
            if(j==0) {
                if(acikKapali == 1){ //z = acik algila
                    bel[i+1][j] = mu*zx[0]*bel_hat[i][j];
                } else { //z = kapali algila
                    bel[i+1][j] = mu*zx[1]*bel_hat[i][j];
                }
            } else {
                if(acikKapali == 1){ //z = acik algila
                    bel[i+1][j] = mu*zx[2]*bel_hat[i][j];
                } else { //z = kapali algila
                    bel[i+1][j] = mu*zx[3]*bel_hat[i][j];
                }
            }
        }
        mu=1/(bel[i+1][0]+bel[i+1][1]);
        cout<<"mu: "<<mu;
        //cout<<"\nBel(X_"<<i<<" = açık): "<<bel[0][0];
        //cout<<"\nBel(X_"<<i<<" = kapalı): "<<bel[0][1];
        bel[i+1][0] = mu*bel[i+1][0];
        bel[i+1][1] = mu*bel[i+1][1];
        cout<<"\nBel(X_"<<i+1<<" = acik): "<<bel[i+1][0];
        cout<<"\nBel(X_"<<i+1<<" = kapali): "<<bel[i+1][1];
    }
    return 0;
}