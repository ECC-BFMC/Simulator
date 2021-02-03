#include "carlikerobot_ros_plugin.hpp"

#define DEBUG false

namespace gazebo
{
    namespace carlikerobot
    {
        /// Movement serialHandler
        CMessageHandler::CMessageHandler(std::string _modelName, IRobotCommandSetter* _setter)
        {
            this->_robotSetter = _setter;

            /*
            if multiple cars are generated, each one will have it's own topic 
            e.g:
            /car_1/Command
            /car_2/Command
            .
            .
            /car_n/Command
            
            */

            // Generate topic name
            std::string topicName = "/" + _modelName + "/Command";
            std::string listen_topicName = "/" + _modelName + "/Response";

            if(!::ros::isInitialized())
            {
                int argc = 0;
                char **argv = NULL;

                // Init a node with the name of _modelName
                ::ros::init(argc, argv, "/" + _modelName, ::ros::init_options::NoSigintHandler);
            }


            this->_rosNode.reset(new ::ros::NodeHandle("/"+_modelName));

            this->_commandSubscriber = this->_rosNode->subscribe(topicName, 1, &CMessageHandler::OnMsgCommand, this);
            
            this->_subscribeRosQueueThread = std::thread(std::bind(&CMessageHandler::QueueThread, this));

            // Feedback message
			this->_feedbackPublisher = this->_rosNode->advertise<car_plugin::Response>(listen_topicName, 2);

            if (DEBUG)
            {
                std::cerr << "\n\n";
                ROS_INFO_STREAM("====================================================================");
                ROS_INFO_STREAM("[carlikerobot_ros_plugin] attached to: " << _modelName);
                ROS_INFO_STREAM("[carlikerobot_ros_plugin] publish to: "  << topicName);
                ROS_INFO_STREAM("[carlikerobot_ros_plugin] listen to: "  << listen_topicName);
                ROS_INFO_STREAM("[carlikerobot_ros_plugin] Usefull data: /Response for ack, /Command for speed and steer");
                ROS_INFO_STREAM("====================================================================");
            }
        }

	CMessageHandler::~CMessageHandler()
	{
		if (this->_rosNode != nullptr)
		{
			this->_rosNode -> shutdown();
		}
		 this->_subscribeRosQueueThread.join();
	}

        // Callback function for receiving messages on the /car_name/Command topic
        void CMessageHandler::OnMsgCommand(car_plugin::CommandConstPtr _msg)
        {            
            switch (_msg->key.v){
                case car_plugin::Key::MOVE:
                    if (DEBUG){ROS_DEBUG("Received MOVE message");}
                    this->moveMessage(_msg->msg_val);
                    break;
                case car_plugin::Key::BRAKE:
                    if (DEBUG){ROS_DEBUG("Received BRAKE message");}
                    this->brakeMessage(_msg->msg_val);
                    break;
                default:
                    if (DEBUG){ROS_DEBUG("Received UNKNOWN message");}
                    this->unknownMessage();
            }
        }

        void CMessageHandler::unknownMessage()
        {
            car_plugin::Response l_resp;
            l_resp.key.v = car_plugin::Key::UNKNOWN;
            l_resp.response = "unknown";
            this->_feedbackPublisher.publish(l_resp);
        }

        void CMessageHandler::brakeMessage(std::vector<float> _msg_val)
        {
            if(_msg_val.size() == 1)
            {
                _robotSetter->setCommand(0.0,_msg_val[0]);
                car_plugin::Response l_resp;
                l_resp.key.v = car_plugin::Key::BRAKE;
                l_resp.response = "ack";
                this->_feedbackPublisher.publish(l_resp);
            }
            else
            {
                car_plugin::Response l_resp;
                l_resp.key.v = car_plugin::Key::BRAKE;
                l_resp.response = "syntax_error";
                this->_feedbackPublisher.publish(l_resp);
            }
        }

