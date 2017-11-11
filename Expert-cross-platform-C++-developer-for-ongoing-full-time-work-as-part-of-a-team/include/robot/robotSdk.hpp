#ifndef __ROBOT_SDK_H
#define __ROBOT_SDK_H


namespace RobotSdk {

	class IRobot {
	public:
		virtual void Move(double distance) = 0;
		virtual void Turn(double angle) = 0;
		virtual void Beep() = 0;
	};

}


#endif
