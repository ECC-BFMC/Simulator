
#include "gps_plugin.hpp"

#define DEBUG false

namespace gazebo
{
    namespace gps
    {   
        GPS::GPS():ModelPlugin() {}
     		
        void GPS::Load(physics::ModelPtr model_ptr, sdf::ElementPtr sdf_ptr)
        {
          nh = boost::make_shared<ros::NodeHandle>();
          timer = nh->createTimer(ros::Duration(0.25), std::bind(&GPS::OnUpdate, this));

  			  // Save a pointer to the model for later use
  			  this->m_model = model_ptr;
  			
        	// Create topic name      	
        	std::string topic_name = "/automobile/localisation";
  	        
          // Initialize ros, if it has not already been initialized.
    			if (!ros::isInitialized())
    			{
      			  int argc = 0;
      			  char **argv = NULL;
      			  ros::init(argc, argv, "localisationNODEvirt", ros::init_options::NoSigintHandler);
    			}

          this->m_ros_node.reset(new ::ros::NodeHandle("/localisationNODEvirt"));

        	this->m_pubGPS = this->m_ros_node->advertise<utils::localisation>(topic_name, 2);
        	
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
		this->m_gps_pose.timestamp  = this->m_model->GetWorld()->SimTime().Float();
           	this->m_gps_pose.posA   = this->m_model->RelativePose().Pos().X() + (rand() / (float)RAND_MAX * 0.2) - 0.1;
           	this->m_gps_pose.posB   = abs(this->m_model->RelativePose().Pos().Y()) + (rand() / (float)RAND_MAX * 0.2) - 0.1;
           	this->m_gps_pose.rotA   = this->m_model->RelativePose().Rot().Yaw();
           	this->m_gps_pose.rotB   = this->m_model->RelativePose().Rot().Yaw();
               this->m_pubGPS.publish(this->m_gps_pose);
        };      
    }; //namespace trafficLight
    GZ_REGISTER_MODEL_PLUGIN(gps::GPS)
}; // namespace gazebo