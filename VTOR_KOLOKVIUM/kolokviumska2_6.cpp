#include <iostream>
#include <cstring>

using namespace std;

class ExistingGame {
private:

public:
    void show() {
        cout << "The game is already in the collection" << endl;
    }
};

class Game {
protected:
    char name[100];
    double price;
    bool onDiscount;
public:
    Game(const char *name = "", double price = 0, bool onDiscount = false) {
        this->price = price;
        this->onDiscount = onDiscount;
        strcpy(this->name, name);
    }

    friend ostream &operator<<(ostream &os, const Game &game) {
        os << "Game: " << game.name << ", regular price: $" << game.price;
        if (game.onDiscount) {
            os << ", bought on sale";
        }
        return os;
    }

    virtual void getNisto() {
    }

    friend istream &operator>>(istream &is, Game &game) {
        is.get();
        is.getline(game.name, 100);
        is >> game.price >> game.onDiscount;
        return is;
    }

    bool operator==(const Game &rhs) const {
        if (strcmp(this->name, rhs.name) == 0) {
            return true;
        } else {
            return false;
        }
    }

    double getPrice() const {
        return price;
    }

    bool isOnDiscount() const {
        return onDiscount;
    }
};

class SubscriptionGame : public Game {
private:
    double monthlyFee;
    int month;
    int year;
public:
    SubscriptionGame(const char *name = "", double price = 0, bool onDiscount = false, double monthlyFee = 0,
                     int month = 0, int year = 0) : Game(name,
                                                         price,
                                                         onDiscount),
                                                    monthlyFee(
                                                            monthlyFee),
                                                    month(month),
                                                    year(year) {

    }

    friend ostream &operator<<(ostream &os, const SubscriptionGame &game) {
        os << static_cast<const Game &>(game) << ", monthly fee: $" << game.monthlyFee << ", purchased: " << game.month
           << "-" << game.year;
        return os;
    }

    friend istream &operator>>(istream &is, SubscriptionGame &game) {
        is.get();
        is.getline(game.name, 100);
        is >> game.price >> game.onDiscount >> game.monthlyFee >> game.month >> game.year;
        return is;
    }

    void getNisto() {
    }

    double getMonthlyFee() const {
        return monthlyFee;
    }

    int getMonth() const {
        return month;
    }

    int getYear() const {
        return year;
    }
};

class User {
private:
    char userName[100];
    Game **games;
    int n;
public:
    User(const char *userName = "", Game **games = nullptr) {
        strcpy(this->userName, userName);
        this->n = 0;
    }

    User(const User &other) {
        strcpy(this->userName, other.userName);
        this->n = other.n;
        this->games = new Game *[n];
        for (int i = 0; i < n; ++i) {
            this->games[i] = games[i];
        }
    }

    User &operator=(const User &other) {
        if (this != &other) {
            strcpy(this->userName, other.userName);
            this->n = other.n;
            delete[] this->games;
            this->games = new Game *[n];
            for (int i = 0; i < n; ++i) {
                this->games[i] = games[i];
            }
        }
        return *this;
    }

    ~User() {
        delete[] this->games;
    }

    User &operator+=(Game &add) {
        for (int i = 0; i < n; ++i) {
            if (*games[i] == add) {
                throw ExistingGame();
            }
        }
        Game **tmp = new Game *[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = games[i];
        }
        tmp[n++] = &add;
        games = tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &os, User &user) {
        os << endl << "User: " << user.userName << endl;
        for (int i = 0; i < user.n; ++i) {
            SubscriptionGame *casted = dynamic_cast<SubscriptionGame *>(user.games[i]);
            if (casted) {
                os << "- " << *casted << endl;

            } else {
                os << "- " << *user.games[i] << endl;
            }
        }
        os << endl;
        return os;
    }

    int total_spent() {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            if (games[i]->isOnDiscount()) {
                sum += (games[i]->getPrice() * 0.7);
            } else {
                sum += games[i]->getPrice();
            }
            SubscriptionGame *casted = dynamic_cast<SubscriptionGame *>(games[i]);
            if (casted) {
                int current = 2018 * 12 + 5;
                int months = casted->getYear() * 12 + casted->getMonth();
                sum += (casted->getMonthlyFee() * (current - months));
            }
        }
        return sum;
    }
};

int main() {
    int test_case_num;

    cin >> test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1) {
        cout << "Testing class Game and operator<< for Game" << std::endl;
        cin.get();
        cin.getline(game_name, 100);
        //cin.get();
        cin >> game_price >> game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout << g;
    } else if (test_case_num == 2) {
        cout << "Testing class SubscriptionGame and operator<< for SubscritionGame" << std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin >> game_price >> game_on_sale;

        cin >> sub_game_monthly_fee;
        cin >> sub_game_month >> sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout << sg;
    } else if (test_case_num == 3) {
        cout << "Testing operator>> for Game" << std::endl;
        Game g;

        cin >> g;

        cout << g;
    } else if (test_case_num == 4) {
        cout << "Testing operator>> for SubscriptionGame" << std::endl;
        SubscriptionGame sg;

        cin >> sg;

        cout << sg;
    } else if (test_case_num == 5) {
        cout << "Testing class User and operator+= for User" << std::endl;
        cin.get();
        cin.getline(username, 100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >> num_user_games;

        //!!!

        for (int i = 0; i < num_user_games; ++i) {

            cin >> game_type;
            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1) {
                cin.get();
                cin.getline(game_name, 100);

                cin >> game_price >> game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            } else if (game_type == 2) {
                cin.get();
                cin.getline(game_name, 100);

                cin >> game_price >> game_on_sale;

                cin >> sub_game_monthly_fee;
                cin >> sub_game_month >> sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month,
                                         sub_game_year);
            }
            u += (*g);
        }

        cout << u;
    } else if (test_case_num == 6) {
        cout << "Testing exception ExistingGame for User" << std::endl;
        cin.get();
        cin.getline(username, 100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >> num_user_games;

        for (int i = 0; i < num_user_games; ++i) {

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1) {
                cin.get();
                cin.getline(game_name, 100);

                cin >> game_price >> game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            } else if (game_type == 2) {
                cin.get();
                cin.getline(game_name, 100);

                cin >> game_price >> game_on_sale;

                cin >> sub_game_monthly_fee;
                cin >> sub_game_month >> sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month,
                                         sub_game_year);
            }

            try {
                u += (*g);
            }
            catch (ExistingGame &ex) {
                ex.show();
            }
        }
        cout << u;
    } else if (test_case_num == 7) {
        cout << "Testing total_spent method() for User" << std::endl;
        cin.get();
        cin.getline(username, 100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >> num_user_games;

        for (int i = 0; i < num_user_games; ++i) {

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1) {
                cin.get();
                cin.getline(game_name, 100);

                cin >> game_price >> game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            } else if (game_type == 2) {
                cin.get();
                cin.getline(game_name, 100);

                cin >> game_price >> game_on_sale;

                cin >> sub_game_monthly_fee;
                cin >> sub_game_month >> sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month,
                                         sub_game_year);
            }
            u += (*g);
        }
        cout << u;
        cout << "Total money spent: $" << u.total_spent() << endl;
    }

    return 0;
}
