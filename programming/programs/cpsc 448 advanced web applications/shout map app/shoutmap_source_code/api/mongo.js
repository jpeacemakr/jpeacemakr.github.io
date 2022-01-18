//import helmet from "helmet";

const Express = require("express");
const Mongoose = require("mongoose");
const BodyParser = require("body-parser");
var cors = require('cors')

var admin = require("firebase-admin");
var serviceAccount = require("../src/environment/cpsc-225-241503-firebase-adminsdk-8dgfl-6028865996.json"); //stores firebase api password
var mongoAccount = require("../src/environment/mongopass.json"); //stores mongo db access password so it is not checked in to git


admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: "https://cpsc-225-241503.firebaseio.com"
});

var app = Express();
app.use(cors());

console.log("mongoAccount.url", mongoAccount.url);
Mongoose.connect(mongoAccount.url);


//set the model for a shout
const ShoutModel = Mongoose.model("shout", {
    username: String,
    shouttext: String,
    longitude: Number, 
    latitude: Number,
    time: String,
    date: String
});

app.use(BodyParser.json());
app.use(BodyParser.urlencoded({ extended: true }));
// allow all origins // not working




//returns hello
app.get("/api/hello", async (request, response) => {
    response.send("Hello world!");
});



//adds a new shout but does not validate anything.
/* 
app.post("/api/newshout", async (request, response) => {
    try {
        var shout = new ShoutModel(request.body);
        var result = await shout.save();
        response.send(result);
    } catch (error) {
        response.status(500).send(error);
    }
});
*/



//adds a new shout
app.post("/api/newshoutwithtoken", async (request, response) => {
    try {
        var shout = new ShoutModel(request.body);
                
        var decodedToken = await admin.auth().verifyIdToken(shout.username);
        
        //console.log("decodedToken", decodedToken);

        var decodedEmail = decodedToken.email;
        
        //console.log("decodedEmail", decodedEmail)

        shout.username = decodedEmail;

        var result = await shout.save();
        
        response.send(result);

    } catch (error) {
        response.status(500).send(error);
    }
});






//returns all shouts
app.get("/api/allshouts", async (request, response) => {
    try {
        var result = await ShoutModel.find().exec();
        response.send(result);
    } catch (error) {
        response.status(500).send(error);
    }
});




//returns shouts within certain distance
app.get("/api/getshouts", async (request, response) => {

    const longitude = req.query.longitude;
    const latitude = req.query.latitude;
    const distance = req.query.distance;
    
    //////////////////////////////////////////////////
    //need to modify to refine mongo search paramaters if I want to show shouts closest to the user

    try {
        var result = await ShoutModel.find().exec();
        response.send(result);
    } catch (error) {
        response.status(500).send(error);
    }
});




//finds a specific person
/*
app.get("/shoutuser/:id", async (request, response) => {
    try {
        var shoutuser = await PersonModel.findById(request.params.id).exec();
        response.send(shoutuser);
    } catch (error) {
        response.status(500).send(error);
    }
});
*/




app.listen(3000, () => {
    console.log("Listening at localhost:3000");
});