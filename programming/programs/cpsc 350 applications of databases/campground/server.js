const express = require("express");

const app = express();

app.set("port", 8080);

app.get("/hello", (req, res) => {
	res.json("Hello World!");
});

app.listen(app.get("port"), () => {
	console.log(`Find the server at: http://localhost:${app.get("port")}/`);
	 // eslint-disable-line no-console
});