#include <iostream>
#include <thread>

#include <gazebo/gazebo.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/common/common.hh>
#include <gazebo/physics/physics.hh>


#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "std_msgs/Float32.h"
#include "traffic_light_plugin.hpp"

#define DEBUG true

namespace gazebo
{
    namespace trafficLight
    {   
        TrafficLight::TrafficLight():ModelPlugin() {}
	TrafficLight::~TrafficLight()
	{
		if (this->m_ros_node != nullptr)
		{
			this->m_ros_node -> shutdown();
		}
		ROS_INFO_STREAM("ENDING");
		this->m_ros_queue_thread.join();
		ROS_INFO_STREAM("The end");
	}
     
        void TrafficLight::Load(physics::ModelPtr model_ptr, sdf::ElementPtr sdf_ptr)
        {        	
			// Save a pointer to the model for later use
			this->m_model = model_ptr;
			
        	// Create transport node
			this->m_node = transport::NodePtr(new transport::Node());
			this->m_node->Init();
        	
        	m_pubLight = this->m_node->Advertise<gazebo::msgs::Light>("~/light/modify");
        	
        	// Save pointers to each link of the traffic light (aka lens)
        	this->m_green_lens_link		= this->m_model->GetLink("green_lens");
			this->m_yellow_lens_link	= this->m_model->GetLink("yellow_lens");
			this->m_red_lens_link	 	= this->m_model->GetLink("red_lens");

			// Scope name
			this->m_scope_name = this->m_red_lens_link->GetScopedName();
      	
            // Initialize ros, if it has not already bee initialized.
			if (!ros::isInitialized())
			{
			  int argc = 0;
			  char **argv = NULL;
			  ros::init(argc, argv, "gazebo_client", ros::init_options::NoSigintHandler);
			}
			
			// Create our ROS node. This acts in a similar manner to the Gazebo node
			// Destroys the object currently managed by the unique_ptr (if any) and takes ownership of ros::NodeHandle("gazebo_client")
			this->m_ros_node.reset(new ros::NodeHandle("gazebo_client"));

			// Create a named topic, and subscribe to it.
			ros::SubscribeOptions so = ros::SubscribeOptions::create<traffic_light_pkg::traffic_light>("/traffic_light_topic", 1,
																						boost::bind(&trafficLight::TrafficLight::OnRosMsg, this, _1),
			      																		ros::VoidPtr(), &this->m_ros_queue);

			this->m_ros_subscriber = this->m_ros_node->subscribe(so);

			// Spin up the queue helper thread.
			this->m_ros_queue_thread = std::thread(std::bind(&trafficLight::TrafficLight::QueueThread, this));

			if(DEBUG)
            {
                std::cerr << "\n\n";
                ROS_INFO_STREAM("====================================================================");
                ROS_INFO_STREAM("[traffic_light_plugin] attached to: " << this->m_model->GetName());
                ROS_INFO_STREAM("[traffic_light_plugin] listen to: /traffic_light_topic ");
                ROS_INFO_STREAM("====================================================================");
            }
        }

		// defining the traffic_light states
        void TrafficLight::redState(const bool state)
        {
        	this->m_msg.set_name(this->m_red_lens_link->GetScopedName() + "::" + static_cast<std::string>("red_lens_light"));
		 	this->m_msg.set_range(state? 5 : 0);
			this->m_pubLight->Publish(m_msg);
        }
        
        void TrafficLight::yellowState(const bool state)
        {
        	this->m_msg.set_name(this->m_yellow_lens_link->GetScopedName() + "::" + static_cast<std::string>("yellow_lens_light"));
		 	this->m_msg.set_range(state? 5 : 0);
			this->m_pubLight->Publish(m_msg);
        }
        void TrafficLight::greenState(const bool state)
        
        {
        	this->m_msg.set_name(this->m_green_lens_link->GetScopedName() + "::" + static_cast<std::string>("green_lens_light"));
		 	this->m_msg.set_range(state? 5 : 0);
			this->m_pubLight->Publish(m_msg);
        }
        
        // Handle an incoming message from ROS
		// _msg A float value that is used to set the velocity
		void TrafficLight::OnRosMsg(const traffic_light_pkg::traffic_lightConstPtr &_msg)
		{
			// TL0 TL1 TL2 
			if(static_cast<int>(_msg->id) == ((this->m_scope_name)[2] - '0'))
			{
				switch(static_cast<int>(_msg->state))
				{
					case TrafficLightColor::RED:
						redState(1); yellowState(0); greenState(0);
						break;

					case TrafficLightColor::YELLOW:
						redState(0); yellowState(1); greenState(0);
						break;

					case TrafficLightColor::GREEN:
						redState(0); yellowState(0); greenState(1);
						break;
				}
			}
		}

		/// \brief ROS helper function that processes messages
		void TrafficLight::QueueThread()
		{
		  static const double timeout = 0.01;
		  while (this->m_ros_node->ok())
		  {
		    this->m_ros_queue.callAvailable(ros::WallDuration(timeout));
		  }
		ROS_INFO_STREAM("ENDEEED THREAD");
		}     
    }; //namespace trafficLight
    GZ_REGISTER_MODEL_PLUGIN(trafficLight::TrafficLight)
}; // namespace gazebo
