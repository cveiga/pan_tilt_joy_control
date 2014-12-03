#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <boost/thread.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <pan_tilt_camera_teleop/PanTiltController.h>

#define umbral 0.3

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

PanTiltController ptc;

bool _dir, _bandera = false;
int _indice;
/*bool _l_joy = false;


void launch_Joy(){
	_l_joy = true;
	
	system("rosrun joy joy_node");
}*/



void envia_OrdenParada(){
	ptc.stopPanTilt();
	switch(_indice){
		case 0:
			if(!_dir)
				std::cout << "STOP DERECHA" << std::endl;
			else
				std::cout << "STOP IZQIERDA" << std::endl;
			break;
		case 1:
			if(!_dir)
				std::cout << "STOP BAJAR" << std::endl;
			else
				std::cout << "STOP SUBIR" << std::endl;
			break;
	}
}



void envia_Orden(){
	switch(_indice){
		case 0:
			if(!_dir){
				std::cout << "DERECHA" << std::endl;
				ptc.right();}
			else{
				std::cout << "IZQIERDA" << std::endl;
				ptc.left();}
			break;
		case 1:
			if(!_dir){
				std::cout << "BAJAR" << std::endl;
				ptc.tiltdown();}
			else{
				std::cout << "SUBIR" << std::endl;
				ptc.tiltup();}
			break;
	}
}



void joy_CallBack(const sensor_msgs::Joy::ConstPtr& joy){
		if(!_bandera){
			for(int i = 0; i < 2/*joy->axes.size()*/; i++){
				if(joy->axes[i] > umbral or joy->axes[i] < -umbral){
					_indice = i;
					if(joy->axes[i] < -umbral){
						_dir = false;
						_bandera = true;
					}
					if(joy->axes[i] > umbral){
						_dir = true;
						_bandera = true;
					}
				}
				
				if(_bandera){
					envia_Orden();
					break;
				}
			}
		}
		else{
			if(joy->axes[_indice] < 0.3 and joy->axes[_indice] > -0.3){
				envia_OrdenParada();
				_bandera = false;
			}
		}
		
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
