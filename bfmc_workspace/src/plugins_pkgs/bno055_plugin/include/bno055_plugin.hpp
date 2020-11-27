#pragma once

namespace gazebo
{
    namespace bno055
    {   
        class BNO055: public ModelPlugin
    	{
        private: 
            physics::ModelPtr                   m_model;
            sdf::ElementPtr                     m_sdf;
            event::ConnectionPtr                m_updateConnection;

            /** ----------------------------------For ROS integration----------------------------------------------------**/
            // A node use for ROS transport
            std::unique_ptr<ros::NodeHandle>    m_ros_node;

            // A ROS publisher
            ros::Publisher                      m_pubBNO;

            // A thread the keeps running the rosQueue
            std::thread                         m_ros_queue_thread;
            
            geometry_msgs::Twist                m_bno055_pose;

        // Default constructor
        public: BNO055();
        public: void Load(physics::ModelPtr, sdf::ElementPtr);
        public: void OnUpdate();        
        };
    };    
};
