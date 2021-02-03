#ifndef CAR_LIKE_ROBOT_PLUGIN_HPP
#define CAR_LIKE_ROBOT_PLUGIN_HPP

#include <gazebo/gazebo.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>

#include <ros/ros.h>
#include <ros/console.h>
#include <ros/callback_queue.h>
#include <ros/subscribe_options.h>
#include <std_msgs/String.h>


#include <cmath>

// Our include files
#include "car_plugin/Command.h"
#include "car_plugin/Response.h"
#include "car_plugin/Key.h"
#include "carlikerobot.hpp"

#ifndef PI
    #define PI 3.141592654
#endif

namespace gazebo
{
	namespace carlikerobot
    {

        class IRobotCommandSetter
        {
            public:
                virtual void setCommand(float, float)=0;
        };       
        
        typedef std::shared_ptr<IRobotCommandSetter> IRobotCommandSetterPtr;

        class CMessageHandler
        {
            public:
                CMessageHandler(std::string, IRobotCommandSetter*);
                ~CMessageHandler();
                void OnMsgCommand(car_plugin::CommandConstPtr _msg);

            private:
                void unknownMessage();
                void brakeMessage(std::vector<float> _msg_val);
                void moveMessage(std::vector<float> _msg_val);
                void QueueThread();
                
                // private variable 
                IRobotCommandSetter*                _robotSetter;

                std::unique_ptr<ros::NodeHandle>    _rosNode;
                ros::Subscriber                     _commandSubscriber;
                ros::Publisher                      _feedbackPublisher;

                ros::CallbackQueue                  _subscriberQueue;
                std::thread                         _subscribeRosQueueThread;

        };
        
        
        class CCarLikeRobotRosPlugin: public ModelPlugin, public IRobotCommandSetter
        {
            
            public:
                CCarLikeRobotRosPlugin();
                virtual ~CCarLikeRobotRosPlugin();
                bool LoadParameterJoints(sdf::ElementPtr _sdf);
                void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);
                void onUpdate();
                void setCommand(float, float);
            private:
                void QueueThread();
                void OnMsgCommand(car_plugin::CommandConstPtr);

                void unknownMessage();
                void brakeMessage(std::vector<float>);
                void moveMessage(std::vector<float>);


                // Private variable
                IWheelsSpeedPtr         _rearWheelsSpeedPtr;
                IWheelsSpeedPtr         _frontWheelSpeedPtr;
                ISteerWheelsPtr         _steerWheelsAnglePtr;
                
                physics::ModelPtr           _model;

                // Pointer to the update event connection
                event::ConnectionPtr        _updateConnection;
                

                std::shared_ptr<CMessageHandler>      _messageHandler;
                
                /// \brief A node use for ROS transport
                std::unique_ptr<ros::NodeHandle> rosNode;
                ros::Subscriber rosSub;
                ros::Publisher  rosPub;
                ros::CallbackQueue rosQueue;
                std::thread rosQueueThread;
                
        };	
	}; // namespace carlikerobot
}; // namespace gazebo

#endif
