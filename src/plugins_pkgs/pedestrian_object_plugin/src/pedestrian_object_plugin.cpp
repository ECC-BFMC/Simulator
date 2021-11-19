#include <gazebo/gazebo.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Vector3.hh>

#define _USE_MATH_DEFINES
#include <cmath>
#include <chrono>
#include <thread>
#include <string>

#include "pedestrian_object_plugin.h"

// This is the distance that triggers the pedestrian
#define CAR_DIST_METER 0.5

namespace gazebo
{
    namespace pedestrian
    {   
        Pedestrian::Pedestrian():ModelPlugin() {}

        /*
        *   This method takes two parameters [GeometricPoint] and one [double]
        * - origin - the pedestrian position
        * - point  - the center point of the region which will trigger the pedestrian
        * - angle  - the rotation of the pedestrian
        */
        GeometricPoint Pedestrian::rotate(GeometricPoint origin, GeometricPoint point, double angle)
        {
            GeometricPoint result_point;
         
            result_point.x = origin.x + (cos(angle) * (point.x - origin.x)) - (sin(angle) * (point.y - origin.y));
            result_point.y = origin.y + (sin(angle) * (point.x - origin.x)) + (cos(angle) * (point.y - origin.y));

            return result_point;
        }

        /*
        *   This method updates the position of the pedestiran. It takes no parameters, but it sets the
        * class members of [Pedestrian] class:
        * - [m_ped_position]    - the (x,y) of the pedestrian
        * - [m_ped_wz]          - the rotation of the pedestrian
        */
        void Pedestrian::updatePedestrianPosition()
        {
            // Save the pedestrian position (x, y)            
            m_ped_position.setPoint(this->m_model->RelativePose().Pos().X(), this->m_model->RelativePose().Pos().Y());

            // Save the pedestrian rotation (wz only)       
            this->m_ped_wz = this->m_model->RelativePose().Rot().Yaw();
        }

        /*
        *   This method updates the position of the rc car. It takes no parameters, but it sets the
        * class members of [Pedestrian] class:
        * - [m_rc_car_position]    - the (x,y) of the rc car
        * - [m_rc_car_wz]          - the rotation of the rc car
        */
        void Pedestrian::updateRcCarPosition()
        {
            //Save the rc_car position (x, y) 
            this->m_rc_car_position.setPoint(this->m_rc_car->RelativePose().Pos().X(), this->m_rc_car->RelativePose().Pos().Y());

            // Save the rc_car rotation (wz only)
            this->m_rc_car_wz = this->m_rc_car->RelativePose().Rot().Yaw();
        }
       
        /*
        *   This method receives two parameters of type [Geometric point] and one of type [double] and:
        *   - it computes the distance between the two points 
        *   - it compares the result with the [double] parameter and returns:
        *       -- true (if the distance is short enough)
        *       -- false (the points are too far away)
        */
        bool Pedestrian::hasReached(const GeometricPoint &first_point, const GeometricPoint &second_point, const double &distance)
        {
            // @distance is in meters
            double local_dist = sqrt(pow((first_point.x - second_point.x), 2) + pow((first_point.y - second_point.y), 2));

            if(local_dist < distance)
            {
                this->m_stopped = true;
                return true;
            }
            return false;
        } 

