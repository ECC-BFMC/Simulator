#include <gazebo/gazebo.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/common/common.hh>
#include <gazebo/physics/physics.hh>

#include <ros/ros.h>
#include <std_msgs/String.h>

#include "carlikerobot.hpp"
#include "rapidjson/document.h"

namespace gazebo
{
	namespace carlikerobot
    {

        class IRobotCommandSetter
        {
            public:
                virtual void setCommand()=0;
                float f_steer;
                float f_speed;
        };       
        
        typedef std::shared_ptr<IRobotCommandSetter> IRobotCommandSetterPtr;

        class CMessageHandler
        {
            public:
                CMessageHandler(std::string, IRobotCommandSetter*);
                ~CMessageHandler();
                void OnMsgCommand(std_msgs::String _msg);

            private:
                void unknownMessage();
                void brakeMessage(float _msg_val);
                void spedMessage(float _msg_val);
                void sterMessage(float _msg_val);
                
                // private variable 
                IRobotCommandSetter*                _robotSetter;

                std::unique_ptr<ros::NodeHandle>    _rosNode;
                ros::Subscriber                     _commandSubscriber;
                ros::Publisher                      _feedbackPublisher;
		
        };
        
        
        class CCarLikeRobotRosPlugin: public ModelPlugin, public IRobotCommandSetter
        {
            
            public:
                bool LoadParameterJoints(sdf::ElementPtr _sdf);
                void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);
                void setCommand();
            private:
                // Private variable
                IWheelsSpeedPtr     _rearWheelsSpeedPtr;
                IWheelsSpeedPtr     _frontWheelSpeedPtr;
                ISteerWheelsPtr     _steerWheelsAnglePtr;
                
                physics::ModelPtr   _model;                

                std::shared_ptr<CMessageHandler>      _messageHandler;
                
        };	
	}; // namespace carlikerobot
}; // namespace gazebo
