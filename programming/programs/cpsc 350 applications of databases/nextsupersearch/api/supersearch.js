const express = require("express");
const app = express();
app.set("port", 8080);

const bodyParser = require("body-parser");
app.use(bodyParser.json({ type: "application/json" }));
app.use(bodyParser.urlencoded({ extended: true }));

//const Bcrypt = require('bcrypt');
const argon2 = require("argon2");

const cors = require("cors");
app.use(cors());


// linking to postgres //////////////////////////////////////////////

const Pool = require("pg").Pool;
const config = {
	host: "localhost",
	user: "parky",
	password: "poparky",
	database: "supersearch"
};

const pool = new Pool(config);




// get requests /////////////////////////////////////////////////////////

// http://localhost:8080/hello
//just used to test it is running
app.get("/api/hello", (req, res) => {
	res.json("Supersearch: Hello World!");
});



/*
localhost:8080/api/searchmovies?searchword=movies 

You should implement a search feature that works similarly to the video. We should be able to search for:

1.	The name of a store (i.e., Starbucks)
2.	The type of a store (i.e., Mexican)
3.	The name of a movie (i.e., Wonder Woman)
4.	All the movies by typing movies.

*/

app.get("/api/searchmovies", async (req, res) => {

try {
	
	var response;
	var template;

	if (req.query.searchword == ""){

			console.log("no search entered");
			res.json({ movies: null });

	} else if (req.query.searchword == "movies") {

		if (req.query.searchzip == "all") {
			console.log("searching database for all movies");
		
			template = "SELECT movies.movie_name, theaters.theater_name, theaters.theater_address, theaters.theater_city, theaters.theater_zip FROM theaters JOIN now_playing ON theaters.theater_id = now_playing.theater_id JOIN movies ON movies.movie_id = now_playing.movie_id";

			response = await pool.query(template);
		
			console.log("search query:");
			console.log(template);

			console.log("search response:");
			console.log(response.rows);
			res.json({ movies: response.rows });
		
		} else {
			console.log("searching database for all movies");
		
			template = "SELECT movies.movie_name, theaters.theater_name, theaters.theater_address, theaters.theater_city, theaters.theater_zip FROM theaters JOIN now_playing ON theaters.theater_id = now_playing.theater_id JOIN movies ON movies.movie_id = now_playing.movie_id WHERE theaters.theater_zip = $1";

			response = await pool.query(template, [req.query.searchzip]);
		
			console.log("search query:");
			console.log(template);

			console.log("search response:");
			console.log(response.rows);
			res.json({ movies: response.rows });
		
		}
		
	} else {

		if (req.query.searchzip == "all") {
			console.log("searching database for:");
			console.log(req.query.searchword + " with no zip");

			template = "SELECT movies.movie_name, theaters.theater_name, theaters.theater_address, theaters.theater_city, theaters.theater_zip FROM theaters JOIN now_playing ON theaters.theater_id = now_playing.theater_id JOIN movies ON movies.movie_id = now_playing.movie_id WHERE movies.movie_name ILIKE $1 OR theaters.theater_name ILIKE $1";
			response = await pool.query(template, ["%" + req.query.searchword + "%"]);
		
			console.log("search query:");
			console.log(template);

			console.log("search response:");
			console.log(response.rows);
		
		} else {
			console.log("searching database for:");
			console.log(req.query.searchword + " with zip " + req.query.searchzip);

			template = "SELECT movies.movie_name, theaters.theater_name, theaters.theater_address, theaters.theater_city, theaters.theater_zip FROM theaters JOIN now_playing ON theaters.theater_id = now_playing.theater_id JOIN movies ON movies.movie_id = now_playing.movie_id WHERE (movies.movie_name ILIKE $1 OR theaters.theater_name ILIKE $1) AND theaters.theater_zip = $2";
			response = await pool.query(template, ["%" + req.query.searchword + "%", req.query.searchzip]);
		
			console.log("search query:");
			console.log(template);

			console.log("search response:");
			console.log(response.rows);
		
		}

		//if no searcword found or nothing entered
		if (response.rowCount == 0) {
			console.log("nothing found");
			res.json({ movies: null });

		//return list of movies
		} else {
			res.json({ movies: response.rows });
		}
		}	

	} catch (err) {
		console.error("Error running query " + err);
		res.json({ status: "error" });
	}

});



/*
localhost:8080/api/searchstores?searchword=stores 

You should implement a search feature that works similarly to the video. We should be able to search for:

1.	The name of a store (i.e., Starbucks)
2.	The type of a store (i.e., Mexican)
3.	The name of a movie (i.e., Wonder Woman)
4.	All the movies by typing movies.

*/



