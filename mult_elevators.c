//? Simulation of the Hertz building elevator car, which picks up passengers
// from the building terminal building going to the Hertz rental car lot.


//TODO: TIMES
// people not exiting elevator. Find way to move elevator or FIX exiting
//
//
#include <iostream>
#include "cpp.h"
#include <string.h>
#include <cmath>
using namespace std;

#define NUM_SEATS 6      // number of seats available on elevator
#define TINY 1.e-20      // a very small time period
//efine FLOOR 0         // named constants for labelling event set
#define LOBBY 0

facility_set *buttons;// ("Floor",2);  // customer queues at each stop
facility_ms *rest;// ("rest");           // dummy facility indicating an idle elevator
facility update_workload ("update_workload");

event_set **here_is_floor;  // all customers can get off elevator CHANGED

mailbox *hop_on; //("board elevator", 2);  // invite one customer to board at this stop
event_set *boarded;// need to have multiple boarded("boarded");             // one customer responds after taking a seat

event *wake_elevator;
event *elevator_called;// ("call button", 2); // call buttons at each location
event_set *going_up; //passengers wait for correct elevator
event_set *going_dn;


void make_passengers(long whereami);       // passenger generator
string places[2] = {"Terminal", "CarLot"}; // where to generate
long group_size();

void passenger(long whoami, long wheretogo);                // passenger trajectory
string people[2] = {"arr_cust","dep_cust"}; // who was generated

void create_set_passengers();
void elevatorManager(int* );
void elevator(int elevatorNum, int currfloor, int direction);                  // trajectory of the elevator car consists of...
int loop_building(long & seats_used, int elevatorNum, int currfloor, int &direction);      // ... repeated trips around building
void load_elevator(long whereami, long & on_board, int elevatorNum, int &direction); // posssibly loading passengers
qtable *elevator_occ;// ("car occupancy");  // time average of how full is the car

int numFloors;
int numElevators;
double mean;
double stdDev;
int **want_off;
int waitingfloor;
const double TIMER = 3600.;
extern "C" void sim(int argc, char *argv[])      // main process
{
  create("sim");
  if(argc < 4) {
    cout << "Error: Needed 3 arguments" << endl;
    exit(0); 
  }
  if(atoi(argv[2]) > atoi(argv[1]) - 1 || atoi(argv[3]) > atoi(argv[1]) - 1){
    cout << "Error: Current floor greater than num floors" << endl;
    exit(0);
  }
  
  numFloors = atoi(argv[1]); //ADDED
  numElevators = 2; //ADDED
  mean = 17; //multiply by 60 to get minutes not seconds
  stdDev = 12;
  int floors[numElevators];

  floors[0] = atoi(argv[2]);
  floors[1] = atoi(argv[3]);
  
  here_is_floor = new event_set*[numElevators];//("here is floor", numFloors + 1);
  buttons = new facility_set("Floor", numFloors);
  elevator_called = new event("call button");
  going_up = new event_set("waiting up elevator", numFloors);
  going_dn = new event_set("waiting dn elevator", numFloors);
  hop_on = new mailbox[numFloors];//;("board elevator", numFloors + 1);
  boarded = new event_set("boarded", numElevators);
  rest = new facility_ms("rest", numElevators);
  wake_elevator = new event("wake elevator");
  elevator_occ = new qtable[numElevators];//("car occupancy"); 
  
  for(int i = 0; i < numElevators; i++){
     elevator_occ[i].set_name("car occupancy");
     elevator_occ[i].add_histogram(NUM_SEATS+1,0,NUM_SEATS);
     here_is_floor[i] = new event_set("here is floor", numFloors);
  }
  
  for (int FLOOR = 0; FLOOR < numFloors; FLOOR++) { 
        hop_on[FLOOR].set_name("board elevator");
	make_passengers(FLOOR);  // generate a stream of arriving customers
  }
  //create_set_passengers();
//  make_passengers(LOBBY);  // generate a stream of departing customers
  elevatorManager(floors);
  //hold(70);
  hold (TIMER);              // wait for a whole day (in seconds) to pass
  report();
  status_facilities();
}

