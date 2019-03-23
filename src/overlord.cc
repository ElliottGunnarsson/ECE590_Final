#include <unistd.h>
#include <chrono>
#include "minion.h"
#include <tuple>
#include <string>

using namespace std::chrono;
using namespace overlord;
using std::make_tuple;

Overlord::Overlord(
    //Factory& fty,
    std::vector<Minion*>& mns
) : Process("lording over"), 
    //_factory(fty),
    _minions(mns)
{
    initscr();   // Start ncurses
    timeout(1);  // Timeout for waiting for user input
    noecho();    // Do not echo user input to the screen
    curs_set(0); // Do not show the cursor
    keypad(stdscr, TRUE); //turn on mouse events
    mousemask(mmask_t BUTTON1_CLICKED, NULL);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
};

void Overlord::draw_pen(){
//50 by 90
for (int i = 0; i<90;i++ ){mvprintw(0,i,"=");mvprintw(50,i,"=");}
for (int i = 0; i<50;i++ ){mvprintw(i,0,"||");mvprintw(i,90,"||");}

string line1 = "The bunnies are running rampant!";
string line2 = "Click on one and click away to separate them.";
string line3 = "If you need to leave press 'Q'";
string line4 = "For debug info press 7";

mvprintw(12,95,line1.c_str());
mvprintw(14,95,line2.c_str());
mvprintw(40,95,line3.c_str());
mvprintw(42,95,line4.c_str());
}

void Overlord::draw_minion(Minion& mn){
int x = std::get<0>(mn.get_coords());
int y = std::get<1>(mn.get_coords()); 


if(mn.current().name() == "fighting"){
    attron(COLOR_PAIR(2));
}else if(mn.current().name() == "select"){
    attron(COLOR_PAIR(3));
}

string line1 = "()()";
string line2 = "(..)";
string line3 = "(,),)";

mvprintw(x,y,line1.c_str());
mvprintw(x+1,y,line2.c_str());
mvprintw(x+2,y,line3.c_str());

attron(COLOR_PAIR(1));
}

void Overlord::draw_debug_info(Minion& mn){
    int x = std::get<0>(mn.get_coords());
    int y = std::get<1>(mn.get_coords()); 
    mvprintw(x,y+6,"Target is %d,%d",std::get<0>(mn.get_coords_target()),std::get<1>(mn.get_coords_target()));
    mvprintw(x+1,y+6,"coords is %d,%d",x,y);
    mvprintw(x+2,y+6,mn.current().name().c_str());
    mvprintw(x+3,y+6,"move calls is %d",mn.get_move_calls());
    if (mn.selected()){
        mvprintw(x+4,y+6,"Selected");
    }else{
        mvprintw(x+4,y+6,"Not Selected");
    }
    if (mn.selected_colide()){
        mvprintw(x+5,y+6,"Selected Colide");
    }else{
        mvprintw(x+5,y+6,"Not Selected Colide");
    }
    mvprintw(x+6,y+6,"colisions is %d",mn.collisions());
}

void Overlord::init(){
 
}

void Overlord::update() {

static int spacing = 1;
static int height = 50;
static int width = 100;

    int c = wgetch(stdscr);
    if (c == KEY_MOUSE) {
    MEVENT event;
    if (getmouse(&event) == OK) {
        handle_click(event.y,event.x);
        //_minions[1]->set_target(make_tuple(event.y,event.x));
      }
    }

    /*************   EDITORS     *******************/
    //add key commands here
    switch ( c ) {            
        case 's':
            std::cout<<"pushed the s button\n";
            emit(Event("start/stop"));
            break;
        case 'r':
            emit(Event("reset"));
            clear(); // Clear the screen of old stuff
            break;
        case '1':
            if(_selection !=-1){
                _minions[_selection]->set_propagate(false);
            }           
            break;
        case '2':
            if(_selection !=-1){
                _minions[_selection]->set_propagate(true);
            }  
            break;
        case '4':
            
            break;
        case '5':
            
            break;
        case '6':
            
            break;
        case '7':
            //emit(Event("move"));
            toggle = !toggle;//mvprintw(40,40,"pushing 7");
            break;
        case '8':
            width--;
            break;
        case 'q':
            std::cout << "halting\n";
            halt();
            break;
        case 'i':emit(Event("idle_check"));break;
        case 'o':emit(Event("travel_check"));break;
        case 'k':emit(Event("idle"));break;
        case 'l':emit(Event("travel"));break;
/*************   END EDITORS     *******************/
    }


    check_collisions();

    clear();
    draw_pen();
    for(int i = 0; i< _minions.size();i++){
        draw_minion(*_minions[i]);
    }
    if (toggle){
        for(int i = 0; i< _minions.size();i++){
        draw_debug_info(*_minions[i]);
        }
    }


    usleep(9999);
}


void Overlord::handle_click(int x, int y){
select_minion(x,y);



}

void Overlord::select_minion(int x,int y){
        for(int i =0;i<_minions.size();i++){
            
                int ix = std::get<0>(_minions[i]->get_coords());
                int iy = std::get<1>(_minions[i]->get_coords());
                if((ix<x) & (x<ix+_minions[i]->get_size_width()) & //){
                    (iy<y & (y<iy+_minions[i]->get_size_height()))){
                        if(_selection != -1){
                            _minions[_selection]->unselect();
                        }
                        _selection = i;
                        _minions[_selection]->select();
                        emit(Event("idle_check"));
                        emit(Event("travel_check"));
                        emit(Event("fight_check"));
                }else{
                    if(_selection !=-1){
                        _minions[_selection]->set_target(make_tuple(x,y));
                    }
                    emit(Event("travel"));
                }
                
            
        }
}


void Overlord::check_collisions(){
    for(int i =0;i<_minions.size();i++){
        _minions[i]->clear_collisions();
        for(int j =0;j<_minions.size();j++){
            if (i!=j){
                int ix = std::get<0>(_minions[i]->get_coords());
                int iy = std::get<1>(_minions[i]->get_coords());
                int jx = std::get<0>(_minions[j]->get_coords());
                int jy = std::get<1>(_minions[j]->get_coords());
                if((ix<jx+_minions[j]->get_size_width()) & (jx<ix+_minions[i]->get_size_width())){
                    if((iy<jy+_minions[j]->get_size_height()) & (jy<iy+_minions[i]->get_size_height())){
                        _minions[i]->add_collision(_minions[j]);
                    }
                }
            }
        }
    }

}