        void CMessageHandler::moveMessage(std::vector<float> _msg_val)
        {
            if(_msg_val.size() == 2)
            {
                _robotSetter->setCommand(_msg_val[0],_msg_val[1]);
                car_plugin::Response l_resp;
                l_resp.key.v = car_plugin::Key::MOVE;
                l_resp.response = "ack";
                this->_feedbackPublisher.publish(l_resp);
            }
            else
            {
                car_plugin::Response l_resp;
                l_resp.key.v = car_plugin::Key::MOVE;
                l_resp.response = "syntax_error";
                this->_feedbackPublisher.publish(l_resp);
            }
        }

        void CMessageHandler::QueueThread()
        {
            static const double timeout = 0.01;
            while (this->_rosNode->ok())
            {
                this->_subscriberQueue.callAvailable(ros::WallDuration(timeout));
            }
        }

        /// end movement serialHandler.




        CCarLikeRobotRosPlugin::CCarLikeRobotRosPlugin(): ModelPlugin()
        {
        }

        CCarLikeRobotRosPlugin::~CCarLikeRobotRosPlugin()
        {
        }
	    

        bool CCarLikeRobotRosPlugin::LoadParameterJoints(sdf::ElementPtr f_sdf)
        {
            // start [wheelbase] [axletrack] [wheelradius] handling*/
            double l_wheelbase   = 0;
            double l_axletrack   = 0;  
            double l_wheelradius = 0; 
            
            if(DEBUG)
            {
                std::cerr << "\n\n";
                ROS_INFO_STREAM("====================================================================");
            }

            if(f_sdf->HasElement("wheelbase"))
            {
                l_wheelbase = f_sdf->Get<double>("wheelbase");

                if(DEBUG)
                {
                    ROS_INFO("OK [wheelbase]   = %f", l_wheelbase);
                }
            }
            else
            {
                if(DEBUG)
                {
                    ROS_INFO("WARNING: [wheelbase] = 0 DEFAULT");
                }
            }
            
            if(f_sdf->HasElement("axletrack"))
            {
                l_axletrack = f_sdf->Get<double>("axletrack");

                if(DEBUG)
                {
                    ROS_INFO("OK [axletrack]   = %f", l_axletrack);
                }
            }
            else
            {
                ROS_INFO("WARNING: [axletrack] = 0 DEFAULT");
            }
            
            if(f_sdf->HasElement("wheelradius"))
            {
                l_wheelradius = f_sdf->Get<double>("wheelradius");

                if(DEBUG)
                {
                    ROS_INFO("OK [wheelradius] = %f", l_wheelradius);
                }
            }
            else
            {
                std::cerr << "WARNING: [wheelradius] = 0 DEFAULT\n";
                std::cerr << "CRITICAL: Invalid plugin parameters, wrong wheel radius.\n\
                              CarLikeRobotPlugin plugin is not loaded.\n";
                return false;
            }
            // end [wheelbase] [axletrack] [wheelradius] handling*/
            
            // start [speed_wheel_joints] [front_wheel_joints] [rear_wheel_joints]
            sdf::ElementPtr l_steering_joints_sdf   = NULL;
            sdf::ElementPtr l_speed_wheel_sdf       = NULL; 
            sdf::ElementPtr l_front_wheel_sdf       = NULL;
            sdf::ElementPtr l_rear_wheel_sdf        = NULL;
            
            if(f_sdf->HasElement("speed_wheel_joints"))
            {
    
                double l_kp_speed = 0;
                double l_ki_speed = 0;
                double l_kd_speed = 0;
    
                l_speed_wheel_sdf = f_sdf->GetElement("speed_wheel_joints");

                if(DEBUG)
                {
                    ROS_INFO_STREAM("====================================================================");
                    std::cerr << "\n\n";
                    ROS_INFO_STREAM("====================================================================");
                    ROS_INFO("FOUND: [speed_wheel_joints]");
                }

                // start [kp] [ki] [kd] 
                if(l_speed_wheel_sdf->HasElement("kp"))
                {
                    l_kp_speed = l_speed_wheel_sdf->Get<double>("kp");
                    
                    if(DEBUG)
                    {
                        ROS_INFO("OK [kp] = %f", l_kp_speed);
                    } 
                }
                else
                {
                    std::cerr << "<kp> under <speed_wheel_joints> not found. 0 DEFAULT\n";
                }

                if(l_speed_wheel_sdf->HasElement("kd"))
                {
                    l_kd_speed = l_speed_wheel_sdf->Get<double>("kd");
                    
                    if(DEBUG)
                    {
                        ROS_INFO("OK [kd] = %f", l_kd_speed);
                    }
                }
                else
                {
                    std::cerr << "<kd> under <speed_wheel_joints> not found. 0 DEFAULT\n";
                }

                if(l_speed_wheel_sdf->HasElement("ki"))
                {
                    l_ki_speed = l_speed_wheel_sdf->Get<double>("ki");
                    
                    if(DEBUG)
                    {
                        ROS_INFO("OK [ki] = %f", l_ki_speed);
                    }
                }
                else
                {
                    std::cerr << "<ki> under <speed_wheel_joints> not found. 0 DEFAULT\n";
                }// end [kp] [ki] [kd] 


                // start HasElement("front_wheel_joints")
                if(l_speed_wheel_sdf->HasElement("front_wheel_joints"))
                {
                    if(DEBUG)
                    {
                        ROS_INFO_STREAM("====================================================================");
                        std::cerr << "\n\n";
                        ROS_INFO_STREAM("====================================================================");
                        ROS_INFO("FOUND: [front_wheel_joints]");
                    }

                    l_front_wheel_sdf = l_speed_wheel_sdf->GetElement("front_wheel_joints");

                    // START FRONT WHEELS CONTROLLER FOR SPINNING
                    std::string l_left  = l_front_wheel_sdf->Get<std::string>("leftjoint");
                    if(l_left == " ")
                    {
                        std::cerr << "CRITICAL: empty front [leftjoint] name. Plugin WAS NOT LOADED. exitting...\n";
                        return false;
                    }
                    else
                    {
                        if(DEBUG)
                        {
                            ROS_INFO("OK front [leftjoint]  name = %s", l_left.c_str());
                        }
                    }

                    std::string l_right = l_front_wheel_sdf->Get<std::string>("rightjoint");
                    if(l_right == " ")
                    {
                        std::cerr << "CRITICAL: empty front [rightjoint] name. Plugin WAS NOT LOADED. exitting...\n";
                        return false;
                    }
                    else
                    {
                        if(DEBUG)
                        {
                            ROS_INFO("OK front [rightjoint] name = %s", l_right.c_str());
                        }
                    }

                    physics::JointPtr l_rightJoint  = this->_model->GetJoint(l_right);
                    if(l_rightJoint == NULL)
                    {
                        std::cerr << "CRITICAL: front [rightjoint] name MISMACH. Check model's joints names\
                                      Plugin WAS NOT LOADED. exitting...\n";
                        return false;
                    }
                    else
                    {
                        if(DEBUG)
                        {
                            ROS_INFO("OK front [rightjoint] was found in model");
                        }
                    }

                    physics::JointPtr l_leftJoint   = this->_model->GetJoint(l_left);
                    if(l_leftJoint == NULL)
                    {
                        std::cerr << "CRITICAL: front [leftjoint] name MISMACH. Check model's joints names\
                                      Plugin WAS NOT LOADED. exitting...\n";
                        return false;
                    }
                    else
                    {
                        if(DEBUG)
                        {
                            ROS_INFO("OK front [leftjoint]  was found in model");
                        }
                    }

                    // PID
                    common::PID l_rightPID  = common::PID(l_kp_speed, l_ki_speed, l_kd_speed);
                    common::PID l_leftPID   = common::PID(l_kp_speed, l_ki_speed, l_kd_speed);

                    // FrontWheelsSpeed
                    this->_frontWheelSpeedPtr = IWheelsSpeedPtr(new CFrontWheelsSpeed(l_axletrack,
                                                                                      l_wheelbase,
                                                                                      l_wheelradius,
                                                                                      l_rightJoint,
                                                                                      l_leftJoint,
                                                                                      l_rightPID,
                                                                                      l_leftPID,
                                                                                      this->_model));
                    // END FRONT WHEELS CONTROLLER FOR SPINNING
                }// END HasElement("front_wheel_joints")


                // start HasElement("rear_wheel_joints") 
                if(l_speed_wheel_sdf->HasElement("rear_wheel_joints"))
                {
                    if(DEBUG)
                    {
                        ROS_INFO_STREAM("====================================================================");
                        std::cerr << "\n\n";
                        ROS_INFO_STREAM("====================================================================");
                        ROS_INFO("FOUND: [rear_wheel_joints]");
                    }

                    l_rear_wheel_sdf = l_speed_wheel_sdf->GetElement("rear_wheel_joints");

                    // START REAR WHEELS CONTROLLER FOR SPINNING
                    std::string l_left  = l_rear_wheel_sdf->Get<std::string>("leftjoint");
                    if(l_left == " ")
                    {
                        std::cerr << "CRITICAL: empty rear [leftjoint] name. Plugin WAS NOT LOADED. exitting...\n";
                        return false;
                    }
                    else
                    {
                        if(DEBUG)
                        {
                            ROS_INFO("OK rear [leftjoint]  name = %s", l_left.c_str());
                        }
                    }

                    std::string l_right = l_rear_wheel_sdf->Get<std::string>("rightjoint");
                    if(l_right == " ")
                    {
                        std::cerr << "CRITICAL: empty rear [rightjoint] name. Plugin WAS NOT LOADED. exitting...\n";
                        return false;
                    }
                    else
                    {
                       if(DEBUG)
                       {
                            ROS_INFO("OK rear [rightjoint] name = %s", l_right.c_str());
                       }
                    }

                    physics::JointPtr l_rightJoint  = this->_model->GetJoint(l_right);
                    if(l_rightJoint == NULL)
                    {
                        std::cerr << "CRITICAL: rear [rightjoint] name MISMACH. Check model's joints names\
                                      Plugin WAS NOT LOADED. exitting...\n";
                        return false; 
                    }
                    else
                    {
                        if(DEBUG)
                        {
                            ROS_INFO("OK rear [rightjoint] was found in model");
                        }
                    }

                    physics::JointPtr l_leftJoint   = this->_model->GetJoint(l_left);
                    if(l_leftJoint == NULL)
                    {
                        std::cerr << "CRITICAL: rear [leftjoint] name MISMACH. Check model's joints names\
                                      Plugin WAS NOT LOADED. exitting...\n";
                        return false;
                    }
                    else
                    {
                        if(DEBUG)
                        {
                            ROS_INFO("OK rear [leftjoint] was found in model");
                        }
                    }

                    // PID
                    common::PID l_rightPID = common::PID(l_kp_speed,l_ki_speed,l_kd_speed);
                    common::PID l_leftPID  = common::PID(l_kp_speed,l_ki_speed,l_kd_speed);
                    
                    // RearWheelsSpeed
                    this->_rearWheelsSpeedPtr = IWheelsSpeedPtr(new CRearWheelsSpeed( l_axletrack
                                                                    ,l_wheelbase
                                                                    ,l_wheelradius
                                                                    ,l_rightJoint
                                                                    ,l_leftJoint
                                                                    ,l_rightPID
                                                                    ,l_leftPID
                                                                    ,this->_model));
                    // END REAR WHEELS CONTROLLER FOR SPINNING
                }// END HasElement("rear_wheel_joints")                
            
            }// END [speed_wheel_joints] [front_wheel_joints] [rear_wheel_joints]
            

            if(f_sdf->HasElement("steer_wheel_joints"))
            {

                l_steering_joints_sdf = f_sdf->GetElement("steer_wheel_joints");
                
                if(DEBUG)
                {
                    ROS_INFO_STREAM("====================================================================");
                    std::cerr << "\n\n";
                    ROS_INFO_STREAM("====================================================================");    
                    ROS_INFO("FOUND: [steer_wheel_joints]");
                }
                
                double l_kp_position = 0;
                double l_ki_position = 0;
                double l_kd_position = 0;

                // start [kp] [ki] [kd] 
                if(l_steering_joints_sdf->HasElement("kp"))
                {
                    l_kp_position = l_steering_joints_sdf->Get<double>("kp");
                    if(DEBUG)
                    {
                        ROS_INFO("OK [kp] = %f", l_kp_position);
                    }
                }
                else
                {
                    std::cerr << "<kp> under <speed_wheel_joints> not found. 0 DEFAULT\n";
                }

                if(l_steering_joints_sdf->HasElement("kd"))
                {
                    l_kd_position = l_steering_joints_sdf->Get<double>("kd");
                    if(DEBUG)
                    {
                        ROS_INFO("OK [kd] = %f", l_kd_position);
                    }
                }
                else
                {
                    std::cerr << "<kd> under <speed_wheel_joints> not found. 0 DEFAULT\n";
                }

                if(l_steering_joints_sdf->HasElement("ki"))
                {
                    l_ki_position = l_steering_joints_sdf->Get<double>("ki");
                    
                    if(DEBUG)
                    {
                        ROS_INFO("OK [ki] = %f", l_ki_position);
                    }
                }
                else
                {
                    std::cerr << "<ki> under <speed_wheel_joints> not found. 0 DEFAULT\n";
                }// end [kp] [ki] [kd] 
                

                // Steering angle pid
                std::string l_left  = l_steering_joints_sdf->Get<std::string>("leftjoint");
                std::string l_right = l_steering_joints_sdf->Get<std::string>("rightjoint");
                
                if(l_left=="" || l_right==""){
                    std::cerr << "CRITICAL: Invalid steering joints. CarLikeRobotPlugin plugin is not loaded.\n";
                    return false;
                }


                physics::JointPtr l_rightJoint = this->_model->GetJoint(l_right);
                physics::JointPtr l_leftJoint  = this->_model->GetJoint(l_left);
                
                if(l_leftJoint==NULL || l_rightJoint==NULL){
                    std::cerr<<"Invalid steering joints. CarLikeRobotPlugin plugin is not loaded.\n";
                    return false;
                }
                ROS_INFO_STREAM("====================================================================");

                if(DEBUG)
                {
                    std::cerr << "\n\n";
                    ROS_INFO_STREAM("====================================================================");
                    ROS_INFO("Steering PID: Kp=%f, Ki=%f, Kd=%f",l_kp_position,l_ki_position,l_kd_position);
                    ROS_INFO("Joint names: %s, %s",l_left.c_str(),l_right.c_str());
                    ROS_INFO_STREAM("====================================================================");
                }

                // PID
                common::PID l_rightPID = common::PID(l_kp_position,l_ki_position,l_kd_position);
                common::PID l_leftPID  = common::PID(l_kp_position,l_ki_position,l_kd_position);
                // A steering angle calculator
                this->_steerWheelsAnglePtr = ISteerWheelsPtr(new CSteerWheelsAngle( l_axletrack
                                                                    ,l_wheelbase
                                                                    ,l_rightJoint
                                                                    ,l_leftJoint
                                                                    ,l_rightPID
                                                                    ,l_leftPID
                                                                    ,this->_model));
                // END HasElement("steer_wheel_joints")
            }

            return true;
        }


