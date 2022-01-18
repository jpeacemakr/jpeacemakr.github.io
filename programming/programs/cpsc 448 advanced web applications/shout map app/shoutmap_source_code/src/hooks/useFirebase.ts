//this is a hook that uses firebase to log in, log out, creater users and retrieve user info

import * as firebase from 'firebase';
import { useState } from "react";

export function useFirebase() {


  const [email, setEmail] = useState<string>();
  const [password, setPassword] = useState<string>();


  //logs the user into firebase
  const userLogin = async (email:any, password:any) => {
    firebase.auth().signInWithEmailAndPassword(email, password)
    .then(resp=>{ console.log(resp); },err=>{ console.log(err); })
  };

  //logs the user out of firebase
  const userLogout = async () => {
    firebase.auth().signOut().then (resp=>{ console.log(resp); },err=>{ console.log(err); });
    setEmail("");
  };

  //creates a user in firebase
  const userCreate = async (email:any, password:any) => {
	firebase.auth().createUserWithEmailAndPassword(email, password)
	.then (resp=>{ console.log(resp, firebase.auth().currentUser); },err=>{ console.log(err); })

  };

  //logs the user to the console. used for testing purposes only
  const logUser = () => { console.log(firebase.auth().currentUser); return firebase.auth().currentUser; };
  
  //returns the user Object
  const getUser = firebase.auth().currentUser;

  //returns the email address from the user Object
  const getEmail = () => { 
    if (getUser) {
        console.log("getUser.email", getUser.email)
      if(getUser.email) {      
        return getUser.email;
      } else {
        console.log("getUser.email is null")  
        return "Not logged in"; 
      }
    } else {
      console.log("getUser is null")  
      return "Not logged in"; 
    };
  }

  
  const getPassword = () => { return password; };



  return {
    email,
    password,
    userLogin,
    userLogout,
    logUser, 
    userCreate,
    getUser,
    setEmail, 
    getEmail, 
    setPassword, 
    getPassword
  };
}





