// By James Peacemaker
// Workshop registration program backend

const express = require("express");
const app = express();
app.set("port", 8080);

const bodyParser = require("body-parser");
app.use(bodyParser.json({ type: "application/json" }));
app.use(bodyParser.urlencoded({ extended: true }));





// linking to postgres //////////////////////////////////////////////

const Pool = require("pg").Pool;
const config = {
	host: "localhost",
	user: "parky",
	password: "poparky",
	database: "workshop2"
};

const pool = new Pool(config);




// get requests /////////////////////////////////////////////////////////

// http://localhost:8080/hello
//just used to test it is running
app.get("/hello", (req, res) => {
	res.json("Hello World!");
});






/* FINISHED 
get: {{URL}}/list-users 
Request
parameters:
key	Sample value
type	full
Response
If type = full return all information from the database:
{
    "users": [
        {
            "username": "ann",
            "firstname": "Ann",
            "lastname": "Mulkern",
            "email": "mulkern@gmail.com"
        },
    ]
}

If type = summary just return firstname and lastname: 
{
    "users": [
        {
            "firstname": "Ann",
            "lastname": "Mulkern"
        },
    ]
}
*/

app.get("/list-users", async (req, res) => {

console.log("----------");
	
try {

		//if type is full
		if (req.query.type == "full") {
			
			const template1 = "SELECT DISTINCT user_name AS username, first_name AS firstname, last_name AS lastname, email FROM users";
			const response1 = await pool.query(template1);
		
			console.log("Listing full desciption of all users.");
			res.json({ users : response1.rows});
		}

		//if type is summary
		else if (req.query.type == "summary") {
			
			const template2 = "SELECT first_name AS firstname, last_name AS lastname FROM users";
			const response2 = await pool.query(template2);
		
			console.log("Listing summary of users.");
			res.json({ users : response2.rows});
		}
		//if workshop name found, return list of attendee names
		
		else {
			console.error("display type not found");
			res.json({ error: "display type not found"});
		}
	} 
	catch (err) {
		console.error("Error running query " + err);
		res.json({ status: "error" });
	}

}

);






/* FINISHED
get: {{URL}}/list-workshops 
Request
No parameters or variables
Response
{
    "workshops": [
        {
            "title": "React Fundamentals",
            "date": "2018-03-16",
            "location": "Boston"
        },
        {
            "title": "Tensorflow",
            "date": "2018-05-06",
            "location": "Martha's Vineyard"
        }]}
*/

app.get("/list-workshops", async (req, res) => {

console.log("----------");
	
try {
		//used for formatting the date
			
		const template1 = "SELECT DISTINCT workshop_name AS title, workshop_date AS date, workshop_location AS location FROM workshops";
		const response1 = await pool.query(template1);
		
		//format the dates in the rows
		var dateFormat = require('dateformat');
		for (const workshop_element of response1.rows){
	      //console.log(workshop_element.date); //before formatting
	      workshop_element.date = dateFormat(workshop_element.date, "yyyy-mm-dd");
		  //console.log(workshop_element.date); //after formatting		
		}

		console.log("Listing desciption of all workshops.");
		res.json({ workshops : response1.rows});
		
	} 
	catch (err) {
		console.error("Error running query " + err);
		res.json({ status: "error" });
	}

}

);






/* FINISHED
get: {{URL}}/attendees 

Request
parameters:

key	Sample value
title	Tensorflow
date	2018-05-06
location	Albuquerque

Response
If workshop not already in database:
{ "error": "workshop does not exist"}

else
{
    "attendees": [
        {
            "firstname": "Maggie",
            "lastname": "Phillips"
        },
        {
            "firstname": "Ann",
            "lastname": "Mulkern"
        }
    ]
}

Notes: Returns list of workshop attendees
*/

app.get("/attendees", async (req, res) => {

console.log("----------");
	
try {

		const search_title = req.query.title;
		const search_date = req.query.date;
		const search_location = req.query.location;

		const template1 = "SELECT * FROM workshops WHERE workshop_name = $1 AND workshop_date = $2 AND workshop_location = $3";
		const response1 = await pool.query(template1, [
				search_title,
				search_date,
				search_location
			]);


		// if workshop does not exist
		if (response1.rows[0] == null) {
			console.error("workshop does not exist")
			res.json({ error : "workshop does not exist"});			
		}
		else {
			console.log("Listing full desciption of all users.");
			
			const template2 = "SELECT users.first_name AS firstname, users.last_name AS lastname FROM workshops JOIN attends ON workshops.workshop_id = attends.workshop_id JOIN users ON users.user_name = attends.user_name WHERE workshop_name = $1 AND workshop_date = $2 AND workshop_location = $3";
			const response2 = await pool.query(template2, [
				search_title,
				search_date,
				search_location
			]);

			res.json({ attendees : response2.rows});
		
		}		
	} 
	catch (err) {
		console.error("Error running query " + err);
		res.json({ status: "error" });
	}

}

);






