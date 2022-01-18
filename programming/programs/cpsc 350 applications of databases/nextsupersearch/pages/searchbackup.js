import React from "react";
import Horizontalnavbar from '../components/horizontalnavbar';
import Footer from "../components/footer";
import Link from 'next/link';
import MyLayout from '../components/mylayout';
import {getInfo} from '../lib/utils.js';




class Search extends React.Component {
	


	constructor(props) {
		super(props);
		this.state = {search: "Type your search here"};
	}

	async handleUpdate(evt){
		this.setState({search: evt.target.value});
		this.setState({foodsearch: await getInfo(evt.target.value)})
		//beware that setState is asynchronous
	}


	searchFound(){
		console.log(this.state);
			
		if (this.state.search != "Type your search here"){
			return <div style={{textAlign: 'left', padding:'40px', background:'#FFFFFF', width:'100%-80px' }}>The food you are searching for can't be found. Please try again.</div>;
		} else {

			return <div style={{textAlign: 'left', padding:'40px', width:'1000px', background:'#FFFFFF'}}>
			<img src='../static/images/cans.jpg' style={{float: 'right', width:'50%', padding: '12px'}}></img>
			<h3>Welcome to Nutrition Finder</h3>
			This website lets you search for detailed nutritional information for hundreds of foods. Just type into the search bar above to begin.
			<h3>About this website</h3>
			This website was created by James Peacemaker, a student at the University of Mary Washington majoring in computer science. This site was created using Next.js and Postgres as a class project for CPSC 350, Application of Databases, taught by Ron Zacharski. 

			</div>;
		}

	}
		

	displayFoods(foodArray)
		{
			if (foodArray.food == undefined) {
				console.log("foodArray.food is null");
				return;

			} else {
				let foodList = "<tr><th><br />Description</th><th>Calories (kcal)</th><th>Protein (g)</th><th>Carbohydrates (g)</th><th>Fiber (g)</th><th>Sugar (g)</th><th>Total fat (g)</th><th>Saturated<br />fat (g)</th><th>Mono-<br />unsaturated fat (g)</th><th>Poly-<br />unsaturated fat (g)</th><th>Cholesterol (mg)</th></tr>";

				for (const currentFood of foodArray.food){
		      		let totalFat = currentFood.fa_sat_g + currentFood.fa_mono_g + currentFood.fa_poly_g;
		      		totalFat = totalFat.toFixed(2);
		      		foodList = foodList + "<tr><td>" + currentFood.description + " (" + currentFood.gmwt_desc1 + ")</td><td>" + currentFood.kcal + "</td><td>" + currentFood.protein_g + "</td><td>" + currentFood.carbohydrate_g + "</td><td>" + currentFood.fiber_td_g + "</td><td>" + currentFood.sugar_g + "</td><td>" + totalFat + "</td><td>" + currentFood.fa_sat_g + "</td><td>" + currentFood.fa_mono_g + "</td><td>" + currentFood.fa_poly_g + "</td><td>" + currentFood.cholestrl_mg + "</td></tr>";
				}

				//return foodList;
				//converts html string to jsx
				return(<table width="100%" className="container" style={{textAlign:"bottom", padding:"10px", borderSpacing:"8px",  background:"#EEEEEE"}} dangerouslySetInnerHTML={{__html: foodList}}></table>);
			}
		}



	

	render() {
			return (

				<MyLayout>
				<head>
					<title>Food Nutrition Search</title>
				</head>
			
				<Horizontalnavbar />
				<div style={{textAlign: "left", padding:"8px", width:"100%-16px", background:"#225522" }}>
				<h3 style={{color: "#EEFFDD", margin:"20px"}}>Search for a food 
				&nbsp;&nbsp;
				<input type='text' value={this.state.search} onChange={this.handleUpdate.bind(this)} size="75"/>
				
				</h3>
				</div>				

				{this.state.foodsearch ? 
				 	 	

					
				 	<div style={{textAlign: "left", padding:"40px", background:"#FFFFFF", width:'100%-80px' }}>
				 	
					{this.displayFoods(this.state.foodsearch)}

					</div> 
					
					:

					<div>

					 	{this.searchFound()}

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

