#include "traffic_light_pkg/traffic_light.h"

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
            sdf::ElementPtr                     m_sdf;
            event::ConnectionPtr                m_updateConnection;

            // A node use for ROS transport
            std::unique_ptr<ros::NodeHandle>    m_ros_node;

            // A ROS subscriber
            ros::Subscriber                     m_ros_subscriber;

            // A ROS callbackqueue that helps process messages
            ros::CallbackQueue                  m_ros_queue;

            // A thread the keeps running the rosQueue
            std::thread                         m_ros_queue_thread;

            traffic_light_pkg::traffic_light    m_traffic_light_msg;
            
            physics::LinkPtr                    m_green_lens_link;
            physics::LinkPtr                    m_yellow_lens_link;
            physics::LinkPtr                    m_red_lens_link;

            std::string                         m_scope_name;


        public: transport::PublisherPtr         m_pubLight;
        public: msgs::Light                     m_msg;
        public: transport::NodePtr              m_node;

        // Default constructor
        public: TrafficLight();
        public: void Load(physics::ModelPtr, sdf::ElementPtr);
        public: void OnRosMsg(const traffic_light_pkg::traffic_lightConstPtr &_msg);
        private: void QueueThread();
        private: void redState(const bool state=0);
        private: void greenState(const bool state=0);
        private: void yellowState(const bool state=0);
        
        };
    };    
};
