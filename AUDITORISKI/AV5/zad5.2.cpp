#include <iostream>
#include <cstring>

using namespace std;

class WebPage {
private:
    char url[100];
    char *content;
public:
    WebPage(char *url = "", char *content = "") {
        strcpy(this->url, url);
        this->content = new char[strlen(content) + 1];
        strcpy(this->content, content);
    }

    WebPage(const WebPage &other) {
        strcpy(this->url, other.url);
        this->content = new char[strlen(other.content) + 1];
        strcpy(this->content, other.content);
    }

    WebPage &operator=(const WebPage &other) {
        if (this != &other) {
            delete[] content;
            strcpy(this->url, other.url);
            this->content = new char[strlen(other.content) + 1];
            strcpy(this->content, other.content);
        }
        return *this;
    }

    ~WebPage() {
        delete[] content;
    }

    bool daliSeIsti(WebPage p) {
        return !(strcmp(url, p.url));
    }

    const char *getUrl() const {
        return url;
    }

    char *getContent() const {
        return content;
    }
};

class WebServer {
private:
    char name[30];
    int number;
    WebPage *pages;
public:
    WebServer(char *name = "", int number = 0, WebPage *pages = 0) {
        strcpy(this->name, name);
        this->number = number;
        this->pages = new WebPage[number];
        for (int i = 0; i < number; ++i) {
            this->pages[i] = pages[i];
        }
    }

    WebServer(const WebServer &other) {
        strcpy(this->name, other.name);
        this->number = other.number;
        this->pages = new WebPage[other.number];
        for (int i = 0; i < number; ++i) {
            this->pages[i] = other.pages[i];
        }
    }

    WebServer &operator=(const WebServer &other) {
        if (this != &other) {
            delete[] pages;
            strcpy(this->name, other.name);
            this->number = other.number;
            pages = new WebPage[other.number];
        }
        return *this;
    }

    ~WebServer() {
        delete[] pages;
    }

    void addPage(WebPage p) {
        for (int i = 0; i < number; ++i) {
            if (pages[i].daliSeIsti(p)) {
                return;
            }
        }
        WebPage *tmp = new WebPage[number + 1];
        for (int i = 0; i < number; ++i) {
            tmp[i] = pages[i];
        }
        tmp[number++] = p;
        delete[] pages;
        pages = tmp;
    }

    void listPages() {
        for (int i = 0; i < number; ++i) {
            cout<<pages[i].getUrl()<<" "<<pages[i].getContent()<<endl;
        }
    }

    void deletePage(WebPage p) {
        int flag = 0;
        for (int i = 0; i < number; ++i) {
            if (pages[i].daliSeIsti(p)) {
                flag++;
            }
        }
        if (!flag) {
            return;
        }
        WebPage *tmp = new WebPage[number - flag];
        int j = 0;
        for (int i = 0; i < number; ++i) {
            if (!pages[i].daliSeIsti(p)) {
                tmp[j] = pages[i];
                j++;
            }
        }
        number -= flag;
        delete[] pages;
        pages = tmp;
    }
};

int main() {
    WebPage wp1("http://www.google.com", "The search engine");
    WebPage wp2("http://www.finki.ukim.mk", "FINKI");
    WebPage wp3("http://www.time.mk", "Site vesti");

    WebServer ws(" Server ");

    ws.addPage(wp1);
    ws.addPage(wp2);
    ws.addPage(wp3);

    ws.listPages();

    cout << "\nAfter delete: \n";
    ws.deletePage(wp3);

    ws.listPages();

    return 0;
}