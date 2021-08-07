#include <iostream>

using namespace std;

// vehicle directions struct for a given road
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

// Road state 
// Contains all the directions of vehicles in a given state
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

// Base Strategy Interface for the strategies
class Strategy
{
    public:
        virtual ~Strategy() {}
        virtual void openRoute(struct road_state* rs, int decrement_value) = 0;
        virtual int get_max(struct road_state* rs) = 0;
};

// Used to interchange the strategies
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

        int get_strategy_values()
        {
             return this->_strategy->get_max(this->_rs);
        }

        void print_state(){
            cout << "###############################################" << endl;
            cout << "eastOne::" << this->_rs->East->straight << "," << this->_rs->North->right << "," <<  this->_rs->East->left << "," << this->_rs->North->uturn << endl;
            cout << "eastTwo::" << this->_rs->East->straight << "," << this->_rs->East->right << "," <<  this->_rs->East->left << "," << this->_rs->East->uturn << endl;
            cout << "westOne::" << this->_rs->West->straight << "," << this->_rs->South->right << "," <<  this->_rs->West->left << "," << this->_rs->South->uturn << endl;
            cout << "westTwo::" << this->_rs->West->straight << "," << this->_rs->West->right << "," <<  this->_rs->West->left << "," << this->_rs->West->uturn << endl;
            cout << "northOne::" << this->_rs->North->straight << "," << this->_rs->West->right << "," <<  this->_rs->North->left << "," << this->_rs->West->uturn << endl;
            cout << "northTwo::" << this->_rs->North->straight << "," << this->_rs->North->right << "," <<  this->_rs->North->left << "," << this->_rs->North->uturn << endl;
            cout << "southOne::" << this->_rs->South->straight << "," << this->_rs->East->right << "," <<  this->_rs->South->left << "," << this->_rs->East->uturn << endl;
            cout << "southTwo::" << this->_rs->South->straight << "," << this->_rs->South->right << "," <<  this->_rs->South->left << "," << this->_rs->South->uturn << endl;
            cout << "###############################################" << endl;
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

//Following classes are the different strategies for the road to induce the traffic
class WestOneStrategy : public Strategy
{
    public:
        void openRoute(struct road_state* rs, int decrement_value)
        {
            rs->West->straight = getValue(rs->West->straight, decrement_value);
            rs->South->right = getValue(rs->South->right, decrement_value);
            rs->West->left = getValue(rs->West->left, decrement_value);
            rs->South->uturn = getValue(rs->South->uturn, decrement_value);
        }

    public:
        int get_max(struct road_state* current_road_state)
        {
             return max(max(current_road_state->West->straight, current_road_state->South->right), max(current_road_state->West->left, current_road_state->South->uturn));;
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
            rs->West->uturn = getValue(rs->West->uturn , decrement_value);
        }

    public:
        int get_max(struct road_state* current_road_state)
        {
             return max(max(current_road_state->West->left, current_road_state->West->right), max(current_road_state->West->straight, current_road_state->West->uturn));
        }
};

class EastOneStrategy : public Strategy
{
    public:
        void openRoute(struct road_state* rs, int decrement_value)
        {
            rs->East->straight = getValue(rs->East->straight, decrement_value);
            rs->North->right = getValue(rs->North->right, decrement_value);
            rs->East->left = getValue(rs->East->left, decrement_value);
            rs->North->uturn = getValue(rs->North->uturn, decrement_value);
        }

    public:
        int get_max(struct road_state* current_road_state)
        {
             return max(max(current_road_state->East->straight, current_road_state->North->right), max(current_road_state->East->left, current_road_state->North->uturn));
        }
};

class EastTwoStrategy : public Strategy
{
    public:
        void openRoute(struct road_state* rs, int decrement_value)
        {
            rs->East->straight = getValue(rs->East->straight, decrement_value);
            rs->East->right = getValue(rs->East->right, decrement_value);
            rs->East->left = getValue(rs->East->left, decrement_value);
            rs->East->uturn = getValue(rs->East->uturn, decrement_value);
        }

    public:
        int get_max(struct road_state* current_road_state)
        {
             return max(max(current_road_state->East->left, current_road_state->East->right), max(current_road_state->East->straight, current_road_state->East->uturn));
        }
};

class NorthOneStrategy : public Strategy
{
    public:
        void openRoute(struct road_state* rs, int decrement_value)
        {
            rs->North->straight = getValue(rs->North->straight, decrement_value);
            rs->West->right = getValue(rs->West->right, decrement_value);
            rs->North->left = getValue(rs->North->left, decrement_value);
            rs->West->uturn = getValue(rs->West->uturn, decrement_value);
        }

    public:
        int get_max(struct road_state* current_road_state)
        {
             return max(max(current_road_state->North->straight, current_road_state->West->right), max(current_road_state->North->left, current_road_state->West->uturn));
        }
};

class NorthTwoStrategy : public Strategy
{
    public:
        void openRoute(struct road_state* rs, int decrement_value)
        {
            rs->North->straight = getValue(rs->North->straight, decrement_value);
            rs->North->right = getValue(rs->North->right, decrement_value);
            rs->North->left = getValue(rs->North->left, decrement_value);
            rs->North->uturn = getValue(rs->North->uturn, decrement_value);
        }

    public:
        int get_max(struct road_state* current_road_state)
        {
             return max(max(current_road_state->North->left, current_road_state->North->right), max(current_road_state->North->straight, current_road_state->North->uturn));
        }
};

class SouthOneStrategy : public Strategy
{
    public:
        void openRoute(struct road_state* rs, int decrement_value)
        {
            rs->South->straight = getValue(rs->South->straight, decrement_value);
            rs->East->right = getValue(rs->East->right, decrement_value);
            rs->South->left = getValue(rs->South->left, decrement_value);
            rs->East->uturn = getValue(rs->East->uturn, decrement_value);
        }

    public:
        int get_max(struct road_state* current_road_state)
        {
             return max(max(current_road_state->South->straight, current_road_state->East->right), max(current_road_state->South->left, current_road_state->East->uturn));
        }
};

class SouthTwoStrategy : public Strategy
{
    public:
        void openRoute(struct road_state* rs, int decrement_value)
        {
            rs->South->straight = getValue(rs->South->straight, decrement_value);
            rs->South->right = getValue(rs->South->right, decrement_value);
            rs->South->left = getValue(rs->South->left, decrement_value);
            rs->South->uturn = getValue(rs->South->uturn, decrement_value);
        }

    public:
        int get_max(struct road_state* current_road_state)
        {
             return max(max(current_road_state->South->left, current_road_state->South->right), max(current_road_state->South->straight, current_road_state->South->uturn));
        }
};

// int main()
// {
//     struct directions *West = new directions(10, 10, 10, 10);
//     struct directions *East = new directions(10, 10, 10, 10);
//     struct directions *North = new directions(10, 10, 10, 10);
//     struct directions *South = new directions(10, 10, 10, 10);
//     struct road_state *rs  = new road_state(West, East, North, South);
//     //Called first strategy
//     Context *context = new Context(new WestOneStrategy, rs, 1);
//     context->changeRoute();
//     // context->print_state();
//     //Change the strategy
//     context->set_strategy(new WestTwoStrategy, 2);
//     context->changeRoute();
//     // context->print_state();
//     //Change the strategy
//     context->set_strategy(new SouthOneStrategy, 3);
//     context->changeRoute();
//     // context->print_state();
//     cout << rs->West->straight << endl;
//     return 0;
// }
