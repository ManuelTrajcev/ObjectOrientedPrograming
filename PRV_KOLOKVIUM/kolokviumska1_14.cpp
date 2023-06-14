#include<iostream>
#include<cstring>

using namespace std;

enum Extension {
    pdf, txt, exe
};
const char *extName[3] = {"pdf", "txt", "exe"};

class File {
private:
    char *nameFile;
    Extension ext;
    char *nameOwner;
    int size;
public:
    File(char *nameFile = "", char *nameOwner = "", int size = 0, Extension ext = txt) {
        this->size = size;
        this->ext = ext;
        this->nameFile = new char[strlen(nameFile) + 1];
        this->nameOwner = new char[strlen(nameOwner) + 1];
        strcpy(this->nameOwner, nameOwner);
        strcpy(this->nameFile, nameFile);
    }

    File(const File &other) {
        this->size = other.size;
        this->ext = other.ext;
        this->nameFile = new char[strlen(other.nameFile) + 1];
        this->nameOwner = new char[strlen(other.nameOwner) + 1];
        strcpy(this->nameOwner, other.nameOwner);
        strcpy(this->nameFile, other.nameFile);
    }

    File &operator=(const File &other) {
        if (this != &other) {
            this->size = other.size;
            this->ext = other.ext;
            delete[] nameFile;
            delete[] nameOwner;
            this->nameFile = new char[strlen(other.nameFile) + 1];
            this->nameOwner = new char[strlen(other.nameOwner) + 1];
            strcpy(this->nameOwner, other.nameOwner);
            strcpy(this->nameFile, other.nameFile);
        }
        return *this;
    }

    ~File() {
        delete[] nameFile;
        delete[] nameOwner;
    }

    void print() {
        cout << "File name: " << nameFile << "." << extName[ext] << endl;
        cout << "File owner: " << nameOwner << endl;
        cout << "File size: " << size << endl;
    }

    bool equals(const File &that) {
        if (this->ext == that.ext) {
            if (strcmp(this->nameFile, that.nameFile) == 0)
                if (strcmp(that.nameOwner, that.nameOwner) == 0)
                    return true;
        }
        return false;
    }

    bool equalsType(const File &that) {
        if (this->ext == that.ext) {
            if (strcmp(that.nameFile, that.nameFile) == 0)
                return true;
        }
        return false;
    }
};

class Folder {
private:
    char *nameFolder;
    int n;
    File *files;
public:
    Folder(char *nameFolder) {
        this->n = 0;
        this->files = nullptr;
        this->nameFolder = new char[strlen(nameFolder) + 1];
        strcpy(this->nameFolder, nameFolder);
    }

    Folder(const Folder &other) {
        this->n = other.n;
        this->nameFolder = new char[strlen(other.nameFolder) + 1];
        strcpy(this->nameFolder, other.nameFolder);
        for (int i = 0; i < n; ++i) {
            this->files[i] = files[i];
        }
    }

    Folder &operator=(const Folder &other) {
        if (this != &other) {
            this->n = other.n;
            delete[] this->nameFolder;
            delete[] this->files;
            this->nameFolder = new char[strlen(other.nameFolder) + 1];
            strcpy(this->nameFolder, other.nameFolder);
            for (int i = 0; i < n; ++i) {
                this->files[i] = files[i];
            }
        }
        return *this;
    }

    ~Folder() {
        delete[] this->nameFolder;
        delete[] this->files;
    }

    void print() {
        cout << "Folder name: " << nameFolder << endl;
        for (int i = 0; i < n; ++i) {
            files[i].print();
        }
    }

    void remove(const File &file) {
        File *tmp = new File[n - 1];
        int count = 0, index;
        for (int i = 0; i < n; ++i) {
            if (files[i].equals(file)) {
                index = i;
                break;
            }
        }
        for (int j = 0; j < n; ++j) {
            if (index != j) {
                tmp[count] = files[j];
                count++;
            }
        }
        delete[] files;
        files = tmp;
        n--;
    }

    void add(const File &file) {
        File *tmp = new File[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = files[i];
        }
        tmp[n] = file;
        n++;
        delete[] files;
        files = tmp;
    }
};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    } else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    } else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    } else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    } else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}