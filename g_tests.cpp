#include <gtest/gtest.h>
#include "solution.h" 

// Testing time struct
TEST(TimeTest, DefaultConstructor) 
{
    solution::Time t;
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
}

TEST(TimeTest, StringConstructor) 
{
    solution::Time t("12:34");
    EXPECT_EQ(t.hour, 12);
    EXPECT_EQ(t.minute, 34);
}

TEST(TimeTest, ToMinutes) 
{
    solution::Time t("1:30");
    EXPECT_EQ(t.toMinutes(), 90);
}

TEST(TimeTest, LessThanOperator) 
{
    solution::Time t1("1:30");
    solution::Time t2("2:00");
    EXPECT_TRUE(t1 < t2);
    EXPECT_FALSE(t2 < t1);
}

TEST(TimeTest, OutputOperator) 
{
    solution::Time t("3:05");
    std::ostringstream os;
    os << t;
    EXPECT_EQ(os.str(), "03:05");
}

// Testing seat struct
TEST(SeatTest, DefaultConstructor) 
{
    solution::Seat s;
    EXPECT_FALSE(s.isTaken);
    EXPECT_EQ(s.totalMoney, 0);
    EXPECT_EQ(s.totalTime, 0);
    EXPECT_EQ(s.clientName, "");
}

// Testing person struct
TEST(PersonTest, ParameterizedConstructor) 
{
    solution::Person p("alice", true, 100);
    EXPECT_EQ(p.name, "alice");
    EXPECT_TRUE(p.isSeated);
    EXPECT_EQ(p.timeSeated, 100);
}

// Testing event struct
TEST(EventTest, StringConstructor) 
{
    solution::Event e("12:34 1 alice");
    EXPECT_EQ(e.time.hour, 12);
    EXPECT_EQ(e.time.minute, 34);
    EXPECT_EQ(e.id, 1);
    EXPECT_EQ(e.clientName, "alice");
}

TEST(EventTest, OutputOperator) 
{
    solution::Event e("12:34 2 Bob 1");
    std::ostringstream os;
    os << e;
    EXPECT_EQ(os.str(), "12:34 2 Bob 1\n");
}

// Testing split function
TEST(UtilityTest, Split)
 {
    std::vector<std::string> result = solution::Split("a,b,c", ",");
    std::vector<std::string> expected = {"a", "b", "c"};
    EXPECT_EQ(result, expected);
}

// Testing validation functions
TEST(UtilityTest, IsValidTableNumber) 
{
    EXPECT_TRUE(solution::isValidTableNumber(5, 10));
    EXPECT_FALSE(solution::isValidTableNumber(11, 10));
}

TEST(UtilityTest, IsValidClientName) 
{
    EXPECT_TRUE(solution::isValidClientName("alice123"));
    EXPECT_FALSE(solution::isValidClientName("alice*"));
}

TEST(UtilityTest, IsValidTime) 
{
    EXPECT_TRUE(solution::isValidTime("12:34"));
    EXPECT_FALSE(solution::isValidTime("25:00"));
}

// Testing functions for handling events
TEST(EventHandlerTest, HandleID1) 
{
    std::unordered_map<std::string, solution::Person> club;
    solution::Event e("12:34 1 alice");
    solution::handleID1(e, club);
    ASSERT_EQ(club.size(), 1);
    EXPECT_EQ(club["alice"].name, "alice");
    EXPECT_FALSE(club["alice"].isSeated);
    EXPECT_EQ(club["alice"].timeSeated, 0);
}

TEST(EventHandlerTest, HandleID2) 
{
    std::unordered_map<std::string, solution::Person> club;
    club["alice"] = solution::Person("alice", false, 0);
    std::vector<solution::Seat> seats(10);
    long long numOfSeatsTaken = 0;
    solution::Event e("12:34 2 alice 1");
    solution::handleID2(e, club, seats, &numOfSeatsTaken);
    EXPECT_TRUE(seats[0].isTaken);
    EXPECT_EQ(seats[0].clientName, "alice");
    EXPECT_TRUE(club["alice"].isSeated);
    EXPECT_EQ(numOfSeatsTaken, 1);
}

TEST(EventHandlerTest, HandleID3) 
{
    std::string message;
    std::unordered_map<std::string, solution::Person> club;
    club["alice"] = solution::Person("alice", false, 0);
    std::queue<solution::Person> peopleQueue;
    solution::Event e("2:00 3 alice");
    solution::handleID3(e, club, 1, peopleQueue, 1);
    EXPECT_EQ(peopleQueue.front().name, "alice");
}

TEST(EventHandlerTest, HandleID4) 
{
    std::unordered_map<std::string, solution::Person> club;
    club["alice"] = solution::Person("alice", true, 60); 
    std::vector<solution::Seat> seats(10);
    seats[1].clientName = "alice";
    seats[1].isTaken = true;
    std::queue<solution::Person> peopleQueue;
    long long numOfSeatsTaken = 1;
    solution::Event e("3:00 4 alice");
    solution::handleID4(e, club, seats, peopleQueue, 10, &numOfSeatsTaken);
    EXPECT_FALSE(seats[1].isTaken);
    EXPECT_EQ(numOfSeatsTaken, 0);
    EXPECT_EQ(seats[1].totalMoney, 20); 
    EXPECT_EQ(seats[1].totalTime, 120);
    EXPECT_EQ(club.find("alice"), club.end());
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