// post requests //////////////////////////////////////////////



/* FINISHED 
Post: {{URL}}/create-user  

Request
X-www-form-urlencoded body variables:

key	Sample value
firstname	Maggie
lastname	Phillips
username	mphillips
email	mphillips@uwm.edu

Response
If username not already in database:

{ "status": "user added"}

else
{ "status": "username taken"}

Notes:
This adds an entry into the database for that user. 
*/



app.post("/create-user", async (req, res) => {

	console.log("----------");

	try {
		
		console.log(req.body);
	
		const first_name_to_add = req.body.firstname;
		const last_name_to_add = req.body.lastname;
		const user_name_to_add = req.body.username;
		const email_to_add = req.body.email;

		//if parameter is missing while trying to add
		if (user_name_to_add == null) {
			console.error("username missing")
			res.json({ error : "username missing"});			
		}

		//search for username and see if it exists already
		else {
			const template1 = "SELECT * FROM users WHERE (user_name = $1)";
			const response1 = await pool.query(template1, [
				user_name_to_add
			]);

			// if username already exists, return status taken
			if (response1.rowCount != 0) {
				console.log("username taken");
				res.json({ status : "username taken"});

			// else add the new user
			} else {
				const template2 = "INSERT INTO users (user_name, first_name, last_name, email) VALUES ($1, $2, $3, $4)";
				const response2 = await pool.query(template2, [
					user_name_to_add,
					first_name_to_add,
					last_name_to_add,
					email_to_add
				]);
			console.log("User added");
			res.json({ status : "user added" });
			}
		}
	} 

	catch (err) {
		console.error(err);
		res.json({ error : "error adding user" });
	}

});









/* FINISHED
Delete: {{URL}}/delete-user 
Request

X-www-form-urlencoded body variables:

key	Sample value
username	mphillips

Response

{ "status": "deleted"}

Notes:
This deletes an entry from the database. 
It needs to remove the entries from the attends table too.
*/


app.delete("/delete-user", async (req, res) => {

	console.log("----------");

	try {
		console.log(req.body);
	
		const user_name_to_delete = req.body.username;


		//if parameter is missing while trying to add
		if (user_name_to_delete == null) {
			console.error("username missing")
			res.json({ error : "username missing"});			
		}

		else {
			
			// delete user from users table	
			const template1 = "DELETE FROM users WHERE user_name = $1";
			const response1 = await pool.query(template1, [
				user_name_to_delete
			]);

			//delete user from attends table
			const template2 = "DELETE FROM attends WHERE user_name = $1";
			const response2 = await pool.query(template2, [
					user_name_to_delete
				]);
			
			console.log("User deleted");
			res.json({ status : "deleted" });
			}
		}
	 

	catch (err) {
		console.error(err);
		res.json({ error : "error deleting user" });
	}

});















/* FINISHED
Post: {{URL}}/add-workshop
Request
X-www-form-urlencoded body variables:

key	Sample value
title	Tensorflow
date	2018-05-06
location	Albuquerque
maxseats	40
instructor	Fiona Helbron

Response
If workshop not already in database:
{ "status": "workshop added"}

else
{ "status": "workshop already in database"}

Notes:
This adds the workshop into the database. A workshop title is not unique. What is unique is a title, date, location tuple
*/


app.post("/add-workshop", async (req, res) => {
	console.log("----------");

	
	try {
		console.log(req.body);
	
		const title_to_add = req.body.title;
		const date_to_add = req.body.date;
		const location_to_add = req.body.location;
		const maxseats_to_add = req.body.maxseats;
		const instructor_to_add = req.body.instructor;

		//if necessary parameter is missing, return an error
		if (title_to_add == null || date_to_add == null || location_to_add == null) {
			console.error("required information missing")
			res.json({ error : "required information missing"});			
		}

		//search for workshop and see if it exists already
		else {
			const template1 = "SELECT * FROM workshops WHERE workshop_name = $1 AND workshop_date = $2 AND workshop_location = $3";
			const response1 = await pool.query(template1, [
				title_to_add,
				date_to_add,
				location_to_add
			]);

			// if username already exists, return status taken
			if (response1.rowCount != 0) {
				console.log("workshop already in database");
				res.json({ status : "workshop already in database"});

			// else add the new user
			} else {
				const template2 = "INSERT INTO workshops (workshop_name, workshop_date, workshop_location, workshop_max_seats, workshop_instructor) VALUES ($1, $2, $3, $4, $5)";
				const response2 = await pool.query(template2, [
					title_to_add,
					date_to_add,
					location_to_add,
					maxseats_to_add,
					instructor_to_add
				]);
			console.log("workshop added");
			res.json({ status : "workshop added" });
			}
		}
	} 

	catch (err) {
		console.error(err);
		res.json({ error : "error adding workshop" });
	}

});





