#include <ros/ros.h>

#include <sensor_msgs/JointState.h>

sensor_msgs::JointState init_msg()
{
    sensor_msgs::JointState msg;
    
    msg.name.push_back("coxa_joint_RB");
    msg.name.push_back("coxa_joint_RM");
    msg.name.push_back("coxa_joint_RF");
    msg.name.push_back("coxa_joint_LB");
    msg.name.push_back("coxa_joint_LM");
    msg.name.push_back("coxa_joint_LF");

    msg.name.push_back("femur_joint_RB");
    msg.name.push_back("femur_joint_RM");
    msg.name.push_back("femur_joint_RF");
    msg.name.push_back("femur_joint_LB");
    msg.name.push_back("femur_joint_LM");
    msg.name.push_back("femur_joint_LF");

    msg.name.push_back("tibia_joint_RB");
    msg.name.push_back("tibia_joint_RM");
    msg.name.push_back("tibia_joint_RF");
    msg.name.push_back("tibia_joint_LB");
    msg.name.push_back("tibia_joint_LM");
    msg.name.push_back("tibia_joint_LF");

    return msg;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "teste_joints");

    ros::NodeHandle nh;
    ros::Publisher pub;

    pub = nh.advertise<sensor_msgs::JointState>("joint_states", 1);

    sensor_msgs::JointState msg = init_msg();

    bool flag = true;

    ros::Rate loop_rate(0.2);
    while (ros::ok())
    {
        msg.position.clear();
        msg.header.stamp = ros::Time::now();

        if (flag == true)
        {  
            for (int i=0; i<18; i++)
                msg.position.push_back(1.57);
            flag = false;
        }
        else
        {
            for (int i=0; i<18; i++)    
                msg.position.push_back(0.0);
            flag = true;
        }

        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

}