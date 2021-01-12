#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct seats{
    int fClassAvail;
    int fClassRes;
    int fClassSold;
    int coachAvail;
    int coachRes;
    int coachSold;
};

struct when{
    string dateDeparture;
    string timeDeparture;
    string dateArrival;
    string timeArrival;
};

struct flight{
    string flightCode;
    string cityDeparture;
    string destination;
    seats planeSeats;
    when planeW;
};

flight airline;

void create(ofstream &data, ofstream &flightcode){
    cout << endl;
    cout << "CREATE FLIGHT RECORDS" << endl;
    cout << "========================================" << endl;

    cout << "Flight Code (e.g CGK-GA1020)\t\t: ";
    cin.get();
    getline(cin, airline.flightCode);
    data << "Flight Code\t\t\t\t\t\t\t\t\t: " << airline.flightCode << endl;
    flightcode << airline.flightCode << endl;

    cout << "City of Departure (e.g Jakarta)\t\t: ";
    getline(cin, airline.cityDeparture);
    data << "City of Departure\t\t\t\t\t\t\t: " << airline.cityDeparture << endl;

    cout << "Destination (e.g Bali)\t\t\t: ";
    getline(cin, airline.destination);
    data << "Destination\t\t\t\t\t\t\t\t\t: " << airline.destination << endl;

    cout << "Date of Departure (e.g 6 January 2021)\t: ";
    getline(cin, airline.planeW.dateDeparture);
    data << "Date of Departure\t\t\t\t\t\t\t: " << airline.planeW.dateDeparture << endl;

    cout << "Time of Departure (e.g 01.00 PM)\t: ";
    getline(cin, airline.planeW.timeDeparture);
    data << "Time of Departure\t\t\t\t\t\t\t: " << airline.planeW.timeDeparture << endl;

    cout << "Date of Arrival (e.g 6 January 2021)\t: ";
    getline(cin, airline.planeW.dateArrival);
    data << "Date of Arrival\t\t\t\t\t\t\t\t: " << airline.planeW.dateArrival << endl;

    cout << "Time of Arrival (e.g 02.30 PM)\t\t: ";
    getline(cin, airline.planeW.timeArrival);
    data << "Time of Arrival\t\t\t\t\t\t\t\t: " << airline.planeW.timeArrival << endl;

    cout << "Number of First-Class Seats (AVAILABLE)\t: ";
    cin >> airline.planeSeats.fClassAvail;
    data << "Number of First-Class Seats (AVAILABLE)\t\t: " << airline.planeSeats.fClassAvail << endl;

    airline.planeSeats.fClassRes = 0;
    data << "Number of First-Class Seats (RESERVATION)\t: " << airline.planeSeats.fClassRes << endl;

    cout << "Number of First-Class Seats (SOLD)\t: ";
    cin >> airline.planeSeats.fClassSold;
    data << "Number of First-Class Seats (SOLD)\t\t\t: " << airline.planeSeats.fClassSold << endl;

    cout << "Number of Coach Seats (AVAILABLE)\t: ";
    cin >> airline.planeSeats.coachAvail;
    data <<"Number of Coach Seats (AVAILABLE)\t\t\t: " << airline.planeSeats.coachAvail << endl;

    airline.planeSeats.coachRes = 0;
    data << "Number of Coach Seats (RESERVATION)\t\t\t: " << airline.planeSeats.coachRes << endl;

    cout << "Number of Coach Seats (SOLD)\t\t: ";
    cin >> airline.planeSeats.coachSold;
    data << "Number of Coach Seats (SOLD)\t\t\t\t: " << airline.planeSeats.coachSold << endl;
    
    cout << endl;
}

