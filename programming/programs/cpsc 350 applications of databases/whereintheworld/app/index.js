var React = require('react');
var ReactDOM = require('react-dom');
require('./style.css');

var Axios = require('axios');







class App extends React.Component {




constructor(props) {
    super(props);
    this.state = { search: "Type search here"};

    this.handleChange = this.handleChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
  }

  handleChange(event) {
    this.setState({search: event.target.value});
  }

  handleSubmit(event) {
        
        let tempState = this.state.search;
        this.setState({submit: tempState})

        console.log("submitting: ");
        console.log(this.state.submit);	

        let tempJson = { search: tempState };

		Axios.post('/api/worldsearch', 
  			tempJson)
		.then((response) => {
  			console.log("Returning search response: ");
  			console.log(response.data);
  			console.log(response.data.status);
  			console.log(response.data.cities);
  			this.setState({answer:response.data});
  			console.log(this.state.answer);
		}, (error) => {
  			console.log(error);
		});
  }

	displaySearch(searchArray)
		{
			if (searchArray.cities == undefined) {
				console.log(this.state);
				return(<p>The city can't be found.</p>);

			} else {
				
				let cityList = "<tr><th>City name</th><th>State/Province</th><th>Country</th></tr>";

				for (const currentCity of searchArray.cities){
		      		cityList = cityList + "<tr><td>" + currentCity.cityname + "</td><td>" + currentCity.district + "</td><td>" + currentCity.countryname + "</td></tr>";
				}

				//return foodList;
				//converts html string to jsx
				return(<table width="100%" className="container" style={{textAlign:"bottom", padding:"10px", borderSpacing:"8px",  background:"#EEEEEE"}} dangerouslySetInnerHTML={{__html: cityList}}></table>);
			}
		}







    render() {
        return (
        	<div>
        	<section>
				<header className="major">
					<h2>Search for cities and countries<br />
						by name, code, or continent</h2>
				</header>
                <div className="row">
                  
                </div>
				<form>
					
					    <div className="12u$">
					        <input type = "text"  name="worldSearch" id="message" value={this.state.search} onChange={this.handleChange.bind(this)}/> &nbsp;<input defaultValue="Find" className="buttonstyle" onClick={this.handleSubmit}/>
					    </div>
					
									

					&nbsp;<br />
									
				</form>



				{this.state.answer ? 
				 	 	

					
				 	<div style={{textAlign: "left", padding:"40px", background:"#FFFFFF", width:'100%-80px' }}>
				 	
						{this.displaySearch(this.state.answer)}

					</div> 
					
					:

					<div>



				 	</div> 

				}

            </section>


					<style>{`
						
						.buttonstyle {
							margin: auto auto;
							padding:3px 10px;
							border: 0;
							cursor: pointer;
							background-color: #336699;  
							color: #ffffff; 
							width: 90px;
							align:center;					
						}
						
						`}</style>




            </div>
        )
    }
}

ReactDOM.render(<App />, document.getElementById('app'));
