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

  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar_passive, 12) == SENT );

  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar_hiactive, 26) == SENT );

  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar_medactive, 8) == SENT );

}

TEST_CASE( "Check and alert status to email") {

  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar_passive, 12) == SENT );

  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar_hiactive, 46) == SENT );

  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar_medactive, 0) == SENT );
}

TEST_CASE( "Check and alert status to email Failure") {

  REQUIRE(checkAndAlert(TO_UNKNOWN, batteryChar_passive, 12) == NOT_SENT );

  REQUIRE(checkAndAlert(TO_UNKNOWN, batteryChar_hiactive, 26) == NOT_SENT );

  REQUIRE(checkAndAlert(TO_UNKNOWN, batteryChar_medactive, 8) == NOT_SENT );
}