app.get("/api/searchstores", async (req, res) => {

try {
	
	var response;
	var template;

	if (req.query.searchword == ""){

			console.log("no search entered");
			res.json({ stores: null });

	} else if (req.query.searchword == "stores") {

		if (req.query.searchzip == "all") {
			console.log("searching database for all stores");
		
			template = "SELECT stores.store_name, string_agg(storetypes.storetype_name, ', ') AS storetype_name, stores.store_address, stores.store_city, stores.store_zip FROM storetypes JOIN now_eating ON storetypes.storetype_id = now_eating.storetype_id JOIN stores ON stores.store_id = now_eating.store_id GROUP BY stores.store_id";

			response = await pool.query(template);
		
			console.log("search query:");
			console.log(template);

			console.log("search response:");
			console.log(response.rows);
			res.json({ stores: response.rows });
		
		} else {
			console.log("searching database for all stores");
		
			template = "SELECT stores.store_name, string_agg(storetypes.storetype_name, ', ') AS storetype_name, stores.store_address, stores.store_city, stores.store_zip FROM storetypes JOIN now_eating ON storetypes.storetype_id = now_eating.storetype_id JOIN stores ON stores.store_id = now_eating.store_id WHERE stores.store_zip = $1 GROUP BY stores.store_id";

			response = await pool.query(template, [req.query.searchzip]);
		
			console.log("search query:");
			console.log(template);

			console.log("search response:");
			console.log(response.rows);
			res.json({ stores: response.rows });
		
		}
		
	} else {

		if (req.query.searchzip == "all") {
			console.log("searching database for:");
			console.log(req.query.searchword + " with no zip");

			template = "SELECT stores.store_name,string_agg(storetypes.storetype_name, ', ') AS storetype_name, stores.store_address, stores.store_city, stores.store_zip FROM storetypes JOIN now_eating ON storetypes.storetype_id = now_eating.storetype_id JOIN stores ON stores.store_id = now_eating.store_id WHERE stores.store_name ILIKE $1 OR storetypes.storetype_name ILIKE $1 GROUP BY stores.store_id";
			response = await pool.query(template, ["%" + req.query.searchword + "%"]);
		
			console.log("search query:");
			console.log(template);

			console.log("search response:");
			console.log(response.rows);
		
		} else {
			console.log("searching database for:");
			console.log(req.query.searchword + " with zip " + req.query.searchzip);

			template = "SELECT stores.store_name, string_agg(storetypes.storetype_name, ', ') AS storetype_name, stores.store_address, stores.store_city, stores.store_zip FROM storetypes JOIN now_eating ON storetypes.storetype_id = now_eating.storetype_id JOIN stores ON stores.store_id = now_eating.store_id WHERE (stores.store_name ILIKE $1 OR storetypes.storetype_name ILIKE $1) AND stores.store_zip = $2 GROUP BY stores.store_id";
			response = await pool.query(template, ["%" + req.query.searchword + "%", req.query.searchzip]);
		
			console.log("search query:");
			console.log(template);

			console.log("search response:");
			console.log(response.rows);
		
		}

		//if no searcword found or nothing entered
		if (response.rowCount == 0) {
			console.log("nothing found");
			res.json({ stores: null });

		//return list of movies
		} else {
			res.json({ stores: response.rows });
		}
		}	

	} catch (err) {
		console.error("Error running query " + err);
		res.json({ status: "error" });
	}

});







// -----------------

app.get("/api/searchstoresbackup", async (req, res) => {

try {
		
	if (req.query.searchword == ""){

			console.log("no search entered");
			res.json({ stores: null });

	} else if (req.query.searchword == "stores") {

		console.log("searching database for all stores");
		
		const template = "SELECT stores.store_name, storetypes.storetype_name, stores.store_address, stores.store_city, stores.store_zip FROM storetypes JOIN now_eating ON storetypes.storetype_id = now_eating.storetype_id JOIN stores ON stores.store_id = now_eating.store_id";

		const response = await pool.query(template);
		

		console.log("search query:");
		console.log(template);

		console.log("search response:");
		console.log(response.rows);
		res.json({ stores: response.rows });
		
	} else {

		console.log("searching database for:");
		console.log(req.query.searchword);

		const template = "SELECT stores.store_name, storetypes.storetype_name, stores.store_address, stores.store_city, stores.store_zip FROM storetypes JOIN now_eating ON storetypes.storetype_id = now_eating.storetype_id JOIN stores ON stores.store_id = now_eating.store_id WHERE stores.store_name ILIKE $1 OR storetypes.storetype_name ILIKE $1";
		const response = await pool.query(template, ["%" + req.query.searchword + "%"]);
		
		console.log("search query:");
		console.log(template);

		console.log("search response:");
		console.log(response.rows);
				
		//if no searcword found or nothing entered
		if (response.rowCount == 0) {
			console.log("nothing found");
			res.json({ stores: null });

		//return list of stores
		} else {
			res.json({ stores: response.rows });
		}
	}	

	} catch (err) {
		console.error("Error running query " + err);
		res.json({ status: "error" });
	}

});