/* FINISHED
Post: {{URL}}/enroll (post request):
Request
X-www-form-urlencoded body variables:

key	Sample value
title	Tensorflow
date	2018-05-06
location	Albuquerque
username	maggie

Response
If username not already in database:
{ "status": "user not in database"}

Else if workshop not already in database:
{ "status": "workshop does not exist"}

Else if user already enrolled in workshop:
{ "status": "user already enrolled"}

Else if workshop already filled (number of people registered equals maxseats):
{ "status": "no seats available"}

Else
{ "status": "user added"}

Notes:
Enrolls a user in a workshop
*/

app.post("/enroll", async (req, res) => {
	console.log("----------");
	
	try {
		console.log(req.body);
		
		const title_to_enroll = req.body.title;
		const date_to_enroll = req.body.date;
		const location_to_enroll = req.body.location;
		const username_to_enroll = req.body.username;
		var keep_going = true;

		//if necessary parameter is missing, return an error
		if (title_to_enroll == null || date_to_enroll == null || location_to_enroll == null || username_to_enroll == null) {
			console.error("required information missing")
			res.json({ error : "required information missing"});			
		}

		else {
			
			//search for username and see if it exists
			console.log("Checking if user in database");

			const template1 = "SELECT * FROM users WHERE user_name = $1";
			const response1 = await pool.query(template1, [
				username_to_enroll
			]);

			if (response1.rowCount == 0) {
				console.log("user not in database");
				res.json({ status : "user not in database"});
				keep_going = false;
			}



			//search for workshop and see if it exists
			console.log("Checking if workshop in database");

			const template2 = "SELECT * FROM workshops WHERE workshop_name = $1 AND workshop_date = $2 AND workshop_location = $3";
			const response2 = await pool.query(template2, [
				title_to_enroll,
				date_to_enroll,
				location_to_enroll
			]);

			if (response2.rowCount == 0 && keep_going == true) {
				console.log("workshop does not exist");
				res.json({ status : "workshop does not exist"});
				keep_going = false;
			}
			
			
		

			//check to see if user is already enrolled in the workshop
			console.log("Checking if user already enrolled");

			const template3 = "SELECT * FROM workshops JOIN attends ON workshops.workshop_id = attends.workshop_id JOIN users ON users.user_name = attends.user_name WHERE workshop_name = $1 AND workshop_date = $2 AND workshop_location = $3 AND attends.user_name = $4";
			const response3 = await pool.query(template3, [
				title_to_enroll,
				date_to_enroll,
				location_to_enroll,
				username_to_enroll
			]);

			if (response3.rowCount != 0 && keep_going == true) {
				console.log("user already enrolled");
				res.json({ status : "user already enrolled"});
				keep_going = false;
			}
						

			//check to see if workshop is full
			console.log("Checking if workshop is full");

			const template4 = "SELECT * FROM workshops WHERE workshop_name = $1 AND workshop_date = $2 AND workshop_location = $3";
			const response4 = await pool.query(template4, [
				title_to_enroll,
				date_to_enroll,
				location_to_enroll
			]);

			const template5 = "SELECT * FROM workshops JOIN attends ON workshops.workshop_id = attends.workshop_id JOIN users ON users.user_name = attends.user_name WHERE workshop_name = $1 AND workshop_date = $2 AND workshop_location = $3";
			const response5 = await pool.query(template5, [
				title_to_enroll,
				date_to_enroll,
				location_to_enroll
			]);

			if (keep_going == true && response5.rowCount == response4.rows[0].workshop_max_seats) {
				console.log("no seats available");
				res.json({ status : "no seats available"});
				keep_going = false;
			}
			

			// else add the new user
			
			if (keep_going == true) {		
				console.log("Adding user to the workshop");
			
				const template7 = "INSERT INTO attends (workshop_id, user_name) VALUES ($1, $2)";
				const response7 = await pool.query(template7, [
					response4.rows[0].workshop_id,
					username_to_enroll
				]);
				console.log("user added");
				res.json({ status : "user added" });
			}
			
		}
	} 

	catch (err) {

		console.error(err);
		res.json({ error : "error adding workshop" });
	}

});





// this goes at the end to listen on the port //////////////////////////////////////

app.listen(app.get("port"), () => {
	console.log(`Find the server at: http://localhost:${app.get("port")}/`);
	 // eslint-disable-line no-console
});



