//Да се напише класа која опишува една e-mail порака. Во класата треба да се
//имплементира метод за прикажување на целокупната порака на екран. Потоа
//да се напише главна програма во која се внесуваат параметрите на пораката, се
//инстанцира објект од оваа класа и се печати на екран неговата содржина. За
//проверување на валидноста на e-mail пораката (постоење на знакот @ во
//адресата) да се напише соодветна функција.

#include <iostream>
#include <cstring>

using namespace std;

class EmailMassage {
private:
    char sender[50];
    char receiver[50];
    char subject[50];
    char body[350];
public:
    EmailMassage(char *_sender, char *_receiver, char *_subject, char *_body) {
        strcpy(sender, _sender);
        strcpy(receiver, _receiver);
        strcpy(subject, _subject);
        strcpy(body, _body);
    }

    void show() {
        cout << "From    :\t" << sender << endl;
        cout << "To      :\t" << receiver << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "Subject:\t" << subject << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "Body: " << body << endl;
        cout << "ENDS";
    }

};

bool valid(char mail[50]) {
//    char *ptr = strstr(mail, "@");        //votr nacin
//    if (ptr == nullptr){
//        return false;
//    }else{
//        return strstr(ptr, ".");
//    }
    int idx = -1;
    for (int i = 0; i < strlen(mail); ++i) {
        if (mail[i] == '@')
            idx = i;
    }
    if (idx == -1) {
        return false;
    } else {
        for (int i = idx; i < strlen(mail); ++i) {
            if (mail[i] == '.') {
                return true;
            }
        }
        return false;
    }
}

int main() {
    char sender[50];
    char receiver[50];
    char subject[50];
    char body[350];
    char garbage;
    cin >> sender >> receiver;
    if (!valid(sender) || !valid(receiver)) {
        cout << "Invalid e-mail";
        return -1;
    }
    cin>>garbage;
    cin.getline(subject, 500);
    cin.getline(body, 350);
    EmailMassage emailMassage(sender, receiver, subject, body);
    emailMassage.show();
    return 0;
}