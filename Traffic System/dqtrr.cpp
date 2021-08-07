#include "StateMachine.hpp"
#include <map>
#include <vector>
#include <fstream>

using namespace std;

struct state_timeline{
    struct state_timeline* next_state;
    string current_state;
    int decrement;
    state_timeline(string cs, int d){
        next_state = NULL;
        current_state = cs;
        decrement = d;
    }
};

struct state_order{
    struct state_order* next_state_order;
    string state;
    state_order(string s){
        state = s;
        next_state_order = NULL;
    }
};

struct state_count{
    int eastOne;
    int eastTwo;
    int westOne;
    int westTwo;
    int northOne;
    int northTwo;
    int southOne;
    int southTwo;
    state_count(int eo, int et, int wo, int wt, int no, int nt, int so, int st){
        eastOne = eo;
        eastTwo = et;
        westOne = wo;
        westTwo = wt;
        northOne = no;
        northTwo = nt;
        southOne = so;
        southTwo = st;
    }
};

Strategy* get_strategy(string state_o){
    if(state_o == "eastOne"){
        return new EastOneStrategy;
    }
    else if(state_o == "eastTwo"){
        return new EastTwoStrategy;
    }
    else if(state_o == "westOne"){
        return new WestOneStrategy;
    }
    else if(state_o == "westTwo"){
        return new WestTwoStrategy;
    }
    else if(state_o == "northOne"){
        return new NorthOneStrategy;
    }
    else if(state_o == "northTwo"){
        return new NorthTwoStrategy;
    }
    else if(state_o == "southOne"){
        return new SouthOneStrategy;
    }
    else if(state_o == "southTwo"){
        return new SouthTwoStrategy;
    }
}

bool check_run(struct state_count* sc){
    if(sc->eastOne == 0 && sc->eastTwo == 0 && sc->westOne == 0 && sc->westTwo == 0 && sc->northOne == 0 && sc->northTwo == 0 && sc->southOne == 0 && sc->southTwo == 0){
        return false;
    }
    return true;
}

state_order* get_state_order(struct state_count* sc){
    map<int, vector<string> > cmap;
    cmap[sc->eastOne].push_back("eastOne");
    cmap[sc->eastTwo].push_back("eastTwo");
    cmap[sc->westOne].push_back("westOne");
    cmap[sc->westTwo].push_back("westTwo");
    cmap[sc->northOne].push_back("northOne");
    cmap[sc->northTwo].push_back("northTwo");
    cmap[sc->southOne].push_back("southOne");
    cmap[sc->southTwo].push_back("southTwo");
    struct state_order* so = new state_order(cmap.begin()->second[0]);
    struct state_order* temp = so;
    int ini = 1;
    for(auto it = cmap.begin(); it != cmap.end(); it++){
        for(int i = ini; i<it->second.size(); i++){
            temp->next_state_order = new state_order(it->second[i]);
            temp = temp->next_state_order;
        }
        ini = 0;
    }
    return so;
};

int get_average(struct state_count* sc){
    int sum = sc->eastOne + sc->eastTwo + sc->northOne + sc->northTwo + sc->southOne + sc->southTwo + sc->westOne + sc->westTwo;
    if(sum<8) return sum;
    return sum/8;
}

state_count* get_state_count(struct road_state* current_road_state){
    struct state_count* sc = new state_count(0, 0, 0, 0, 0, 0, 0, 0);
    sc->eastOne = max(max(current_road_state->East->straight, current_road_state->North->right), max(current_road_state->East->left, current_road_state->North->uturn));
    sc->eastTwo = max(max(current_road_state->East->left, current_road_state->East->right), max(current_road_state->East->straight, current_road_state->East->uturn));
    sc->westOne = max(max(current_road_state->West->straight, current_road_state->South->right), max(current_road_state->West->left, current_road_state->South->uturn));
    sc->westTwo = max(max(current_road_state->West->left, current_road_state->West->right), max(current_road_state->West->straight, current_road_state->West->uturn));
    sc->northOne = max(max(current_road_state->North->straight, current_road_state->West->right), max(current_road_state->North->left, current_road_state->West->uturn));
    sc->northTwo = max(max(current_road_state->North->left, current_road_state->North->right), max(current_road_state->North->straight, current_road_state->North->uturn));
    sc->southOne = max(max(current_road_state->South->straight, current_road_state->East->right), max(current_road_state->South->left, current_road_state->East->uturn));
    sc->southTwo = max(max(current_road_state->South->left, current_road_state->South->right), max(current_road_state->South->straight, current_road_state->South->uturn));
    return sc;
};

state_timeline* dqtrr(struct road_state* rs, struct state_order* so){
    struct state_timeline* st = NULL;
    struct state_timeline* temp = NULL;
    struct state_count* sc = get_state_count(rs);
    Context *context;
    struct state_order* temp_order = so;
    while(check_run(sc)){
        while(temp_order != NULL){
            int decrement = get_average(sc);
            context = new Context(get_strategy(temp_order->state), rs, decrement);
            if(context->get_strategy_values() != 0){
                int d_value = (context->get_strategy_values()>decrement)?decrement:context->get_strategy_values();
                if(temp == NULL){
                    temp = new state_timeline(temp_order->state, d_value);
                    st = temp;
                }
                else{
                    temp->next_state = new state_timeline(temp_order->state, d_value);
                    temp = temp->next_state;
                }
                context->changeRoute();
                sc = get_state_count(rs);
                // context->print_state();
            }
            temp_order = temp_order->next_state_order;
        }
        temp_order = so;
    }
    return st;
}

int main(int argc, char **args){
    int values[4][4];
    int k=1;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            values[i][j] = stoi(args[k]);
            k++;
        }
    }
    struct directions* west_directions = new directions(values[0][0], values[0][1], values[0][2], values[0][3]);
    struct directions* east_directions = new directions(values[1][0], values[1][1], values[1][2], values[1][3]);
    struct directions* north_directions = new directions(values[2][0], values[2][1], values[2][2], values[2][3]);
    struct directions* south_directions = new directions(values[3][0], values[3][1], values[3][2], values[3][3]);
    struct road_state* current_road_state = new road_state(west_directions, east_directions, north_directions, south_directions);
    struct state_order* so = get_state_order(get_state_count(current_road_state));
    struct state_timeline* st = dqtrr(current_road_state, so);
    ofstream output_file;
    output_file.open("output.json");
    output_file << "[\n";
    while(st != NULL){
        if(st->next_state != NULL){
            output_file << "\t{ " << '"' << st->current_state << '"' << " : " << st->decrement << "},\n";
        }
        else{
            output_file << "\t{ " << '"' << st->current_state << '"' << " : " << st->decrement << "}\n";
        }
        st = st->next_state;
    }
    output_file << "]\n";
    output_file.close();
    return 0;
};