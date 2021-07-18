#include <iostream>

using namespace std;

struct directions{
    int left;
    int right;
    int straight;
    int uturn;
    directions(int l, int r, int s, int u)
    {
        left = l;
        right = r;
        straight = s;
        uturn = u;
    }
};

struct road_state{
    struct directions *West;
    struct directions *East;
    struct directions *North;
    struct directions *South;
    road_state(struct directions *w, struct directions *e, struct directions *n, struct directions *s){
        West = w;
        East = e;
        North = n;
        South = s;
    }
};

class Strategy
{
    public:
        virtual ~Strategy() {}
        virtual void openRoute(struct road_state* rs, int decrement_value) = 0;
};

class Context
{
    private:
        Strategy *_strategy;

    private:
        struct road_state* _rs;

    private:
        int decrement_value;

    public:
        Context(Strategy *strategy = nullptr, struct road_state* rs = nullptr, int dec = 0)
        {
            this->_strategy = strategy;
            this->_rs = rs;
            this->decrement_value = dec;
        }
        ~Context()
        {
            delete this->_strategy;
        }

        void set_strategy(Strategy *strategy, int dec)
        {
            delete this->_strategy;
            this->_strategy = strategy;
            this->decrement_value = dec;
        }

        void changeRoute() const
        {
            this->_strategy->openRoute(this->_rs, this->decrement_value);
        }

        void print_state()
        {
            cout << "West" << endl;
            cout << "straight-->" << this->_rs->West->straight << endl;
            cout << "left-->" << this->_rs->West->left << endl;
            cout << "right-->" << this->_rs->West->right << endl;
            cout << "uturn-->" << this->_rs->West->uturn << endl;
            cout << "East" << endl;
            cout << "straight-->" << this->_rs->East->straight << endl;
            cout << "left-->" << this->_rs->East->left << endl;
            cout << "right-->" << this->_rs->East->right << endl;
            cout << "uturn-->" << this->_rs->East->uturn << endl;
            cout << "North" << endl;
            cout << "straight-->" << this->_rs->North->straight << endl;
            cout << "left-->" << this->_rs->North->left << endl;
            cout << "right-->" << this->_rs->North->right << endl;
            cout << "uturn-->" << this->_rs->North->uturn << endl;
            cout << "South" << endl;
            cout << "straight-->" << this->_rs->South->straight << endl;
            cout << "left-->" << this->_rs->South->left << endl;
            cout << "right-->" << this->_rs->South->right << endl;
            cout << "uturn-->" << this->_rs->South->uturn << endl;
        }

};

int getValue(int value, int decrement_value)
{
    if(value > decrement_value)
    {
        return value - decrement_value;
    }
    else
    {
        return 0;
    }
};

class WestOneStrategy : public Strategy
{
    public:
        void openRoute(struct road_state* rs, int decrement_value)
        {
            rs->West->straight = getValue(rs->West->straight, decrement_value);
            rs->South->right = getValue(rs->South->right, decrement_value);
            rs->West->left = getValue(rs->West->left, decrement_value);
            rs->East->left = getValue(rs->East->left, decrement_value);
            rs->North->left = getValue(rs->North->left, decrement_value);
            rs->South->left = getValue(rs->South->left, decrement_value);
            rs->West->uturn = getValue(rs->West->uturn, decrement_value);
            rs->South->uturn = getValue(rs->South->uturn, decrement_value);
        }
};

class WestTwoStrategy : public Strategy
{
    public:
        void openRoute(struct road_state* rs, int decrement_value)
        {
            rs->West->straight = getValue(rs->West->straight, decrement_value);
            rs->West->right = getValue(rs->West->right, decrement_value);
            rs->West->left = getValue(rs->West->left, decrement_value);
            rs->East->left = getValue(rs->East->left, decrement_value);
            rs->North->left = getValue(rs->North->left, decrement_value);
            rs->South->left = getValue(rs->South->left, decrement_value);
            rs->West->uturn = getValue(rs->West->uturn , decrement_value);
            rs->South->uturn = getValue(rs->South->uturn, decrement_value);
        }
};

