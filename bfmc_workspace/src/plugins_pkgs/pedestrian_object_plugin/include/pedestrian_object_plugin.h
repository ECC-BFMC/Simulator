#pragma once

// The Rc car model name in the Gazebo simulator
#define RC_CAR_NAME "rcCar"

// The maximum ditance from the selected zones which will trigger the pedestrian

#define L(var) #var 
#define LOG(var) ::std::cerr << L(var) << "= " << var << '\n'
#define CP(var) ::std::cerr << "CHEKCPOINT " << var << "\n";

#include "geometric_point.h"

namespace Cardinal
{
    // All values are in radians
    const double south  = 4.712388;
    const double north  = 1.570796;
    const double east   = 3.141592;
    const double west   = 0;
};

namespace Dist
{
    // meters
    const double thin_mark          = 0.020;
    const double road_width         = 0.720;
    const double lane_width         = 0.350;
    const double half_lane          = lane_width / 2;
    const double middle_to_middle   = 0.370;
};



namespace gazebo
{
    namespace pedestrian
    {
        enum class States
        {
            wait_for_car,
            car_on_the_first_lane,
            car_on_the_second_lane,
            go_to_the_right_side_of_the_road,
            return_to_the_left_side_of_the_road,
        };
       

        class Pedestrian: public ModelPlugin
    	{
        private: 
            physics::ModelPtr                   m_model;
            physics::ModelPtr                   m_rc_car;
            std::string                         m_rc_car_name{RC_CAR_NAME};

            sdf::ElementPtr                     m_sdf;

            event::ConnectionPtr                m_updateConnection;

            States                              m_state = States::wait_for_car;

            bool                                m_stopped = true;

            // Pedestrian
            ignition::math::Vector3d            m_ped_velocity;
            GeometricPoint                      m_ped_position;
            double                              m_ped_wz;
            
            // Car
            GeometricPoint                      m_rc_car_position;
            double                              m_rc_car_wz;
            
            // Where the car should be in order to start the pedestrian movement
            GeometricPoint                      m_near_point;
            GeometricPoint                      m_far_point;

            // Where the pedestrian will move
            GeometricPoint                      wait_for_car_point;
            GeometricPoint                      first_lane_point;
            GeometricPoint                      second_lane_point;
            GeometricPoint                      right_side_of_the_road_point;

            gazebo::common::Time                m_timestamp;          
            ignition::math::Vector3d            m_speed{0,0,0};
            ignition::math::Vector3d            m_last_speed{0,0,0};


            boost::mutex m_mutex;

        // Default constructor
        public: Pedestrian();

        // This method returns the absolut position of the point related to the pedestrian orientation
        private: GeometricPoint rotate(GeometricPoint, GeometricPoint, double);     
        
        // Stores in [m_ped_position] and [m_ped_rotation] the current pedestrian position
        private: void updatePedestrianPosition();
       
        // Stores in [m_rc_car_position] and [m_rc_car_rotation] the current pedestrian position
        private: void updateRcCarPosition();

        private: ignition::math::Vector3d calculateVelocity(float velocity, bool isForward);

        // This method returns True if the time is in interval and false if it's not
        private: bool timeChecker(const gazebo::common::Time &start_time,
                                  const gazebo::common::Time &current_time, const float duration);

        // It receives 2 points and check if they are closer than the specified distance (aka the third parameter)
        private: bool hasReached(const GeometricPoint&, const GeometricPoint&, const double&);

        /* Based on the pedestrian position, it sets two points (the centers of the two zones that
        *  will trigger the pedestrian move)
        */
        private: void generatePoints();

        public: void Load(physics::ModelPtr, sdf::ElementPtr);
        public: void OnUpdate();
        };
    };    
};