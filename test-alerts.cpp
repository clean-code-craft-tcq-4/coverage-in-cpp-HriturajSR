#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
REQUIRE(inferBreach(40, 20, 30) == TOO_HIGH);
REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}
TEST_CASE("classiTemperature breach") {
  
REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,20) == NORMAL);
REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -20) == TOO_LOW);
REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 40) == TOO_HIGH);

REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 20) == NORMAL);
REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -20) == TOO_LOW);
REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);

REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 20) == NORMAL);
REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -20) == TOO_LOW);
REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 50) == TOO_HIGH);

}

TEST_CASE( "Check and alert status to controller") {

BatteryCharacter batteryChar {PASSIVE_COOLING,"LG_Li-po"};
checkAndAlert(TO_CONTROLLER, batteryChar, TOO_LOW);
checkAndAlert(TO_CONTROLLER, batteryChar, NORMAL);
checkAndAlert(TO_CONTROLLER, batteryChar,TOO_HIGH);

}

TEST_CASE("Test for Email : LowValue"){
BatteryCharacter batteryCheckForEmail_1 = {.coolingType = PASSIVE_COOLING};

ostringstream sendEmail;
streambuf* streamBuffer_1 = cout.rdbuf();
cout.rdbuf(sendEmail.rdbuf());

checkAndAlert(TO_EMAIL, batteryCheckForEmail_1, -10);

cout.rdbuf(streamBuffer_1);
REQUIRE(sendEmail.str() == "To:a.b@c.com\nHi, the temperature is too low\n");	
}

TEST_CASE("Test for Email : HighValue"){
BatteryCharacter batteryCheckForEmail_2 = {.coolingType = HI_ACTIVE_COOLING};

ostringstream sendEmail;
streambuf* streamBuffer_2 = cout.rdbuf();
cout.rdbuf(sendEmail.rdbuf());

checkAndAlert(TO_EMAIL, batteryCheckForEmail_2, 46);

cout.rdbuf(streamBuffer_2);
REQUIRE(sendEmail.str() == "To:a.b@c.com\nHi, the temperature is too high\n");	
}
