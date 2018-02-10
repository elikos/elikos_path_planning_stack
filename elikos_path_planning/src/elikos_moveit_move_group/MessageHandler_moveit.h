#ifndef MESSAGE_HANDLER_moveit
#define MESSAGE_HANDLER_moveit


#include "moveit_move_group.h"

class MessageHandler_moveit
{
public:
    MessageHandler_moveit();
    ~MessageHandler_moveit();
    void dispatchMessageTarget(const elikos_msgs::DMCmd::ConstPtr &input);
    elikos_msgs::DMCmd getDMCmd();
    bool hasNewMessage();
private:
    ros::NodeHandle nh_;
    ros::Subscriber sub_;
    elikos_msgs::DMCmd input_;
    bool hasNewMessage_;
};

#endif /// MESSAGE_HANDLER_TTF