void erase(ofstream &outfile, ofstream &flightfile, ifstream &inflight, ifstream &infile){
    cout << endl;

    // untuk menunjukkan Flight Code ke user
    string data;
    
    int testEmpty = 0;
    while (!inflight.eof()){
        getline(inflight, data);
        if (data == "" && testEmpty == 0){
            cout << "There is no Flight Records" << endl;
            return;
        }
        if (testEmpty == 0){
            cout << "LIST OF FLIGHT RECORDS" << endl;
            cout << "========================================" << endl;
        }
        cout << data << endl;
        testEmpty++;
    }
    

    // input Flight Code yang ingin di-delete
    string codeErase;
    cout << "DELETE FLIGHT RECORDS" << endl;
    cout << "========================================" << endl;
    cout << "Enter The Flight Code\t: ";
    cin.get();
    getline(cin, codeErase);

    // membuka ulang flightcode.txt
    inflight.close();
    inflight.open("flightcode.txt");

    // mencari apakah input user ada pada Data Flight Code
    ofstream oTempFC;
    ifstream iTempFC;
    oTempFC.open("flightcodeTemp.txt", ios::trunc);
    int i = 1;
    bool found = false;
    while(!inflight.eof()){
        string code;
        getline(inflight, code);
        if (code == codeErase){
            // jika ada 2 flight code sama
            if (found == true){
                oTempFC << code << endl;
                continue;
            }
            found = true;
            continue;
        }
        oTempFC << code << endl; // => input FlightCode ke flightcodeTemp.txt
        if (found==true){
            continue;
        }
        i+=13;
    }

    // jika tidak ada,
    if (found == false){
        cout << "Not Found!" << endl;
        return;
    }
    
    flightfile.close();
    flightfile.open("flightcode.txt", ios::trunc);
    flightfile.close();
    flightfile.open("flightcode.txt");
    iTempFC.open("flightcodeTemp.txt");
    while(!iTempFC.eof()){
        string codeTemp;
        getline(iTempFC, codeTemp);
        if (codeTemp == "") continue;
        flightfile << codeTemp << endl;
    }
    

    // memasukkan data ke temp.txt
    // flight records yang ingin di-delete tidak dimasukkan ke temp.txt;
    ofstream tempData;
    ifstream inTempData;
    tempData.open("temp.txt", ios::trunc);
    infile.close();
    infile.open("data.txt");
    int j;
    for (j = 1; !infile.eof(); j++){
        string temp;
        if (j >= i && j<=i+12){
            getline(infile, temp);
            continue;
        }
        getline(infile, temp);
        tempData << temp << endl;
    }
    
    infile.close();
    inTempData.open("temp.txt");

    // menghapus semua data yang terdapat pada Data Utama
    outfile.close();
    outfile.open("data.txt", ios::trunc);
    outfile.close();
    outfile.open("data.txt");

    int k = 1;
    while(k!=j){
        string transfer;
        getline(inTempData, transfer);
        if (transfer == "") {
            k++;
            continue;
        }
        outfile << transfer << endl;
        k++;
    }
    infile.open("data.txt");

    cout << endl;
    cout << "Flight Records Deleted" << endl;
}

