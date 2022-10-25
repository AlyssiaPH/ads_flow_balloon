console.log("cc");

const { SerialPort } = require('serialport')
//Load HTTP module
const http = require("http");
const path = require("path");
const hostname = "127.0.0.1";
const port = 3000;
const express = require('express');
const gtts = require("gtts");
const app = express();

app.get('/', function(req, res) {
    res.sendFile(path.join(__dirname, '/index.html'));



});



    app.get('/hear', function (req, res) {
        const gttsTe = new gtts('Venez à la Coding Factory !', 'fr');
        gttsTe.stream().pipe(res);
    });

        console.log('Open url to hear Hallelujah http://localhost:3000/hear');


app.listen(port);

console.log('Server started at http://localhost:' + port);

//listen for request on port 3000, and as a callback function have the port listened on logged

/*const serialport = new SerialPort({
    path: '/dev/tty.BLTH',
    baudRate: 57600,
})
 */