async function execute_query(query, args){
	try{
		console.log("starting query")
		var response = await pool.query(query, args);
		console.log("finishing query")
	}
	catch(e){
		console.error(e);
	}
}


//create user when given the info. encrypt the password before storing
app.post("/api/create-user", async (req, res) => {

	try 
	{
		console.log(req.body);
	
		const username = req.body.username;
		const password = req.body.password;
		const name = req.body.name;
		const zip = req.body.zip;
		
		console.log("username: " + username);
		console.log("password: " + password);
		console.log("name: " + name);
		console.log("zip: " + zip);


		//if parameter is missing while trying to add
		if (username == null || password == null || name == null || zip == null) 
		{
			console.error("information missing")
			res.json({ status: "information missing"});			
		}

		//search for username and see if it exists already
		else 
		{
			
			console.log("searching for user");

			const template2 = "SELECT * FROM users WHERE (user_username = $1)";
			
			console.log("searching template created: " + template2);

			const response2 = await pool.query(template2, [ username ]);
			
			console.log(response2.rows);
			console.log("search result rows: " + response2.rowCount);

			// if username already exists, return status taken
			if (response2.rowCount != 0) 
			{
				console.log("username taken");
				res.json({ status: "username taken"});

			// else add the new user
			} 
			else 
			{
				
				let hash = await argon2.hash(password);

				execute_query("INSERT INTO users (user_name, user_username, user_password, user_zip) VALUES ($1, $2, $3, $4)", [name, username, hash, zip]);
				console.log("User added");

				res.json({ status: "user added",
					password: password,
					username: username,
					name: name,
					zip: zip
				});
				
				/* 
				Bcrypt.hash(password, 10, function(err, hash){
					console.log(password);
					console.log("test: " + hash);
					console.log(name);
					console.log(username);
					console.log(zip);
					
					execute_query("INSERT INTO users (user_name, user_username, user_password, user_zip) VALUES ($1, $2, $3, $4)", [name, username, hash, zip]);
					console.log("User added");

					res.json({ status: "user added",
						password: password,
						username: username,
						name: name,
						zip: zip
					 });
				
				})
				*/




				/* this was for unhashed password
				console.log("adding user");						
				const template3 = "INSERT INTO users (user_name, user_username, user_password, user_zip) VALUES ($1, $2, $3, $4)";
				const response3 = await pool.query(template3, [
					name, username, password, zip
				]);
				console.log("User added");
				res.json({ status: "user added" });
				
				*/

			}
		}
	} 

	catch (err) {
		console.error(err);
		res.json({ status: "error adding user" });
	}

});






//given username and password, return name and zip if found

app.post("/api/check-login", async (req, res) => 
{
	const username = req.body.username;
	const password = req.body.password;
	
	console.log(req.body);
	console.log(username);
	console.log(password);

	try 
	{
		const template2 = "SELECT * FROM users WHERE user_username = $1";
		const result = await pool.query(template2, [ username ]);

		//console.log("found user: ");
		//console.log(result.rows);
		//console.log(result.rowCount);
		

		if (result.rowCount == 1) 
		{
			console.log("starting argon2 compare");
			//console.log(password);
			//console.log(result.rows[0].user_password);

			if (await argon2.verify(result.rows[0].user_password, password)) {
				console.log("Passwords match.");
				res.json({ status: "Passwords match",
						password: password,
						username: username,
						name: result.rows[0].user_name,
						zip: result.rows[0].user_zip
					 });
			} else {
				console.log("Password Incorrect.");
				res.json({ status: "Password Incorrect" });
			}


			/*
			Bcrypt.compare(password, result.rows[0].user_password, function(err, res2)
			{
				console.log("inside bcrypt compare");
				
				if (res2) {
					//if we get a response then passwords match
					console.log("Passwords match.");
					res.json({ status: "Passwords match",
						password: password,
						username: username,
						name: result.rows[0].user_name,
						zip: result.rows[0].user_zip
					 });
				}
				else 
				{
					console.log("Password Incorrect.");
					res.json({ status: "Password Incorrect" });
				}
				return;
			})
			*/

		}
		else 
		{
			res.json({ status: "Username not found" });
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