void update(ofstream &outfile, ofstream &flightfile, ifstream &inflight, ifstream &infile){
    cout << endl;

    string data;
    int testEmpty = 0;
    while (!inflight.eof()){
        getline(inflight, data);
        if (data == "" && testEmpty == 0){
            cout << "There is no Flight Records" << endl;
            return;
        }
        if (testEmpty == 0){
            cout << "LIST OF FLIGHT RECORDS" << endl;
            cout << "========================================" << endl;
        }
        cout << data << endl;
        testEmpty++;
    }

    string codeUpdate;
    cout << "UPDATE FLIGHT RECORDS" << endl;
    cout << "========================================" << endl;
    cout << "Enter The Flight Code\t: ";
    cin.get();
    getline(cin, codeUpdate);

    inflight.close();
    inflight.open("flightcode.txt");

    bool found = false;
    int i = 1;
    while(!inflight.eof()){
        string code;
        getline(inflight, code);
        if (code == codeUpdate){
            found = true;
            break;
        }
        i+=13;
    }

    if (found == false){
        cout << "Not Found!" << endl;
        return;
    }

    int j = 1;
    ofstream update;
    ifstream inUpdate;
    update.open("update.txt", ios::trunc);
    while (!infile.eof()){
        string transfer;
        getline(infile, transfer);
        if (j==i){
            update << transfer << endl;

            for (int k = i+1; k<=i+7; k++){
                getline(infile, transfer);
            }

            //input ulang
            cout << "City of Departure (e.g Jakarta)\t\t: ";
            getline(cin, airline.cityDeparture);
            update << "City of Departure\t\t\t\t\t\t\t: " << airline.cityDeparture << endl;

            cout << "Destination (e.g Bali)\t\t\t: ";
            getline(cin, airline.destination);
            update << "Destination\t\t\t\t\t\t\t\t\t: " << airline.destination << endl;

            cout << "Date of Departure (e.g 6 January 2021)\t: ";
            getline(cin, airline.planeW.dateDeparture);
            update << "Date of Departure\t\t\t\t\t\t\t: " << airline.planeW.dateDeparture << endl;

            cout << "Time of Departure (e.g 01.00 PM)\t: ";
            getline(cin, airline.planeW.timeDeparture);
            update << "Time of Departure\t\t\t\t\t\t\t: " << airline.planeW.timeDeparture << endl;

            cout << "Date of Arrival (e.g 6 January 2021)\t: ";
            getline(cin, airline.planeW.dateArrival);
            update << "Date of Arrival\t\t\t\t\t\t\t\t: " << airline.planeW.dateArrival << endl;

            cout << "Time of Arrival (e.g 02.30 PM)\t\t: ";
            getline(cin, airline.planeW.timeArrival);
            update << "Time of Arrival\t\t\t\t\t\t\t\t: " << airline.planeW.timeArrival << endl;

            cout << "Number of First-Class Seats (AVAILABLE)\t: ";
            cin >> airline.planeSeats.fClassAvail;
            update << "Number of First-Class Seats (AVAILABLE)\t\t: " << airline.planeSeats.fClassAvail << endl;
            
            string fRes;
            getline(infile, fRes);
            update << fRes << endl;

            for (int k = i+9; k<= i+10; k++){
                getline(infile, transfer);
            }


            cout << "Number of First-Class Seats (SOLD)\t: ";
            cin >> airline.planeSeats.fClassSold;
            update << "Number of First-Class Seats (SOLD)\t\t\t: " << airline.planeSeats.fClassSold << endl;

            cout << "Number of Coach Seats (AVAILABLE)\t: ";
            cin >> airline.planeSeats.coachAvail;
            update << "Number of Coach Seats (AVAILABLE)\t\t\t: " << airline.planeSeats.coachAvail << endl;

            string cRes;
            getline(infile, cRes);
            update << cRes << endl;

            getline (infile, transfer);

            cout << "Number of Coach Seats (SOLD)\t\t: ";
            cin >> airline.planeSeats.coachSold;
            update << "Number of Coach Seats (SOLD)\t\t\t\t: " << airline.planeSeats.coachSold << endl;
            j+=12;
            continue;
        }
        update << transfer << endl;
        j++;
    }

    infile.close();
    infile.open("data.txt");
    inUpdate.open("update.txt");
    outfile.close();
    outfile.open("data.txt", ios::trunc);
    outfile.close();
    outfile.open("data.txt");

    int k = 1;
    while(k!=j){
        string trfToData;
        getline(inUpdate, trfToData);
        outfile << trfToData << endl;
        k++;
    }
    inUpdate.close();
    update.close();
}

