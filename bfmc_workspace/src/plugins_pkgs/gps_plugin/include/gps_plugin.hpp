#pragma once

namespace gazebo
{
    namespace gps
    {   
        class GPS: public ModelPlugin
    	{
        private: 
            physics::ModelPtr                   m_model;
            sdf::ElementPtr                     m_sdf;
            event::ConnectionPtr                m_updateConnection;

            // A node use for ROS transport
            std::unique_ptr<ros::NodeHandle>    m_ros_node;

            // A ROS publisher
            ros::Publisher                      m_pubGPS;

            // A thread the keeps running the rosQueue
            std::thread                         m_ros_queue_thread;

            // The gps message
            geometry_msgs::Twist                m_gps_pose;

            // Timer for 1s delay
            gazebo::common::Time                m_timestamp;          


        // Default constructor
        public: GPS();
        public: void Load(physics::ModelPtr, sdf::ElementPtr);
        public: void OnUpdate();        
        };
    };    
};
