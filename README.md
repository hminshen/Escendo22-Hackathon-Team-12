##Table Occupancy System for Hawker Centers

This project showcases the proof of concept for a table occupancy system that has the following features:
- IR sensors to detect people occupying a table, with light indicators to show whether a particuar table is occupied
- A central display within the hawker center that shows the locations of zones within the hawker centre, with their corresponding number of vacant tables

To showcase the proof of concept within this 3 day hackathon, our team of 3 made use of the following:
- An Arduino Microcontroller connected to photoelectric sensors to detect people at the occupied table, with LEDs to display the occupancy status of the table
- Microcontroller sends the table occupancy data to the central computer via the wifi module
- Using the Flask API library and ReactJS as the frontend to display the occupancy status information on a webpage (simulating a central display)
