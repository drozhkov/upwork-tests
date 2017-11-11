#include <iostream>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../include/robot/myRobot.hpp"


using namespace Robot;


class TestRobot : public RobotSdk::IRobot {
public:
	MOCK_METHOD0( Beep, void() );
	MOCK_METHOD1( Move, void( double distance ) );
	MOCK_METHOD1( Turn, void( double angle ) );
};


std::vector<std::shared_ptr<Command>> Commands =
	{ 
		std::shared_ptr<Command>( new CommandBeep() )
		, std::shared_ptr<Command>( new CommandMove( 1 ) ) 
		, std::shared_ptr<Command>( new CommandTurn( 2 ) ) 
		, std::shared_ptr<Command>( new CommandMove( 3 ) ) 
		, std::shared_ptr<Command>( new CommandTurn( 4 ) ) 
		, std::shared_ptr<Command>( new CommandBeep() ) 
	};


TEST( Robot, Commands )
{
	TestRobot dummyRobot;
	MyRobot robot( dummyRobot );

	EXPECT_CALL( dummyRobot, Beep() )
		.Times( ::testing::AtLeast( 1 ) );

	EXPECT_CALL( dummyRobot, Move( 1 ) )
		.Times( ::testing::AtLeast( 1 ) );

	EXPECT_CALL( dummyRobot, Move( 3 ) )
		.Times( ::testing::AtLeast( 1 ) );

	EXPECT_CALL( dummyRobot, Turn( 2 ) )
		.Times( ::testing::AtLeast( 1 ) );

	EXPECT_CALL( dummyRobot, Turn( 4 ) )
		.Times( ::testing::AtLeast( 1 ) );

	for (size_t i = 0; i < Commands.size(); i++) {
		robot.Execute( *Commands[i] );
	}

	auto & commands = robot.Commands();

	EXPECT_TRUE( commands.size() == Commands.size() );

	for (size_t i = 0; i < commands.size(); i++) {
		EXPECT_TRUE( commands[i]->Type() == Commands[i]->Type() );

		switch (commands[i]->Type()) {
			case CommandType::Move:
				{
					auto cmd1 = static_cast<CommandMove *>(commands[i].get());
					auto cmd2 = static_cast<CommandMove *>(Commands[i].get());

					EXPECT_TRUE( static_cast<int>(cmd1->Distance()) == static_cast<int>(cmd2->Distance()) );
				}

				break;

			case CommandType::Turn:
				{
					auto cmd1 = static_cast<CommandTurn *>(commands[i].get());
					auto cmd2 = static_cast<CommandTurn *>(Commands[i].get());

					EXPECT_TRUE( static_cast<int>(cmd1->Angle()) == static_cast<int>(cmd2->Angle()) );
				}

				break;
		}
	}
}

int main( int argc, char * argv[] )
{
	::testing::InitGoogleMock( &argc, argv );	

	return RUN_ALL_TESTS();
}
