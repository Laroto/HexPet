#include <ros/ros.h>
#include <vector>
#include <string>
#include <std_msgs/Float64.h>

#include "hexpet/joint_cmd_msg.h"

std::vector<std::string> topic_names;
std::vector<ros::Publisher> pub_vec;

void init_names()
{
    std::vector<std::string> joint_names;

    joint_names.push_back("tibia_joint_LF");
    joint_names.push_back("femur_joint_LF");
    joint_names.push_back("coxa_joint_LF");

    joint_names.push_back("tibia_joint_RF");
    joint_names.push_back("femur_joint_RF");
    joint_names.push_back("coxa_joint_RF");

    joint_names.push_back("tibia_joint_LM");
    joint_names.push_back("femur_joint_LM");
    joint_names.push_back("coxa_joint_LM");

    joint_names.push_back("tibia_joint_RM");
    joint_names.push_back("femur_joint_RM");
    joint_names.push_back("coxa_joint_RM");

    joint_names.push_back("tibia_joint_LB");
    joint_names.push_back("femur_joint_LB");
    joint_names.push_back("coxa_joint_LB");

    joint_names.push_back("tibia_joint_RB");
    joint_names.push_back("femur_joint_RB");
    joint_names.push_back("coxa_joint_RB");

    for (int i=0; i<18; i++)
    {
        topic_names.push_back("/hexpet/" + joint_names[i] + "_position_controller/command");
    }
}

// Use service for serial servos
void callback (const hexpet::joint_cmd_msgConstPtr &in_msg) // For RC servos with constant PWM 
{
    std::vector<std_msgs::Float64> out_msg;

    //  1  2  3     4  5  6
    //  7  8  9    10 11 12
    // 13 14 15    16 17 18

    for (int i=0; i<18; i++)
    {
        std_msgs::Float64 init_data;       
        out_msg.push_back(init_data);
    }

    out_msg[0].data  = in_msg->tibia_LF;
    out_msg[1].data  = in_msg->femur_LF;
    out_msg[2].data  = in_msg->coxa_LF;
    out_msg[3].data  = in_msg->tibia_RF;
    out_msg[4].data  = in_msg->femur_RF;
    out_msg[5].data  = in_msg->coxa_RF;
    out_msg[6].data  = in_msg->tibia_LM;
    out_msg[7].data  = in_msg->femur_LM;
    out_msg[8].data  = in_msg->coxa_LM;
    out_msg[9].data  = in_msg->tibia_RM;
    out_msg[10].data = in_msg->femur_RM;
    out_msg[11].data = in_msg->coxa_RM;
    out_msg[12].data = in_msg->tibia_LB;
    out_msg[13].data = in_msg->femur_LB;
    out_msg[14].data = in_msg->coxa_LB;
    out_msg[15].data = in_msg->tibia_RB;
    out_msg[16].data = in_msg->femur_RB;
    out_msg[17].data = in_msg->coxa_RB;

    //int j = 0;
    for (int j=0; j<18; j++)
        pub_vec[j].publish(out_msg[j]);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "interpreter");

    ros::NodeHandle nh;
    ros::Subscriber sub;

    init_names();

    sub = nh.subscribe("/hexpet/joint_commands", 1, callback);

    for (int i=0; i<18; i++)
        pub_vec.push_back ( nh.advertise<std_msgs::Float64>(topic_names[i],1) );

    while(ros::ok())
    {
        ros::spin();
    }
}
