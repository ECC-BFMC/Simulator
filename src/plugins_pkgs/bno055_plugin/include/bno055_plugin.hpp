#pragma once
#include <gazebo/gazebo.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/common/common.hh>
#include <gazebo/physics/physics.hh>

#include "ros/ros.h"
#include "utils/IMU.h"


namespace gazebo
{
    namespace bno055
    {   
        class BNO055: public ModelPlugin
    	{
        private: 
            physics::ModelPtr                   m_model;
            ros::NodeHandlePtr		  nh;
            ros::Timer				  timer;

            /** ----------------------------------For ROS integration----------------------------------------------------**/
            // A node use for ROS transport
            std::unique_ptr<ros::NodeHandle>    m_ros_node;

            // A ROS publisher
            ros::Publisher                      m_pubBNO;
            
            utils::IMU                  m_bno055_pose;

        // Default constructor
        public: BNO055();
        public: void Load(physics::ModelPtr, sdf::ElementPtr);
        public: void OnUpdate();        
        };
    };    
};