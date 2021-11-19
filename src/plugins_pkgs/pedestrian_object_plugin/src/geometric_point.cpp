#include "geometric_point.h"

namespace gazebo
{
    namespace pedestrian
    {   
        ::std::ostream& operator<<(::std::ostream& o, GeometricPoint gp)
        {
            o << "(" << gp.x << ", " << gp.y << ")";
            return o; 
        }

        GeometricPoint::GeometricPoint(){}

        GeometricPoint::GeometricPoint(const double &x, const double &y)
        {
            this->setPoint(x, y);
        } 

        void GeometricPoint::setPoint(GeometricPoint geometric_point)
        {
            this->x = geometric_point.x;
            this->y = geometric_point.y;
        }

        void GeometricPoint::setPoint(const double &x, const double &y)
        {
            this->x = x;
            this->y = y;
        }

        double GeometricPoint::operator[](unsigned int index)
        {
            if(index == 0)
            {
                return this->x;
            }
            else if (index == 1)
            {
                return this->y;
            }
            else
            {
                throw std::out_of_range("for operator[] in geometric point only allowed indexes : {0, 1}");
            }
        }
        
        void GeometricPoint::print()
        {
            std::cerr << this->x << " " << this->y;
        }
    }; // namespace pedestrian
}; // namespace gazebo