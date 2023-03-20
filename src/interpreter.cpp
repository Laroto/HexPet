#include <ros/ros.h>
#include <vector>
#include <string>
#include <std_msgs/Float64.h>

#include "HexPet/joint_cmd_msg"

std::vector<std::string> topic_names;
std::vector<ros::Publisher> pub_vec;

void init_names()
{
    std::vector<std::string> joint_names;

    joint_names.push_back("coxa_joint_RB");
    joint_names.push_back("coxa_joint_RM");
    joint_names.push_back("coxa_joint_RF");
    joint_names.push_back("coxa_joint_LB");
    joint_names.push_back("coxa_joint_LM");
    joint_names.push_back("coxa_joint_LF");

    joint_names.push_back("femur_joint_RB");
    joint_names.push_back("femur_joint_RM");
    joint_names.push_back("femur_joint_RF");
    joint_names.push_back("femur_joint_LB");
    joint_names.push_back("femur_joint_LM");
    joint_names.push_back("femur_joint_LF");

    joint_names.push_back("tibia_joint_RB");
    joint_names.push_back("tibia_joint_RM");
    joint_names.push_back("tibia_joint_RF");
    joint_names.push_back("tibia_joint_LB");
    joint_names.push_back("tibia_joint_LM");
    joint_names.push_back("tibia_joint_LF");

    for (int i=0; i<18; i++)
    {
        topic_names[i] = "/hexpet/" + joint_names[i] + "_position_controller/command";
    }
}

// Use service for serial servos
void callback (HexPet::joint_cmd_msgConstPtr &in_msg) // For RC servos with constant PWM 
{
    std::vector<std_msgs::Float64> out_msg;

    //  1  2  3     4  5  6
    //  7  8  9    10 11 12
    // 13 14 15    16 17 18

    out_msg[1]  = in_msg->tibia_LF
    out_msg[2]  = in_msg->femur_LF
    out_msg[3]  = in_msg->coxa_LF
    out_msg[4]  = in_msg->tibia_RF
    out_msg[5]  = in_msg->femur_RF
    out_msg[6]  = in_msg->coxa_RF
    out_msg[7]  = in_msg->tibia_LM
    out_msg[8]  = in_msg->femur_LM
    out_msg[9]  = in_msg->coxa_LM
    out_msg[10] = in_msg->tibia_RM
    out_msg[11] = in_msg->femur_RM
    out_msg[12] = in_msg->coxa_RM
    out_msg[13] = in_msg->tibia_LB
    out_msg[14] = in_msg->femur_LB
    out_msg[15] = in_msg->coxa_LB
    out_msg[16] = in_msg->tibia_RB
    out_msg[17] = in_msg->femur_RB
    out_msg[18] = in_msg->coxa_RB

    for (int i=0; i<18;i++)
        pub_vec[i].publish(out_msg[i]);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "teste_joints");

    ros::NodeHandle nh;
    ros::Subscriber sub;

    init_names();

    sub = nh.subscribe("/hexpet/joint_commands", 1, callback);

    for (int i=0; i<18; i++)
        pub_vec[i] = nh.advertise<std_msgs::Float64>(topic_names[i],1);

    while(ros::ok())
    {
        ros::spin();
    }
}
