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
	database: "world"
};

const pool = new Pool(config);




// get requests /////////////////////////////////////////////////////////

// http://localhost:8080/hello
//just used to test it is running
app.get("/api/hello", (req, res) => {
	res.json("Hello Worldsearch!");
});



/*
localhost:8080/api/search?food=chicken 
You app will allow a user to type in a city name (*Albuquerque*), country name (*Canada*), country code or continent, 
*/

app.post("/api/worldsearch", async (req, res) => 
{
	console.log(req.body);

	const searchword = req.body.search;

	
	console.log(searchword);

	try 
	{
		const template2 = 'SELECT DISTINCT city.name AS cityname, city.district, country.name AS countryname FROM city JOIN country ON city.countrycode = country.code JOIN countrylanguage ON countrylanguage.countrycode = city.countrycode WHERE (city.name = $1 OR country.name = $1 OR city.countrycode = $1 OR country.continent = $1)';
		const result = await pool.query(template2, [ searchword ]);

		if (result.rowCount == 0) 
		{
			res.json({ status: "Match not found" });
		
		}
		else 
		{
			
			console.log("There's a match.");
			console.log(result.rows);
			
			res.json({ status: "Match found",
						cities: result.rows
			});
			
		}
		
	} 
	catch (err) 
	{
		console.log(err);
	}

});







// this goes at the end to listen on the port //////////////////////////////////////

app.listen(app.get("port"), () => {
	console.log(`Find the server at: http://localhost:${app.get("port")}/`);
	 // eslint-disable-line no-console
});



