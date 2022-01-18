require("isomorphic-fetch");
import BPromise from "bluebird";




function handleError(error) {
  //console.log(error);
  return null;
}



{/*returns a Json object from a url*/}
function getJson(url){
	return fetch(url).then(function(resp){
		console.log(url,resp);
		return resp.json();
		}
	)
}

{/*returns the json oject of a campground*/}
function getCampground(campgroundname){
	console.log(`http://35.190.190.219/info?q=${campgroundname}`);
	return getJson(`http://35.190.190.219/info?q=${campgroundname}`);
}

{/* .all waits to return all the asynchronous functions*/}
function getCampgroundData(name) {
	return BPromise.all([getCampground(name)]).then(function([campground]){
		return { campground };
		} 
	)
}













module.exports = {
/*
  getInfo: function(user) {
    return getProfile(user).catch(handleError);
  }
*/

/*
  getInfo: function(user) {
    return getUserData(user).catch(handleError);
  }
*/

getInfo: function(name) {
    return getCampgroundData(name).catch(handleError);
  	}

};







