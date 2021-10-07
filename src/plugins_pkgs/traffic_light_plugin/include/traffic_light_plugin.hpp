#include <thread>

#include <gazebo/gazebo.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/common/common.hh>
#include <gazebo/physics/physics.hh>

#include "ros/ros.h"

#include "std_msgs/Byte.h"

#pragma once

namespace gazebo
{
    namespace trafficLight
    {   
        enum TrafficLightColor {RED, YELLOW, GREEN};

        class TrafficLight: public ModelPlugin
    	{
	public: 
		~TrafficLight();
        private: 
            physics::ModelPtr                   m_model;

            // A node use for ROS transport
            std::unique_ptr<ros::NodeHandle>    m_ros_node;

            // A ROS subscriber
            ros::Subscriber                     m_ros_subscriber;

            std_msgs::Byte                      m_traffic_light_msg;
            
            physics::LinkPtr                    m_green_lens_link;
            physics::LinkPtr                    m_yellow_lens_link;
            physics::LinkPtr                    m_red_lens_link;

            std::string                         name;

        public: transport::PublisherPtr         m_pubLight;
        public: msgs::Light                     m_msg;
        public: transport::NodePtr              m_node;

        // Default constructor
        public: TrafficLight();
        public: void Load(physics::ModelPtr, sdf::ElementPtr);
        public: void OnRosMsg(std_msgs::Byte);
        private: void redState(const bool state=0);
        private: void greenState(const bool state=0);
        private: void yellowState(const bool state=0);
        
        };
    };    
};
