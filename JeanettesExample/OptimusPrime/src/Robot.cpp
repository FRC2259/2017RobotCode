/* HOW TO DEPLOY
 * Right click on the project name (OptimusPrime)
 * GOTO the `Run As` sub-menu
 * Select `WPILib C++ Deploy`
 */

/* USEFUL DOCUMENTATION (add to this list as you find useful things)
 * WPILib docs: http://first.wpi.edu/FRC/roborio/release/docs/cpp/index.html
 * (look at Classes/Class List/frc)
 * FRC C++ Programming guide: C:\Users\cecrobotics\Desktop\FRC_C___Programming
 * Using the joysticks: http://wpilib.screenstepslive.com/s/3120/m/7912/l/133053-joysticks
 */

#include <iostream>
#include <memory>
#include <string>

#include <WPILib.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

class Robot: public frc::IterativeRobot {
	frc::Talon leftDrive1;
	frc::Talon leftDrive2;
	frc::Talon rightDrive1;
	frc::Talon rightDrive2;
	frc::Talon lift;
	frc::Talon intake;
	frc::Talon shooter;
	frc::Talon agitator;
	frc::Joystick stick1 {0};
	frc::Joystick stick2 {1};

public:
	Robot() : //Order matters - this should match what's above
		leftDrive1(0),
		leftDrive2(1),
		rightDrive1(2),
		rightDrive2(3),
		lift(4),
		intake(5),
		shooter(6),
		agitator(7) {

	}

	void RobotInit() {
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
	}

	/*
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit() override {
		autoSelected = chooser.GetSelected();
		// std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {
		if (stick1.GetButton(frc::Joystick::ButtonType::kTriggerButton)) {
			this->agitator.Set(1);
		}
		else {
			this->agitator.Set(0);
		}

		if(stick1.GetRawButton(8)) {
			this ->leftDrive2.Set(1);
		}
		else {
			this->leftDrive2.Set(0);
		}
	}

	void TestPeriodic() {
		lw->Run();

	}

private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;
};

;START_ROBOT_CLASS(Robot)