void elevatorManager(int floors[]) {
  create("elevatorManager");
  for(int i = 0; i < numElevators; i++)
     elevator(i, floors[i], 0);                // create a single elevator at floor i with direction 0 (resting)
  while(1){
    elevator_called->wait(); //wake up when passenger calls 
    //for(int i = 0; i < numFloors; i++){ //FIX wake up resting elevatori
 //      if(((*going_up)[i].wait_cnt() || (*going_dn)[i].wait_cnt()) && 1) { //check if somone wants to go up at floor i
		//assume no elevator en route, so wake up closest sleeping elevator and send direction
//		cout << "Wake up elevator" << endl;
                waitingfloor = 1;
		(*wake_elevator).set();		
                //check if an elevator is already en route else wake nearest resting elevator
//        }
    //}
  }
}


void create_set_passengers(){
    int numpassengers = 10; //change this to total num passengers
    long whereami[10] = {6, 3, 1 , 2, 3, 4, 5, 2, 5, 6}; //array of positions to start at
    long wheretogo= 0; 
    for(int i = 0; i < numpassengers; i++) {
       do{
          wheretogo = random(0,numFloors - 1); //creates random floor to go to
	} while(whereami[i] == wheretogo);  //repeat if you are already there
        passenger(whereami[i], wheretogo);
    }
}
// Model segment 1: generate groups of new passengers at specified location

