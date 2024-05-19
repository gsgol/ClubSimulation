#include "solution.h"

namespace solution
{
    std::vector<std::string> Split (std::string s, std::string delimiter)
    {   
        std::vector<std::string> ans;
        s += delimiter;
        size_t pos = 0;
        std::string token;
        while ((s.find(delimiter)) != std::string::npos) 
        {
            pos = s.find(delimiter);
            token = s.substr(0, pos);
            ans.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        
        return ans;
    }

    // Функция для проверки валидности номера стола
    bool isValidTableNumber(long long tableNumber, long long maxTableNumber) 
    {
        return tableNumber >= 1 && tableNumber <= maxTableNumber;
    }
    
    // Функция для проверки валидности имени клиента
    bool isValidClientName(const std::string& name)
    {
        std::regex namePattern("^[a-z0-9_-]+$");
        return std::regex_match(name, namePattern);
    }


    // Функция для проверки валидности времени
    bool isValidTime(const std::string& time) 
    {
        std::regex timePattern("^[0-2][0-9]:[0-5][0-9]$");
        if (!std::regex_match(time, timePattern)) 
        {
            return false;
        }
        int hours = std::stoi(time.substr(0, 2));
        int minutes = std::stoi(time.substr(3, 2));
        return hours < 24 && minutes < 60;
    }

    // Функция для проверки последовательности событий
    bool areEventsSequential(const Event ev1, const Event ev2) 
    {
        if (ev2.time < ev1.time)
        {
            return false;
        }

        return true;
    }

    void handleID11 (const Event event, std::unordered_map <std::string, Person>& club)
    {
        club.erase(event.clientName);
        std::cout << event.time << " 11 " << event.clientName << std::endl;
    }

    void handleID12 (const Event event, std::queue<Person>& peopleQueue, std::vector<Seat>& seats, std::unordered_map <std::string, Person>& club,  
                    long long* numOfSeatsTaken)
    {
        for (int i = 0; i < seats.size(); ++i)
        {
            if (seats.at(i).isTaken == false)
            {
                std::cout << event.time << " 12 " << peopleQueue.front().name << " " << i + 1 << std::endl;
                seats.at(i).clientName = peopleQueue.front().name;
                seats.at(i).isTaken = true;
                club.at(peopleQueue.front().name).isSeated = true;
                club.at(peopleQueue.front().name).timeSeated = event.time.toMinutes();
                *numOfSeatsTaken += 1;
                peopleQueue.pop();
                break;
            }
        }
    }

    void handleID13 (const Event event, std::string message)
    {
        std::cout << event.time << " 13 " << message << std::endl;
    }



    void handleID1 (const Event event, std::unordered_map <std::string, Person>& club)
    {
        if (club.find(event.clientName) == club.end())
        {
            club.insert({event.clientName, Person(event.clientName, false, 0)});
        }
        else
        {
            solution::handleID13(event, "YouShallNotPass");
        }
    }

    void handleID2 (const Event event, std::unordered_map <std::string, Person>& club, std::vector<Seat>& seats, long long* numOfSeatsTaken)
    {
        if (club.find(event.clientName) != club.end())
        {
            long long tableID =  event.tableNumber - 1;
            if (seats.at(tableID).isTaken == false)
            {
                seats.at(tableID).clientName = event.clientName;
                seats.at(tableID).isTaken = true;
                club.at(event.clientName).isSeated = true;
                club.at(event.clientName).timeSeated = event.time.toMinutes();
                *numOfSeatsTaken += 1;
            }
            else
            {
                solution::handleID13(event, "PlaceIsBusy");
            }

        }
        else
        {
            solution::handleID13(event, "ClientUnknown");
        }
    }
    void handleID3(const Event event, std::unordered_map <std::string, Person>& club, const long long numOfSeatsTaken,  std::queue<Person>& peopleQueue,
                const long long numOfSeats)
    {
        if(club.find(event.clientName) != club.end())
        {
            if(club.at(event.clientName).isSeated == true)
            {
                solution::handleID13(event, "ClientAlreadySeated");
                return;
            }
        

            if(numOfSeats == numOfSeatsTaken)
            {
                if (peopleQueue.size() < numOfSeats)
                {
                    peopleQueue.emplace(Person(event.clientName, false, 0));
                }
                else
                {
                    solution::handleID11(event, club);
                }
            }
            else
            {
                solution::handleID13(event, "ICanWaitNoLonger!");

            }
        }
        else
        {
            solution::handleID13(event, "ClientUnknown");
        }
    }
    void handleID4(const Event event, std::unordered_map <std::string, Person>& club, std::vector<Seat>& seats, std::queue<Person>& peopleQueue, 
                   long long price, long long* numOfSeatsTaken)
    {
        if(club.find(event.clientName) != club.end())
        {
            if(club.at(event.clientName).isSeated == true)
            {
                for (int i = 0; i < seats.size(); ++i)
                {
                    if (seats.at(i).clientName == event.clientName)
                    {
                        seats.at(i).clientName = "";
                        seats.at(i).isTaken = false;
                        seats.at(i).totalMoney += std::ceil(((event.time.toMinutes() - club.at(event.clientName).timeSeated)) / 60.0) * price;
                        seats.at(i).totalTime += event.time.toMinutes() - club.at(event.clientName).timeSeated;
                        club.erase(event.clientName);
                        *numOfSeatsTaken -= 1;
                    }
                }
                if(!peopleQueue.empty())
                {
                    solution::handleID12(event, peopleQueue, seats, club, numOfSeatsTaken);
                }
            }
            else
            {
                club.erase(event.clientName);
            }
    
        }
        else
        {
            solution::handleID13(event, "ClientUnknown");
        }
    }

    int simulation(std::string fileName)
    {
        std::queue<Person> peopleQueue;
        std::unordered_map <std::string, Person> club;
        long long  numOfSeats, price, numOfSeatsTaken = 0;
        std::ifstream ifs(fileName);


        if (!ifs.is_open()) 
        {
            std::cerr << "Failed to open input file." <<  std::endl;
            return 1;
        }

        ifs >> numOfSeats;

        std::vector<Seat> seats(numOfSeats);

        std::string line;

        getline(ifs, line); 

        getline(ifs, line);

        Time openTime = Time(line.substr(0, 5));
        Time closingTime = Time(line.substr(6, 5));

        ifs >> price;

        getline(ifs, line); 
        
        std::cout << openTime << std::endl;

        Event prevEvent("00:00 1 prevClient");

        while (getline(ifs, line)) 
        {
            if(!solution::isValidTime(line.substr(0, line.find(" "))))
            {
                std::cout << line << std::endl;
                std::cout << "Incorrect time: " << line.substr(0, line.find(" ")) << std::endl;
                return 0;
            }
            Event event = Event(line);

            std::cout << event;

            if(!solution::areEventsSequential(prevEvent, event))
            {
                std::cout << "Events are not sequential: first event time: " << prevEvent.time << " , seccond event time: " << event.time << std::endl;
                return 0;
            }


            if(!solution::isValidClientName(event.clientName))
            {
                std::cout << "Incorrect name of client: " << event.clientName << std::endl;
                return 0;
            }

            switch (event.id)
            {
            case 1:
                if (event.time < openTime)
                {
                    solution::handleID13(event, "NotOpenYet");
                }
                else
                {
                    solution::handleID1(event, club);
                }
                break;
            case 2:
                if(!isValidTableNumber(event.tableNumber, numOfSeats))
                {            
                    std::cout << "Incorrect number of table: " << event.tableNumber << std::endl;
                    return 0;
                }
                solution::handleID2(event, club, seats, &numOfSeatsTaken);
                break;
            case 3:
                solution::handleID3(event, club, numOfSeatsTaken, peopleQueue, numOfSeats);
                break;
            case 4:
                solution::handleID4(event, club, seats, peopleQueue, price, &numOfSeatsTaken);
                break;
            }
            prevEvent = event;
        }
        std::vector<std::string> sortedNames;
        if (!club.empty())
        {
            for(auto client: club)
            {
                sortedNames.push_back(client.first);
                for (int i = 0; i < seats.size(); ++i)
                {
                    if (seats.at(i).clientName == client.first)
                    {
                        seats.at(i).clientName = "";
                        seats.at(i).isTaken = false;
                        seats.at(i).totalMoney += std::ceil(((closingTime.toMinutes() - club.at(client.first).timeSeated)) / 60.0) * price;
                        seats.at(i).totalTime += closingTime.toMinutes() - club.at(client.first).timeSeated;
                        numOfSeatsTaken -= 1;
                    }
                }
            }
        }
        std::sort(sortedNames.begin(), sortedNames.end());
        for(auto name: sortedNames)
        {
            solution::handleID11(Event(closingTime, name), club);
        }
        std::cout << closingTime << std::endl;

        for (int i = 0; i < seats.size(); ++i)
        {
            std::string stringTime = std::to_string(seats.at(i).totalTime/60) + ":" + std::to_string(seats.at(i).totalTime%60);
            std::cout << i + 1 << " " << seats.at(i).totalMoney << " " << Time(stringTime) << std::endl;
        }

        return 0;
    }
}