#pragma once
#include <iostream>
#include <ostream>


namespace gazebo
{
    namespace pedestrian
    {  

    	class GeometricPoint
        {
            public: double x = 0;
            public: double y = 0;

            public: GeometricPoint();
            public: GeometricPoint(const double &, const double &);
			public: friend ::std::ostream& operator<<(::std::ostream&, GeometricPoint);

            public: void setPoint(GeometricPoint);
            public: void setPoint(const double &, const double &);
            public: double operator[](unsigned int index);
            public: void print(); 


        }; 
  };
};