#include <iostream>
#include <thread>

#include <gazebo/gazebo.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/common/common.hh>
#include <gazebo/physics/physics.hh>


#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "geometry_msgs/Twist.h"
#include "gps_plugin.hpp"
#include <ignition/math/Vector3.hh>

#define DEBUG false

namespace gazebo
{
    namespace gps
    {   
        GPS::GPS():ModelPlugin() {}
     		
        void GPS::Load(physics::ModelPtr model_ptr, sdf::ElementPtr sdf_ptr)
        {
          this->m_updateConnection = event::Events::ConnectWorldUpdateBegin(std::bind(&GPS::OnUpdate, this));

  			  // Save a pointer to the model for later use
  			  this->m_model = model_ptr;
  			
        	// Create topic name      	
        	std::string topic_name = "/" + this->m_model->GetName() + "/GPS";
  	        
          // Initialize ros, if it has not already been initialized.
    			if (!ros::isInitialized())
    			{
      			  int argc = 0;
      			  char **argv = NULL;
      			  ros::init(argc, argv, "gazebo_client_gps", ros::init_options::NoSigintHandler);
    			}

          this->m_ros_node.reset(new ::ros::NodeHandle("/gazebo_client_gps"));

        	this->m_pubGPS = this->m_ros_node->advertise<geometry_msgs::Twist>(topic_name, 2);

          this->m_gps_pose.linear.z   = 0;
          this->m_gps_pose.angular.x  = 0;
          this->m_gps_pose.angular.y  = 0;

          this->m_timestamp = this->m_model->GetWorld()->SimTime();
          if(DEBUG)
          {
              std::cerr << "\n\n";
              ROS_INFO_STREAM("====================================================================");
              ROS_INFO_STREAM("[gps_plugin] attached to: " << this->m_model->GetName());
              ROS_INFO_STREAM("[gps_plugin] publish to: "  << topic_name);
              ROS_INFO_STREAM("[gps_plugin] Usefull data: linear x, linear y, angular z");
              ROS_INFO_STREAM("====================================================================\n\n");
          }
        }

        // Publish the updated values
        void GPS::OnUpdate()
        {        

           	this->m_gps_pose.linear.x   = this->m_model->RelativePose().Pos().X();
           	this->m_gps_pose.linear.y   = abs(this->m_model->RelativePose().Pos().Y());
           	this->m_gps_pose.angular.z  = this->m_model->RelativePose().Rot().Yaw();
           	

            if((this->m_model->GetWorld()->SimTime() - this->m_timestamp).Float() > 1)
            {    
              this->m_pubGPS.publish(this->m_gps_pose);
              this->m_timestamp = this->m_model->GetWorld()->SimTime();
            }

        };      
    }; //namespace trafficLight
    GZ_REGISTER_MODEL_PLUGIN(gps::GPS)
}; // namespace gazebo
