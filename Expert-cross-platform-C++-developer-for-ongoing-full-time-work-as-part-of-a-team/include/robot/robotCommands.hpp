#ifndef __ROBOT_COMMANDS_H
#define __ROBOT_COMMANDS_H


namespace Robot {

	enum class CommandType {
		_undefined = 0,
		Move = 1,
		Turn,
		Beep
	};

	class Command {
	protected:
		CommandType m_type;

	protected:
		Command( CommandType type )
			: m_type( type )
		{
		}

	public:
		virtual ~Command()
		{
		}

		CommandType Type() const
		{
			return m_type;
		}
	};

	class CommandMove : public Command {
	protected:
		double m_distance;

	public:
		CommandMove( double distance )
			: Command( CommandType::Move )
			, m_distance( distance )
		{
		}

		double Distance() const
		{
			return m_distance;
		}
	};

	class CommandTurn : public Command {
	protected:
		double m_angle;

	public:
		CommandTurn( double angle )
			: Command( CommandType::Turn )
			, m_angle( angle )
		{
		}

		double Angle() const
		{
			return m_angle;
		}
	};

	class CommandBeep : public Command {
	public:
		CommandBeep()
			: Command( CommandType::Beep )
		{
		}
	};

}


#endif
