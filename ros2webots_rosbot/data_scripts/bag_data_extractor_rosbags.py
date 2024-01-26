from rosbags.rosbag2 import Reader
from rosbags.serde import deserialize_cdr
import time

# create reader instance and open for reading
with Reader('/home/mjavadzallaghi/ros2_ws/ros2webots/baglog/rosbot_data_20240125_225927.bag') as reader:
    # topic and msgtype information is available on .connections list
    for connection in reader.connections:
        print(connection.topic, connection.msgtype)

    # iterate over messages
    for connection, timestamp, rawdata in reader.messages():
        # print(connection.topic, connection.msgtype)

        if connection.topic == '/webots/rosbot/imu':
            print(connection.topic, connection.msgtype)
            # print(timestamp)
            # print(rawdata) 
            msg_data = deserialize_cdr(rawdata, connection.msgtype)
            print(msg_data, '\n\n\n')
            # print(msg_data[0], '\n')
            # print(msg_data.)
        #     msg = deserialize_cdr(rawdata, connection.msgtype)
        #     print(msg.header.frame_id)

    # # messages() accepts connection filters
    # connections = [x for x in reader.connections if x.topic == '/webots/rosbot/imu']
    # for connection, timestamp, rawdata in reader.messages(connections=connections):
    #     msg = deserialize_cdr(rawdata, connection.msgtype)
    #     print(msg.header.frame_id)
