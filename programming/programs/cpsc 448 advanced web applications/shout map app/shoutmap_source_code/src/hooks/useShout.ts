//this is a hook that is used to list shouts and post shouts using GPS coordinates

import * as firebase from 'firebase';
import { useState } from 'react';
import { useFirebase } from '../hooks/useFirebase';
import { Plugins } from '@capacitor/core';

require("isomorphic-fetch");


export function useShout() {

  var [shoutlist, setShoutlist] = useState(); //the list of shouts
  var [shoutlisttext, setShoutlisttext] = useState(); //the list of shouts in text form. for testing only
  var [shouttext, setShouttext] = useState(); //the text of the shoutbeing posted

  const { getEmail } = useFirebase(); //used to retrieve the user email address

  const { Geolocation } = Plugins;


  //retrieves the list of shouts from mongodb. then saves the list of shouts to the shoutlist variable.
  //also saves a text version to shoutlisttest. for testing purposes.
  //makes a get request to the api
  const shoutRead = async (longValue:any, latValue:any, distanceValue:any) => {
  // var url = `/api/allshouts?longitude=${longValue}+lat=${latValue}+dist=${distanceValue}`;
    var url = `http://localhost:3000/api/allshouts?longitude=${longValue}+lat=${latValue}+dist=${distanceValue}`;
  
    var shoutText = " ";

    var shoutToReturn = await fetch(url)
    .then(resp=>{ console.log("FETCHING", "URL", url, "resp", resp); return resp.json(); }, err=>{ console.log(err); })

    .then((responseJSON) => {
        console.log("responseJSON", responseJSON);

        shoutText = JSON.stringify(responseJSON);
        console.log("shoutText", shoutText);
    
        shoutlisttext = setShoutlisttext(shoutText);
        
        shoutlist = setShoutlist(responseJSON);
  
      }).then(() => {

        console.log("shoutlisttext", shoutlisttext);
        console.log("shoutlist", shoutlist);

      });
  
    return shoutToReturn;

  };


  const getShouttextlist = () => {
    return shoutlisttext;
  };


  const getShoutlist = () => {
    return shoutlist;
  };






//This is for testing purposes only. it posts without GPS coordinates
//user_info is json object with username and password
//makes a post request to the api
const createShout = (shout_info:any) => {
  const header = {
    Accept: "application/json",
    "Content-Type": "application/x-www-form-urlencoded"
  };
  console.log(shout_info);  
  const searchParams = new URLSearchParams(shout_info);
  
  console.log("searchParams", searchParams);  

  return fetch("http://localhost:3000/api/newshout", {
//  return fetch("/api/newshout", {
    method: "POST",
    headers: header,
    body: searchParams

  }).then(function(resp) {
    var shoutReturn = resp.json();
    console.log("returning json", shoutReturn);
    return shoutReturn;
  });
}




//retrieves the GPS coordinates and user's email then posts the message to mongodb.
//makes a post request to the api
const createShoutGPS = async (shoutString:string) => {


  //create the json for the post rquest, starting with the header, then add body
  const header = {
    Accept: "application/json",
    "Content-Type": "application/x-www-form-urlencoded"
  };

  var tempGPS = await Geolocation.getCurrentPosition(); //get GPS location

  var today = new Date();
  var todayDate = (today.getMonth()+1)+ '-' + today.getDate() + '-' + today.getFullYear();
  var todayTime = today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds();

  const shoutInfo = { 
    username: getEmail(),
    shouttext: shoutString,
    longitude: tempGPS.coords.longitude.toString(),
    latitude: tempGPS.coords.latitude.toString(),
    date: todayDate, 
    time: todayTime
  }
  console.log("shoutInfo", shoutInfo);  


  //send the post request
  const searchParams = new URLSearchParams(shoutInfo);
  console.log("searchParams", searchParams);  

  //return fetch("/api/newshout", {
  return fetch("http://localhost:3000/api/newshout", {  
    method: "POST",
    headers: header,
    body: searchParams

  }).then(function(resp) {
    var shoutReturn = resp.json();
    console.log("returning json", shoutReturn);
    return shoutReturn;
  });
}






//retrieves the GPS coordinates and user's email then posts the message to mongodb.
//makes a post request to the api
const createShoutGPSWithToken = async (shoutString:string) => {


  //create the json for the post rquest, starting with the header, then add body
  const header = {
    Accept: "application/json",
    "Content-Type": "application/x-www-form-urlencoded"
  };

  var tempGPS = await Geolocation.getCurrentPosition(); //get GPS location

  //swap out token with logged in user's username
  //var userToken = await firebase.auth().currentUser.getIdToken(true);//get current logged in user's token
  var userToken = "";
  var user = await firebase.auth().currentUser;//get current logged in user's token
  console.log("user", user);

  if (user) {
    if (user.getIdToken(true)){ 
      userToken = await user.getIdToken(true);
      console.log("userToken", userToken);
    }
  }

  var today = new Date();
  var todayDate = (today.getMonth()+1)+ '-' + today.getDate() + '-' + today.getFullYear();
  var todayTime = today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds();

  const shoutInfo = { 
    username: userToken,
    shouttext: shoutString,
    longitude: tempGPS.coords.longitude.toString(),
    latitude: tempGPS.coords.latitude.toString(),
    date: todayDate, 
    time: todayTime
  }
  console.log("shoutInfo", shoutInfo);  


  //send the post request
  const searchParams = new URLSearchParams(shoutInfo);
  console.log("searchParams", searchParams);  

  //return fetch("/api/newshout", {
  return fetch("http://localhost:3000/api/newshoutwithtoken", {  
    method: "POST",
    headers: header,
    body: searchParams

  }).then(function(resp) {
    var shoutReturn = resp.json();
    console.log("returning json", shoutReturn);
    return shoutReturn;
  });
}







  const getShouttext = () => { return shouttext; };



  return {
    shouttext,

    shoutRead,
    getShoutlist, 
    getShouttextlist,

    createShout,
    createShoutGPS,
    createShoutGPSWithToken,

    getShouttext, 
    setShouttext
  };
}





