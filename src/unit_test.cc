#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "gtest/gtest.h"
#include "overlord.h"
#include "minion.h"
#include <ncurses.h>

#include <tuple>


namespace {
 
    using namespace elma;
    using namespace overlord;
    using std::tuple;
    using std::make_tuple;
    using std::get;

    TEST(Overlord,Construction) { 
    Manager m;
    Minion elf;
    Minion goblin;

    std::vector<Minion*> _minions = {&elf,
                                    &goblin};

    Overlord ov(_minions);
    

    m.schedule(ov, 100_ms)
     .schedule(elf, 100_ms)
     .schedule(goblin, 100_ms)
     .init()
     .start()
     .run(1_s);
     //.emit(Event("move"))

        //.stop();
        //std::cout<<"Test 1\n";
     endwin(); 

    EXPECT_EQ(elf.current().name(),"fighting");
    }

    // More tests go here. You should aim to test every
    // method of every object, either directly or indirectly,
    // although testing user interfaces is notoriously 
    // difficult.


 

    TEST(Minion,State_changes) { 
    Manager m;
    Minion elf;
    Minion goblin;
    std::vector<Minion*> _minions = {&elf,
                                    &goblin};

    Overlord ov(_minions);
    
    elf.set_target(make_tuple(2,2));
    goblin.set_target(make_tuple(30,30));

    m.schedule(ov, 100_ms)
     .schedule(elf, 100_ms)
     .schedule(goblin, 100_ms)
     .init()
     .start();

//start idle
EXPECT_EQ(elf.current().name(),"idle");//test idle
m.emit(Event("idle_check"));//emit check_idle
EXPECT_EQ(elf.current().name(),"idle");//test idle
elf.select();//select
m.emit(Event("idle_check"));//emit idle checck
EXPECT_EQ(elf.current().name(),"select");//test selected
m.emit(Event("travel"));//emit travel
EXPECT_EQ(elf.current().name(),"traveling");//test treaveling
elf.unselect();//unselcet
m.emit(Event("travel_check"));//emit travel sellect
EXPECT_EQ(elf.current().name(),"traveling");//test treaveling
m.emit(Event("travel_colide"));//emit colide
EXPECT_EQ(elf.current().name(),"traveling");//test traveling
elf.select_colide();//slect collide
m.emit(Event("travel_colide"));//emit collide
EXPECT_EQ(elf.current().name(),"colide");//test colide
m.emit(Event("fight"));//emit emit fight
EXPECT_EQ(elf.current().name(),"fighting");//test fight

endwin();

    }

TEST(Minion_Basics,Constructors) { 
    Minion a(make_tuple(5,7));                                  //start position
    Minion b(tuple<int,int>,double = 2);                        //attack
    Minion c(tuple<int,int>,double,double = 2);                 //defence
    Minion d(tuple<int,int>,double,double,double = 2);          //efficientcy
    Minion e(tuple<int,int>,double,double,double,int = 2);       //speed
    Minion f(tuple<int,int>,double,double,double,int,int = 2);   //reach
    Minion g;                                                    //default
}

TEST(Minion_Basics,Get_Coords) { 
    Minion elf(make_tuple(5,7));

    EXPECT_EQ(get<0>(elf.get_coords()),5);
    EXPECT_EQ(get<1>(elf.get_coords()),7);
    EXPECT_EQ(get<0>(elf.get_coords_target()),5);
    EXPECT_EQ(get<1>(elf.get_coords_target()),7);

    elf.set_target(make_tuple(20,15));

    EXPECT_EQ(get<0>(elf.get_coords()),5);
    EXPECT_EQ(get<1>(elf.get_coords()),7);
    EXPECT_EQ(get<0>(elf.get_coords_target()),20);
    EXPECT_EQ(get<1>(elf.get_coords_target()),15);
}

TEST(Minion_Basics,Collision) { 
    
    
    Manager m;
    Minion elf(make_tuple(5,7));
    Minion goblin(make_tuple(5,7));
    Minion horse(make_tuple(20,20));

    std::vector<Minion*> _minions = {&elf,
                                    &goblin,
                                    &horse};

    Overlord ov(_minions);
    
    m.schedule(ov, 100_ms)
     .schedule(elf, 100_ms)
     .schedule(goblin, 100_ms)
     .schedule(horse, 100_ms)
     .init()
     .start()
     .run(300_ms);
     endwin();

    EXPECT_EQ(elf.collisions(),1);
    EXPECT_EQ(goblin.collisions(),1);
    EXPECT_EQ(horse.collisions(),0);
}

TEST(Minion_Basics,Move_Calls) { 
    Manager m;
    Minion elf;
    Minion goblin;
    std::vector<Minion*> _minions = {&elf,
                                    &goblin};

    Overlord ov(_minions);
    
    elf.set_target(make_tuple(2,2));
    goblin.set_target(make_tuple(30,30));

    m.schedule(ov, 100_ms)
     .schedule(elf, 100_ms)
     .schedule(goblin, 100_ms)
     .init()
     .start();

    EXPECT_EQ(elf.get_move_calls(),0);
    elf.move_minion();
    elf.move_minion();
    elf.move_minion();
    EXPECT_EQ(elf.get_move_calls(),3);
}

TEST(Minion_Basics,Get_size) { 
    Minion elf(make_tuple(5,7));
    
    EXPECT_EQ(elf.get_size_height(),3);
    EXPECT_EQ(elf.get_size_width(),4);
}

TEST(Minion_Basics,Select) { 
    Minion elf(make_tuple(5,7));
    
    EXPECT_EQ(elf.selected(),false);
    elf.select();
    EXPECT_EQ(elf.selected(),true);
    elf.unselect();
    EXPECT_EQ(elf.selected(),false);
}

TEST(Minion_Basics,Colide_Select) { 
    Minion elf(make_tuple(5,7));
    
    EXPECT_EQ(elf.selected_colide(),false);
    elf.select_colide();
    EXPECT_EQ(elf.selected_colide(),true);
    elf.unselect_colide();
    EXPECT_EQ(elf.selected_colide(),false);
}



}