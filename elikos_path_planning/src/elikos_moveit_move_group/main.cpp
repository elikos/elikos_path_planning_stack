#include <memory>
#include "MessageHandler_moveit.h"

int main(int argc, char* argv[])
{
    // ROS Init
    ros::init( argc, argv, "moveit_move_group" );

    ros::NodeHandle nh;
    ros::Publisher pub;
    ros::Publisher debug_pub;
    pub = nh.advertise<elikos_msgs::TrajectoryCmd>("elikos_trajectory", 1);
    debug_pub = nh.advertise<geometry_msgs::Transform>("elikos_trajectory_debug", 1);

    //Asynchronous spinner to compute the motion plan
    ros::AsyncSpinner spinner(1);
    spinner.start();

    //Messagehandler to receive the goal pose.
    MessageHandler_moveit messageHandler;

    Moveit_move_group move_group_;

    ros::Rate r(10);
    while(ros::ok())
    {
        if(messageHandler.hasNewMessage())
        {
            elikos_msgs::DMCmd dm_cmd = messageHandler.getDMCmd();
            elikos_msgs::TrajectoryCmd traj_cmd;
            traj_cmd.cmdCode = dm_cmd.cmdCode;
            traj_cmd.destination = dm_cmd.pose.pose;

            if (dm_cmd.cmdCode == elikos_msgs::DMCmd::MOVE_TO_POINT)
            {
                traj_cmd.trajectory = move_group_.move(dm_cmd.pose);
            }

            pub.publish(traj_cmd);
            if (traj_cmd.trajectory.points.size() > 0) {
                if (traj_cmd.trajectory.points[0].transforms.size() > 0) {
                    debug_pub.publish(traj_cmd.trajectory.points[0].transforms[0]);
                }
            }
        }
        ros::spinOnce();
        r.sleep();
    }

}
