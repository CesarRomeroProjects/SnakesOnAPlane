#include "catch_amalgamated.hpp"
#include <string>
#include "Plane.hpp"
#include "Player.hpp"

// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.
// However, be aware that if ANY test marked "Required" fails, 
// your score for the portion will be zero, regardless of other considerations.


namespace{


TEST_CASE("PlayerCharacterCanDieTest", "[RequiredProject]")
{
	Plane a(10, 20);
	a.addPlayer(3, 6);
	Player* p = a.player();
	REQUIRE_FALSE( p->isDead());
	p->setDead();
	REQUIRE(p->isDead());
}


TEST_CASE("DoNotStepOnSnakes", "[RequiredProject]")
{
	Plane a(20, 1);
	a.addPlayer(1, 1);
	Player* p = a.player();
	a.addSnake(2, 1);
	REQUIRE(p->move(Plane::SOUTH).find(" died") != std::string::npos);
}


TEST_CASE("PlayerMovementRequiredTest", "[RequiredProject]")
{
	Plane a(1, 20);
	a.addPlayer(1, 3);
	Player* p = a.player(); 
	REQUIRE(p->row() == 1);
	REQUIRE(p->col() == 3);
	p->move(Plane::WEST); 
	REQUIRE(p->row() == 1);
	REQUIRE(p->col() == 2);
	p->move(Plane::WEST); 
	REQUIRE(p->row() == 1);
	REQUIRE(p->col() == 1);
}



TEST_CASE("PlayerCanPushTest1", "[RequiredProject]")
{

	Plane c(3, 20);
	c.addPlayer(2, 10);
	c.addSnake(1, 10);
	c.addSnake(3, 10);
	Player * p = c.player();
	p->push();
                        	
	REQUIRE(c.numberOfSnakesAt(1, 10) == 0);
	REQUIRE(c.numberOfSnakesAt(3,10) == 0);
	REQUIRE( c.snakeCount() == 0);
}


TEST_CASE("PlayerCanPushTest2", "[RequiredProject]")
{
	Plane c(20, 20);
	c.addPlayer(19, 10);
	c.addSnake(20, 10);
	c.addSnake(3, 10);
	Player * p = c.player();
	p->push();
	REQUIRE(c.numberOfSnakesAt(20, 10) == 0 );
	REQUIRE(c.numberOfSnakesAt(3,10) == 1 );
	REQUIRE(c.snakeCount() == 1);
	
}



                        
} // end namespace

