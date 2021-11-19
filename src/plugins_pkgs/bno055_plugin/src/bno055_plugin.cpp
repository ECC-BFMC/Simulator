#include "bno055_plugin.hpp"

#define DEBUG false

namespace gazebo
{
    namespace bno055
    {   
        BNO055::BNO055():ModelPlugin() {}

        void BNO055::Load(physics::ModelPtr model_ptr, sdf::ElementPtr sdf_ptr)
        {
            nh = boost::make_shared<ros::NodeHandle>();	
            timer = nh->createTimer(ros::Duration(0.1), std::bind(&BNO055::OnUpdate, this));
	    	
      			// Save a pointer to the model for later use
      			this->m_model = model_ptr;
      			
          	// Create topic name        	
          	std::string topic_name = "/automobile/IMU";
	        

            // Initialize ros, if it has not already bee initialized.
      			if (!ros::isInitialized())
      			{
        			  int argc = 0;
        			  char **argv = NULL;
        			  ros::init(argc, argv, "gazebo_client_bno", ros::init_options::NoSigintHandler);
      			}

            this->m_ros_node.reset(new ::ros::NodeHandle("/bnoNODEvirt"));
          	this->m_pubBNO = this->m_ros_node->advertise<utils::IMU>(topic_name, 2);


            if(DEBUG)
            {
                std::cerr << "\n\n";
                ROS_INFO_STREAM("====================================================================");
                ROS_INFO_STREAM("[bno055_plugin] attached to: " << this->m_model->GetName());
                ROS_INFO_STREAM("[bno055_plugin] publish to: "  << topic_name);
                ROS_INFO_STREAM("[bno055_plugin] Usefull data: linear z, angular x, angular y, angular z");
                ROS_INFO_STREAM("====================================================================");
            }
        }

        // Publish the updated values
        void BNO055::OnUpdate()
        {        
          
           	this->m_bno055_pose.roll = this->m_model->RelativePose().Rot().Roll();
		this->m_bno055_pose.pitch = this->m_model->RelativePose().Rot().Pitch();
           	this->m_bno055_pose.yaw = this->m_model->RelativePose().Rot().Yaw();
           	
            this->m_pubBNO.publish(this->m_bno055_pose);
        };      
    }; //namespace trafficLight
    GZ_REGISTER_MODEL_PLUGIN(bno055::BNO055)
}; // namespace gazebo
