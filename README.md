##Table Occupancy System for Hawker Centers

This project showcases the proof of concept for a table occupancy system that has the following features:
- IR sensors to detect people occupying a table, with light indicators to show whether a particular table is occupied
- A central display within the hawker center that shows the locations of zones within the hawker centre, with their corresponding number of vacant tables

To showcase the proof of concept within this 3 day hackathon, our team of 3 made use of the following:
- An Arduino Microcontroller connected to photoelectric sensors to detect people at the occupied table, with LEDs to display the occupancy status of the table
- Microcontroller sends the table occupancy data to the central computer via the wifi module
- Using the Flask API library and ReactJS as the frontend to display the occupancy status information on a webpage (simulating a central display)

Note:
- LEDlightingdraft.ino was used for the arduino to indicate the occupancy status of the table using LEDs and sensors, and sending the data to the central computer using the wifi module
- Files under the src folder were used to display the webpage (central display), and the node Modules were not added due to size limit (in case you want to do an npm start with the files directly)