class EastOneStrategy : public Strategy
{
    public:
        void openRoute(struct road_state* rs, int decrement_value)
        {
            rs->East->straight = getValue(rs->East->straight, decrement_value);
            rs->North->left = getValue(rs->North->left, decrement_value);
            rs->West->left = getValue(rs->West->left, decrement_value);
            rs->East->left = getValue(rs->East->left, decrement_value);
            rs->North->left = getValue(rs->North->left, decrement_value);
            rs->South->left = getValue(rs->South->left, decrement_value);
            rs->North->uturn = getValue(rs->North->uturn, decrement_value);
            rs->East->uturn = getValue(rs->East->uturn, decrement_value);
        }
};

class EastTwoStrategy : public Strategy
{
    public:
        void openRoute(struct road_state* rs, int decrement_value)
        {
            rs->East->straight = getValue(rs->East->straight, decrement_value);
            rs->East->right = getValue(rs->East->right, decrement_value);
            rs->West->left = getValue(rs->West->left, decrement_value);
            rs->East->left = getValue(rs->East->left, decrement_value);
            rs->North->left = getValue(rs->North->left, decrement_value);
            rs->South->left = getValue(rs->South->left, decrement_value);
            rs->North->uturn = getValue(rs->North->uturn, decrement_value);
            rs->East->uturn = getValue(rs->East->uturn, decrement_value);
        }
};

class NorthOneStrategy : public Strategy
{
    public:
        void openRoute(struct road_state* rs, int decrement_value)
        {
            rs->North->straight = getValue(rs->North->straight, decrement_value);
            rs->West->right = getValue(rs->West->right, decrement_value);
            rs->West->left = getValue(rs->West->left, decrement_value);
            rs->East->left = getValue(rs->East->left, decrement_value);
            rs->North->left = getValue(rs->North->left, decrement_value);
            rs->South->left = getValue(rs->South->left , decrement_value);
            rs->North->uturn = getValue(rs->North->uturn, decrement_value);
            rs->West->uturn = getValue(rs->West->uturn, decrement_value);
        }
};

class NorthTwoStrategy : public Strategy
{
    public:
        void openRoute(struct road_state* rs, int decrement_value)
        {
            rs->North->straight = getValue(rs->North->straight, decrement_value);
            rs->North->right = getValue(rs->North->right, decrement_value);
            rs->West->left = getValue(rs->West->left, decrement_value);
            rs->East->left = getValue(rs->East->left, decrement_value);
            rs->North->left = getValue(rs->North->left, decrement_value);
            rs->South->left = getValue(rs->South->left, decrement_value);
            rs->North->uturn = getValue(rs->North->uturn, decrement_value);
            rs->West->uturn = getValue(rs->West->uturn, decrement_value);
        }
};

class SouthOneStrategy : public Strategy
{
    public:
        void openRoute(struct road_state* rs, int decrement_value)
        {
            rs->South->straight = getValue(rs->South->straight, decrement_value);
            rs->East->right = getValue(rs->East->right, decrement_value);
            rs->West->left = getValue(rs->West->left, decrement_value);
            rs->East->left = getValue(rs->East->left, decrement_value);
            rs->North->left = getValue(rs->North->left, decrement_value);
            rs->South->left = getValue(rs->South->left, decrement_value);
            rs->East->uturn = getValue(rs->East->uturn, decrement_value);
            rs->South->uturn = getValue(rs->South->uturn, decrement_value);
        }
};

class SouthTwoStrategy : public Strategy
{
    public:
        void openRoute(struct road_state* rs, int decrement_value)
        {
            rs->South->straight = getValue(rs->South->straight, decrement_value);
            rs->South->right = getValue(rs->South->right, decrement_value);
            rs->West->left = getValue(rs->West->left, decrement_value);
            rs->East->left = getValue(rs->East->left, decrement_value);
            rs->North->left = getValue(rs->North->left, decrement_value);
            rs->South->left = getValue(rs->South->left, decrement_value);
            rs->East->uturn = getValue(rs->East->uturn, decrement_value);
            rs->South->uturn = getValue(rs->South->uturn, decrement_value);
        }
};

int main()
{
    struct directions *West = new directions(10, 10, 10, 10);
    struct directions *East = new directions(10, 10, 10, 10);
    struct directions *North = new directions(10, 10, 10, 10);
    struct directions *South = new directions(10, 10, 10, 10);
    struct road_state *rs  = new road_state(West, East, North, South);
    Context *context = new Context(new WestOneStrategy, rs, 1);
    context->changeRoute();
    context->print_state();
    context->set_strategy(new WestTwoStrategy, 2);
    context->changeRoute();
    context->print_state();
    return 0;
}