        void CCarLikeRobotRosPlugin::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
        {
            
            // Safety check
            if (_parent->GetJointCount() == 0)
            {
                std::cerr << "Invalid joint count, CarLikeRobotPlugin plugin not loaded\n";
                return;
            }
            this->_model = _parent;
            bool isLoaded = this->LoadParameterJoints(_sdf);
            if(!isLoaded){
                return;
            }

            double l_initial_steer = _sdf->Get<double>("initial_steer");
            double l_initial_speed = _sdf->Get<double>("initial_speed");

            this->setCommand(l_initial_speed,l_initial_steer);
            
            _messageHandler = std::shared_ptr<CMessageHandler>(new CMessageHandler(this->_model->GetName(),this));
        }

        void CCarLikeRobotRosPlugin::setCommand(float f_speed,float f_steer){
            if(this->_rearWheelsSpeedPtr!=NULL){
               this->_rearWheelsSpeedPtr->update(f_steer,f_speed); 
            }
            
            if(this->_frontWheelSpeedPtr!=NULL){
                this->_frontWheelSpeedPtr->update(f_steer,f_speed);    
            }

            if(this->_steerWheelsAnglePtr!=NULL){
                this->_steerWheelsAnglePtr->update(f_steer);               
            }
            
        }

        void CCarLikeRobotRosPlugin::OnMsgCommand(car_plugin::CommandConstPtr _msg){
            
            
            switch (_msg->key.v){
                case car_plugin::Key::MOVE:
                    this->moveMessage(_msg->msg_val);
                    ROS_DEBUG("Received MOVE message");
                    break;

                case car_plugin::Key::BRAKE:
                    this->brakeMessage(_msg->msg_val);
                    ROS_DEBUG("Received BRAKE message");
                    break;
                
                default:
                    this->unknownMessage();
                    ROS_DEBUG("Received UNKNOWN message");

            }
        }
        
