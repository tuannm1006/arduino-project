var express = require("express");
var app = express();
var server = require("http").createServer(app);
var WebSocket = require("ws");
var ws = new WebSocket.Server({
  server,
});
var clients = [];

app.get("/", (req, res, ext) => {
  res.sendFile(__dirname + "/public/index.html");
});

app.use(express.static("public"));

function broadcast(socket, data) {
  for (var i = 0; i < clients.length; i++) {
    if (clients[i] != socket) {
      clients[i].send(data);
    }
  }
}
ws.on("connection", function (socket, req) {
  console.log("a client connected");
  clients.push(socket);
  socket.on("message", function (message) {
    console.log("received: %s", message);
    broadcast(socket, message);
  });
  socket.on("close", function () {
    var index = clients.indexOf(socket);
    clients.splice(index, 1);
    console.log("disconnected");
  });
});
server.listen(3000);
console.log("Server listening on port 3000");
