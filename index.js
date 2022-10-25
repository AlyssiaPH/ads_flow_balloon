console.log("cc");

const { SerialPort } = require('serialport')
//Load HTTP module
const http = require("http");
const path = require("path");
const hostname = "127.0.0.1";
const port = 3000;
const express = require('express');
const app = express();



//Create HTTP server and listen on port 3000 for requests
const server = http.createServer((req, res) => {
    //Set the response HTTP header with HTTP status and Content type
    res.statusCode = 200;
    res.setHeader("Content-Type", "text/plain");
    res.end("Hello World\n");
    server.listen(port, hostname, () => {
    console.log(`Server running at http://${hostname}:${port}/`);
});

});

app.get('/', function(req, res) {
    res.sendFile(path.join(__dirname, '/index.html'));
});

app.listen(port);

console.log('Server started at http://localhost:' + port);

//listen for request on port 3000, and as a callback function have the port listened on logged


/*const serialport = new SerialPort({
    path: '/dev/tty.BLTH',
    baudRate: 57600,
})
 */