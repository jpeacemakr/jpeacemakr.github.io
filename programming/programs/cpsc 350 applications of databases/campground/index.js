const express = require("express");

const app = express();

app.set("port", 8080);

app.get("/hello", (req, res) => {
	res.json("Hello World!");
});


app.get("/vacancybasic", (req, res) => {
	console.log(req.query);
});


app.get("/vacancy", (req, res) => {
	console.log(req.query.q);
	const campground = req.query.q;
	if (campground == "Saddle") {
		res.json({ campground: campground, sites: 5 });
	} else {
		res.json({ campground: campground, sites: 0 });
	}
});


app.listen(app.get("port"), () => {
	console.log(`Find the server at: http://localhost:${app.get("port")}/`);
	 // eslint-disable-line no-console
});