void make_passengers(long whereami)
{
  const char* myName;
  if(!whereami) myName=places[1].c_str(); // hack because CSIM wants a char*
  else myName = places[0].c_str();
  create(myName);
  long wheretogo = 0;
  while(clock < TIMER)          // run for one day (in minutes)
  {
    hold(uniform(1/((mean + stdDev)/300), 1/((mean - stdDev)/300)));           // exponential interarrivals, mean 10 minutes // FIXME - Maybe? might spawn people too quickly.
hold(50);    
long group = 1;
    for (long i=0;i<group;i++){  // create each member of the group
	do{
          wheretogo = random(0,numFloors - 1); //creates random floor to go to
	} while(whereami == wheretogo);  //repeat if you are already there
     // for(int a = 0; a < numFloors; a++){
          passenger(whereami, wheretogo);      // new passenger appears at this location
     //}
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

  long int elevatorNum = -1;  
  int up = (wheretogo > whoami);
  int dn = (wheretogo < whoami);
  (*buttons)[whoami].reserve();     // join the queue at my starting location
  update_workload.reserve();        // protects the (*elevator_called) access
  (*elevator_called).set();
  update_workload.release(); 
  if(up){  //wait for the arrow light above the elevator (necessary to differentiate between up and down)
      (*going_up)[whoami].queue();// != TIMED_OUT);
      hop_on[whoami].receive(&elevatorNum); // wait for elevator to open doors
  }
  else{ //wait for down arrow light
      (*going_dn)[whoami].queue();// != TIMED_OUT)
      hop_on[whoami].receive(&elevatorNum);        // wait for elevator to open doors
  }
 // else {//FIXME if *I* waited too long, just take the stairs (reality: too many processes were killing the sim) Most likely remove. currently should be impossible
   //   (*buttons)[whoami].release();
      //flag something to be able to track that we missed someone?
  //}
  update_workload.reserve(); 
//  hold(uniform(0.5,1.0));        // takes time to get seated
  (*boarded)[elevatorNum].set();    // tell elevator you are out of the way of door
  (*buttons)[whoami].release();     // let next person (if any) access button (true bossy people dont let others press the button cuz you already have)
  update_workload.release();      
  //cout << "waiting on " << elevatorNum << " for floor " << wheretogo << endl;
  (*here_is_floor[elevatorNum])[wheretogo].wait();            // everybody off when elevator reaches next stop
  //cout << "exited " << elevatorNum << endl;
}

// Model segment 3: the elevator car

void elevator(int elevatorNum, int currfloor, int direction) {
  create ("elevator");
  //cout << "CREATED ELEVATOR" << endl;
  while(1) {  // loop forever
    // start off in idle state, waiting for the first call...
    rest->reserve();                  // relax at curr floor till called from somewhere (NEEDED TO TRACK HOW LONG SOMEONE RESTS)
    direction = 0;
    //cout << "going to sleep" << endl;
    (*wake_elevator).wait();	     //waits for manager to detect someone
    //cout << "woke up" << endl;
    direction = waitingfloor - currfloor;    //positive if waiting floor > currfloor
    rest->release();                   // and back to work we go!
    //cout << "got out" << endl;
    long seats_used = 0;              // elevator is initially empty
    elevator_occ[elevatorNum].note_value(seats_used);
    //cout << "hello" << endl;
    // Keep going around the loop until there are no calls waiting
    currfloor = loop_building(seats_used, elevatorNum, currfloor, direction);
  }
}

int loop_building(long & seats_used, int elevatorNum, int currfloor, int &direction) { // one trip around the building
  // Start by picking up departing passengers at car lot
  hold(2); //open doors
  load_elevator(LOBBY, seats_used, elevatorNum, direction); //get a direction
  //cout << "leaving lobby with "<< seats_used << endl;
  if(direction > 0) direction = 1; // simplifies the direction down to 1 or -1 to make addition work later
  if(direction < 0) direction = -1;

  hold(3); //close doors

  int oldFloor = currfloor; //elevator to stop at

  elevator_occ[elevatorNum].note_value(seats_used); //set seats on table
  //cout << seats_used << " people on car" << elevatorNum << " " <<direction << endl;;

  for(; currfloor < numFloors && currfloor >= 0 && direction != 0; currfloor += direction){ //FIX - elevator does not stop at every floor

    if(seats_used == NUM_SEATS && (*here_is_floor[elevatorNum])[currfloor].wait_cnt() == 0) //if seats are full and no one is waiting for this floor, skip it
       continue;
    
    hold(5 * sqrt(abs(currfloor - oldFloor)));  // fix this 1 and 0 should be last floor and new floor
    oldFloor = currfloor; //So the above if skips this and this allows the below function to work
    //cout << "looking for here is floor " << elevatorNum << " " << currfloor << endl;

  // drop off all departing passengers at building floor
    if((*here_is_floor[elevatorNum])[currfloor].wait_cnt()) {
     cout << "pop\n"; 
      //cout << (*here_is_floor[elevatorNum])[currfloor].wait_cnt() << " people getting off " << elevatorNum << endl;
      seats_used -= (*here_is_floor[elevatorNum])[currfloor].wait_cnt();
      hold(2); //open door
      (*here_is_floor[elevatorNum])[currfloor].set(); // open door and let them off
      elevator_occ[elevatorNum].note_value(seats_used);
      hold(uniform(5,15)); // wait for unloading 
      (*here_is_floor[elevatorNum])[currfloor].clear(); // open door and let them off
      hold(3); //close door
      if(seats_used == 0) direction = 0;
   }
   elevator_occ[elevatorNum].note_value(seats_used);

    // pick up arriving passengers at building terminal
    load_elevator(currfloor, seats_used, elevatorNum, direction);
    if(direction == 0) return currfloor;
   
    }

  //All passengers off at top or bottom floors
  if(seats_used > 0) {
    seats_used = 0;
    hold(2);
    (*here_is_floor[elevatorNum])[currfloor].set(); // open door and let them off
    hold(uniform(5,15)); //unload
    hold(3); // close doors
    elevator_occ[elevatorNum].note_value(seats_used);
  }
  return currfloor;
  // Back to starting point. Bus is empty. Maybe I can rest...
}

void load_elevator(long whereami, long & on_board, int elevatorNum, int &direction)  // manage passenger loading
{
  //sets direction if starting from rest
  if(direction == 0 && ((*going_up)[whereami].wait_cnt())) direction = 1; 
  else if(direction == 0 && ((*going_dn)[whereami].wait_cnt())) direction = -1; 
  else if (direction == 0) return; //noone at floor, so return
  //cout << "hi" << endl;
  // invite passengers to enter, one at a time, until all seats are full
  if(direction > 0) { //if going up
     while((on_board < NUM_SEATS) && ((*going_up)[whereami].wait_cnt()) &&
    	((*buttons)[whereami].num_busy() + (*buttons)[whereami].qlength() > 0))
     {
        (*going_up)[whereami].set(); //tell floor that elevator going up arrived (its the arrow light above the elevator)
        hop_on[whereami].send(elevatorNum);// invite one person to board
	(*going_up)[whereami].clear(); //turn off the light
        (*boarded)[elevatorNum].wait();  // pause until that person is seated
        on_board++; 
        hold(TINY);  // let next passenger (if any) reset the button
     }
   }
   else if(direction < 0) { //going down
     while((on_board < NUM_SEATS) && ((*going_dn)[whereami].wait_cnt()) && 
    	((*buttons)[whereami].num_busy() + (*buttons)[whereami].qlength() > 0)) 
     {
	(*going_dn)[whereami].set(); //arrow light
        hop_on[whereami].send(elevatorNum);// invite one person to board
	(*going_dn)[whereami].clear(); //turn off arrow light
        (*boarded)[elevatorNum].wait();  // pause until that person is seated
        on_board++;
        hold(TINY);  // let next passenger (if any) reset the button
     }
  }
  hold(uniform(5,15)); //time spent loading
}
