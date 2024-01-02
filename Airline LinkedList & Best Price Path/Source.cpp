/*
            FALL 2023-2024, CS-204 HOMEWORK#2
               © OSMAN SAH YILMAZ, 31316
                    28 October 2023
*/


#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace std;

int flight_id_counter = 0;
int airline_id_counter = 0;

struct flight {
    string from;
    string to;
    int hour;
    int min;
    int price;
    int ID;

    flight* next;
    flight* prev;

    //TO DO: implemented constructor
    //Hint: You may need to implement multiple constructors
    flight(string f, string t, int h, int m, int p, int id)
        : from(f), to(t), hour(h), min(m), price(p), ID(id), next(nullptr), prev(nullptr)
    {};

};

struct airline {
    string name;
    int ID;
    airline* next;
    flight* flights;

    //TO DO: implemented constructor
    //Hint: You may need to implement multiple constructors
    airline(string n, int id, airline* ne = nullptr)
        : name(n), ID(id), next(ne), flights(nullptr) {};
};

//introsort to sort flights based on hours and mins
bool compareFlights(const flight& flight1, const flight& flight2) {
    if (flight1.hour != flight2.hour) {
        return flight1.hour < flight2.hour;
    }
    return flight1.min < flight2.min;
}

void sortFlights(vector<vector<flight>>& flights) {
    for (vector<flight>& flightList : flights) {
        sort(flightList.begin(), flightList.end(), compareFlights);
    }
}

pair<vector<string>, vector<vector<flight>>> read_files(bool input_done) {

    ///READ FLIGHTS///
    vector<string> airlines;
    vector<vector<flight>> flights(100); //start with a previously sized vector or you get seg fault (for sure) (THANKS)
    int flight_id_counter = 0;

    while (not input_done) {
        string airline_name;
        string filename;
        cout << "Enter the name of airline: ";
        cin >> airline_name;
        cout << "Enter the name of airline file: ";
        cin >> filename;
        ifstream input(filename);

        if (filename == "done") {
            input_done = true;
            return make_pair(airlines, flights);
        }

        while (input.fail()) {
            cout << "Could not open file: " << filename << endl;
            cout << "Enter the name of airline: ";
            cin >> airline_name;
            cout << "Enter the name of airline file: ";
            cin >> filename;
            input.open(filename);

            if (filename == "done") {
                input_done = true;
                return make_pair(airlines, flights);
            }
        }

        airlines.push_back(airline_name);


        cout << "Processing input file: " << filename << endl;

        int line_no = 0;
        vector<string> lines;
        string line;
        int vector_location = airlines.size() - 1;
        while (getline(input, line)) {
            lines.push_back(line);
            line_no += 1;
            if (line_no % 5 == 0) {
                flight a_flight(lines[line_no - 5], lines[line_no - 4], stoi(lines[line_no - 3]), stoi(lines[line_no - 2]), stoi(lines[line_no - 1]), ::flight_id_counter++);
                flights[vector_location].push_back(a_flight);
            }
        }
    }
    if (input_done) {
        cout << "Input files are already read, however you can do manual changes.." << endl;
    }

    return make_pair(airlines, flights);
}



airline* make_linked_list_structure(vector<string> airlines, vector<vector<flight>> flights) {
    //TO DO: Implemented
    airline* head = nullptr;
    airline* currentAirline = nullptr;
    sortFlights(flights);
    /*
    for (int i = 0; i < flights.size(); i++) {
        for (int j = 0; j < flights[i].size(); j++) {
            cout << flights[i][j].from << "  " << flights[i][j].hour << "  " << flights[i][j].min << endl;
        }
    }
    */
    
    for (size_t i = 0; i < airlines.size(); i++) {
        airline* newAirline = new airline(airlines[i], ::airline_id_counter++);
        // Add flights to the airline
        flight* prevFlight = nullptr;


        for (size_t j = 0; j < flights[i].size(); j++) {
            flight* newFlight = new flight(flights[i][j].from, flights[i][j].to, flights[i][j].hour, flights[i][j].min, flights[i][j].price, flights[i][j].ID);

            if (!newAirline->flights) {
                newAirline->flights = newFlight;
            }
            else {
                prevFlight->next = newFlight;
                newFlight->prev = prevFlight;
            }

            prevFlight = newFlight;
            if (j == flights[i].size()) {
                newFlight->next = nullptr;
                break;
            }
        }

        if (!head) {
            head = newAirline;
        }
        else {
            currentAirline->next = newAirline;
        }

        currentAirline = newAirline;
        if (i == airlines.size()) {
            newAirline->next = nullptr;
            break;
        }
    }


    return head;
}

