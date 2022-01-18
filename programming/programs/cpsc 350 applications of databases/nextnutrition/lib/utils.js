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
function getFood(foodname){
	console.log(`http://localhost/api/search?food=${foodname}`);
	return getJson(`http://localhost/api/search?food=${foodname}`);
}

{/* .all waits to return all the asynchronous functions*/}
function getFoodData(name) {
	return BPromise.all([getFood(name)]).then(function([food]){
		console.log("getFoodData:");
		console.log(food);
		return { food };
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
    return getFoodData(name).catch(handleError);
  	}

};







