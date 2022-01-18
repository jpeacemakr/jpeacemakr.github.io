import React from "react";
import Horizontalnavbar from '../components/horizontalnavbar';
import Footer from "../components/footer";
import Link from 'next/link';
import MyLayout from '../components/mylayout';
import {getInfo} from '../lib/utils.js';
import jsCookie from "js-cookie";




class Search extends React.Component {
	


	constructor(props) {
		super(props);
		this.state = {search: "Type your search here", moviesearch:"", storesearch:""};
		this.state.moviesearch = {movies:undefined};
		this.state.storesearch = {stores:undefined};
	}


	async handleUpdate(evt){
		let searchMovieWords = evt.target.value;
		let searchStoreWords = evt.target.value;
		let searchWord = evt.target.value;
		let searchZip = "all"

		jsCookie.get("zip") ? 
			searchZip = jsCookie.get("zip") : null;
		


		this.setState({search: searchWord});
		this.setState({moviesearch: await getInfo(searchMovieWords,"movies", searchZip)});
		this.setState({storesearch: await getInfo(searchStoreWords,"stores", searchZip)});		
		//beware that setState is asynchronous. it does not like having getInfo with same variable, so i made a copy
	}


	searchFound(){
		console.log(this.state);
			
		if (this.state.search != "Type your search here" && this.state.search != ""){
			return <div style={{textAlign: 'center', padding:'40px', background:'#FFFFFF', width:'100%-80px', height:"500px" }}>The item you are searching for can't be found. Please try again.</div>;
		} else {

			return <div style={{textAlign: 'left', padding:'40px', width:'70%', background:'#FFFFFF'}}>
			<h3>Welcome to Super Search</h3> 
			This website lets you search for places to eat or movies. Just type into the search bar above to begin. Type "movies" to search for all movies or "stores" to search for all stores and restaurants. You can register for an account or log in to search just in your zip code.
			<h3>About this website</h3>
			This website was created by James Peacemaker, a student at the University of Mary Washington majoring in computer science. It is not fully functional and is more of a proof of concept to demonstrate a login feature with encrypted passwords. This site was created using Next.js and Postgres as a class project for CPSC 350, Application of Databases, taught by Ron Zacharski. 

			</div>;
		}

	}
		

	displayMovieSearch()
		{
					
			if (this.state.moviesearch.movies == undefined ) {
				console.log("this.state.moviesearch.movies is null");
				return;

			} else {
				let superList = "<tr><th>Movie</th><th>Theater name</th><th>Address</th><th>City</th><th>Zip code</th></tr>";

				for (const currentSupersearch of this.state.moviesearch.movies){
		      		superList = superList + "<tr><td>" + currentSupersearch.movie_name + "</td><td>" + currentSupersearch.theater_name + "</td><td>" + currentSupersearch.theater_address + "</td><td>" + currentSupersearch.theater_city + "</td><td>" + currentSupersearch.theater_zip + "</td></tr>";
				}

				//return superList;
				//converts html string to jsx
				return(<><h2 style={{color:"#336699"}}>Movies</h2><table width="100%" className="container" style={{textAlign:"bottom", padding:"10px", borderSpacing:"8px",  background:"#EEEEEE"}} dangerouslySetInnerHTML={{__html: superList}}></table></>);
			}
		}




		displayStoreSearch() 
		{
					
			if (this.state.storesearch.stores == undefined) {
				console.log("this.state.storesearch.stores is null");
				return;

			} else {
				let superList2 = "<tr><th>Store name</th><th>Store type</th><th>Address</th><th>City</th><th>Zip code</th></tr>";

				for (const currentSupersearch of this.state.storesearch.stores){
		      		superList2 = superList2 + "<tr><td>" + currentSupersearch.store_name + "</td><td>" +currentSupersearch.storetype_name + "</td><td>" + currentSupersearch.store_address + "</td><td>" + currentSupersearch.store_city + "</td><td>" + currentSupersearch.store_zip + "</td></tr>";
				}

				//return superList;
				//converts html string to jsx
				return(<><h2 style={{color:"#336699"}}>Stores</h2><table width="100%" className="container" style={{textAlign:"bottom", padding:"10px", borderSpacing:"8px",  background:"#EEEEEE"}} dangerouslySetInnerHTML={{__html: superList2}}></table></>);
			}
		}



	

	render() {
			return (

				<MyLayout>
				<head>
					<title>Super Search</title>
				</head>
			
				<Horizontalnavbar />
				<div style={{textAlign: "center", padding:"8px", width:"100%-16px", background:"#002244" }}>
				<h3 style={{color: "#EEFFDD", margin:"20px"}}>Search 
				&nbsp;&nbsp;
				<input type='text' value={this.state.search} onChange={this.handleUpdate.bind(this)} size="75"/>
				
				</h3>
				</div>				

				{this.state.moviesearch.movies || this.state.storesearch.stores ? 
				 	 	

					
				 	<div style={{textAlign: "left", padding:"40px", background:"#FFFFFF", width:'100%-80px' }}>
				 	
					{this.displayMovieSearch()}
					
					{this.displayStoreSearch()}


					</div> 
					
					:

					<div>
						<center>
					 	{this.searchFound()}
					 	<br />
					 	</center>

				 	</div> 

				}
						
				<Footer />

					<style jsx>{`
						
						

						
	
					

						`}</style>
						</MyLayout>
						
						);
					}		
				}

				export default Search;