void print_all(airline* head) {
    airline* currentAirline = head;
    if (!currentAirline) {
        cout << "List is empty." << endl;
    }else{
        while (currentAirline != nullptr) {
            // Print airline name
            cout << "###################################" << endl;
            cout << "### AIRLINE ID: " << currentAirline->ID << " ###" << endl;
            cout << "NAME:" << currentAirline->name << endl;
            cout << "FLIGHTS: ";
            flight* currentFlight = currentAirline->flights;
            while (currentFlight != nullptr) {
                // Print flight information
                cout << "#[" << currentFlight->ID << "|" << currentFlight->from << "->" << currentFlight->to << "|" << currentFlight->hour << ":" << currentFlight->min << "|" << currentFlight->price << "TRY" << "]#";
                // Move to the next flight
                currentFlight = currentFlight->next;

            }
            // Move to the next airline
            currentAirline = currentAirline->next;
        }
    }
    

}

void add_flight_with_input(airline* head) {
    string AIRLINE, FROM, TO;
    int HOUR, MIN, PRICE;
    bool found = false;
    flight* currentFlight = 0;

    cout << "AIRLINE: ";
    cin >> AIRLINE;
    cout << "FROM: ";
    cin >> FROM;
    cout << "TO: ";
    cin >> TO;
    cout << "HOUR: ";
    cin >> HOUR;
    cout << "MIN: ";
    cin >> MIN;
    cout << "PRICE: ";
    cin >> PRICE;

    flight* newFlight = new flight(FROM, TO, HOUR, MIN, PRICE, ::flight_id_counter++);
    cout << "Flight ID " << (flight_id_counter-1) << " is added to the list.." << endl;

    airline* currentAirline = head;
    while (true) {
        if (currentAirline->name == AIRLINE) {
            found = true;
            currentFlight = currentAirline->flights;
            // Find the correct position to insert the new flight
            while (currentFlight->next != nullptr && (currentFlight->next->hour < newFlight->hour || (currentFlight->next->hour == newFlight->hour && currentFlight->next->min < newFlight->min))) {
                currentFlight = currentFlight->next;
            }
        }
        if (found) {
            newFlight->next = currentFlight->next;
            newFlight->prev = currentFlight;
            if (currentFlight->next != nullptr) {
                currentFlight->next->prev = newFlight;
            }
            currentFlight->next = newFlight;
            break;
        }
        if (currentAirline->next == nullptr && !found) {
            airline* newAirline = new airline(AIRLINE, ::airline_id_counter++);
            currentAirline->next = newAirline; // Connect the new airline to the existing list
            cout << "New airline " << newAirline->name << endl;
            newAirline->flights = newFlight;
            newFlight->prev = nullptr;
            newFlight->next = nullptr;
            newAirline->next = nullptr;
            break;
        }
        currentAirline = currentAirline->next;
    }
}

void remove_flight_with_input(airline* head) {
    airline* currentAirline = head;
    airline* prevAirline = nullptr;
    int flight_id;

    cout << "Flight id to remove: ";
    cin >> flight_id;

    while (currentAirline) {
        flight* currentFlight = currentAirline->flights;
        flight* prevFlight = nullptr;

        while (currentFlight) {
            if (currentFlight->ID == flight_id) {
                // Flight with the given ID found, remove it
                if (prevFlight) {
                    prevFlight->next = currentFlight->next;
                }
                else {
                    currentAirline->flights = currentFlight->next;
                }
                delete currentFlight;
                cout << "Removing flight id: " << flight_id << endl;

                // Check if the airline has no more flights
                if (currentAirline->flights == nullptr) {
                    if (prevAirline) {
                        prevAirline->next = currentAirline->next;
                    }
                    else {
                        head = currentAirline->next;
                    }
                    cout << "Flight ID "<< flight_id <<" is removed from the list..";
                    cout << "Removing airline " << currentAirline->name << endl;
                    delete currentAirline;
                }
                return; // Flight removed, exit function
            }
            prevFlight = currentFlight;
            currentFlight = currentFlight->next;
        }

        prevAirline = currentAirline;
        currentAirline = currentAirline->next;
    }

    cout << "There is no flight with id " << flight_id << endl;
}

// Recursive function to find all paths
void findPaths(airline* head, airline* currentAirline, const string& currentLocation, int transfersLeft, vector<flight*>& currentPath, vector<vector<flight*>>& allPaths, const string& destination) {
    if (transfersLeft < 0) {
        return;
    }

    flight* currentFlight = currentAirline->flights;
    while (currentFlight) {
        if (currentFlight->from == currentLocation) {
            // Add the current flight to the path.
            currentPath.push_back(currentFlight);

            if (currentFlight->to == destination) {
                // If the destination is reached, add the path to allPaths.
                allPaths.push_back(currentPath);
            }
            else {
                // Recursively search for paths from the destination of the current flight.
                findPaths(head, head, currentFlight->to, transfersLeft - 1, currentPath, allPaths, destination);
            }

            // Remove the last flight to backtrack correctly.
            currentPath.pop_back();
        }
        // Move to the next flight of the current airline.
        currentFlight = currentFlight->next;
        if (currentFlight == nullptr && currentAirline->next != nullptr) {
            currentAirline = currentAirline->next;
            currentFlight = currentAirline->flights;
        }
        else if (currentFlight == nullptr && currentAirline->next == nullptr) {
            break;
        }
    }
}

