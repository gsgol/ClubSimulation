#pragma once

#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <regex>

namespace solution
{
    //Struct to store time
    struct Time {
        int hour;
        int minute;
        
        Time ()
        {
            hour = 0;
            minute = 0;
        }

        Time(std::string timeStr) {
            sscanf(timeStr.c_str(), "%d:%d", &hour, &minute);
        }

        //  The output operator for convenient time output
        friend std::ostream& operator<<(std::ostream& os, const Time& t) {
            std::string modHour = std::to_string(t.hour);
            std::string modMinute = std::to_string(t.minute);
            if (t.hour < 10)
            {
                modHour = "0"  + modHour;
            }
            if (t.minute < 10)
            {
                modMinute = "0"  + modMinute;
            }
            os << modHour << ":" << modMinute;
            return os;
        }

        // Overloaded operator  <
        bool operator<(const Time& other) const {
            if (hour != other.hour)
                return hour < other.hour;
            return minute < other.minute;
        }

        // Function to convert time to minutes
        long long toMinutes() const
        {
            return hour * 60 + minute;
        }
    };

    // Struct to store information about seats
    struct Seat
    {
        bool isTaken;
        long long totalMoney;
        long long totalTime;
        std::string clientName;

        Seat()
        {
            isTaken = false;
            totalMoney = 0;
            totalTime = 0;
            clientName= "";
        }
    };

    // Struct to store information about person
    struct Person
    {
        std::string name;
        bool isSeated;
        long long timeSeated;
        
        Person() = default;

        Person(std::string t_name, bool t_isSeated, long long t_timeSeated)
        {
            name = t_name;
            isSeated = t_isSeated;
            timeSeated = t_timeSeated;
        }

    };

    // Struct to store information about event
    struct Event {
        Time time;
        int id;
        std::string clientName;
        int tableNumber;

        Event() = default;
        
        Event(std::string eventStr) 
        {
            std::istringstream iss(eventStr);
            std::string timeStr;
            iss >> timeStr;
            time = Time(timeStr);
            iss >> id;
            if (id == 1 || id == 2 || id == 3 || id == 4) {
                iss >> clientName;
                if (id == 2)
                    iss >> tableNumber;
            }
        }

        Event(Time t_time, std::string t_clientName)
        {
            time = t_time;
            clientName = t_clientName;
            id = 0;
            tableNumber = 0;
        }

        //  The output operator for convenient event output
        friend std::ostream& operator<<(std::ostream& os, const Event& ev) {
            os << ev.time << " " << ev.id << " " << ev.clientName;
            if (ev.id == 2)
            {
                os << " " << ev.tableNumber;
            }
            os << std::endl;
            return os;
        }
    };

    /**
    * @brief: function to split string 
    * @param[in]: s - string to split, delimeter - the line by which the division takes place
    */
    std::vector<std::string> Split (std::string s, std::string delimiter);

    /**
    * @brief: function to check if the number of table is valid
    * @param[in]: tablenumber - number of table to validate, maxTableNumber - number of tables in the club 
    */
    bool isValidTableNumber(long long tableNumber, long long maxTableNumber);

    /**
    * @brief: function to check if the name of the client is valid
    * @param[in]: name - name of the client to validate
    */
    bool isValidClientName(const std::string& name);

    /**
    * @brief: function to check if the time is valid
    * @param[in]: time - string of time to validate
    */
    bool isValidTime(const std::string& time);

    /**
    * @brief: function to check are the events sequential
    * @param[in]: ev1 - first event, ev2 - second event
    */
    bool areEventsSequential(const Event ev1, const Event ev2);

    /**
    * @brief: function to send event with ID 11
    * @param[in]: event - event that occuried, club - the state of club
    */
    void handleID11 (const Event event, std::unordered_map <std::string, Person>& club);

    /**
    * @brief: function to send event with ID 12
    * @param[in]: event - event that occuried, peopleQueue - queue of people in the club,  seats - inforamtion about seats in club, club - the state of club, numOfSeatsTaken - number of seats that already taken
    */
    void handleID12 (const Event event, std::queue<Person>& peopleQueue, std::vector<Seat>& seats, std::unordered_map <std::string, Person>& club,  long long* numOfSeatsTaken);

    /**
    * @brief: function to send event with ID 13
    * @param[in]: event - event that occuried, message - message to send
    */
    void handleID13 (const Event event, std::string message);

    /**
    * @brief: function to send event with ID 1
    * @param[in]: event - event that occuried, club - the state of club
    */
    void handleID1 (const Event event, std::unordered_map <std::string, Person>& club);

    /**
    * @brief: function to send event with ID 2
    * @param[in]: event - event that occuried, club - the state of club, seats - inforamtion about seats in club, numOfSeatsTaken - number of seats that already taken
    */
    void handleID2 (const Event event, std::unordered_map <std::string, Person>& club, std::vector<Seat>& seats, long long* numOfSeatsTaken);

    /**
    * @brief: function to send event with ID 3
    * @param[in]: event - event that occuried, club - the state of club, numOfSeatsTaken - number of seats that already taken, peopleQueue - queue of people in the club, numOfSeates - number of seats in the club
    */
    void handleID3(const Event event, std::unordered_map <std::string, Person>& club, const long long numOfSeatsTaken,  std::queue<Person>& peopleQueue, const long long numOfSeats);

    /**
    * @brief: function to send event with ID 4
    * @param[in]: event - event that occuried, club - the state of club, seats - inforamtion about seats in club, peopleQueue - queue of people in the club,
    *           price - price per hour, numOfSeatsTaken - number of seats that already taken
    */
    void handleID4(const Event event, std::unordered_map <std::string, Person>& club, std::vector<Seat>& seats, std::queue<Person>& peopleQueue, long long price, long long* numOfSeatsTaken);

    /**
    * @brief: function to simulate the club working
    * @param[in]: fileName - name of file that contains information about club
    */
    int simulation(std::string fileName);
}