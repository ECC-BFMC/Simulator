#include "traffic_light_plugin.hpp"

#define DEBUG false

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
	}
     
        void TrafficLight::Load(physics::ModelPtr model_ptr, sdf::ElementPtr sdf_ptr)
        {        	
			// Save a pointer to the model for later use
			this->m_model = model_ptr;
			this->name = this->m_model->GetName();
			
        	// Create transport node
			this->m_node = transport::NodePtr(new transport::Node());
			this->m_node->Init();
        	
        	this->m_pubLight = this->m_node->Advertise<gazebo::msgs::Light>("~/light/modify");
        	
        	// Save pointers to each link of the traffic light (aka lens)
        	this->m_green_lens_link		= this->m_model->GetLink("green_lens");
			this->m_yellow_lens_link	= this->m_model->GetLink("yellow_lens");
			this->m_red_lens_link	 	= this->m_model->GetLink("red_lens");
      	
            // Initialize ros, if it has not already bee initialized.
			if (!ros::isInitialized())
			{
			  int argc = 0;
			  char **argv = NULL;
			  ros::init(argc, argv, "gazebo_client", ros::init_options::NoSigintHandler);
			}
			
			// Create our ROS node. This acts in a similar manner to the Gazebo node
			this->m_ros_node.reset(new ros::NodeHandle("trafficlightNODEvirt" + this->name));

			// Create a subscriber
			this->m_ros_subscriber = this->m_ros_node->subscribe("/automobile/trafficlight/" + this->name, 1, &trafficLight::TrafficLight::OnRosMsg, this);

			if(DEBUG)
            {
                std::cerr << "\n\n";
                ROS_INFO_STREAM("====================================================================");
                ROS_INFO_STREAM("[traffic_light_plugin] attached to: " << this->name);
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
		void TrafficLight::OnRosMsg(std_msgs::Byte _msg)
		{
			switch(_msg.data)
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
		};
    }; //namespace trafficLight
    GZ_REGISTER_MODEL_PLUGIN(trafficLight::TrafficLight)
}; // namespace gazebo
