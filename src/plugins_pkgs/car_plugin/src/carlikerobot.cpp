#include "carlikerobot.hpp"

#define DEBUG false

namespace gazebo{
    namespace carlikerobot{
        /*
        axletrack : the distance between the wheels as you look the car frontal
        wheelbase : the distance between the wheels as you look the car from side
        */

        /// FRONT
	    CFrontWheelsSpeed::CFrontWheelsSpeed(float             axletrack, 
                                             float             wheelbase,
                                             float             wheelradius,
                                             physics::JointPtr jointRight,
                                             physics::JointPtr jointLeft,
                                             common::PID       pidRight,
                                             common::PID       pidLeft,
                                             physics::ModelPtr model)
        {
            this->_axletrack    = axletrack;
            this->_wheelbase    = wheelbase;
            this->_wheelradius  = wheelradius;
            this->_jointRight   = jointRight;
            this->_jointLeft    = jointLeft;
            this->_pidRight     = pidRight;
            this->_pidLeft      = pidLeft;
            this->_model        = model;

            this->_model->GetJointController()->SetVelocityPID(this->_jointRight->GetScopedName(), this->_pidRight);

            this->_model->GetJointController()->SetVelocityPID(this->_jointLeft->GetScopedName(), this->_pidLeft);
    
        }


        void CFrontWheelsSpeed::update(float steeringAngle_deg, float speed_meter_per_sec)
        {

            // Convert from m/s in rads/sec
            
            float  speed_rad_per_sec = speed_meter_per_sec / this->_wheelradius;
            
            
            float l_K = tan(steeringAngle_deg / 180.0 * PI)/this->_wheelbase;

            float l_Vr_R = speed_rad_per_sec*sqrt((pow(2.0-this->_axletrack*l_K,2.0)+pow(2.0*l_K*this->_wheelbase,2))/(4.0*(1.0+pow(_wheelbase*l_K,2.0))));
            float l_Vr_L = speed_rad_per_sec*sqrt((pow(2.0+_axletrack*l_K,2.0)+pow(2.0*l_K*_wheelbase,2))/(4.0*(1.0+pow(_wheelbase*l_K,2.0))));

            if(DEBUG)
            {
                ROS_INFO("Front speed:\t\t[%f, %f]", l_Vr_L, l_Vr_R);
            }

            _model->GetJointController()->SetVelocityTarget(this->_jointLeft->GetScopedName(),l_Vr_L);
            _model->GetJointController()->SetVelocityTarget(this->_jointRight->GetScopedName(),l_Vr_R);
            
        }


        /// REAR
        CRearWheelsSpeed::CRearWheelsSpeed(float             f_axletrack,
                                           float             f_wheelbase,
                                           float             f_wheelradius,
                                           physics::JointPtr f_jointRight,
                                           physics::JointPtr f_jointLeft,
                                           common::PID       f_pidRight,
                                           common::PID       f_pidLeft,
                                           physics::ModelPtr f_model)
        {
           this->_axletrack     = f_axletrack;
           this->_wheelbase     = f_wheelbase;
           this->_wheelradius   = f_wheelradius;
           this->_jointRight    = f_jointRight;
           this->_jointLeft     = f_jointLeft;
           this->_pidRight      = f_pidRight;
           this->_pidLeft       = f_pidLeft;
           this->_model         = f_model;
        
            this->_model->GetJointController()->SetVelocityPID(this->_jointRight->GetScopedName(), this->_pidRight);
            this->_model->GetJointController()->SetVelocityPID(this->_jointLeft->GetScopedName(), this->_pidLeft);
        }

        void CRearWheelsSpeed::update(float f_steerAngle_deg,float f_Vr_m_meterpsec)
        {
            float  l_Vr_m_radpsec = f_Vr_m_meterpsec/_wheelradius;

            float l_K = tan(f_steerAngle_deg/180.0*PI)/this->_wheelbase;
            float l_Vr_R = l_Vr_m_radpsec*(2-_axletrack*l_K)/2;
            float l_Vr_L = l_Vr_m_radpsec*(2+_axletrack*l_K)/2;

            if(DEBUG)
            {
                ROS_INFO("Rear speed:\t\t[%f, %f]",l_Vr_L, l_Vr_R);
            }

            this->_model->GetJointController()->SetVelocityTarget(this->_jointLeft->GetScopedName(),l_Vr_L);
            this->_model->GetJointController()->SetVelocityTarget(this->_jointRight->GetScopedName(),l_Vr_R);
        }


        /// STEERING ANGLE
        CSteerWheelsAngle::CSteerWheelsAngle(float              f_axletrack,
                                             float              f_wheelbase,
                                             physics::JointPtr  f_jointRight,
                                             physics::JointPtr  f_jointLeft,
                                             common::PID        f_pidRight,
                                             common::PID        f_pidLeft,
                                             physics::ModelPtr  f_model)
        {
            this->_axletrack    = f_axletrack;
            this->_wheelbase    = f_wheelbase;
            this->_jointRight   = f_jointRight;
            this->_jointLeft    = f_jointLeft;
            this->_pidRight     = f_pidRight;
            this->_pidLeft      = f_pidLeft;
            this->_model        = f_model;               
        
            this->_model->GetJointController()->SetPositionPID(this->_jointRight->GetScopedName(), this->_pidRight);
            this->_model->GetJointController()->SetPositionPID(this->_jointLeft->GetScopedName(), this->_pidLeft);
        }

        void CSteerWheelsAngle::update(float f_steerAngle_deg)
        {
            
            float l_K = tan(f_steerAngle_deg / 180.0 * PI) / this->_wheelbase;
            float l_steer_right = -1.0 * atan(_wheelbase * 2.0 * l_K / (2.0 - this->_axletrack * l_K));
            float l_steer_left = -1.0 * atan(_wheelbase * 2.0 * l_K / (2.0 + this->_axletrack * l_K));

            if(DEBUG)
            {
                ROS_INFO("Angle:\t\t\t[%f, %f]", l_steer_left*180.0/PI,l_steer_right*180.0/PI);
                ROS_INFO_STREAM("====================================================================");
            }
            

            _model->GetJointController()->SetPositionTarget(this->_jointLeft->GetScopedName(), l_steer_left);
            _model->GetJointController()->SetPositionTarget(this->_jointRight->GetScopedName(), l_steer_right); 
        }
    }; // namespace carlikerobot
} // namespace gazebo