        /*
        *   This method creates two points (aka the two zone's center that will trigger the pedestrian) relative to
        * the pedestrian (which has been correctly spawned on the map). Afterwords it moves the points so that it
        * corresponds also to the rotation of the pedestrian.
        *
        */
        void Pedestrian::generatePoints()
        {     

            /** Generate the points which will trigger the pedestrian*/
            //*
            //*
            //*
            GeometricPoint  far_point{this->m_ped_position.x + 0.5, this->m_ped_position.y + Dist::road_width};
            GeometricPoint near_point{this->m_ped_position.x - 0.5, this->m_ped_position.y + Dist::lane_width};

            GeometricPoint result_near          = rotate(m_ped_position, near_point, this->m_ped_wz);
            GeometricPoint result_far           = rotate(m_ped_position, far_point, this->m_ped_wz);

            this->m_near_point.setPoint(result_near);
            this->m_far_point.setPoint(result_far);


            /** Generate the points where the pedestrian will be stopped during the simulation*/
            //*
            //*
            //*
            GeometricPoint              first_lane_point{this->m_ped_position.x, this->m_ped_position.y + Dist::lane_width + Dist::thin_mark};
            GeometricPoint             second_lane_point{this->m_ped_position.x, this->m_ped_position.y + 2 * Dist::lane_width + 2 * Dist::thin_mark};
            GeometricPoint  right_side_of_the_road_point{this->m_ped_position.x, this->m_ped_position.y + Dist::road_width + 2 * Dist::thin_mark + Dist::lane_width};
            
            GeometricPoint result_first_lane_point             = rotate(m_ped_position, first_lane_point, this->m_ped_wz);
            GeometricPoint result_second_lane_point            = rotate(m_ped_position, second_lane_point, this->m_ped_wz);
            GeometricPoint result_right_side_of_the_road_point = rotate(m_ped_position, right_side_of_the_road_point, this->m_ped_wz);
            
            // Store the points where the pedestrial will be stopped 
            this->wait_for_car_point.setPoint(this->m_ped_position.x, this->m_ped_position.y);
            this->first_lane_point.setPoint(result_first_lane_point);
            this->second_lane_point.setPoint(result_second_lane_point);
            this->right_side_of_the_road_point.setPoint(result_right_side_of_the_road_point);
        }

        ignition::math::Vector3d Pedestrian::calculateVelocity(float velocity, bool isForward=true)
        {   
            if(velocity != 0)
            {
                // This boolean helps the pedestrian to not get stuck
                this->m_stopped = false;
            }

            //velocity should be between (0;1)
            int8_t sign = isForward? -1 : 1;

            double x = sign * (velocity * sin(this->m_ped_wz));
            double y = (-1) * sign * (velocity * cos(this->m_ped_wz));
            return ignition::math::Vector3d{x, y, 0};
        }

        bool Pedestrian::timeChecker(const gazebo::common::Time &start_time, const gazebo::common::Time &current_time, const float duration)
        {   
            //This method returns true if current_time is in interval and false if it's not            
            if((current_time-start_time).Float() > duration)
            {    
                return true;
            }
            return false;
        }
        
        void Pedestrian::Load(physics::ModelPtr model_ptr, sdf::ElementPtr sdf_ptr)
        {

            // Listen to the update event, which is broadcasted every simulation iteration
            this->m_updateConnection = event::Events::ConnectWorldUpdateBegin(std::bind(&Pedestrian::OnUpdate, this));

            // Save the pointers for later use
            this->m_model   = model_ptr;
            this->m_sdf     = sdf_ptr;

            // Actualize the pedestrian position
            updatePedestrianPosition();

            // Get the center points of the zones which will trigger the pedestrian to move;k
            generatePoints();

            // Get Model pointer to the rc_car by name
            
            if(this->m_sdf->HasElement("rc_car_name"))
            {
                this->m_rc_car_name = this->m_sdf->Get<std::string>("rc_car_name");
            }
            else
            {
                std::cerr << "\n\n*******************************************************************\n";
                std::cerr << "*******************************************************************\n";
                std::cerr << "WARNING: In [pedestrian_object] sdf file no rc_car_name was found";
                std::cerr << "Default rc_car_name: [ " << this->m_rc_car_name << " ]\n";
                std::cerr << "*******************************************************************";
                std::cerr << "*******************************************************************\n\n";
            }

            if((this->m_rc_car =this->m_model->GetWorld()->ModelByName(this->m_rc_car_name)) == NULL)
            {
                std::cerr << "\n\n*******************************************************************\n";
                std::cerr << "*******************************************************************\n";
                std::cerr << "WARNING: While loading [pedestrian_object_plugin] The rc car model witth the name [ " << this->m_rc_car_name << " ] was not found\n";
                std::cerr << "The name can be modified in the sdf file of the pedestrian_object_models, adding the \"<rc_car_name>\" tag\n";
                std::cerr << "*******************************************************************\n";
                std::cerr << "*******************************************************************\n\n";
            }
        }

