#include <iostream>
#include <cstring>

using namespace std;

class Ekipa {
    char ime[50];
    char grad[50];
    char stadion[50];
public:
    Ekipa(char *ime = "imae", char *grad = "grad", char *stadion = "stadion") {
        strcpy(this->ime, ime);
        strcpy(this->grad, grad);
        strcpy(this->stadion, stadion);
    }

    Ekipa(const Ekipa &other) {
        strcpy(this->ime, other.ime);
        strcpy(this->grad, other.grad);
        strcpy(this->stadion, other.stadion);
    }

    ~Ekipa() {
    }

    void setIme(char *ime) {
        strcpy(this->ime, ime);

    }

    void setGrad(char *grad) {
        strcpy(this->grad, grad);

    }

    void setStadion(char *stadion) {
        strcpy(this->stadion, stadion);

    }

    const char *getIme() const {
        return ime;
    }

    const char *getGrad() const {
        return grad;
    }

    const char *getStadion() const {
        return stadion;
    }

    void print() {
        cout << ime << " " << grad << " " << stadion << endl;
    }
};

class Natprevar {
    Ekipa *domakin;
    Ekipa *gostin;
    int golD;
    int golG;
public:
    Natprevar(Ekipa &domakin, Ekipa &gostin, int golD = 0, int golG = 0) {
        this->golD = golD;
        this->golG = golG;
        this->domakin = new Ekipa(domakin);
        this->gostin = new Ekipa(gostin);
    }

    Natprevar(const Natprevar &other) {
        this->golD = other.golD;
        this->golG = other.golG;
        this->domakin = new Ekipa(*other.domakin);
        this->gostin = new Ekipa(*other.gostin);
    }

    Ekipa *getDomakin() const {
        return domakin;
    }

    void setDomakin(Ekipa *domakin) {
        Natprevar::domakin = domakin;
    }

    Ekipa *getGostin() const {
        return gostin;
    }

    void setGostin(Ekipa *gostin) {
        Natprevar::gostin = gostin;
    }

    int getGolD() const {
        return golD;
    }

    void setGolD(int golD) {
        Natprevar::golD = golD;
    }

    int getGolG() const {
        return golG;
    }

    void setGolG(int golG) {
        Natprevar::golG = golG;
    }

    bool isTip(Natprevar natprevar, char tip);
};

bool isTip(Natprevar natprevar, char tip) {
    if ((natprevar.getGolD() == natprevar.getGolG()) && tip == 'X')
        return true;
    if ((natprevar.getGolD() > natprevar.getGolG()) && tip == '1')
        return true;
    if ((natprevar.getGolD() < natprevar.getGolG()) && tip == '2')
        return true;
    return false;
}

int main() {
//    char tip;
//    Ekipa ekipa1("Real", "Madrin", "Sant. Ber.");
//    Ekipa ekipa2("Barca", "Barselona", "Cam nou");
//    Natprevar first(ekipa1, ekipa2, 1, 3);
//    cin >> tip;
//    if (isTip(first, tip)) {
//        cout << "Pogodok";
//    } else {
//        cout << "Gresen tip";
//    }
    int n;
    cin>>n;
    Ekipa *ekipi = new Ekipa [n];
    char name[20], city[20], stadium[20];
    for (int i = 0; i < n; ++i) {
        cin>>name>>city>>stadium;
        ekipi[i]=Ekipa(name,city,stadium);
    }
    for (int i = 0; i < n; ++i) {
        cout<<ekipi[i].getIme()<<" "<<ekipi[i].getGrad()<<" "<<ekipi[i].getStadion()<<endl;
    }
    delete [] ekipi;
    return 0;
}