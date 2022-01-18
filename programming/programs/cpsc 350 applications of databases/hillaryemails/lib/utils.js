


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




function getHillaryEmail(searchword){
	console.log(`http://localhost/api/emailsearch?word=${searchword}`);
	return getJson(`http://localhost/api/emailsearch?word=${searchword}`);
}


{/* .all waits to return all the asynchronous functions*/}
function getHillaryEmailData(word) {
	return BPromise.all([getHillaryEmail(word)]).then(function([hillaryEmail]){
		console.log("getHillaryEmailData:");
		console.log(hillaryEmail);
		return hillaryEmail;
		} 
	)
}





function getHillaryEmailId(searchword){
	console.log(`http://localhost/api/emailsearchid?word=${searchword}`);
	return getJson(`http://localhost/api/emailsearchid?word=${searchword}`);
}


{/* .all waits to return all the asynchronous functions*/}
function getHillaryEmailDataId(word) {
	return BPromise.all([getHillaryEmailId(word)]).then(function([hillaryEmail]){
		console.log("getHillaryEmailDataId:");
		console.log(hillaryEmail);
		return hillaryEmail;
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
    return getHillaryEmailData(name).catch(handleError);
  	},


getId: function(name) {
    return getHillaryEmailDataId(name).catch(handleError);
  	}




};







