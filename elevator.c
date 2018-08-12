// Simulation of the Hertz airport shuttle bus, which picks up passengers
// from the airport terminal building going to the Hertz rental car lot.

#include <iostream>
#include "cpp.h"
#include <string.h>
using namespace std;

#define NUM_SEATS 6      // number of seats available on shuttle
#define TINY 1.e-20      // a very small time period
//efine FLOOR 0         // named constants for labelling event set
#define LOBBY 0

facility_set *buttons;// ("Curb",2);  // customer queues at each stop
//facility rest ("rest");           // dummy facility indicating an idle shuttle

//event_set *get_off_now;  // all customers can get off shuttle CHANGED
mailbox_set *going_up;
mailbox_set *going_down;
event_set *here_is_floor;

event_set *hop_on; //("board shuttle", 2);  // invite one customer to board at this stop
event boarded ("boarded");             // one customer responds after taking a seat

event_set *elevator_called;// ("call button", 2); // call buttons at each location

void update_workload(long whereami);       // passenger generator
string places[2] = {"Terminal", "CarLot"}; // where to generate
long group_size();

void passenger(long whoami, long wheretogo);                // passenger trajectory
string people[2] = {"arr_cust","dep_cust"}; // who was generated

void elevator();                  // trajectory of the shuttle bus consists of...
void loop_around_airport(long & seats_used);      // ... repeated trips around airport
void load_elevator(long whereami, long & on_board); // posssibly loading passengers
qtable elevator_occ("bus occupancy");  // time average of how full is the bus

int numElevators;

extern "C" void sim(int argc, char *argv[])      // main process
{
  create("sim");
  if(argc < 4) {
    cout << "Error: Needed 3 arguments" << endl;
    exit(0); 
  }
  numElevators = atoi(argv[1]); //ADDED
  elevator_occ.add_histogram(NUM_SEATS+1,0,NUM_SEATS);
  here_is_floor = new event_set("here is floor", numElevators + 1);
  buttons = new facility_set("Floor", numElevators + 1);
  elevator_called = new event_set("call button", numElevators + 1);
  hop_on = new event_set("board elevator", numElevators + 1);
    for (int FLOOR = 0; FLOOR < numElevators+ 1; FLOOR++) {
	update_workload(FLOOR);  // generate a stream of arriving customers
  }
//  update_workload(LOBBY);  // generate a stream of departing customers
  elevator();                // create a single shuttle
  hold(70);
  //hold (1440);              // wait for a whole day (in minutes) to pass
  report();
  status_facilities();
}

// Model segment 1: generate groups of new passengers at specified location

void update_workload(long whereami)
{
  const char* myName;
  if(!whereami) myName=places[1].c_str(); // hack because CSIM wants a char*
  else myName = places[0].c_str();
  create(myName);
  long wheretogo = 0;
  while(clock < 1440.)          // run for one day (in minutes)
  {
    hold(expntl(10));           // exponential interarrivals, mean 10 minutes
    long group = group_size();
    for (long i=0;i<group;i++){  // create each member of the group
      if(whereami == LOBBY){
        wheretogo = random(1,numElevators);
      }
      passenger(whereami, wheretogo);      // new passenger appears at this location
    }
  }
}

// Model segment 2: activities followed by an individual passenger

void passenger(long whoami, long wheretogo)
{
  
  const char* myName;
  if(!whoami) myName=people[1].c_str(); // hack because CSIM wants a char*
  else myName = people[0].c_str();
  create(myName);

 (*buttons)[whoami].reserve();     // join the queue at my starting location
  (*elevator_called)[whoami].set();  // head of queue, so call shuttle
  (*hop_on)[whoami].queue();        // wait for shuttle and invitation to board
  (*elevator_called)[whoami].clear();// cancel my call; next in line will push 
  hold(uniform(0.5,1.0));        // takes time to get seated
  boarded.set();                 // tell driver you are in your seat
 (*buttons)[whoami].release();     // let next person (if any) access button
  (*here_is_floor)[wheretogo].wait();            // everybody off when shuttle reaches next stop
}

// Model segment 3: the shuttle bus

void elevator() {
  create ("elevator");
  while(1) {  // loop forever
    // start off in idle state, waiting for the first call...
   
    //************************************************************
    // REST CODE **********************
    // ************************************************************
    /*     rest.reserve();                  // relax at garage till called from somewhere
    long who_pushed = (*shuttle_called).wait_any();
    (*shuttle_called)[who_pushed].set(); // loop exit needs to see event
    rest.release();                   // and back to work we go!
    */
    //****************************************************************
    // END REST CODE **********************
    // *****************************************************************
    
    
    long seats_used = 0;              // shuttle is initially empty
    elevator_occ.note_value(seats_used);

    hold(2);  // 2 minutes to reach car lot stop

    bool call_waiting = false;
    for(int i = 0; i <= numElevators; i++) {
	if((*elevator_called)[i].state() == OCC){
		call_waiting = true;
		break;
	}
    }
    // Keep going around the loop until there are no calls waiting
    while (call_waiting)
      loop_around_airport(seats_used);
  }
}

long group_size() {  // calculates the number of passengers in a group
  double x = prob();
  if (x < 0.3) return 1;
  else {
    if (x < 0.7) return 2;
    else return 5;
  }
}

void loop_around_airport(long & seats_used) { // one trip around the airport
  // Start by picking up departing passengers at car lot
  load_elevator(LOBBY, seats_used);
  elevator_occ.note_value(seats_used);
 // cout << seats_used << " people on the bus" << endl;;
  for(int FLOOR = 1; FLOOR <= numElevators; FLOOR++){
    hold (uniform(3,5));  // drive to airport terminal

  // drop off all departing passengers at airport terminal
    if((*here_is_floor)[FLOOR].wait_cnt()) {
     // cout << (*here_is_floor)[FLOOR].wait_cnt() << " people getting off" << endl;
      seats_used -= (*here_is_floor)[FLOOR].wait_cnt();
      (*here_is_floor)[FLOOR].set(); // open door and let them off
      elevator_occ.note_value(seats_used);
    }

    // pick up arriving passengers at airport terminal
    load_elevator(FLOOR, seats_used);
    elevator_occ.note_value(seats_used);
    cout << seats_used << " people on the bus" << endl;;

 }
  hold (uniform(3,5));  // drive to Hertz car lot

  // drop off all arriving passengers at car lot
  if(seats_used > 0) {
    seats_used = 0;
    //cout << (*here_is_floor)[0].wait_cnt() << " people go at Carport" << endl;
    (*here_is_floor)[LOBBY].set(); // open door and let them off
    elevator_occ.note_value(seats_used);
  }
  // Back to starting point. Bus is empty. Maybe I can rest...
}

void load_elevator(long whereami, long & on_board)  // manage passenger loading
{
  // invite passengers to enter, one at a time, until all seats are full
  while((on_board < NUM_SEATS) &&
    ((*buttons)[whereami].num_busy() + (*buttons)[whereami].qlength() > 0))
  {
    (*hop_on)[whereami].set();// invite one person to board
    boarded.wait();  // pause until that person is seated
    on_board++;
    hold(TINY);  // let next passenger (if any) reset the button
  }
}