        void CCarLikeRobotRosPlugin::unknownMessage(){
            car_plugin::Response l_resp;
            l_resp.key.v = car_plugin::Key::UNKNOWN;
            l_resp.response = "unknown";
            this->rosPub.publish(l_resp);
        }

        void CCarLikeRobotRosPlugin::brakeMessage(std::vector<float> _msg_val){
            if(_msg_val.size()==1){
                this->setCommand(0.0,_msg_val[0]);
                car_plugin::Response l_resp;
                l_resp.key.v = car_plugin::Key::BRAKE;
                l_resp.response = "ack";
                this->rosPub.publish(l_resp);
            }
            else{
                car_plugin::Response l_resp;
                l_resp.key.v = car_plugin::Key::BRAKE;
                l_resp.response = "syntax_error";
                this->rosPub.publish(l_resp);
            }
        }

        void CCarLikeRobotRosPlugin::moveMessage(std::vector<float> _msg_val){
            if(_msg_val.size()==2){
                this->setCommand(_msg_val[0],_msg_val[0]);
                car_plugin::Response l_resp;
                l_resp.key.v = car_plugin::Key::MOVE;
                l_resp.response = "ack";
                this->rosPub.publish(l_resp);
            }
            else{
                car_plugin::Response l_resp;
                l_resp.key.v = car_plugin::Key::MOVE;
                l_resp.response = "syntax_error";
                this->rosPub.publish(l_resp);
            }
        }

        void CCarLikeRobotRosPlugin::QueueThread()
        {
            static const double timeout = 0.01;
            while (this->rosNode->ok())
            {
                this->rosQueue.callAvailable(ros::WallDuration(timeout));
            }
        }

        void CCarLikeRobotRosPlugin::onUpdate(){
        }
                
    }; // namespace CarLikeRobot
    GZ_REGISTER_MODEL_PLUGIN(carlikerobot::CCarLikeRobotRosPlugin)
} // namespace gazebo
