#include <ros/ros.h>

#include "hexpet/joint_cmd_msg.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "teste_all");

    ros::NodeHandle nh;
    ros::Publisher pub;

    pub = nh.advertise<hexpet::joint_cmd_msg>("/hexpet/joint_commands", 1);

    hexpet::joint_cmd_msg msg;
    
    msg.tibia_LF = 0;
    msg.femur_LF = 0;
    msg.coxa_LF = 0;

    msg.tibia_RF = 0;
    msg.femur_RF = 0;
    msg.coxa_RF = 0;

    msg.tibia_LM = 0;
    msg.femur_LM = 0;
    msg.coxa_LM = 0;

    msg.tibia_RM = 0;
    msg.femur_RM = 0;
    msg.coxa_RM = 0;

    msg.tibia_LB = 0;
    msg.femur_LB = 0;
    msg.coxa_LB = 0;

    msg.tibia_RB = 0;
    msg.femur_RB = 0;
    msg.coxa_RB = 0;

    std::cout << "input coxa_LF value " << std::endl; 
    while(ros::ok)
    {
        pub.publish(msg);
        double val;
        std::cin >> val;
        msg.femur_LF = (double) val;
    }
}