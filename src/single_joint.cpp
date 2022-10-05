#include <ros/ros.h>

#include <std_msgs/Float64.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "teste_joints");

    ros::NodeHandle nh;
    ros::Publisher pub;

    pub = nh.advertise<std_msgs::Float64>("/hexpet/femur_joint_LM_position_controller/command", 1);

    std_msgs::Float64 msg;

    bool flag = true;

    ros::Rate loop_rate(0.33);
    while (ros::ok())
    {
        if (flag == true)
        {  
            msg.data = 0.0;
            flag = false;
        }
        else
        {       
            msg.data = -1.57;
            flag = true;
        }

        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

}