void reservation(ofstream &outfile, ifstream &inflight, ifstream &infile){
    int command;
    cout << endl;
    cout << "RESERVATION FLIGHT RECORDS" << endl;
    cout << "========================================" << endl;
    cout << "1 = Make Reservation" << endl;
    cout << "2 = Cancel Reservation" << endl;
    cout << "Enter the number: ";
    cin >> command;

    if (command == 1){
        cout << endl;
        string data, codeReservation;
        int testEmpty = 0;
        while (!inflight.eof()){
            getline(inflight, data);
            if (data == "" && testEmpty == 0){
                cout << "There is no Flight Records" << endl;
                return;
            }
            if (testEmpty == 0){
                cout << "LIST OF FLIGHT RECORDS" << endl;
                cout << "========================================" << endl;
            }
            cout << data << endl;
            testEmpty++;
        }
        cout << "Enter The Flight Code\t: ";
        cin.get();
        getline(cin, codeReservation);

        inflight.close();
        inflight.open("flightcode.txt");

        bool found = false;
        int i = 1;
        while(!inflight.eof()){
            string code;
            getline(inflight, code);
            if (code == codeReservation){
                found = true;
                break;
            }
            i+=13;
        }

        if(found == false){
            cout << "Not Found!" << endl;
            return;
        }

        cout << endl;
        int commandSeats;
        cout << "SEATS" << endl;
        cout << "========================================" << endl;
        cout << "1 = First-Class Seats" << endl;
        cout << "2 = Coach Seats" << endl;
        cout << "Enter The Number: ";
        cin >> commandSeats;
        cin.get();

        if (commandSeats == 1){
            int j = 1;
            while(!infile.eof()){
                string ava;
                getline(infile, ava);
                if (j == i+7){
                    cout << endl;
                    cout << ava << endl;
                }
                j++;
            }
            infile.close();
            infile.open("data.txt");

            int numRes;
            cout << endl;
            cout << "Number of Reservation\t: ";
            cin >> numRes;

            ofstream tempRData;
            ifstream inRData;
            tempRData.open("tempRes.txt", ios::trunc);

            int k = 1;
            while(!infile.eof()){
                string transfer;
                getline(infile, transfer);
                if (k == i+8){
                    tempRData << "Number of First-Class Seats (RESERVATION)\t: " << numRes << endl;
                    k++;
                    continue;
                }
                tempRData << transfer << endl;
                k++;
            }

            infile.close();
            inRData.open("tempRes.txt");
            outfile.close();
            outfile.open("data.txt", ios::trunc);
            outfile.close();
            outfile.open("data.txt");

            while(!inRData.eof()){
                string transfer;
                getline(inRData, transfer);
                if(transfer == "") break;
                outfile << transfer << endl;
            }

            infile.open("data.txt");
        }

        else if (commandSeats == 2){
            int j = 1;
            while(!infile.eof()){
                string ava;
                getline(infile, ava);
                if (j == i+10){
                    cout << endl;
                    cout << ava << endl;
                }
                j++;
            }
            infile.close();
            infile.open("data.txt");

            int numRes;
            cout << endl;
            cout << "Number of Reservation\t: ";
            cin >> numRes;

            ofstream tempRdata;
            ifstream inRData;
            tempRdata.open("tempRes.txt", ios::trunc);

            int k = 1;
            while(!infile.eof()){
                string transfer;
                getline(infile, transfer);
                if (k == i+11){
                    tempRdata << "Number of Coach Seats (RESERVATION)\t\t\t: " << numRes << endl;
                    k++;
                    continue;
                }
                tempRdata << transfer << endl;
                k++;
            }

            infile.close();
            inRData.open("tempRes.txt");
            outfile.close();
            outfile.open("data.txt", ios::trunc);
            outfile.close();
            outfile.open("data.txt");

            while (!inRData.eof()){
                string transfer;
                getline(inRData, transfer);
                if (transfer == "") break;
                outfile << transfer << endl;
            }

            infile.open("data.txt");
        }

        else {
            cout << "Wrong Input!" << endl;
            return;
        }

    }

    else if (command == 2){
        cout << endl;
        string data, codeReservation;
        int testEmpty = 0;
        while (!inflight.eof()){
            getline(inflight, data);
            if (data == "" && testEmpty == 0){
                cout << "There is no Flight Records" << endl;
                return;
            }
            if (testEmpty == 0){
                cout << "LIST OF FLIGHT RECORDS" << endl;
                cout << "========================================" << endl;
            }
            cout << data << endl;
            testEmpty++;
        }
        cout << "Enter The Flight Code\t: ";
        cin.get();
        getline(cin, codeReservation);

        inflight.close();
        inflight.open("flightcode.txt");

        bool found = false;
        int i = 1;
        while (!inflight.eof()){
            string code;
            getline(inflight, code);
            if (code == codeReservation){
                found = true;
                break;
            }
            i += 13;
        }

        if (found == false){
            cout << "Not Found!" << endl;
            return;
        }

        cout << endl;
        int commandSeats;
        cout << "SEATS" << endl;
        cout << "========================================" << endl;
        cout << "1 = First-Class Seats" << endl;
        cout << "2 = Coach Seats" << endl;
        cout << "Enter The Number: ";
        cin >> commandSeats;
        cin.get();

        if (commandSeats == 1){
            int j = 1;
            while (!infile.eof()){
                string ava;
                getline(infile, ava);
                if (j == i + 8){
                    cout << endl;
                    cout << ava << endl;
                }
                j++;
            }
            infile.close();
            infile.open("data.txt");

            int numCancelRes, numRes;
            cout << endl;
            cout << "Number of Reservation\t: ";
            cin >> numRes;
            cout << "Cancel of Reservation\t: ";
            cin >> numCancelRes;

            ofstream tempRData;
            ifstream inRData;
            tempRData.open("tempRes.txt", ios::trunc);

            int k = 1;
            while (!infile.eof()){
                string transfer;
                getline(infile, transfer);
                if (k == i + 8){
                    tempRData << "Number of First-Class Seats (RESERVATION)\t: " << numRes-numCancelRes << endl;
                    k++;
                    continue;
                }
                if (transfer == "") break;
                tempRData << transfer << endl;
                k++;
            }

            infile.close();
            inRData.open("tempRes.txt");
            outfile.close();
            outfile.open("data.txt", ios::trunc);
            outfile.close();
            outfile.open("data.txt");

            while (!inRData.eof()){
                string transfer;
                getline(inRData, transfer);
                if (transfer == "") break;
                outfile << transfer << endl;
            }

            infile.open("data.txt");
        }

        else if (commandSeats == 2){
            int j = 1;
            while (!infile.eof()){
                string ava;
                getline(infile, ava);
                if (j == i + 11)
                {
                    cout << endl;
                    cout << ava << endl;
                }
                j++;
            }
            infile.close();
            infile.open("data.txt");

            int numCancelRes, numRes;
            cout << endl;
            cout << "Number of Reservation\t: ";
            cin >> numRes;
            cout << "Cancel of Reservation\t: ";
            cin >> numCancelRes;

            ofstream tempRData;
            ifstream inRData;
            tempRData.open("tempRes.txt", ios::trunc);

            int k = 1;
            while (!infile.eof()){
                string transfer;
                getline(infile, transfer);
                if (k == i + 11){
                    tempRData << "Number of Coach Seats (RESERVATION)\t\t\t: " << numRes - numCancelRes << endl;
                    k++;
                    continue;
                }
                if (transfer == "")
                    break;
                tempRData << transfer << endl;
                k++;
            }

            infile.close();
            inRData.open("tempRes.txt");
            outfile.close();
            outfile.open("data.txt", ios::trunc);
            outfile.close();
            outfile.open("data.txt");

            while (!inRData.eof()){
                string transfer;
                getline(inRData, transfer);
                if (transfer == "")
                    break;
                outfile << transfer << endl;
            }

            infile.open("data.txt");
        }

        else{
            cout << "Wrong Input!" << endl;
            return;
        }
    }
   
    else{
        cout << "Wrong Input!" << endl;
    }
}

