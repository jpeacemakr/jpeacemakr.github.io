import Horizontalnavbar from '../components/horizontalnavbar.js';
import MyLayout from '../components/mylayout.js';
import Link from 'next/link';
import React from "react";
import {getInfo} from '../lib/utils.js';
import Footer from '../components/footer.js';


class Search extends React.Component {
	


	constructor(props) {
		super(props);
		this.state={search: "", emailfound: ""};
	}

	handleUpdate(evt){
		this.setState({search: evt.target.value})
	}


	searchFound(){
		console.log(this.state);
			
		if ((this.state.emailfound != "") && (this.state.search != "")){
			return <div style={{textAlign: 'left', padding:'40px', background:'#FFFFFF', width:'636px' }}>The phrase you are searching for can't be found.</div>;
		} else {
			return <div style={{textAlign: 'left', padding:'40px', background:'#FFFFFF', width:'80%' }}>Secretary of State Hillary Clinton drew controversy when it was discovered she used a private email server for official business. The server contained thousands of emails, including some with classified or other sensitive information. While she said the email server was legal, it was used as political fodder in the 2016 presidential race, in which she lost to Donald Trump. This website allows you to search the emails that were publicly made available.
<h3>About this website</h3>
This website was created by James Peacemaker, a student at the University of Mary Washington majoring in computer science. This site was created using Next.js and Elasticsearch as a class project for CPSC 350, Application of Databases, taught by Ron Zacharski. 

			</div>;

		}
	}
		


	async handleSearch(evt) {

		this.state.emailfound = this.state.search;
		const emailSearchResult = await getInfo(this.state.search);

		console.log(emailSearchResult);
		this.setState({emailsearch : emailSearchResult});
	}
		



	


	displayEmails2(){

		const PostLink = props => (
 	 
	    <Link href="/p/[id]" as={`/p/${props.id}`}>
	      <a target="_blank">{props.id}</a>
   	 </Link>
  	
	);


		console.log("this.state.emailsearch");
		
		console.log(this.state.emailsearch);
		
		if (this.state.emailfound != "" && this.state.emailfound != " ") {


			if (this.state.emailsearch.hits.total.value == 0) {
				return <div style={{textAlign: 'center', padding:'20px', background:'#FFFFFF', width:'636px' }}><center>The phrase you are searching for can't be found.</center></div>;	

			} else {


				var data = this.state.emailsearch.hits.hits;
				var listItems = data.map((currentEmailSearch) => <tr><td> {currentEmailSearch._source.MetadataDateSent.replace("T"," ").replace("+00:00","")} </td><td> {currentEmailSearch._source.MetadataFrom} </td><td> {currentEmailSearch._source.MetadataTo} </td><td>{currentEmailSearch._source.MetadataSubject}</td><td> <PostLink id={`${currentEmailSearch._source.DocNumber}`} /> </td></tr>);

			console.log(listItems);

					return <><h3>Top 20 search results:</h3><table width="100%" style={{textAlign:"bottom", padding:"10px", borderSpacing:"12px",  background:"#EEEEEE"}}><tr><th>Date</th><th>Sender</th><th>Recipient</th><th>Subject</th><th>Document Number</th></tr> { listItems }</table></>;

				}

		} else {

				return <div style={{textAlign: 'center', padding:'20px', background:'#FFFFFF', width:'636px' }}>Enter a search phrase to begin.</div>;

		}
	}



	render() {
			return (

				<>
				<head>
					<title>Search Hillary Clinton emails: Search</title>

				</head>
			
				<MyLayout>
				<Horizontalnavbar />
				<div style={{textAlign: "center", width:"100%"}}><center>
				<br />&nbsp;
				<div style={{textAlign: "center", padding:"8px", width:"700px", background:"#EEEEEE" }}>
				<h3 style={{color: "#339999"}}>Search emails 
				&nbsp;&nbsp;
				<input type='text' value={this.state.search} onChange={this.handleUpdate.bind(this)} />
				<span className="button-style" onClick={this.handleSearch.bind(this)}>SEARCH</span>

</h3>
</div>				

				{this.state.emailsearch ? 
				 
					
				 	

					
				 	<div style={{textAlign: "left", padding:"40px", background:"#FFFFFF", width:'80%' }}>
					
					<p>{this.displayEmails2()}</p>
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
							background-color: #339999;  
							color: #ffffff; 
							width: 90px;
							font-family: "Helvetica";
							align:center;
							font-size:13px;					
						}
						


a:link, a:visited {
  color: #669999;
  text-decoration: none;
  display: inline-block;
}



a:hover {
  color: #336666;
}


						

						
				



						`}</style>
						</MyLayout>
						</>
						);
					}		
				}

				export default Search;

