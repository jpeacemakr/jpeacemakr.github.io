const express = require("express");
const app = express();
app.set("port", 8080);

const bodyParser = require("body-parser");
app.use(bodyParser.json({ type: "application/json" }));
app.use(bodyParser.urlencoded({ extended: true }));


const cors = require("cors");
app.use(cors());


// linking to postgres //////////////////////////////////////////////

const Pool = require("pg").Pool;
const config = {
	host: "localhost",
	user: "parky",
	password: "poparky",
	database: "food_nutrition"
};

const pool = new Pool(config);




// get requests /////////////////////////////////////////////////////////

// http://localhost:8080/hello
//just used to test it is running
app.get("/api/hello", (req, res) => {
	res.json("Hello World!");
});



/*
localhost:8080/api/search?food=chicken 
*/


app.get("/api/search", async (req, res) => {

try {
		
	if (req.query.food == ""){

			console.log("food not found");
			res.json();


	} else {

		console.log("searching database for:");
		console.log(req.query.food);

		const template = "SELECT * FROM entries WHERE description ILIKE $1 LIMIT 20";
		const response = await pool.query(template, ["%" + req.query.food + "%"]);
		
		console.log("search query:");
		console.log(template);

		console.log("search response:");
		console.log(response.rows);
				
		//if no food found or nothing entered
		if (response.rowCount == 0) {
			console.log("food not found");
			res.json();

		//return list of food names
		} else {
			res.json(response.rows);
		}

	}	


	} catch (err) {
		console.error("Error running query " + err);
		res.json({ status: "error" });
	}

});







// this goes at the end to listen on the port //////////////////////////////////////

app.listen(app.get("port"), () => {
	console.log(`Find the server at: http://localhost:${app.get("port")}/`);
	 // eslint-disable-line no-console
});