int pathfinder(airline* head) {

    //TO DO: Implemented
    //Hint: A recursive search seems like the best solution.
    //Hint: You don't have to use doubly linked list features
    cout << "Where are you now?" << endl;
    string source;
    cin >> source;

    cout << "Where do you want to go?" << endl;
    string destination;
    cin >> destination;

    cout << "Maximum number of transfers: " << endl;
    int maxTransfers;
    cin >> maxTransfers;
    

    //finding all paths
    vector<vector<flight*>> allPaths;
    airline* currentAirline = head;
    vector<flight*> currentPath; // Initialize an empty path.
    findPaths(head, currentAirline, source, maxTransfers, currentPath, allPaths, destination);

    //finding best price & path
    int bestPrice = 0;
    if (allPaths.size() == 1) {
        for (size_t i = 0; i < allPaths[0].size(); i++) {
            bestPrice += allPaths[0][i]->price;
        }
    }
    int first = 0, sec = 0;
    while (allPaths.size() > 1){
        first = 0, sec = 0;
        for (size_t i = 0; i < allPaths[0].size(); i++){
            first += allPaths[0][i]->price;
        }
        for (size_t i = 0; i < allPaths[1].size(); i++){
            sec += allPaths[1][i]->price;
        }
        if (first>sec){
            bestPrice = sec;
            allPaths.erase(allPaths.begin());
        }
        else {
            bestPrice = first;
            allPaths.erase(allPaths.begin() + 1);
        }
    }

    // printing path
    
    if (allPaths.size() == 1) {
        cout << "##Best price path##" << endl;
        for (size_t i = 0; i < allPaths[0].size(); i++)
        {
            cout << "[" << allPaths[0][i]->ID << "|" << allPaths[0][i]->from << "->" << allPaths[0][i]->to << "|" << allPaths[0][i]->hour << ":" << allPaths[0][i]->min << "|" << allPaths[0][i]->price << "]";
            if (i != allPaths[0].size() - 1)
            {
                cout << "->";
            }
        }
        cout << " $TOTAL PRICE: " << bestPrice << endl;
    }
    else {
        cout << "No path found between " << source << " and " << destination << endl;

    }
    allPaths.clear();
    return 1;
}


void delete_linked_list(airline*& head) {
    //TO DO: Implemented
    while (head != nullptr) {
        airline* currentAirline = head;
        head = head->next;

        flight* currentFlight = currentAirline->flights;
        while (currentFlight != nullptr) {
            flight* nextFlight = currentFlight->next;
            delete currentFlight;
            currentFlight = nextFlight;
        }

        delete currentAirline;
    }
}



//
void printMainMenu() {
    cout << endl;
    cout << "I***********************************************I" << endl
        << "I               0 - DELETE DATA                 I" << endl
        << "I               1 - READ FILES                  I" << endl
        << "I               2 - PRINT ALL FLIGHTS           I" << endl
        << "I               3 - ADD FLIGHT                  I" << endl
        << "I               4 - REMOVE FLIGHT               I" << endl
        << "I               5 - PATH FINDER                 I" << endl
        << "I               6 - EXIT                        I" << endl
        << "I***********************************************I" << endl
        << ">>";
    cout << endl;
}

void processMainMenu() {

    pair<vector<string>, vector<vector<flight>>> lines_flights;
    airline* head = 0;
    bool input_done = false;

    char input;
    do {
        printMainMenu();
        cout << "Please enter your option " << endl;
        cin >> input;
        switch (input) {
        case '0':
            delete_linked_list(head);
            cout << "Data is deleted!" << endl;
            input_done = false;
            break;
        case '1':
            if (not input_done) {
                lines_flights = read_files(input_done);
                head = make_linked_list_structure(lines_flights.first, lines_flights.second);
                cout << "Files are read.." << endl;
            }
            else {
                cout << "Files are already read.." << endl;
            }
            input_done = true;
            break;
        case '2':
            print_all(head);
            break;
        case '3':
            cout << "Adding manual entry:" << endl;
            add_flight_with_input(head);
            break;
        case '4':
            remove_flight_with_input(head);
            break;
        case '5':
            pathfinder(head);
            break;
        case '6':
            cout << "Exiting.." << endl;
            exit(0);
        default:
            cout << "Invalid option: please enter again" << endl;
        }
    } while (true);
}
//


int main() {

    processMainMenu();
    //Comply with the provided structs and specified linked list structure for a seamless grading

    return 0;

}




