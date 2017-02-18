/* HOW TO DEPLOY
 * Right click on the project name (OptimusPrime)
 * GOTO the `Run As` sub-menu
 * Select `WPILib C++ Deploy`
 */

/* USEFUL DOCUMENTATION (add to this list as you find useful things)
 * WPILib docs: http://first.wpi.edu/FRC/roborio/release/docs/cpp/index.html
 * (look at Classes/Class List/frc)
 * FRC C++ Programming guide: C:\Users\cecrobotics\Desktop\FRC_C___Programming
 * Using the joysticks:jhjh http://wpilib.screenstepslive.com/s/3120/m/7912/l/133053-joysticks
 * TIMER DOCUMENTATION: (note getfpgatime) http://first.wpi.edu/FRC/roborio/release/docs/cpp/classfrc_1_1Timer.html#a5f16e8da27d2a5a5242dead46de05d97
 */

#include <iostream>
#include <memory>
#include <string>

#include <Timer.h>
#include <WPILib.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

class Robot: public frc::IterativeRobot {
	frc::RobotDrive drive;
	frc::Talon lift;
	frc::Talon intake;
	frc::Talon shooter;
	frc::Talon agitator;
	frc::Joystick stick1 {0};
	frc::Joystick stick2 {1};
	frc::Timer shooterTimer;
	frc::Timer autoTimer;
	bool intakeRun; //true if the intake is running
	bool intakeLast; //true if the intake button was pressed last time through the periodic loop
	double agitatorDelay = 2;
	double autoPeriod = 3;
	double revAgitator = 1;
public:
	Robot() : //Order matters - this should match what's above
		drive(0,1,2,3),
		lift(4),
		intake(5),
		shooter(6),
		agitator(7),
		shooterTimer(),
		autoTimer(),
		intakeRun(),
		intakeLast() {

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
		autoTimer.Stop();
		autoTimer.Reset();
	}

	void AutonomousPeriodic() {
		autoTimer.Start();
		while (autoPeriod > autoTimer.Get()){
		drive.TankDrive(-0.5,-0.5,0);
	}
	}

	void TeleopInit() {
		intakeRun = false;
		intakeLast = false;

		shooterTimer.Stop();
		shooterTimer.Reset();
	}

	void TeleopPeriodic() {

		drive.TankDrive(stick1,stick2,false);


//////////////////////////////Shooter/////////////////////////
		if (stick2.GetButton(frc::Joystick::ButtonType::kTriggerButton)) {
			shooterTimer.Start();
			this->shooter.Set(.9);
			if (agitatorDelay < shooterTimer.Get()){
				this->agitator.Set(0.2);
			}
		}
		else if (stick2.GetRawButton(4)){
			shooterTimer.Start();
			if (revAgitator > shooterTimer.Get()){
				this->agitator.Set(-0.2);
			}
			else {
				this->agitator.Set(0);
			}
		}
		else {
			shooterTimer.Stop();
			shooterTimer.Reset();
			this->agitator.Set(0);
			this->shooter.Set(0);
		}

	/////////////////////////////Intake///////////////////////////
		if(intakeLast == false && stick2.GetRawButton(2)) {
			if(intakeRun == true ) {
				this ->intake.Set(0);
				intakeRun = false;
			} else {
				this->intake.Set(-.5);
				intakeRun = true;
			}
		}

		intakeLast = stick2.GetRawButton(2);

	//////////////////////////Lift/////////////////
		if (stick2.GetRawButton(3)){
			this->lift.Set(.7);}
		else{
			this->lift.Set(0);
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
