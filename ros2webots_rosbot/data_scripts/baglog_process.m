bag = rosbag("\\wsl.localhost\Ubuntu\home\mjavadzallaghi\ros2_ws\ros2webots\baglog\rosbot_data_20240125_225927.bag")
bag.AvailableTopics;
bag.MessageList;
bagselect1 = select(bag,"Topic","/webots/rosbot/imu");
msgs = readMessages(bagselect1,"DataFormat","struct");
msgs{1}.AngularVelocity.X;