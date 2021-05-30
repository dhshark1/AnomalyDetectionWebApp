# AnomalyDetectionWebApp

### Overview and features 

Our project consists of 3 parts: 

1. View 
2. Controller
3. Model + CPP server

The View is a simple HTML and CSS page that contains a form, that sends a POST request to the controller. The user inputs an algorithm name and two valid CSV files, and expects recieve a table of the anomalies detected by the algorithm. The Model is a backend function that communicates with a CPP server that detects the anomalies. 

### Structure of the project

In the repository, we ave a few important folders: 

1. AnomalyDetectionWebCPPSIDE - this is the c++ server
2. View - simple HTML and CSS files that display our project on the browser
3. Controller - a javascript file that return the html index file for a "/" get request and a JSON + HTML table of the anomalies for a "/detect" POST request. communicates with the Model
4. Model - a javascript file that communicates with the CPP service. sends the controller the anomalies. 

In addition, the executable file CPP_SERVICE which any user can run on a linux machine without recompiling the CPP server

### Manual

1. Install the latest version of NodeJS
2. Start a new Express project on your computer - https://expressjs.com/en/starter/installing.html for instructions
3. Download the following modules through your terminal of the project- express-fileupload, JSDOM: npm i express-fileupload, npm i jsdom
4. Download/clone the repository
5. Insert the View, Controller, and Model folders from this repository into the Express project 
6. Run the CPP server (in linux- run ./CPP_SERVICE or on a different OS you must create a CLION project and compile our CPP server folder)
7. Run Node-JS server via the controller folder (index.js)
8. Open localhost:8080 on your browser

### UML

https://github.com/dhshark1/AnomalyDetectionWebApp/blob/main/webappuml.pdf

### Video Explaining the Project

https://youtu.be/F0gvDKaHrh4
