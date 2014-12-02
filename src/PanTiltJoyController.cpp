#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <boost/thread.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>


/** /////////////////////////////////////////////////////////////////////////////////////////
 * 	"axes" vector de 8 elementos															/
	joy->axes[0] ---->>  joystick izq, eje X ---> derecha = -1, izquierda = 1				/
	joy->axes[1] ---->>  joystick izq, eje Y ---> arriba = 1, abajo = -1					/
	joy->axes[2] ---->>  LT ---> reposo = 1, apretado = -1, mitad = 0						/
	joy->axes[3] ---->>  joystick der, eje X ---> derecha = -1, izquierda = 1				/
	joy->axes[4] ---->>  joystick der, eje Y ---> arriba = 1, abajo = -1					/
	joy->axes[5] ---->>  RT ---> reposo = 1, apretado = -1, mitad = 0						/
	joy->axes[6] ---->>  cruceta central, eje X ---> derecha = -1, izquierda = 1			/
	joy->axes[7] ---->>  cruceta central, eje Y ---> arriba = 1, abajo = -1					/
																							/
 *	"buttons" vector de 11 elementos. Todos tienen valor 0 en reposo y valor 1 pulsados		/
	joy->buttons[0] ---->> A																/
	joy->buttons[1] ---->> B																/
	joy->buttons[2] ---->> X																/
	joy->buttons[3] ---->> Y																/
	joy->buttons[4] ---->> LB																/
	joy->buttons[5] ---->> RB																/
	joy->buttons[6] ---->> BACK																/
	joy->buttons[7] ---->> START															/
	joy->buttons[8] ---->> XBox																/
	joy->buttons[9] ---->> Joystick izquierdo												/
	joy->buttons[10] ---->> Joystick derecho												/
///////////////////////////////////////////////////////////////////////////////////////////*/


/*bool _l_joy = false;


void launch_Joy(){
	_l_joy = true;
	
	system("rosrun joy joy_node");
}*/


void joy_CallBack(const sensor_msgs::Joy::ConstPtr& joy){
	std::cout << "tenemos " << joy->axes.size() << " ejes " << std::endl;
	std::cout << "tenemos " << joy->buttons.size() << " botones " << std::endl;
	
	std::cout << joy->buttons[0] << std::endl; //A
	std::cout << joy->buttons[1] << std::endl; //B
	std::cout << joy->buttons[2] << std::endl; //X
	std::cout << joy->buttons[3] << std::endl; //Y
	std::cout << joy->buttons[4] << std::endl; //LB
	std::cout << joy->buttons[5] << std::endl; //RB
	std::cout << joy->buttons[6] << std::endl; //BACK
	std::cout << joy->buttons[7] << std::endl; //START
	std::cout << joy->buttons[8] << std::endl; //XBox
	std::cout << joy->buttons[9] << std::endl; //Joystick izquierdo
	std::cout << joy->buttons[10] << std::endl; //Joystick derecho
}


int main(int argc, char **argv){
	/*if(!_l_joy){
		boost::thread th1(launch_Joy);
		
		th1.join();
	}*/
	
	ros::init(argc, argv, "PanTiltJoyController");
	ros::NodeHandle n;
	
	ros::Subscriber sub_joy = n.subscribe("/joy", 10, joy_CallBack);
	
	ros::spin();
	
	return 0;
}
