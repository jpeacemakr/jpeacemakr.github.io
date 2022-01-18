import Horizontalnavbar from '../components/Horizontalnavbar';
import MyLayout from '../components/MyLayout';
import Link from 'next/link';
import React from "react";
import {getInfo} from '../lib/utils.js';
import Footer from '../components/Footer';


class Search extends React.Component {
	


	constructor(props) {
		super(props);
		this.state={search: "Type your search here", campfound: "Type your search here"};
	}

	handleUpdate(evt){
		this.setState({search: evt.target.value})
	}


	searchFound(){
		console.log(this.state);
		
		if ((this.state.campfound != "Type your search here") && (this.state.search != "Type your search here")){
			return <div style={{textAlign: 'left', padding:'40px', background:'#FFFFFF', width:'636px' }}>The campground you are searching for can't be found. (Names are case sensitive.)</div>;
		}
	}
	


	async handleSearch(evt) {

		this.state.campfound = this.state.search;
		const campsearch = await getInfo(this.state.search);
		console.log(campsearch);
		this.setState({campsearch});
	}
	


	render() {
		return (

			<>
			<head>
			<title>Campground.org: Search</title>

			</head>
			
			<MyLayout>
			<Horizontalnavbar />
			<div style={{textAlign: "center", width:"100%", backgroundImage:"url('../static/images/search.jpg')", height:"650px", backgroundSize:"cover"}}><center>
			<br />&nbsp;
			<div style={{textAlign: "center", padding:"8px", width:"700px", background:"#EEEEFF" }}>
			<h3 style={{color: "#336699"}}>Search for a campground 
			&nbsp;&nbsp;
			<input type='text' value={this.state.search} onChange={this.handleUpdate.bind(this)} />
			<span className="button-style" onClick={this.handleSearch.bind(this)}>SEARCH</span>

			</h3>
			</div>				

			{this.state.campsearch ? 
				
				
				

				
				<div style={{textAlign: "left", padding:"40px", background:"#FFFFFF", width:'636px' }}>
				<h3>
				<img style= {{maxWidth:'400px', marginLeft:"20px", float: "right"}} src={this.state.campsearch.campground.image_url} />
				{this.state.campsearch.campground.name}
				</h3>
				
				<p>{this.state.campsearch.campground.description}</p>
				</div> 
				

				
				:

				<div>

				{this.searchFound()}

				</div> 


			}
			</center>
			</div>
			
			<Footer />



			<style jsx>{`
				
				.button-style {
					margin: auto auto;
					padding:3px 10px;
					border=0;
					cursor: pointer;
					background-color: #336699;  
					color: #ffffff; 
					width: 90px;
					font-family: "Helvetica";
					align:center;
					font-size:13px;					
				}
				



				

				
				



				`}</style>
				</MyLayout>
				</>
				);
			}		
		}

		export default Search;