        void Pedestrian::OnUpdate()
        {
            if((this->m_rc_car = this->m_model->GetWorld()->ModelByName(this->m_rc_car_name)) == NULL)
            {
                return;
            }

            //it is a callback function that updates the positions every iteration
            updatePedestrianPosition();
            updateRcCarPosition();            
            
            switch (this->m_state)
            {
                case States::wait_for_car:
                        
                    if(hasReached(this->m_rc_car_position, this->m_near_point, CAR_DIST_METER))            // If the car is close to the NEAR LANE
                    {  
                        this->m_speed = calculateVelocity(1);
                        this->m_state = States::car_on_the_first_lane;
                    }
                    else if(hasReached(this->m_rc_car_position, this->m_far_point, CAR_DIST_METER))        // If the car is close to the FAR LANE
                    {
                        this->m_speed = calculateVelocity(1);
                        this->m_state = States::car_on_the_second_lane;
                    }
                    break;

                
                case States::car_on_the_first_lane:
                    
                    // The pedestrian has reach the First possition
                    if (hasReached(this->m_ped_position, this->first_lane_point, 0.05) || this->m_stopped) 
                    {   
                        // Stop the pedestrian 
                        this->m_speed = calculateVelocity(0);

                        if(timeChecker(this->m_timestamp, this->m_model->GetWorld()->SimTime(), 5)) // if 5 seconds have passed
                        {   
                            this->m_speed = calculateVelocity(1); // start the pedestrian
                            this->m_state = States::go_to_the_right_side_of_the_road; // send it to 3rd state
                        }  
                    }
                    break;

            case States::car_on_the_second_lane:
                    
                    if (hasReached(this->m_ped_position, this->second_lane_point, 0.05) || this->m_stopped) // if the pedestrian has reached the second position
                    {   
                        this->m_speed = calculateVelocity(0); // stop the pedestrian

                        if(timeChecker(this->m_timestamp, this->m_model->GetWorld()->SimTime(), 5)) // if 5 seconds have passed
                        {
                            this->m_speed = calculateVelocity(1); // start the pedestrian
                            this->m_state = States::go_to_the_right_side_of_the_road; // send it to 3rd state
                        }
                    }
                    break;

            case States::go_to_the_right_side_of_the_road:

                    if (hasReached(this->m_ped_position, this->right_side_of_the_road_point, 0.05) || this->m_stopped) // if the pedestrian has reached the 3rd position
                    {   
                        this->m_speed = calculateVelocity(0); // stop the pedestrian
                                                
                        if(timeChecker(this->m_timestamp, this->m_model->GetWorld()->SimTime(), 5)) // if 5 sec have passed
                        {
                            this->m_speed = calculateVelocity(1, false); // start the pedestrian backwards
                            this->m_state = States::return_to_the_left_side_of_the_road; // send it to start state
                        }
                
                    }
                    break;

            case States::return_to_the_left_side_of_the_road:

                    if (hasReached(this->m_ped_position, this->wait_for_car_point, 0.05) || this->m_stopped) // if the pedestrian has reached the end position
                    {   
                        this->m_speed = calculateVelocity(0); // stop the pedestrian

                    
                        if(timeChecker(this->m_timestamp, this->m_model->GetWorld()->SimTime(), 10)) // if 10 sec have passed
                        {
                            this->m_state = States::wait_for_car; // send it to wait_for_car state
                        }
                    }
                    break;
            }

            // The pedestrian state what changed (from sitting to moving or viceversa)
            if (this->m_speed != this->m_last_speed)
            {
                this->m_timestamp = this->m_model->GetWorld()->SimTime();
            }

            this->m_model->SetLinearVel(this->m_speed);
            
            // Update the last speed to the current one
            this->m_last_speed = this->m_speed;
        };      
    }; //namespace pedestrian
    GZ_REGISTER_MODEL_PLUGIN(pedestrian::Pedestrian)
}; // namespace gazebo