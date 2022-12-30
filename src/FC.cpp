#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64MultiArray.h"
#include "sensor_msgs/Imu.h"
#include <sstream>
#include "PID.h"


int cycletimeSek = 0.0001;
sensor_msgs::Imu IMU;
PID yawpid(1,1,1,cycletimeSek);

void MotorMixerAlgorithm(){
  //int esc_1 = throttle - pid_output_pitch + pid_output_roll - pid_output_yaw; //Calculate the pulse for esc 1 (front-right - CCW)
  //int esc_2 = throttle + pid_output_pitch + pid_output_roll + pid_output_yaw; //Calculate the pulse for esc 2 (rear-right - CW)
  //int esc_3 = throttle + pid_output_pitch - pid_output_roll - pid_output_yaw; //Calculate the pulse for esc 3 (rear-left - CCW)
  //int esc_4 = throttle - pid_output_pitch - pid_output_roll + pid_output_yaw; //Calculate the pulse for esc 4 (front-left - CW)
}
void IMUCallback(const sensor_msgs::Imu::ConstPtr& data){
  IMU = data;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "FC_COMAND_TESTER");
  ros::NodeHandle n;
  ros::Publisher CMD_pub = n.advertise<std_msgs::Float64MultiArray>("/quad/joint_motor_controller/command", 1);
  ros::Rate loop_rate(0.001);
  ros::Subscriber sub = n.subscribe("/sensors/imu", 1000, IMUCallback);

  int count = 0;
  while (ros::ok())
  {
    std_msgs::Float64MultiArray msg;
    float a = 80;
    msg.data = {a,-a,a,-a};

    //ROS_INFO("published motorpower at");
    //CMD_pub.publish(msg);




    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
