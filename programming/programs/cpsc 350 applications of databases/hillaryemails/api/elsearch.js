const express = require("express");
const app = express();
app.set("port", 8080);

const bodyParser = require("body-parser");
app.use(bodyParser.json({ type: "application/json" }));
app.use(bodyParser.urlencoded({ extended: true }));


const cors = require("cors");
app.use(cors());

var elasticsearch = require('elasticsearch');
var client = new elasticsearch.Client({
//   hosts: [ 'http://elastic:elb00mstick@35.188.249.235/es']
   hosts: [ 'http://apiuser:apib00mstick@/es']

});

// linking to postgres //////////////////////////////////////////////

/* 
const Pool = require("pg").Pool;
const config = {
	host: "localhost",
	user: "parky",
	password: "poparky",
	database: "food_nutrition"
};

const pool = new Pool(config);
*/



// get requests /////////////////////////////////////////////////////////

// http://localhost:8080/hello
//just used to test it is running
app.get("/api/hello", (req, res) => {
	res.json("Hello World!");
});



app.get("/api/testping", (req, res) => {

client.cluster.health({},function(err,resp,status) {  
  console.log("-- Client Health --",resp);
  });


client.ping({
     requestTimeout: 30000,
 	 }, function(error) {
     if (error) {
         console.error('elasticsearch cluster is down!');
     } else {
         console.log('Everything is ok');
     }
 });

res.json("Testing elasticsearch.");
});







app.get("/api/emailsearch", (req, res) => {
		
client.search({
    index: 'hillary',
    size: 20,
    type: 'emails',
    q: 'RawText:' + req.query.word
}).then(function(resp) {
    console.log(resp.hits.hits);
    res.json(resp);

}, function(err) {
    console.trace(err.message);
	res.json(err.message);    

});


});






app.get("/api/emailsearchid", (req, res) => {
        
client.search({
    index: 'hillary',
    type: 'emails',
    q: 'DocNumber:' + req.query.word
}).then(function(resp) {
    console.log(resp.hits.hits);
    res.json(resp);

}, function(err) {
    console.trace(err.message);
    res.json(err.message);    

});


});





// this goes at the end to listen on the port //////////////////////////////////////

app.listen(app.get("port"), () => {
	console.log(`Find the server at: http://localhost:${app.get("port")}/`);
	 // eslint-disable-line no-console
});