int main(){

    // Data Utama
    ofstream outfile;
    ifstream infile;

    // Data Flight Code 
    ofstream flightfile;
    ifstream inflight;


    outfile.open("data.txt", ios::app);
    flightfile.open("flightcode.txt", ios::app);
    if (!outfile.is_open()){
        outfile.open("data.txt", ios::trunc);
    }
    if (!flightfile.is_open()){
        flightfile.open("flightcode.txt", ios::trunc);
    }
    infile.open("data.txt");
    inflight.open("flightcode.txt");

    int command;

start:
    cout << endl;
    cout << "WELCOME TO AIRLINE RESERVATION SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "1 = Create Flight Records" << endl;
    cout << "2 = Delete Flight Records" << endl;
    cout << "3 = Update Flight Records" << endl;
    cout << "4 = Reservation" << endl;
    cout << "0 = Exit" << endl;
    cout << "Enter the number: ";
    cin >> command;

    enum option{
        EXIT = 0,
        CREATE = 1,
        DELETE,
        UPDATE,
        RESERVATION
    };

    if (command == EXIT){
        infile.close();
        outfile.close();
        return 0;
    }
    else if (command == CREATE){
        create(outfile, flightfile);
    }
    else if (command == DELETE){
        erase(outfile, flightfile, inflight, infile);
        inflight.close();
        inflight.open("flightcode.txt");
    }
    else if (command == UPDATE){
        update(outfile, flightfile, inflight, infile);
        inflight.close();
        inflight.open("flightcode.txt");
    }
    else if (command == RESERVATION){
        reservation(outfile, inflight, infile);
        inflight.close();
        inflight.open("flightcode.txt");
    }

    goto start;
    return 0;
}