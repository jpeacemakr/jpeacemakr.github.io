import Router from "next/router";
import jsCookie from "js-cookie";
//import getLogin from "../utils/getlogin.js"
require("isomorphic-fetch");
import BPromise from "bluebird";
import MyLayout from '../components/mylayout';
import Horizontalnavbar from '../components/horizontalnavbar';
import Footer from "../components/footer";








class Login extends React.Component {





async handleSearch(evt) {
  console.log("starting handleSearch");
  const that2 = this;
  
  const loggedInUser = await this.postlogin({
    username: this.state.username,
    password: this.state.password
  });
  this.setState({ loggedInUser });
  if (loggedInUser.status == "Passwords match") {

    jsCookie.set("name", loggedInUser.name);
    jsCookie.set("password", loggedInUser.password);
    jsCookie.set("username", loggedInUser.username);
    jsCookie.set("zip", loggedInUser.zip);
    
    Router.replace("/");
  } else {
    Router.replace("/wrongpassword");



  }
}



//post request
//user_info is json object with username and password
postlogin(user_info) {
  const header = {
    Accept: "application/json",
    "Content-Type": "application/x-www-form-urlencoded"
  };
  console.log(user_info);  
  const searchParams = new URLSearchParams(user_info);
  
  console.log(searchParams);  
  return fetch("http://localhost:8080/api/check-login", {
    method: "POST",
    headers: header,
    body: searchParams

  }).then(function(resp) {
    console.log("returning json");
    return resp.json();
  });
}




constructor(props) {
    super(props);
    this.state = {username: "Enter your user name", password: "Enter your password"};
  }

async handleUserUpdate(evt){
    this.setState({username: evt.target.value});
    //beware that setState is asynchronous
  } 


async handlePasswordUpdate(evt){
    this.setState({password: evt.target.value});
    //beware that setState is asynchronous
  }



render() {
  const that = this;
  jsCookie.remove("screenname");
  return (
    <MyLayout>
      <Horizontalnavbar />
<div style={{textAlign: "center", padding:"8px", width:"100%-16px", background:"#002244" }}>
        <h3 style={{color: "#EEFFDD", margin:"20px"}}>Log in to search your zip code 
            
        </h3>
        </div>  


      <center>
      <div style={{textAlign: "center", padding:"8px", width:"600px", height:"100px", background:"#FFFFFF" }}>
      <br />
      <div style={{textAlign: "center", padding:"8px", width:"100%-16", background:"#EEEEEE" }}>
     <br />
     <h3>The username or password you entered <br />was incorrect. Please try again.</h3>
     Username&nbsp;&nbsp;
      <input
        type="text"
        className="text-style"
        value={this.state.username}
        onChange={this.handleUserUpdate.bind(this)}
      />
      <br /> <br />
      
      Password&nbsp;&nbsp;
      <input
        type="password"
        className="text-style"
        value={this.state.password}
        onChange={this.handlePasswordUpdate.bind(this)}
      />
      <br />
      <br />
      
      <div className="button-style" onClick={this.handleSearch.bind(that)} className="button-style">
        SUBMIT
      </div>
      
      <br /> 
      </div>


      <Footer />
      <br /> 
      <br /> 
      <br /> 
      <br /> 
      <br /> 
      <br /> 
      <br /> 
      <br /> 
      <br /> 
      <br /> 
&nbsp;
      </div>
      </center>


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
              textAlign: "center";         
            }
            



            




            `}</style>

      </MyLayout>
      );
}

}

export default Login;
