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

{/*sends the url to getJson fucntion*/}
function getSupersearch(name,category,zip){
//	console.log(`http://localhost/api/search${category}?searchword=${name}&searchzip=${zip}`);
//	return getJson(`http://localhost/api/search${category}?searchword=${name}&searchzip=${zip}`);
	console.log(`/api/search${category}?searchword=${name}&searchzip=${zip}`);
	return getJson(`/api/search${category}?searchword=${name}&searchzip=${zip}`);


}

{/* .all waits to return all the asynchronous functions*/}
function getSupersearchData(name,category,zip) {
	return BPromise.all([getSupersearch(name,category,zip)]).then(function([supersearch]){
		console.log("getSupersearchData:");
		console.log(supersearch);
		return supersearch;
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

getInfo: function(name,category,zip) {
    return getSupersearchData(name,category,zip).catch(handleError);
  	}

};







