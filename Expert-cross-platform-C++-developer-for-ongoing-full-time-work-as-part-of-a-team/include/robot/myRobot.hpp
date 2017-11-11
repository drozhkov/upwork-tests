#ifndef __MY_ROBOT_H
#define __MY_ROBOT_H


#include <vector>
#include <memory>

#include "robotSdk.hpp"

#include "robotCommands.hpp"


namespace Robot {

	class MyRobot : public RobotSdk::IRobot	{
	protected:
		RobotSdk::IRobot & m_robot;
		std::vector<std::shared_ptr<Command>> m_commands;

	public:
		MyRobot( RobotSdk::IRobot & robot )
			: m_robot( robot )
		{
		}

		void Move(double distance) override
		{
			m_robot.Move( distance );
			m_commands.push_back( std::shared_ptr<Command>( new CommandMove( distance ) ) );
		}

		void Turn(double angle) override
		{
			m_robot.Turn( angle );
			m_commands.push_back( std::shared_ptr<Command>( new CommandTurn( angle ) ) );
		}

		void Beep() override
		{
			m_robot.Beep();
			m_commands.push_back( std::shared_ptr<Command>( new CommandBeep() ) );
		}

		void Execute( Command & command )
		{
			switch (command.Type()) {
				case CommandType::Turn:
					{
						CommandTurn & cmd = static_cast<CommandTurn &>(command);
						Turn( cmd.Angle() );
					}

					break;

				case CommandType::Move:
					{
						CommandMove & cmd = static_cast<CommandMove &>(command);
						Move( cmd.Distance() );
					}

					break;

				case CommandType::Beep:
					Beep();
					break;
			}
		}

		const std::vector<std::shared_ptr<Command>> & Commands() const
		{
			return m_commands;
		}

		void Replay( const std::vector<std::shared_ptr<Command>> & commands )
		{
			for (size_t i = 0; i < commands.size(); i++) {
				Execute( *commands[i] );
			}
		}
	};

}


#endif
