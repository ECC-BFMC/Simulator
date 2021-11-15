#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ros/ros.h>

#ifndef PI
#define PI 3.141592654
#endif

namespace gazebo
{
	namespace carlikerobot
	{
	
	    class IWheelsSpeed
        {
	        public:
                virtual void update(float,float)=0;
	    };

	    class CRearWheelsSpeed: public IWheelsSpeed
        {
            public:
                CRearWheelsSpeed(float,
                                 float,
                                 float,
                                 physics::JointPtr,
                                 physics::JointPtr,
                                 common::PID,
                                 common::PID,
                                 physics::ModelPtr);

                void update(float,float);
            
            private:
                float               _axletrack;
                float               _wheelbase;
                float               _wheelradius;

                // Joints
                physics::JointPtr   _jointRight;
                physics::JointPtr   _jointLeft;

                // PID
                common::PID         _pidRight;
                common::PID         _pidLeft;

                // Model for setting the target
                physics::ModelPtr   _model;
        };

        class CFrontWheelsSpeed: public IWheelsSpeed
        {
            public:
                CFrontWheelsSpeed(float,
                                  float,
                                  float,
                                  physics::JointPtr,
                                  physics::JointPtr,
                                  common::PID,
                                  common::PID,
                                  physics::ModelPtr);

                void update(float,float);
            
            private:
                float               _axletrack;
                float               _wheelbase;
                float               _wheelradius;
                
                // Joints
                physics::JointPtr   _jointRight;
                physics::JointPtr   _jointLeft;
                
                // PID
                common::PID         _pidRight;
                common::PID         _pidLeft;
                
                // Model for setting the target
                physics::ModelPtr   _model;
        };
        
        class ISteerWheels
        {
            public:
                virtual void update(float)=0;
        };

        class CSteerWheelsAngle:public ISteerWheels
        {
            public:
                CSteerWheelsAngle(float,
                                  float,
                                  physics::JointPtr,
                                  physics::JointPtr,
                                  common::PID,
                                  common::PID,
                                  physics::ModelPtr);

                void update(float);
            
            private:
                float               _axletrack;
                float               _wheelbase;
            
                // Joints
                physics::JointPtr   _jointRight;
                physics::JointPtr   _jointLeft;
            
                //PID
                common::PID         _pidRight;
                common::PID         _pidLeft;
            
                // Model for setting the targer
                physics::ModelPtr   _model;
        };

        // Shared pointer types definition for rotation speed controllers.
        typedef std::shared_ptr<IWheelsSpeed> IWheelsSpeedPtr;        
        typedef std::shared_ptr<CRearWheelsSpeed> CRearWheelsSpeedPtr;
        typedef std::shared_ptr<CFrontWheelsSpeed> CFrontWheelsSpeedPtr;
        
        // Shared pointer types definition for steering angle controllers.
        typedef std::shared_ptr<ISteerWheels> ISteerWheelsPtr;
        typedef std::shared_ptr<CSteerWheelsAngle> CSteerWheelsAnglePtr;
        
    }; // namespace carlikerobot
}; // gazebo
